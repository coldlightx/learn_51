#include <REGX52.H>


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
	
	P2 = position_code;
	
	P0 = NUMBER_TABLE[number];
}

void main()
{
	
	
	// P2_4 = 1;
	// P2_3 = 0;
	// P2_2 = 1;
	
	// P0 = 01111101;
	
	// P0 = 0x7D;
	
	display_number(3, 1);
	
	while(1);
}

