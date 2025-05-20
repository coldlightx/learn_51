#if !defined(__TIME0_H__)
#define __TIME0_H__

void Timer0_Reg_Init(void);
void Timer0_Init(void);		//1毫秒@11.0592MHz
void init_T2(unsigned int init_value);
void timer0_inner_counter_init();
void timer0_inner_counter_start();
void timer0_inner_counter_stop();
void timer0_inner_counter_restart();
unsigned int timer0_inner_counter_get_time();

#endif // __TIME0_H__
