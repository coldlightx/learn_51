#if !defined(__DS1302_H__)
#define __DS1302_H__


void DS1302_init();
void DS1302_write(unsigned char command, unsigned char data_);
unsigned char DS1302_read(unsigned char command);


#endif // __DS1302_H__
