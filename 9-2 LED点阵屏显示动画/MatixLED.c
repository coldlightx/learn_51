#include <REGX52.H>
#include "delay.h"

sbit SER = P3^4;
sbit SCK = P3^6;
sbit RCK = P3^5;

void _74HC595_write_data(unsigned char byte)
{
    unsigned char i;

    SCK = 0;
    RCK = 0;

    /*
    使用PZ的烧录器, 必须将SRE先置0, 否则74HC595放入缓存的内容有问题, 
    但是重启该问题会被解决, 使用STC-ISP冷重启烧录的方式也不会存在问题
    */
    SER = 0; 

    for (i = 0; i < 8; i++)
    {
        SER = byte & (0x80 >> i);
        SCK = 1;
        SCK = 0;
    }

    RCK = 1;
    RCK = 0;
}

void matrix_led_show_column(unsigned char column, unsigned char col_value)
{
    _74HC595_write_data(col_value);
    P0 = ~(0x80 >> column);

    delay(1);
    P0 = 0xFF; // 消隐

}

void matrix_led_show(unsigned char *cols, unsigned char ncol)
{
    int col;
    for (col = 0; col < 8 && col < ncol; col++)
        matrix_led_show_column(col, cols[col]);
}


void matrix_led_show_shift_animation(unsigned char *animation, unsigned char ncol)
{
    unsigned char offset=0, count=0;

    while (1)
    {
        matrix_led_show(animation+offset, 8);
        count++;

        if (count > 10)
        {
            count = 0;
            offset++;
            if(offset >= ncol - 8)
                break;
        }
        
    }
}

void matrix_led_show_frame_animation(unsigned char *animation, unsigned char ncol, unsigned char frame_delta)
{

    unsigned char offset=0, count=0;

    while (1)
    {
        matrix_led_show(animation+offset, 8);

        count++;
        if (count > frame_delta)
        {
            count = 0;
            offset += 8;
            if (offset >= ncol)
                break;
        }
    }
}