#include <mcs51reg.h>
#include "key.h"
#include "lcd.h"
#include "delay.h"

SBIT(BEEP, 0xA0, 5);

void main()
{
    unsigned char key = 0;
    unsigned int i;

    display_number(1, 0);

    while (1)
    {
        key = get_key();
        
        if (key)
        {
            for (i = 0; i < 500; i++)
            {
                BEEP = !BEEP;
                delay_n10us(50);
            }
            display_number(1, key);
        }

    }
}