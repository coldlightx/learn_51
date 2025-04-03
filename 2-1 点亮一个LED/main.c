#include <REGX52.H>

#include <INTRINS.H>

sfr ISP_DOWNS = 0xE7;
sbit ISP_SW = P3^0;

void detect_load_code()
{
	if (!ISP_SW)
	{
		ISP_DOWNS = 0x60;
	}

}
void main()
{
	// P2 = 0xFE;

	while(1)
	{
		P2 = 0xFE;
		detect_load_code();
	}

}
