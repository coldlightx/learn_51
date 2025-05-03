#include <mcs51reg.h>
#include <stdio.h>
#include "LCD1602.h"
#include "delay.h"
#include "DS18B20.h"
#include "serial_log.h"
#include "key.h"
#include "timer.h"
#include "AT24C02.h"

signed char T_low = 0;
signed char T_high = 0;

void display_temperature(float temperature)
{
    int int_part;
    int decimal_part;

    LCD_ShowString(1, 1, "T:");

    if (temperature < 0)
    {
        temperature = -temperature;
        LCD_ShowChar(1, 3, '-');
    }
    else
    {
        LCD_ShowChar(1, 3, '+');
    }

    int_part = temperature;
    decimal_part = ((long) (temperature * 100)) % 100;

    LCD_ShowNum(1, 4, temperature, 3);
    LCD_ShowChar(1, 7, '.');
    LCD_ShowNum(1, 8, decimal_part, 2);
}

void show_temperature_config()
{
    LCD_ShowString(2, 1, "TH:");
    LCD_ShowSignedNum(2, 4, T_high, 3);
    LCD_ShowString(2, 10, "TL:");
    LCD_ShowSignedNum(2, 13, T_low, 3);
}

void read_temperature_config()
{

    T_high = AT24C02_read_byte(0);
    T_low = AT24C02_read_byte(1);

    if (T_high > 125)
        T_high = 0;

    if (T_low < -55 || T_low >= T_high)
        T_low = T_high - 1;
}

void save_temperature_config()
{
    AT24C02_write_byte(0, T_high);
    AT24C02_write_byte(1, T_low);
}


void operate_for_key(unsigned char key)
{

    if (!key)
        return;

    switch (key)
    {
    case 1:
        T_high++;
        if (T_high >= 125)
            T_high = 125;
        break;
    
    case 2:
        T_high--;
        if (T_high <= T_low)
            T_high++;

        break;
    
    case 3:
        T_low++;

        if (T_low >= T_high)
            T_low--;
            
        break;
        
    case 4:
        T_low--;
        if (T_low <= -55)
            T_low = -55;
        break;

    default:
        break;
    }

    save_temperature_config();
}

/*
    检查温度是否处于正常范围
    Args:
        无
    Return:
        正常返回0, 超出最大值返回1, 低于最小值返回2
*/
unsigned char check_temperature(float temperature)
{
    unsigned char res = 0;
    if (temperature > T_high)
        res = 1;
        
    if (temperature < T_low)
        res = 2;
    
    return res;
}


void show_alarm(float temperature)
{
    LCD_ShowString(1, 12, "OV:");

    switch (check_temperature(temperature))
    {
    case 0:
        LCD_ShowString(1, 12, "     "); // 清空警告内容
        break;
    
    case 1:
        LCD_ShowString(1, 15, "TH");
        break;

    case 2:
        LCD_ShowString(1, 15, "TL");
        break;

    default:
        break;
    }
}



void main()
{

    unsigned char key = 0;

    float temperature = 0;
    Timer0_Init();

    LCD_Init();
    DS18B20_convert_temperature();
    read_temperature_config();
    delay(500);
    
    while (1)
    {
        DS18B20_convert_temperature();
        temperature = DS18B20_read_temperature();
        display_temperature(temperature);
        operate_for_key(get_key());
        show_temperature_config();
        show_alarm(temperature);
    }
    
}



void timer0_routine() __interrupt(1)
{
    static unsigned int counter = 0;
    counter++;
    
    if (counter >= 20)
    {
        counter = 0;
        key_loop();
    }
    Timer0_Reg_Init();
}