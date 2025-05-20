#include <mcs51reg.h>
#include <stdio.h>
#include "IR.h"
#include "timer.h"
#include "int0.h"
#include "serial_log.h"

unsigned int time_arr[36] = {0};
unsigned char time_arr_index = 0;
IRData IR_data = {
    .state = IDLE,
    .data = {0},
    .address = 0,
    .command = 0,
    .write_index = 0,
    .data_received = 0,
    .repeat = 0,
    .start_time = 0
};


void IR_init()
{
    int0_init();
    timer0_inner_counter_init();
}

unsigned char IR_data_received()
{
    unsigned char data_received = 0;
    if (IR_data.data_received)
    {
        data_received = IR_data.data_received;
        // 这里不应该屏蔽外部红外中断, 
        // 如果屏蔽中断, 那么当解开屏蔽之后, 存在可能性:
        // 新的数据覆盖旧的数据, 主程序先消费一次新的数据,
        // 这时IR_data.data_received被中断置为1, 主程序会
        // 再消费一次新数据.
        // 如果不屏蔽中断, IR_data.data_received
        // 被中断置1, 再被该处(主程序中)置0后, 主程序消费
        // 一次新数据(旧数据已被中断覆盖), 因为
        // IR_data.data_received已被置0, 新数据不会被再次
        // 消费
        IR_data.data_received = 0;
        // 若在此处以后被中断, 则还是存在新数据被消费两次
        // 的情况, 如果保证数据检索时间小于下一个数据接收
        // 完成的时间,也可以避免这种情况的发生
    }

    return data_received;
}


unsigned char IR_get_repeat()
{
    if (IR_data.repeat)
    {
        IR_data.repeat = 0;
        return 1;
    }

    return 0;
}

unsigned char IR_get_address()
{
    return IR_data.address;
}

unsigned char IR_get_command()
{
    return IR_data.command;
}



void handle_wait_state(unsigned int time)
{
    if (time >= 13500 - DELTA - 1000 && time <= 13500 + DELTA)
    {
        IR_data.start_time = time;
        IR_data.state = RECEIVE_DATA;
        IR_data.write_index = 0;
    }
    else if (time >= 11250 - DELTA - 750 && time <= 11250 + DELTA)
    {

        /*
        在实际测试过程中发现, 按键按下一次,
        遥控器随后有概率会发出一个repeat, 导致
        好像按键按下了两次, 实际不然.
        */
        IR_data.repeat = 1;
        IR_data.state = IDLE;
    }
    else
        // 在遇到该下降沿时, 指令不符合预期,
        // 则重新等待新的有效指令(start或者repeat)
        IR_data.state = WAIT;
}

void handle_data_receive(unsigned int time)
{

    // 经过实际测试, 所有的阈值(最大值和最小值)应该减小300
    if (time >= 1120 - DELTA - 300 && time <= 1120 + DELTA - 300)
    {
        IR_data.data[IR_data.write_index/8] &= ~(0x01 << (IR_data.write_index%8));
        IR_data.write_index++;
    }
    else if (time >= 2250 - DELTA - 300 && time <= 2250 + DELTA - 300)
    {
        IR_data.data[IR_data.write_index/8] |= 0x01 << (IR_data.write_index%8);
        IR_data.write_index++;
    }
    else
    {
        IR_data.state = WAIT;
        IR_data.write_index = 0;
    }

    if (IR_data.write_index > 31)
    {
        // 32位数据接收完成
        // 先进行数据反码校验
        unsigned char address_verify = ~IR_data.data[1];
        unsigned char command_verify = ~IR_data.data[3];
        if (IR_data.data[0] == address_verify && IR_data.data[2] == command_verify)
        {
            IR_data.data_received = 1;
            IR_data.address = IR_data.data[0];
            IR_data.command = IR_data.data[2];
        }
        else
        {
            printf_fast("data verify error:\naddress:%x, ~address:%x\ncommand:%x, ~command:%x",
                IR_data.data[0], address_verify, IR_data.data[2], command_verify);
        }

        IR_data.state = IDLE;
        IR_data.write_index = 0;
    }
}



void record_time(unsigned int time)
{

    time_arr[time_arr_index++] = time;

    if (time_arr_index >= 34)
    {
        printf_fast("time arr: ");
        for (unsigned char i = 0; i < time_arr_index; i++)
        {
            printf_fast("%u ", time_arr[i]);
        }
        printf_fast("\n");
        time_arr_index = 0;

        printf_fast("%d, %d, %d, %d, %d, %x, %x, %x, %x\n",
            IR_data.start_time, IR_data.data_received,
            IR_data.address, IR_data.command,
            IR_data.write_index, IR_data.data[0],
            IR_data.data[1], IR_data.data[2], IR_data.data[3]);
    }
}

void IR_int0_routine() __interrupt(0)
{
    unsigned int time = timer0_inner_counter_get_time();
    timer0_inner_counter_restart();

    switch (IR_data.state)
    {
    case IDLE:
        IR_data.state = WAIT;
        break;
 
    case WAIT:
        handle_wait_state(time);
        break;

    case RECEIVE_DATA:
        handle_data_receive(time);
        break;

    default:
        break;
    }
}


