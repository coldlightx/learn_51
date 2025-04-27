#include <mcs51reg.h>
#include "I2C.h"
#include "delay.h"

#define AT24C02_ADDR 0xA0


void AT24C02_write_byte(unsigned char word_addr, unsigned char data)
{
    I2C_start();
    I2C_send_byte(AT24C02_ADDR);
    I2C_send_byte(word_addr);
    I2C_send_byte(data);
    I2C_stop();
    delay(5);
}


unsigned char AT24C02_read_byte(unsigned char word_addr)
{
    unsigned char data;

    I2C_start();
    I2C_send_byte(AT24C02_ADDR);
    I2C_send_byte(word_addr);

    I2C_start(); // 重新开始
    I2C_send_byte(AT24C02_ADDR | 0x01);

    data = I2C_receive_byte();
    I2C_send_ACK(1);
    I2C_stop();

    return data;
}
