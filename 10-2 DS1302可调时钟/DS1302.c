#include <8052.h>
#include "DS1302.h"

__sbit __at (0xB0+6) SCLK;
__sbit __at (0xB0+4) IO;
__sbit __at (0xB0+5) CE;

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR 0x84
#define DS1302_DATE 0x86
#define DS1302_MONTH 0x88
#define DS1302_DAY 0x8A
#define DS1302_YEAR 0x8C
#define DS1302_WP 0x8E


void DS1302_init()
{
    CE = 0;
    SCLK = 0;
}


void _DS1302_send(unsigned char data_)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        IO = data_ & (0x01 << i);
        SCLK = 0;
        SCLK = 1;
    }
}

unsigned char _DS1302_recv()
{
    // 进入该函数之前, SCLK应该处于高电平
    unsigned char data_ = 0;
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        SCLK = 0;
        SCLK = 1;
        if(IO) data_ |= (0x01 << i);
    }

    return data_;
}

void DS1302_write(unsigned char command, unsigned char data_)
{
    DS1302_init();
    
    CE = 1;
    _DS1302_send(command);
    _DS1302_send(data_);

    SCLK = 0;
    CE = 0;
}


unsigned char DS1302_read(unsigned char command)
{

    unsigned char data_ = 0;
    DS1302_init();
    CE = 1;

    IO = 0; // 这里必须置0, 否则读出的数据有问题 可能性: IO在未置零前处于不确定状态, 影响了command的写入
    _DS1302_send(command | 0x01);
    data_ = _DS1302_recv();

    SCLK = 0;
    CE = 0;
    return data_;
}



void DS1302_disable_write_protect()
{
    DS1302_write(DS1302_WP, 0x00);
}


void DS1302_enable_write_protect()
{
    DS1302_write(DS1302_WP, 0x80);
}


unsigned char BCD_to_DEC(unsigned char bcd_data)
{
    return ((bcd_data>>4) * 10) + (bcd_data & 0x0F);
}

unsigned char DEC_to_BCD(unsigned char dec_data)
{
    return (dec_data/10 * 16) + dec_data % 10;
}



unsigned char DS1302_get_year()
{
    return BCD_to_DEC(DS1302_read(DS1302_YEAR));
}


unsigned char DS1302_get_month()
{
    return BCD_to_DEC(DS1302_read(DS1302_MONTH));
}

unsigned char DS1302_get_date()
{
    return BCD_to_DEC(DS1302_read(DS1302_DATE));
}

unsigned char DS1302_get_day()
{
    return BCD_to_DEC(DS1302_read(DS1302_DAY));
}


unsigned char DS1302_get_hour()
{
    return BCD_to_DEC(DS1302_read(DS1302_HOUR));
}

unsigned char DS1302_get_minute()
{
    return BCD_to_DEC(DS1302_read(DS1302_MINUTE));
}

unsigned char DS1302_get_second()
{
    return BCD_to_DEC(DS1302_read(DS1302_SECOND));
}


void DS1302_set_year(unsigned char year)
{
    DS1302_write(DS1302_YEAR, DEC_to_BCD(year));
}


void DS1302_set_month(unsigned char month)
{
    DS1302_write(DS1302_MONTH, DEC_to_BCD(month));
}

void DS1302_set_date(unsigned char date)
{
    DS1302_write(DS1302_DATE, DEC_to_BCD(date));
}

void DS1302_set_day(unsigned char day)
{
    DS1302_write(DS1302_DAY, DEC_to_BCD(day));
}


void DS1302_set_hour(unsigned char hour)
{
    DS1302_write(DS1302_HOUR, DEC_to_BCD(hour));
}

void DS1302_set_minute(unsigned char minute)
{
    DS1302_write(DS1302_MINUTE, DEC_to_BCD(minute));
}

void DS1302_set_second(unsigned char second)
{
    DS1302_write(DS1302_SECOND, DEC_to_BCD(second));
}


void DS1302_get_datetime(DateTime * datetime)
{
    datetime->year = DS1302_get_year();
    datetime->month = DS1302_get_month();
    datetime->date = DS1302_get_date();
    datetime->day = DS1302_get_day();
    datetime->hour = DS1302_get_hour();
    datetime->minute = DS1302_get_minute();
    datetime->second = DS1302_get_second();
}


void DS1302_set_datetime(DateTime * datetime)
{
    DS1302_set_year(datetime->year);
    DS1302_set_month(datetime->month);
    DS1302_set_date(datetime->date);
    DS1302_set_day(datetime->day);
    DS1302_set_hour(datetime->hour);
    DS1302_set_minute(datetime->minute);
    DS1302_set_second(datetime->second);
}

