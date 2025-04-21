#include <mcs51reg.h>
#include <stdio.h>
#include "delay.h"
#include "UART.h"
#include "serial_log.h"

void main()
{
    unsigned char num = 0;
    P2 = 0xFF;

    while (1)
    {
        UART_send('A');
        UART_send('B');
        UART_send('\n');
        
        printf_fast("Hello, World!\n");
        P2 = ~(num++); // 用来测试程序是否执行到这里以及程序是否存在重新执行的现象
        delay(500);
    }
}

/*
在sdcc中, 如果将ES置为1,
则必须定义中断函数, 否则程序在首次UART_send之后,
会从头重新开始执行
*/
void UART_routine() __interrupt(4)
{
    unsigned char received;
    if (RI)
    {
        RI = 0;
    }
}