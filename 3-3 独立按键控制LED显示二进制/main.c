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
	
	unsigned char num = 0;
	
	while(1)
	{
		if (P3_1 == 0)
		{
			
			// xiao dou
			sleep(20);
			while(P3_1 == 0);
			sleep(20);

			num++;
			P2 = ~num;
			
		}
	}
}
