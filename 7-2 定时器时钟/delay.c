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



unsigned char nearest_non_zero_bit(unsigned char number)
{
    unsigned char bit_position = 8;
    int i;

    for (i = 0; i < 8; i++)
    {
        if (get_bit_value(number, i))
        {    
            bit_position = i;
            return bit_position;
        }
    }
    return bit_position;
}