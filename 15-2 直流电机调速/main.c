#include <mcs51reg.h>
#include <stdio.h>
#include "timer.h"
#include "key.h"
#include "lcd.h"
#include "serial_log.h"
#include "delay.h"

SBIT(MOTOR, 0x90, 0);

#define COUNTER_MAX 100
unsigned int timer_counter = 0;
unsigned int timer_threshold = 0;

unsigned char speed = 0;


void operate_for_key(unsigned char key)
{

    switch (key)
    {
    case 1:
        speed++;
        break;
    
    case 2:
        speed--;
        break;

    default:
        return;
    }

    speed %= 4;

    switch (speed)
    {
    case 0:
        timer_threshold = 0;
        break;
    
    case 1:
        timer_threshold = 50;
        break;
    
    case 2:
        timer_threshold = 75;
        break;

    case 3:
        timer_threshold = 100;
        break;

    default:
        break;
    }

    lcd_display_number(8, speed);
}

void main(void)
{
    unsigned char key = 0;
    
    Timer0_Init();
    init_T2(0xFFF7); // 10us
    
    lcd_display_number(8, speed);
    
    while (1)
    {
        operate_for_key(get_key());
    }
}


void timer0_routine() __interrupt(1)
{
    static unsigned int key_counter = 0, lcd_counter = 0;

    Timer0_Reg_Init();

    if (lcd_counter++ >= 1){
        lcd_counter = 0;
        lcd_loop();
    }
    
    if (key_counter++ >= 20)
    {
        key_counter = 0;
        key_loop();
    }

}


void time2_routine() __interrupt(5)
{

    static unsigned int timer_counter = 0;
    if (timer_counter++ > COUNTER_MAX)
        timer_counter = 0;
    
    if (timer_counter < timer_threshold)
        MOTOR = 1;
    else
        MOTOR = 0;

    TF2 = 0;

}