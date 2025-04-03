#ifndef __DELAY_H__
#define __DELAY_H__
#include <REGX52.H>
#include "delay.h"

void delay(unsigned int);
unsigned char get_bit_value(unsigned int number, unsigned char bit_position);

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
