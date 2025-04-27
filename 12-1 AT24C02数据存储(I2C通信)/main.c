#include <mcs51reg.h>
#include "AT24C02.h"
#include "delay.h"
#include "LCD1602.h"
#include "key.h"

int main(int argc, char const *argv[])
{
    unsigned char key;

    LCD_Init();

    unsigned int number = 0;
    LCD_ShowNum(1, 1, number, 5);
    while (1)
    {
        key = get_key();

        switch (key)
        {
        case 1:
            number++;
            LCD_ShowNum(1, 1, number, 5);
            break;
        
        case 2:
            number--;
            LCD_ShowNum(1, 1, number, 5);
            break;

        case 3:
            AT24C02_write_byte(0, number);
            AT24C02_write_byte(1, number>>8);

            LCD_ShowString(2, 1, "Write OK!");
            delay(1000);
            LCD_ShowString(2, 1, "         ");
            break;

        case 4:
            number = AT24C02_read_byte(0);
            
            // C语言有integer promotion, 当unsigned char数据左移8位时, 会自动提升为16位int类型
            number |= (AT24C02_read_byte(1)<<8);
            LCD_ShowNum(1, 1, number, 5);
            LCD_ShowString(2, 1, "Load OK!");
            delay(1000);
            LCD_ShowString(2, 1, "        ");
            break;

        default:
            break;
        }
    }
    
    return 0;
}
