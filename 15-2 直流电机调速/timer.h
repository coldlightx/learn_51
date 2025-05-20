#if !defined(__TIME0_H__)
#define __TIME0_H__

void Timer0_Reg_Init(void);
void Timer0_Init(void);		//1毫秒@11.0592MHz
void init_T2(unsigned int init_value);

SFR(T2CON, 0xc8);
SFR(T2MOD, 0xc9);
SFR(RCAP2L, 0xca);
SFR(RCAP2H, 0xcb);
SFR(TL2, 0xcc);
SFR(TH2, 0xcd);

SBIT(TF2, 0xc8, 7);
SBIT(TR2, 0xc8, 2);
SBIT(ET2, 0xa8, 5);

#endif // __TIME0_H__
