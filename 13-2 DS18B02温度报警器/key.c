#include <mcs51reg.h>
#include "delay.h"

unsigned char key_pressed = 0;

unsigned char get_key()
{
    unsigned char tmp;
    
    tmp = key_pressed;
    key_pressed = 0;

    return tmp;
}

unsigned char scan_key()
{
    unsigned char key_number = 0, bit_position=0;
    bit_position = nearest_non_zero_bit(~P3 & 0x0F);

    if (bit_position < 8)
        key_number = bit_position + 1;

    if (key_number > 4)
        key_number = 0;

    // 将按键调整一下
    if (key_number == 1)
        key_number = 2;
    else if (key_number == 2)
        key_number = 1;
    
    return key_number;
}


// key模块中断函数扫描入口
void key_loop(void)
{
    static unsigned char last_key, current_key;
    last_key = current_key;
    current_key = scan_key();

    // 检测下降沿
    if (last_key == 0 && current_key > 0)
        key_pressed = current_key;

}