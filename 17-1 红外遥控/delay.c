#include <mcs51reg.h>

void Delay1ms(void) //@11.0592MHz
{
	unsigned char i, j;

	i = 2;
	j = 199;
	do
	{
		while (--j)
			;
	} while (--i);
}

void delay(int milliseconds)
{

	while (milliseconds-- > 0)
	{
		unsigned char i, j;

		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void init_t0()
{
	TR0 = 0;
	TMOD = (TMOD & 0xF0) | 0x01;
	ET0 = 0;
}

/*
	延迟clock_count个时钟周期, 每个时钟周期的长度为1.085us
	Args:
		clock_count: 时钟周期个数
	return:
		无
*/
void delay_clock(unsigned int clock_count)
{
	if ((TMOD & 0x0F) != 0x01)
		init_t0();

	unsigned int reload = 0xffff - clock_count + 1;
	TH0 = reload >> 8;
	TL0 = reload;

	TR0 = 1;
	while (!TF0)
		;
	TF0 = 0;
	TR0 = 0;
}

void delay_n10us(unsigned int n)
{
	unsigned int i;
	unsigned int j;

	for (j = 0; j < n; j++)
	{
		i = 2;
		while (--i)
			;
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