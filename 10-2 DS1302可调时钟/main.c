#include <8052.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "key.h"
#include "printf.h"

// 0 for display mode, 1 for edit mode
unsigned char MODE = 0;
unsigned char SELECT = 1;

// always store the current time
DateTime current_time;


int cycle(int value, int min_value, int max_value)
{
    if (value < min_value)
        return max_value;
        
    if (value > max_value)
        return min_value;

    return value;
}


void show_datetime(DateTime *datetime)
{
    char buffer[30]="\0";

    // show date
    snprintf(buffer, 50, "20%02bu-%02bu-%02bu", datetime->year, datetime->month, datetime->date);
    LCD_ShowString(1, 3, buffer);

    LCD_ShowNum(1, 14, datetime->day, 1);

    snprintf(buffer, 50, "%02bu:%02bu:%02bu", datetime->hour, datetime->minute, datetime->second);
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


void modify_time_by_step(unsigned char position, char step)
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
        modify_time_by_step(SELECT, 1);
        break;
    case 4:
        modify_time_by_step(SELECT, -1);
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

    while (1)
    {
        DS1302_get_datetime(&datetime);
        show_datetime(&datetime);

        LCD_ShowNum(2, 1, SELECT, 2);
        key_number = get_key();

        if (key_number)
        {
            key_pressed(key_number);
            LCD_ShowNum(2, 15, key_number, 2);
        }
    }
}
