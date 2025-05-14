#include <mcs51reg.h>
#include <compiler.h>

SBIT(CS, 0xB0, 5);
SBIT(DCLK, 0xB0, 6);
SBIT(DIN, 0xB0, 4);
SBIT(DOUT, 0xB0, 7);


void spi_select()
{
    DCLK = 0;
    CS = 0;
}



void spi_send_byte(unsigned char data)
{
    for (unsigned char i = 0; i < 8; i++)
    {
        DIN = data & (0x80 >> i);
        DCLK = 1;
        DCLK = 0;
    }
}


unsigned char spi_receive_byte()
{
    unsigned char data = 0;
    for (char i = 0; i < 8; i++)
    {
        DCLK = 1;
        DCLK = 0;
        if (DOUT) data |= (0x80 >> i);
    }

    return data;
}

unsigned int spi_receive_double_byte()
{
    unsigned int data = 0;

    for (char i = 0; i < 16; i++)
    {
        DCLK = 1;
        DCLK = 0;
        if (DOUT) data |= (0x8000 >> i);
    }

    return data;
}



void spi_unselect()
{
    CS = 1;
}

