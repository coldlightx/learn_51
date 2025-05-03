#include <mcs51reg.h>
#include <stdio.h>
#include "serial_log.h"

SBIT(DQ, 0xB0, 7);

unsigned char OneWire_start()
{
    unsigned char i;
    unsigned char ack;

    EA = 0;

    DQ = 1;
    
    DQ = 0;
    i = 221; while (--i); // delay 480 us

    DQ = 1;
    i = 27; while (--i); // delay 60us
    
    ack = DQ;

    // 必须要在这里把从机响应的480us走完, 否则稍后的操作都会出现问题
    i = 221; while (--i); // delay 480 us  

    EA = 1;

    return ack;
}

void OneWire_send_bit(unsigned char bit)
{
    unsigned char i;
    DQ = 0;
    i = 6; while (--i); // delay 15us

    DQ = bit;
    i = 20; while (--i); // delay 45us

    DQ = 1; // 释放总线
}


unsigned char OneWire_receive_bit()
{
    unsigned char i;

    unsigned char bit;

    DQ = 0;
    i = 2; while (--i); // delay 5us

    DQ = 1;
    i = 2; while (--i); // delay 5us

    bit = DQ;
    i = 163; while (--i); // delay 55us
    return bit;
}


void OneWire_send_byte(unsigned char byte)
{
    unsigned char i = 0;


    EA = 0;

    for (i = 0; i < 8; i++)
        OneWire_send_bit(byte & (0x01 << i));

    EA = 1;
    
}


unsigned char OneWire_receive_byte()
{
    unsigned char i = 0;
    unsigned char byte = 0;

    EA = 0;

    for (i = 0; i < 8; i++)
        if(OneWire_receive_bit())
            byte |= (0x01 << i);

    EA = 1;

    return byte;
}


