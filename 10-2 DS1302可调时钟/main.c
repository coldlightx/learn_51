#include <8052.H>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
#include "DS1302.h"
#include "key.h"
#include "timer0.h"
#include "delay.h"

// 0 for display mode, 1 for edit mode
unsigned char MODE = 0;
unsigned char SELECT = 1;
unsigned char HIDE = 0;

// always store the current time
DateTime current_time;

unsigned char printf_buffer[32] = "\0";
unsigned char printf_buffer_index = 0;

int putchar(int c)
{
    printf_buffer[printf_buffer_index++] = c;
    return c;
}


int cycle(int value, int min_value, int max_value)
{
    if (value < min_value)
        return max_value;
        
    if (value > max_value)
        return min_value;

    return value;
}

typedef struct
{
    unsigned char type; // 1 for date, 2 for time, 0 for invalid
    unsigned char index;
    unsigned char length;
} Mask;

Mask get_time_mask_for_select(unsigned char select)
{
    switch (select)
    {
    case 1:
    {
        Mask mask = {1, 0, 4};
        return mask;
    }

    case 2:
    {
        Mask mask = {1, 5, 2};
        return mask;
    }

    case 3:
    {
        Mask mask = {1, 8, 2};
        return mask;
    }
    case 4:
    {
        Mask mask = {1, 11, 1};
        return mask;
    }

    case 5:
    {
        Mask mask = {2, 0, 2};
        return mask;
    }

    case 6:
    {
        Mask mask = {2, 3, 2};
        return mask;
    }

    case 7:
    {
        Mask mask = {2, 6, 2};
        return mask;
    }
    default:
    {
        Mask mask = {0, 0, 0};
        return mask;
    }
    }
}

void mask_string(char * s, char mask, unsigned char start, unsigned char end)
{
    unsigned int i;
    for (i = start; i < end; i++)
        s[i] = mask;
}


void date_string(DateTime * datetime, unsigned char * buffer)
{
    printf_buffer_index = 0;
    printf_fast("20%02d-%02d-%02d %1d", datetime->year, datetime->month, datetime->date, datetime->day);
    printf_buffer[printf_buffer_index] = '\0';

    strcpy(buffer, printf_buffer);
}


void time_string(DateTime * datetime, unsigned char * buffer)
{
    printf_buffer_index = 0;
    printf_fast("%02d:%02d:%02d", datetime->hour, datetime->minute, datetime->second);
    printf_buffer[printf_buffer_index] = '\0';
    strcpy(buffer, printf_buffer);
}


void show_datetime(DateTime *datetime, unsigned char mode, unsigned char select, unsigned char hide)
{
    
    Mask time_mask;

    unsigned char buffer[32];
    
    time_mask = get_time_mask_for_select(select);

    date_string(datetime, buffer);
    if (mode && hide && time_mask.type == 1)
        mask_string(buffer, ' ', time_mask.index, time_mask.index + time_mask.length);
    LCD_ShowString(1, 3, buffer);


    time_string(datetime, buffer);
    if (mode && hide && time_mask.type == 2)
        mask_string(buffer, ' ', time_mask.index, time_mask.index + time_mask.length);
    LCD_ShowString(2, 4, buffer);
}

void start_edit_toggle()
{
    MODE = !MODE;
    SELECT = 1;
}

void select_button_clicked()
{
    if (MODE)
        SELECT = cycle(++SELECT, 1, 7);
}


unsigned is_leap_year(unsigned char year)
{
    return year % 4 == 0;
}


unsigned char is_in(unsigned char number, unsigned char *array, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++)
        if (number == array[i]) return 1;

    return 0;
}

unsigned char get_month_type(unsigned char month)
{

    unsigned char dayue[] = {1, 3, 5, 7, 8, 10, 12};
    unsigned char xiaoyue[] = {4, 6, 9, 11};

    if (is_in(month, dayue, 7))
    {
        return 1;
    } else if (is_in(month, xiaoyue, 4))
    {
        return 2;
    } else if (month == 2)
    {
        return 3;
    }
    return 5;
}


unsigned char get_max_days_for_month(unsigned char year, unsigned char month)
{

    switch (get_month_type(month))
    {
    case 1: // 大月
        return 31;
    case 2: // 平月
        return 30;

    case 3: // 2月
        if (is_leap_year(year))
            return 29;
        else
            return 28;
    default:
        return 1;
    }

}




void set_year(unsigned char year)
{
    unsigned char month, date;
    month = DS1302_get_month();
    date = DS1302_get_date();

    year = cycle(year, 0, 99);

    DS1302_set_year(year);

    if (month == 2 && date >= 29)
    {
        if (!is_leap_year(year))
        {
            date = 28;
            DS1302_set_date(date);
        }
    }
}

void set_month(unsigned char month)
{
    unsigned char year, date, max_date;
    year = DS1302_get_year();
    date = DS1302_get_date();

    month = cycle(month, 1, 12);

    DS1302_set_month(month);

    max_date = get_max_days_for_month(year, month);

    if (date > max_date)
    {
        date = max_date;
        DS1302_set_date(date);
    }

}


void set_date(unsigned char date)
{
    unsigned char year, month, max_date;

    year = DS1302_get_year();
    month = DS1302_get_month();

    max_date = get_max_days_for_month(year, month);
    date = cycle(date, 1, max_date);

    DS1302_set_date(date);
}


void modify_time_by_step(unsigned char position, int step)
{

    switch (position)
    {
    case 1:
        set_year((DS1302_get_year() + step) % 100);
        break;
    case 2:
        set_month(DS1302_get_month() + step);
        break;
    case 3:
        set_date(DS1302_get_date() + step);
        break;

    case 4:
        DS1302_set_day(cycle(DS1302_get_day() + step, 1, 7));
        break;

    case 5:
        DS1302_set_hour(cycle(DS1302_get_hour() + step, 0, 23));
        break;

    case 6:
        DS1302_set_minute(cycle(DS1302_get_minute() + step, 0, 59));
        break;
    case 7:
        DS1302_set_second(cycle(DS1302_get_second() + step, 0, 59));
        break;

    default:
        break;
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
        if(MODE) modify_time_by_step(SELECT, 1);
        break;
    case 4:
        if(MODE) modify_time_by_step(SELECT, -1);
        break;
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
    Timer0_Init();

    while (1)
    {
        DS1302_get_datetime(&datetime);
        show_datetime(&datetime, MODE, SELECT, HIDE);

        key_number = get_key();

        if (key_number)
        {
            key_pressed(key_number);
        }
    }
}


void timer0_routine() __interrupt(1)
{
    static unsigned int counter = 0;
    counter++;
    
    if (counter >= 500)
    {
        counter = 0;
        HIDE = !HIDE;
    }
    Timer0_Reg_Init();
}