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

void DS1302_get_datetime(DateTime * datetime);
void DS1302_set_datetime(DateTime * datetime);

#endif // __DS1302_H__
