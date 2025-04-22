#include <mcs51reg.h>
#include <stdio.h>
#include "delay.h"
#include "serial_log.h"


#define BEEP P2_5


SFR(T2CON, 0xc8);
SFR(T2MOD, 0xc9);
SFR(RCAP2L, 0xca);
SFR(RCAP2H, 0xcb);
SFR(TL2, 0xcc);
SFR(TH2, 0xcd);

SBIT(TF2, 0xc8, 7);
SBIT(TR2, 0xc8, 2);

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

    printf_fast("start beep\nhalf_period: %dus\nmax_count: %d\ndelay_clock: %d\n", half_period, max_count, delay_clock_);

    for (i = 0; i < max_count; i++)
    {
        BEEP = !BEEP;
        delay_clock(delay_clock_);
    }

    printf_fast("beep complete.");
}



void clock_beep(unsigned int duration_ms, unsigned int frequency)
{
    unsigned int half_period;

    unsigned int max_count;

    half_period = 10000 / frequency * 100 / 2; // 1us base

    max_count =  duration_ms * 1.0 / half_period * 1000;

    unsigned int delay_clock = half_period / 1.08;

    init_T2(0xffff - delay_clock + 1);
    
    printf_fast("start beep\nhalf_period: %dus\nmax_count: %d\ndelay_clock: %d\n", half_period, max_count, delay_clock);

    TR2 = 1;
    while (max_count-- > 0)
    {
        while(!TF2);
        BEEP = !BEEP;
        TF2 = 0;
    }

    TR2 = 0;
    printf_fast("beep complete.");
}