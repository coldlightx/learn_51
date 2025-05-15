#include <mcs51reg.h>
#include <stdio.h>
#include "timer.h"
#include "delay.h"
#include "serial_log.h"

SBIT(DA, 0xA0, 1);

#define COUNTER_MAX 100

unsigned int timer_run_times = 0;
unsigned int timer_threshold = 0;


void delay_600us()
{
    unsigned char i, j;
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}


void show_timer_run_times()
{
    EA = 0;
    printf_fast("timer run times: %d\n", timer_run_times);
    timer_run_times = 0;
    EA = 1;
}

void main(void)
{
    unsigned char key = 0;
    
    init_T2(0xFFA4); // 100us

    while (1)
    {
        for (unsigned char i = 0; i <= COUNTER_MAX + 1; i++)
        {
            timer_threshold = i;
            delay(10);
        }

        for (unsigned char i = 0; i <= COUNTER_MAX; i++)
        {
            timer_threshold = COUNTER_MAX - i;
            delay(10);
        }

    }
}

SBIT(TF2, 0xc8, 7);

void timer2_routine() __interrupt(5)
{
    static unsigned int timer_counter = 0;

    if (timer_counter++ > COUNTER_MAX)
        timer_counter = 0;
    
    if (timer_counter < timer_threshold)
        DA = 1;
    else
        DA = 0;

    TF2 = 0;
}