#include <mcs51reg.h>
#include <stdio.h>
#include "LCD1602.h"
#include "timer.h"
#include "delay.h"
#include "int0.h"
#include "IR.h"
#include "serial_log.h"



void process_IR()
{
    static unsigned char number = 0;
    unsigned char address = 0;
    unsigned char command = 0;

    if (IR_data_received() || IR_get_repeat())
    {
        address = IR_get_address();
        command = IR_get_command();
        LCD_show_hex_number(2, 1, address, 2);
        LCD_show_hex_number(2, 8, command, 2);

        switch (command)
        {
        case IR_VOL_PLUS:
            number++;
            break;
        
        case IR_VOL_MINUS:
            number--;
            break;

        default:
            break;
        }
        
        LCD_show_number(2, 14, number, 3);
    }
}


void operation_time_measurement()
{
    unsigned int time = 0;
    unsigned int arr[32];

    timer0_inner_counter_init();
    timer0_inner_counter_start();

    printf_fast("a number is %d\n", 63209);
    time = timer0_inner_counter_get_time();
    printf_fast("printf_fast cost time: %d\n", time);
    timer0_inner_counter_restart();

    LCD_show_number(2, 8, 56783, 5);
    time = timer0_inner_counter_get_time();
    printf_fast("LCD show number cost time: %d\n", time);
    timer0_inner_counter_restart();

    printf_fast("%d\n", 63209);
    time = timer0_inner_counter_get_time();
    printf_fast("printf_fast numbercost time: %d\n", time);
    timer0_inner_counter_restart();

    arr[1] = 58901;
    time = timer0_inner_counter_get_time();
    printf_fast("assign number to array cost time: %d\n", time);
    timer0_inner_counter_restart();
}

void main()
{
    unsigned char number = 0;
    unsigned int time = 0;

    LCD_init();
    IR_init();
    LCD_show_string(1, 1, "ADDR   CMD   NUM");
    LCD_show_string(2, 1, "00     00    000");

    while (1)
    {
        process_IR();
    }
}


