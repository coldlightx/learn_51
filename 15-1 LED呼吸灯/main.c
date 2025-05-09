#include <mcs51reg.h>
#include "delay.h"

SBIT(LED, 0xA0, 0);


void delay_time(int time)
{
    while (time-- > 0);
}


void light_led(unsigned int time, unsigned int light_time)
{
    if (light_time > 0) LED = 0;
    delay_time(light_time);

    LED = 1;
    delay_time(time - light_time);
}


void main(void)
{

    unsigned int period = 100;

    while (1)
    {
        for (int i = 0; i < period; i++)
           for (int j = 0; j < 10; j++)
               light_led(period, period - i);

        for (int i = 0; i < period; i++)
            for (int j = 0; j < 10; j++)
                light_led(period, i);
    }
}