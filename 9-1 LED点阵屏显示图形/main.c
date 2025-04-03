#include <REGX52.H>
#include "delay.h"
#include "MatrixLCD.h"


void main()
{
    unsigned char cols[] = {0x3C, 0x42, 0xA9, 0x85, 0x85, 0xA9, 0x42, 0x3C};

    while (1)
    {
        matrix_led_show(cols, 8);
    }
}
