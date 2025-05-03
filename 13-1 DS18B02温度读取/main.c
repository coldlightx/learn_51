#include <mcs51reg.h>
#include <stdio.h>
#include "LCD1602.h"
#include "delay.h"
#include "DS18B20.h"
#include "serial_log.h"


void display_temperature(float temperature)
{
    int int_part;
    int decimal_part;

    printf_fast_f("input temperature is %.4f\n", temperature);

    if (temperature < 0)
    {
        temperature = -temperature;    
        LCD_ShowChar(2, 1, '-');
    }
    else
    {
        LCD_ShowChar(2, 1, ' ');
    }

    int_part = temperature;
    decimal_part = ((long) (temperature * 10000)) % 10000;

    LCD_ShowNum(2, 2, temperature, 3);
    LCD_ShowChar(2, 5, '.');
    LCD_ShowNum(2, 6, decimal_part, 4);
}


void main()
{

    LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");

    DS18B20_convert_temperature();
    delay(500);
    
    while (1)
    {
        DS18B20_convert_temperature();
        display_temperature(DS18B20_read_temperature());
    }
    
}