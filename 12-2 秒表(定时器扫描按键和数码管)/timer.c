#include <mcs51reg.h>


// =================== Timer 0 ====================
void Timer0_Reg_Init(void)
{
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
}

// 优先使用这个
void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
    EA = 1;                 // CPU全局中断使能
}


/* T0定时器中断接口函数示例
void timer0_routine() __interrupt(1)
{
    static unsigned int counter = 0;
    counter++;
    
    if (counter >= 1000)
    {
        counter = 0;
        // put your code here
    }
    Timer0_Reg_Init();
}
*/



void timer0_register_init()
{
    TH0 = 64536/256;
    TL0 = 64536%256;
}

unsigned int counter = 0;
void timer0_init_own()
{
    // 设置定时器模式 TMOD
    /*
    GATE = 0 仅由TR0控制T0定时器是否开启
    C/T = 0 将T0用作定时器
    M1, M0 = 0, 1 16位定时器
    */
    TMOD &= 0xF0;
    TMOD |= 0x01;

    // 设置定时器 TCON
    TF0 = 0; // 中断标志位清0
    TR0 = 1; // timer 0 开始计数

    counter = 0;
    timer0_register_init();

    // 中断寄存器设置
    EA = 1; // CPU 开放中断
    ET0 = 1; // 允许T0中断

    PT0 =  0; // 设置T0中断优先级
}



// =================== Timer 2 ====================
SFR(T2CON, 0xc8);
SFR(T2MOD, 0xc9);
SFR(RCAP2L, 0xca);
SFR(RCAP2H, 0xcb);
SFR(TL2, 0xcc);
SFR(TH2, 0xcd);

SBIT(TF2, 0xc8, 7);
SBIT(TR2, 0xc8, 2);
SBIT(ET2, 0xa8, 5);

void init_T2(unsigned int init_value)
{
    T2CON = 0x00;
    T2MOD = 0x00;
    
    RCAP2H = init_value >> 8;
    RCAP2L = init_value;

    TH2 = RCAP2H;
    TL2 = RCAP2L;
}


/*
void time2_routine() __interrupt(5)
{
    BEEP = !BEEP;
    TF2 = 0;
}
*/
