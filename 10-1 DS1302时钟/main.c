#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"


void main()
{

    unsigned char seconds = 0;

    P0 = 0;
    // LCD_Init();
    // LCD_ShowString(1, 1, "RTC");

    DS1302_write(0x80, 0x06);

    seconds = DS1302_read(0x81);

    P2 = seconds;

    // LCD_ShowNum(2, 1, 3, 3);
    while (1)
    {
        P2 = DS1302_read(0x81);
        P2_1 = 0;
    }
    
}