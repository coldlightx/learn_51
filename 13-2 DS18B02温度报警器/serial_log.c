#include "UART.h"

int putchar(int c)
{
    UART_send(c);
    return c;
}