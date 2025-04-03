#include <REGX52.H>


void UART_Init() // 28800bps@11.0592MHz
{
    SCON = 0x50;
    PCON &= 0x3F;

    TMOD &= 0x0F;
    TMOD |= 0x20;
    TF1 = 0;
    TR1 = 1;

    // TH1 的计算公式:256 -  SYSCLK / 12 / 32 * (2^(SMOD), 波特率倍速为2, 不倍速为1) / 波特率
    TH1 = 0xFF;
    TL1 = 0XFF;

    ET1 = 0; // 禁止计时器中断
    EA = 1;
    ES = 1;
}

void UART_send(unsigned char byte)
{
    SBUF = byte;
    while (TI == 0);
    // 此时TI被置1
    TI = 0; // TI 复位
}

/*
void UART_routine() interrupt 4
{
    unsigned char received;
    if (RI)
    {
        received = SBUF;
        UART_send(received);
        RI = 0;
    }
}
*/