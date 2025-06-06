#include <mcs51reg.h>

void int0_init()
{
    IT0 = 1;
    IE0 = 0;
    EX0 = 1;
    EA = 1;
    PX0 = 1;
}


/*
void int0_routine() __interrupt(0)
{
}
*/
