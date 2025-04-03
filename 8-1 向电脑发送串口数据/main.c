#include <REGX52.H>
#include "delay.h"
#include "UART.h"


void main()
{

    unsigned char num = 0;
    UART_Init();
    while (1)
    {
        // UART_send(num++);
        UART_send('A');
        delay(1000);
    }
    
}