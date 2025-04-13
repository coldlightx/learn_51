/*
compile step:
sdcc -mmcs51 main.c
then use stc-isp to download the main.ihx
*/

#include <8051.h>

void main()
{
	P2 = 0xAF;
	while(1)
	{
	}

}
