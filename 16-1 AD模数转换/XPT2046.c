#include "spi.h"
#include "delay.h"

unsigned char ain_addr[4] = {1, 5, 2, 6};

unsigned int XPT2046_read_by_command(unsigned char command)
{
    unsigned int data;

    spi_select();
    spi_send_byte(command);
    data = spi_receive_double_byte();
    spi_unselect();

    return data;
}


/*
    读取芯片指定ain口的AD转换数据
    Args:
        ain_index: ain口的标号
        mode: 转换模式, 0代表12位, 1代表8位
*/
unsigned int XPI2046_read_ain(unsigned char ain_index, unsigned char mode)
{
    unsigned char command = 0x84;

    command |= (ain_addr[ain_index] << 4);

    if (mode) command |= 0x08;

    unsigned int data = XPT2046_read_by_command(command);

    if (mode)
        data = data >> 8;
    else
        data = data >> 4;

    return data;
}