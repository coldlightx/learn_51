#include <mcs51reg.h>
#include <stdio.h>
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "serial_log.h"
#include "buzzer.h"

void main()
{
    unsigned char key = 0;


    display_number(1, 0);
    while (1)
    {
        key = get_key();

        if (key)
        {
            clock_beep_loop(200, 1000);
            display_number(1, key);
        }
    }
}