#include <REGX52.H>
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


void sleep(int milliseconds)
{

	while(milliseconds-- > 0)
	{
		
		Delay1ms();
	}

}

void main()
{
	// P2 = 0xFE;

	while(1)
	{
		P2 = 0xFE;
		sleep(500);
	
		P2 = 0xFF;
		sleep(500);

	}

}
