#include <mcs51reg.h>
#include "I2C.h"

SBIT(SCL, 0xA0, 1);
SBIT(SDA, 0xA0, 0);


void I2C_start(void)
{
    SDA = 1;
    SCL = 1;
    SDA = 0;

    SCL = 0;
}


void I2C_stop(void)
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}


unsigned char I2C_send_byte(unsigned char byte)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        SDA = byte & (0x80>>i);
        SCL = 1;
        SCL = 0;
    }
    
    return I2C_receive_ACK();
}


unsigned char I2C_receive_byte(void)
{
    unsigned char byte = 0x00;
    unsigned char i;

    SDA = 1; // 释放SDA

    for (i = 0; i < 8; i++)
    {
        SCL = 1;
        if (SDA) byte |= (0x80>>i);
        SCL = 0;
    }


    return byte;
}


void I2C_send_ACK(unsigned char ack)
{
    SDA = ack;
    SCL = 1;
    SCL = 0;
}


unsigned char I2C_receive_ACK(void)
{
    unsigned char ack;

    SDA = 1; // 释放SDA
    SCL = 1;
    ack = SDA;
    SCL = 0;
    return ack;
}



