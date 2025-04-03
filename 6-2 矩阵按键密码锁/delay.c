#include <INTRINS.H>

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


void delay(int milliseconds)
{

	while(milliseconds-- > 0)
	{
		Delay1ms();
	}
	
}

unsigned char get_bit_value(unsigned int number, unsigned char bit_position)
{
	return (number >> bit_position) & 0x01;
}


void debounce(unsigned char *reg, unsigned char bit_position, unsigned char status)
{
	if(bit_position > 7)
		return;
	delay(20);
	while(get_bit_value(*reg, bit_position) == status);
	delay(20);
}