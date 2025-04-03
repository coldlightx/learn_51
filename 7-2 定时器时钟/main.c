#include <REGX52.H>
#include "timer0.h"
#include "LCD1602.h"


typedef struct Date
{
    unsigned int hour;
    unsigned int minute;
    unsigned int second;

} Date;
    
unsigned long seconds = 86390;


Date parse_time(unsigned long seconds)
{
    Date date;

    date.hour = seconds / 3600 % 24;
    date.minute = seconds % 3600 / 60;
    date.second = seconds % 3600 % 60;

    return date;
}

void show_time(unsigned long seconds)
{
    Date date;
    date = parse_time(seconds);

    LCD_ShowString(2, 3, ":");
    LCD_ShowString(2, 6, ":");

    LCD_ShowNum(2, 1, date.hour, 2);
    LCD_ShowNum(2, 4, date.minute, 2);
    LCD_ShowNum(2, 7, date.second, 2);
}

void main()
{
    Timer0_Init();
    LCD_Init();
    LCD_ShowString(1, 1, "Clock:");
    while (1)
    {
        show_time(seconds);
    }

    
}


void timer0_routine() interrupt 1
{
    static unsigned int counter = 0;
    counter++;
    
    if (counter >= 1000)
    {
        counter = 0;
        seconds++;

        if (seconds >= 86400)
            seconds = 0;
    }
    Timer0_Reg_Init();
}