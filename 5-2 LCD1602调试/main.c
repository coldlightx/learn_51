#include <REGX52.H>
#include "LCD1602.h"

void main()
{

    LCD_Init();
    LCD_ShowChar(1, 2, 'A');

    LCD_ShowString(1, 4, "Hello, world!");

    LCD_ShowNum(2, 1, 123, 3);

    // LCD_ShowSignedNum(2, 5, -12, 3);
    // LCD_ShowHexNum(2, 10, 0xAF, 2);

    LCD_ShowBinNum(2, 5, 0xAF, 8);
    while (1)
    {
        
    }
    
}