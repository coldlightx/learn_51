#include <mcs51reg.H>
#include "delay.h"

unsigned char showing_numbers[8]={10,10,10,10,10,10,10,10};

unsigned char NUMBER_TABLE[] = {
	0x3F, // 0: 00111111
	0x06, // 1: 00000110
	0x5B, // 2: 01011011
	0x4F, // 3: 01001111
	0x66, // 4: 01100110
	0x6D, // 5: 01101101
	0x7D, // 6: 01111101
	0x07, // 7: 00000111
	0x7F, // 8: 01111111
	0x6F, // 9: 01101111
	0x00, // 不显示
	0x40, // -: 01000000
};


void lcd_display_number(unsigned char position, unsigned char number)
{
	if (position > 8)
		return;
	
	showing_numbers[position-1] = number;
}


void update_number(unsigned char position, unsigned char number)
{
	unsigned char position_code;

	if (position > 8)
		return;
	
	position -= 1;
	
	position_code = position << 2;

	P0 = 0; // xiaoyin
	P2  &= 0xE3;  //0B11100011
	P2 |= position_code;
	
	P0 = NUMBER_TABLE[number];
}


void lcd_loop(void)
{
	// lcd中断扫描入口 推荐 1ms/次
	static unsigned char index=0;
	update_number(index+1, showing_numbers[index]);

	if (index++ >= 7)
		index = 0;
}