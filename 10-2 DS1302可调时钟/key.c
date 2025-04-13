#include <8052.h>
#include "delay.h"


unsigned char get_key()
{
    unsigned char key_number = 0, bit_position=0;
    bit_position = nearest_non_zero_bit(~P3 & 0x0F);

    if (bit_position < 8)
    {
        DEBOUNCE(P3, bit_position, 0);
        key_number = bit_position + 1;
    }

    if (key_number > 4)
        key_number = 0;

    // 将按键调整一下
    if (key_number == 1)
        key_number = 2;
    else if (key_number == 2)
        key_number = 1;
    
    return key_number;
}