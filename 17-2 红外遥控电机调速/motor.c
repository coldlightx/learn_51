#include <mcs51reg.h>
#include <stdio.h>
#include "motor.h"
#include "timer.h"
#include "serial_log.h"
#include "delay.h"

unsigned char timer_threshold = 0;


void motor_init()
{
    // timer2_init(0xFFA4); // 100us
    timer1_init(0xFFA4); // 100us
    motor_set_speed(0);
}


void motor_set_speed(unsigned char speed)
{
    timer_threshold = speed;
}

void timer1_routine() __interrupt(3)
{
    static unsigned char timer_counter = 0;
    // 一定要把对定时器的值重置放在最前面, 使得定时器的初始值总能得到有效重置
    // 1毫秒@11.0592MHz
    TH1 = 0xFF;
    TL1 = 0xA4;
    
    if (timer_counter++ > COUNTER_MAX)
        timer_counter = 0;

    if (timer_counter < timer_threshold)
        MOTOR = 1;
    else
        MOTOR = 0;
}