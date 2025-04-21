#include <mcs51reg.h>
#include <serial_IO.h>
#include "delay.h"

void main()
{
    unsigned char num = 0;

    P2 = 0xFF;
    while (1)
    {
        putchar('A'); // 57600bps@11.0592Mhz
        putchar('B');
        P2 = ~(num++);
        delay(500);
    }
}