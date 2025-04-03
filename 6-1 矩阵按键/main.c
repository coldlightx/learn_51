#include <REGX52.H>
#include <math.h>
#include "LCD1602.h"
#include "matrix_key.h"



void main()
{
    int key_number=0;
    LCD_Init();
    while (1)
    {
        key_number = get_matrix_key();
        if (key_number)
            LCD_ShowNum(1, 1, key_number, 3);
    }

}
