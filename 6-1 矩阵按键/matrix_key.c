#include <REGX52.H>
#include <math.h>
#include "delay.h"

unsigned char nearest_non_zero_bit(unsigned char number)
{
    unsigned char bit_position = 8;
    int i;

    for (i = 0; i < 8; i++)
    {
        if (get_bit_value(number, i))
        {    
            bit_position = i;
            return bit_position;
        }
    }
    return bit_position;
}

unsigned char get_matrix_key()
{
    int col, row;

    unsigned char key_number = 0, triggered_bit_position = 0;
    P1 = 0xF0;
    for (col = 0; col < 4; col++)
    {
        P1 = ~(0x08 >> col);
        
        // 0~7
        triggered_bit_position = nearest_non_zero_bit(~P1 & 0xF0);
        if (triggered_bit_position > 7)
            continue;

        row = 7 - triggered_bit_position;
        DEBOUNCE(P1, triggered_bit_position, 0);

        if (row>=0 && row <= 3)
        {
            key_number = 4 * row + 1 + col;
            return key_number; // 扫描到首个已按下的按键之后直接返回
        }
    }
    return key_number;
}

