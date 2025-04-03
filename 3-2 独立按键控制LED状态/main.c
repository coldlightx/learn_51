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
	
	bit inverse_state;
	while(1)
	{
		
		if (P3_1 == 0)
		{
			sleep(20);
			
			inverse_state = ~P2_0;
			
			while(P3_1 == 0)
			{
				P2_0 = inverse_state;
			}
			sleep(20);
			
		}
		
	}
	
}
