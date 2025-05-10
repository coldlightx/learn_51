#if !defined(__UART_H__)
#define __UART_H__

void UART_Init(); // 28800bps@11.0592MHz
void UART_send(unsigned char byte);

#endif // __UART_H__
