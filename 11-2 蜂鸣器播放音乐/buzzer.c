#include <mcs51reg.h>
// #include <stdio.h>
// #include "serial_log.h"
#include "delay.h"


#define BEEP P2_5


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

void beep(unsigned int duration_ms, unsigned int frequency)
{
    unsigned int half_period;

    unsigned int max_count;

    half_period = 10000 / frequency * 100 / 2; // 1us base

    max_count = duration_ms * 1.0 / half_period * 1000;

    unsigned int delay_clock_ = half_period / 1.08;

    unsigned int i;

    // printf_fast("start beep\nhalf_period: %dus\nmax_count: %d\ndelay_clock: %d\n", half_period, max_count, delay_clock_);

    for (i = 0; i < max_count; i++)
    {
        BEEP = !BEEP;
        delay_clock(delay_clock_);
    }

    // printf_fast("beep complete.");
}



void clock_beep_loop(unsigned int duration_ms, unsigned int frequency)
{
    // 采用监听TF2的方式, 不用中断处理, 误差为17ms
    unsigned int half_period;

    unsigned int max_count;

    half_period = 1000000.0 / frequency / 2; // 1us base

    max_count =  duration_ms * 1.0 / half_period * 1000;

    unsigned int delay_clock = half_period / 1.08;

    init_T2(0xffff - delay_clock + 1);
    
    TR2 = 1;
    while (max_count-- > 0)
    {
        while(!TF2);
        BEEP = !BEEP;
        TF2 = 0;
    }

    TR2 = 0;
}


void clock_beep(unsigned int duration_ms, unsigned int frequency)
{
    // 在主程序中delay, 在中断中beep, 误差为30ms
    unsigned int half_period;


    half_period = 1000000.0 / frequency / 2; // 1us base

    unsigned int delay_clock = half_period;

    init_T2(0xffff - delay_clock + 1);
    ET2 = 1;
    EA = 1;
    
    // printf_fast("start beep\ninput_frequency: %d\nhalf_period: %dus\ndelay_clock: %d\n", frequency, half_period, delay_clock);
    TR2 = 1;
    delay(duration_ms);
    TR2 = 0;
    // printf_fast("beep complete.");
}

void time2_routine() __interrupt(5)
{
    BEEP = !BEEP;
    TF2 = 0;
}