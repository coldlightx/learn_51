#include <mcs51reg.h>
#include <stdio.h>
#include "timer.h"
#include "key.h"
#include "lcd.h"
#include "delay.h"
#include "motor.h"
#include "IR.h"
#include "serial_log.h"


void operate_for_command(unsigned char command)
{
    static unsigned char speed = 0;

    switch (command)
    {
    case IR_ZERO:
        speed = 0;
        motor_set_speed(0);
        break;
    
    case IR_ONE:
        speed = 1;
        motor_set_speed(COUNTER_MAX/2);
        break;
    
    case IR_TWO:
        speed = 2;
        motor_set_speed(COUNTER_MAX*0.75);
        break;

    case IR_THREE:
        speed = 3;
        motor_set_speed(COUNTER_MAX);
        break;

    default:
        printf_fast("no match.\n");
        break;
    }

    lcd_display_number_static(8, speed);
}

void main(void)
{
    unsigned char key = 0;
    
    motor_init();
    IR_init();

    lcd_display_number_static(8, 0);

    motor_set_speed(0);

    P3_2 = 1;
    while (1)
    {

        // for (unsigned char i = 0; i < 35; i++)
        // {
        //     P3_2 = !P3_2;
        //     delay(10);
        // }
        
        if (IR_data_received())
        {
            unsigned char command = IR_get_command();
            operate_for_command(command);
        }
    }
}


void timer0_routine() __interrupt(1)
{
    static unsigned int counter = 0;
    Timer0_Reg_Init(); // 一定要把对定时器的值重置放在最前面, 使得定时器的初始值总能得到有效重置

    counter++;
    
    if (counter >= 1000)
    {
        // printf_fast("t0\n");
        P2_1 = !P2_1;
        counter = 0;

        // put your code here
    }
}