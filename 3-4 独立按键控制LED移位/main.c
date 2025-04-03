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
	
	unsigned char click_num = 0;
	
	while(1)
	{
		
		if (P3_1 == 0)
		{
			sleep(20);
			while(P3_1 == 0);
			sleep(20);
			
			click_num--;
		}
		
		if (P3_0 == 0)
		{
			sleep(20);
			while(P3_0 == 0);
			sleep(20);
			click_num++;
		}
		
		if (click_num <0)
		{
			click_num = 7;
		}
		click_num %= 8;
		
		P2 = ~(0x01 << click_num);

	}
}
