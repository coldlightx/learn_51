#include <REGX52.H>
#include <STDIO.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "key.h"

// 0 for display mode, 1 for edit mode
unsigned char MODE = 0;
unsigned char SELECT = 0;

// always store the current time
DateTime current_time;

void show_datetime(DateTime *datetime)
{
    char buffer[30];

    // show date
    sprintf(buffer, "20%02bu-%02bu-%02bu", datetime->year, datetime->month, datetime->date);
    LCD_ShowString(1, 3, buffer);

    LCD_ShowNum(1, 14, datetime->day, 1);

    sprintf(buffer, "%02bu:%02bu:%02bu", datetime->hour, datetime->minute, datetime->second);
    LCD_ShowString(2, 4, buffer);
}

void start_edit_toggle()
{
    MODE = !MODE;
    SELECT = 0;
}

void select_button_clicked()
{
    if (!MODE)
        return SELECT++;
    SELECT %= 7;
}

void increase_time(unsigned char position)
{

    unsigned char data;

    switch (position)
    {
    case 0:
        data = DS1302_get_year();
        DS1302_set_year((data + 1) % 100);
    }
}

void key_pressed(unsigned char key_number)
{

    switch (key_number)
    {
    case 1:
        start_edit_toggle();
        break;
    case 2:
        select_button_clicked();
        break;
    case 3:
    case 4:
    default:
        break;
    };
}

void main()
{

    unsigned char seconds = 0;
    unsigned char minutes = 0;

    unsigned char key_number = 0;

    DateTime datetime = {25, 4, 9, 3, 22, 0, 50};

    DS1302_disable_write_protect();
    DS1302_set_datetime(&datetime);

    LCD_Init();

    while (1)
    {
        DS1302_get_datetime(&datetime);
        show_datetime(&datetime);
        key_number = get_key();

        if (key_number)
        {
            key_pressed(key_number);
        }
    }
}
