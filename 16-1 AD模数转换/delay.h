#ifndef __DELAY_H__
#define __DELAY_H__

void delay(unsigned int);
void delay_n10us(unsigned int n);
void delay_clock(unsigned int us);
void delay_n100us(unsigned char n);
unsigned char get_bit_value(unsigned int number, unsigned char bit_position);
unsigned char nearest_non_zero_bit(unsigned char number);


/*
	@brief 按键消抖
	@param reg 寄存器地址
	@param bit_position 位地址 0~7
	@param status 按键按下时, 寄存器位的值 0或者1
	@retval 无
*/
#define DEBOUNCE(reg, bit_position, status)\
{\
	delay(20);\
	while(bit_position <= 7 && get_bit_value(reg, bit_position) == status);\
	delay(20);\
}\

#endif
