#include <REGX52.H>
#include <INTRINS.H>
#include <math.h>

void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


void sleep(int milliseconds)
{

	while(milliseconds-- > 0)
	{
		
		Delay1ms();
	}

}

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
};

void display_number(unsigned char position, unsigned char number)
{
	unsigned char position_code;
	
	position -= 1;
	
	position_code = position << 2;

	position_code |= 0xE3;// 0B11100011
	
	P0 = 0; // xiaoyin
	P2 = position_code;
	
	P0 = NUMBER_TABLE[number];
	sleep(1); // make LED brighter
}

void main()
{
	
	while(1)
	{
		
		display_number(3, 3);
		display_number(2, 2);
		display_number(1, 1);
		
	};
}

