#include <REGX52.H>
#include <math.h>
#include "LCD1602.h"
#include "matrix_key.h"


void main()
{
    int key_number=0, count=0;
    unsigned int password = 0;
    LCD_Init();

    LCD_ShowString(1, 1, "Password:");
    LCD_ShowNum(2, 1, password, 4);
    while (1)
    {
        key_number = get_matrix_key();
        if (!key_number)
            continue;
        
        if (key_number <= 10 && count < 4)
        {
            password *= 10;
            password += key_number%10;
            count++;

            LCD_ShowNum(2, 1, password, 4);
        }

        
        switch (key_number)
        {
        case 11: // confirm
            if (password == 2345)
                LCD_ShowString(1, 13, "OK! ");
            else
                LCD_ShowString(1, 13, "ERR!");
            password = 0;
            count = 0;
            LCD_ShowNum(2, 1, password, 4);
            break;
        
        case 12: // cancel
            password = 0;
            count = 0;
            LCD_ShowNum(2, 1, password, 4);
            LCD_ShowString(1, 13, "    ");
            break;

        default:
            break;
        }
    }

}
