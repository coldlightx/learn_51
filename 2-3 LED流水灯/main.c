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

void main()
{
	int i;
	for (i=0; i<=7; i++)
	{
		int a = pow(2, i);
		P2 = ~a;
		sleep(200);
	}
	
}