#include <mcs51reg.h>
#include <math.h>

SBIT(EN, 0xA0, 7);
SBIT(RS, 0xA0, 6);
SBIT(RW, 0xA0, 5);

SFR(DATA, 0x80);


void Delay100us(void)	//@11.0592MHz
{
	unsigned char i;

	i = 43;
	while (--i);
}

void LCD_send_byte(unsigned char type, unsigned char byte)
{
    RS = type;

    RW = 0;
    DATA = byte;

    EN = 1;
    Delay100us();
    EN = 0;
    Delay100us();
}


void LCD_send_command(unsigned char command)
{
    LCD_send_byte(0, command);
}


void LCD_send_data(unsigned char data)
{
    LCD_send_byte(1, data);
}


void LCD_init()
{
    //输入方式设置: 数据读写操作后, AC自动加一, 画面不动
    LCD_send_command(0x06);

    // 显示开关控制: 显示开, 光标关, 闪烁关
    LCD_send_command(0x0c);

    // 功能设置: 8位数据接口,两行显示, 5x7点阵
    LCD_send_command(0x38);
}


void LCD_set_ddram_addr(unsigned char row, unsigned char column)
{

    unsigned char offset = 0;

    unsigned char addr = 0;

    if (row == 2)
        offset = 0x40;

    addr = offset + column - 1;

    LCD_send_command(0x80 | addr);
}

void LCD_show_char(unsigned char row, unsigned char column, char c)
{
    LCD_set_ddram_addr(row, column);
    LCD_send_data(c);
}


void LCD_show_string(unsigned char row, unsigned char column, char * s)
{
    LCD_set_ddram_addr(row, column);
    unsigned char * p;

    while (*(p=s++))
        LCD_send_data(*p);
}


void unsinged_number_to_string(unsigned int number, unsigned char length, char * s)
{
    for (int i = 0; i < length; i++)
    {
        unsigned long base = powf(10, length - 1 - i);
        *s++ = number / base % 10 + '0';
        number %= base;
    }
    *s = '\0';
}


void LCD_show_number(unsigned char row, unsigned char column, unsigned int number, unsigned char length)
{
    char s[17] = "";
    unsinged_number_to_string(number, length, s);
    LCD_show_string(row, column, s);
}


void LCD_show_signed_number(unsigned char row, unsigned char column, int number, unsigned char length)
{
    char s[17] = "";

    if (number < 0)
    {
        s[0] = '-';
        number = -number;
    }
    else
        s[0] = '+';
    
    unsinged_number_to_string(number, length, s+1);

    LCD_show_string(row, column, s);
}



void LCD_show_hex_number(unsigned char row, unsigned char column, unsigned char number, unsigned char length)
{
    LCD_set_ddram_addr(row, column);

    unsigned char c;
    for (int i = 0; i < length; i++)
    {
        unsigned long base = powf(16, length - 1 - i);

        c = (number / base) % 16;

        if (c >= 10)
            c = c - 10 + 'A';
        else
            c += '0';


        LCD_send_data(c);
    }

}


void LCD_show_bin_number(unsigned char row, unsigned char column, unsigned char number, unsigned char length)
{
    LCD_set_ddram_addr(row, column);

    unsigned char c;

    for (int i = 0; i < length; i++)
    {
        unsigned long base = powf(2, length - 1 - i);
        c = (number / base) % 2 + '0';
        
        LCD_send_data(c);
    }
    
}