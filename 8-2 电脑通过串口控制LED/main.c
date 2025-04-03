#include <REGX52.H>
#include "delay.h"
#include "UART.h"


void main()
{

    unsigned char num = 0;
    UART_Init();
    while (1)
    {
    }
    
}


void UART_routine() interrupt 4
{
    unsigned char received;
    if (RI)
    {
        received = SBUF;
        UART_send(received);
        P2 = ~received;
        RI = 0;
    }
}