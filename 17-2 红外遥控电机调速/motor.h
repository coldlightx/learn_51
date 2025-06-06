#if !defined(__MOTOR_H__)
#define __MOTOR_H__

#define COUNTER_MAX 100

SBIT(MOTOR, 0x90, 0);

void motor_init();
void motor_set_speed(unsigned char speed);

// void timer2_routine() __interrupt(5);
void timer1_routine() __interrupt(3);

#endif // __MOTOR_H__
