#include "LCD1602.h"
#include "delay.h"


void main(void)
{

    LCD_init();

    LCD_show_char(1, 1, 'A');

    LCD_show_string(1, 3, "Hello!");

    LCD_show_number(1, 10, 12, 3);

    LCD_show_signed_number(1, 14, -6, 2);

    LCD_show_hex_number(2, 1, 0xA6, 2);

    LCD_show_bin_number(2, 4, 0xAF, 8);

    LCD_show_char(2, 13, 0xDF);
    LCD_show_char(2, 14, 'C');

    LCD_show_char(2, 16, 0xE0);

    LCD_show_string(1, 18, "Welcome to China.");

    while (1)
    {
        LCD_send_command(0x18); // 画面向左平移一个字符位
        delay(500);
    }
    
}