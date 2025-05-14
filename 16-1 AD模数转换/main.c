#include "XPT2046.h"
#include "LCD1602.h"
#include "delay.h"

void main(void)
{
    LCD_init();
    LCD_show_string(1, 1, " ADJ   NTC  GR");
    while (1)
    {
        unsigned int data = XPI2046_read_ain(0, 0);
        LCD_show_number(2, 1, data, 4);
        float v = data / 4095. * 5;
        LCD_show_float_number(2, 1, v, 5, 2);
        LCD_show_char(2, 6, 'V');

        // show NTC
        data = XPI2046_read_ain(1, 0);
        LCD_show_number(2, 8, data, 4);

        // show GR
        data = XPI2046_read_ain(2, 0);
        LCD_show_number(2, 13, data, 4);

        delay(10);
    }
}