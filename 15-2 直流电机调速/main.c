#include <mcs51reg.h>
#include <stdio.h>
#include "timer.h"
#include "key.h"
#include "lcd.h"
#include "serial_log.h"
#include "delay.h"

SBIT(LED, 0xA0, 0);

#define COUNTER_MAX 100
unsigned int timer_counter = 0;
unsigned int timer_threshold = 0;

unsigned char speed = 0;


void operate_for_key(unsigned char key)
{

    printf_fast("key pressed is: %d\n", key);
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
        timer_threshold = 10;
        break;
    
    case 2:
        timer_threshold = 50;
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
    Timer0_Init();
    init_T2(0xFF91); // 10us

    lcd_display_number(8, speed);

    printf_fast("program start.\n");

    while (1)
    {

        unsigned char key = get_key();
        operate_for_key(key);
        // if (key)
        // {
        //     // P2_7 = 1;
        //     // P2_7 = 0;
        //     // delay(10);
        //     // P2_7 = 1;
        //     operate_for_key(key);
        // }

        // P2_7 = 1;

    }
}


void timer0_routine() __interrupt(1)
{
    static unsigned int key_counter = 0, lcd_counter = 0;


    P2_6 = 0;
    if (lcd_counter++ >= 1){
        lcd_counter = 0;
        lcd_loop();
    }
    
    if (key_counter++ >= 20)
    {
        key_counter = 0;
        key_loop();
    }
    
    Timer0_Reg_Init();

    P2_6 = 1;

}


void time2_routine() __interrupt(5)
{

    static unsigned int timer_counter = 0;
    if (timer_counter++ > COUNTER_MAX)
        timer_counter = 0;
    
    if (timer_counter < timer_threshold)
        LED = 0;
    else
        LED = 1;

}