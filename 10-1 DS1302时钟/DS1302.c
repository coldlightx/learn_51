#include <REGX52.H>

sbit SCLK = P3^6;
sbit IO = P3^4;
sbit CE = P3^5;


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
        if(IO) data_ |= (0x01 << i);
        SCLK = 1;
    }

    return data_;
}

void DS1302_write(unsigned char command, unsigned char data_)
{
    DS1302_init();
    
    CE = 1;
    IO = 0;
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

    IO = 0;

    _DS1302_send(command);
    data_ = _DS1302_recv();

    SCLK = 0;
    CE = 0;

    return data_;
}
