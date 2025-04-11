#if !defined(__DS1302_H__)
#define __DS1302_H__

typedef struct DateTime
{
    unsigned char year;
    unsigned char month;
    unsigned char date;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} DateTime;


void DS1302_init();
void DS1302_write(unsigned char command, unsigned char data_);
unsigned char DS1302_read(unsigned char command);
void DS1302_disable_write_protect();
void DS1302_enable_write_protect();
unsigned char BCD_to_DEC(unsigned char bcd_data);


unsigned char DS1302_get_year();
unsigned char DS1302_get_month();
unsigned char DS1302_get_date();
unsigned char DS1302_get_day();
unsigned char DS1302_get_hour();
unsigned char DS1302_get_minute();
unsigned char DS1302_get_second();

void DS1302_set_year(unsigned char year);
void DS1302_set_month(unsigned char year);
void DS1302_set_date(unsigned char year);
void DS1302_set_day(unsigned char year);
void DS1302_set_hour(unsigned char year);
void DS1302_set_minute(unsigned char year);
void DS1302_set_second(unsigned char year);

void DS1302_get_datetime(DateTime * datetime);
void DS1302_set_datetime(DateTime * datetime);

#endif // __DS1302_H__
