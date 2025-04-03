#include <REGX52.H>
#include <INTRINS.H>
#include "timer0.h"
#include "key.h"


unsigned char LED_MODE = 0;
void main()
{
    unsigned char key_number = 0;
    Timer0_Init();

    P2 = 0xFE;
    while (1)
    {
        key_number = get_key();

        switch (key_number)
        {
        case 1: // 左移
            LED_MODE = 0;
            break;
        case 2: // 右移
            LED_MODE = 1;
            break;
        default:
            break;
        }

    }

}

void timer0_routine() interrupt 1
{
    static unsigned int counter = 0;
    counter++;

    if (counter >= 500)
    {
        counter = 0;

        if (LED_MODE == 0)
            P2 = _cror_(P2, 1);
        
        if (LED_MODE == 1)
            P2 = _crol_(P2, 1);

    }
    Timer0_Reg_Init();
}
