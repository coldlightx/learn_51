#include <REGX52.H>
#include <STDIO.H>
#include "LCD1602.h"
#include "DS1302.h"


void show_datetime(DateTime * datetime)
{
    char buffer[30];

    // show date
    sprintf(buffer, "20%02bu-%02bu-%02bu", datetime->year, datetime->month, datetime->date);
    LCD_ShowString(1, 5, buffer);

    LCD_ShowNum(1, 16, datetime->day, 1);
    
    sprintf(buffer, "%02bu:%02bu:%02bu", datetime->hour, datetime->minute, datetime->second);
    LCD_ShowString(2, 6, buffer);
}

void main()
{

    unsigned char seconds = 0;
    unsigned char minutes = 0;

    DateTime datetime = {25, 4, 9, 3, 22, 0, 50};

    DS1302_disable_write_protect();
    DS1302_set_datetime(&datetime);

    LCD_Init();
    LCD_ShowString(1, 1, "RTC");

    while (1)
    {
        DS1302_get_datetime(&datetime);
        show_datetime(&datetime);
    }
}

