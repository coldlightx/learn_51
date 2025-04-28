#include <mcs51reg.h>
#include <stdio.h>
#include "AT24C02.h"
#include "timer.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "AT24C02.h"
#include "serial_log.h"

unsigned char minutes=0, seconds=0;
unsigned int milliseconds=0;
unsigned char running;


void display_time()
{
    display_number(8, minutes/10);
    display_number(7, minutes%10);
    display_number(6, 11);
    display_number(5, seconds/10);
    display_number(4, seconds%10);
    display_number(3, 11);
    display_number(2, milliseconds/100);
    display_number(1, milliseconds%100/10);
}



void operate_for_key(unsigned char key)
{
    switch (key)
    {
    case 1:
        // 开始/暂停
        running = !running;
        break;
    
    
    case 2:
        // 清零
        minutes = 0;
        seconds = 0;
        milliseconds = 0;
        break;

    case 3:
        printf_fast("value saved: minutes: %d, seconds: %d, milliseconds: %d\n", 
            minutes, seconds, milliseconds);
        AT24C02_write_byte(0, minutes);
        AT24C02_write_byte(1, seconds);
        AT24C02_write_byte(2, milliseconds/10);
        AT24C02_write_byte(3, milliseconds%10);
        break;
    
    case 4:
        minutes = AT24C02_read_byte(0);
        seconds = AT24C02_read_byte(1);
        milliseconds = AT24C02_read_byte(2) * 10;
        milliseconds += AT24C02_read_byte(3);
        printf_fast("value readout: minutes: %d, seconds: %d, milliseconds: %d\n", 
            minutes, seconds, milliseconds);
        break;

    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    unsigned char key = 0;

    Timer0_Init();

    while (1)
    {
        key = get_key();
        operate_for_key(key);
        display_time();
    }
    
    return 0;
}

void time_loop()
{
    if (!running)
        return;

    milliseconds += 1;
        
    if (milliseconds >= 1000)
    {
        milliseconds = 0;
        seconds += 1;
    }

    if (seconds >= 60)
    {
        seconds = 0;
        minutes += 1;
    }

    if (minutes >= 60)
    {
        minutes = 0;
    }

}
void timer0_routine() __interrupt(1)
{
    // 1ms 中断一次
    static unsigned int counter_key = 0;
    static unsigned int counter_lcd = 0;
    static unsigned int counter_timer = 0;
    
    Timer0_Reg_Init();
    
    // lcd的扫描必须要放在key扫描的前面, 因为key每20ms扫描一次, 如果key在
    // 前, 会导致lcd闪烁不稳定
    if (counter_lcd++ >= 1)
    {
        counter_lcd = 0;
        lcd_loop();
    }

    if (counter_timer++ >= 1)
    {
        counter_timer = 0;
        time_loop();
    }
    
    if (counter_key++ >= 20)
    {
        counter_key = 0;
        key_loop();
    }


}
