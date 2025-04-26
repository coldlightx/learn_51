#if !defined(__BUZZER_H__)
#define __BUZZER_H__

void beep(unsigned int duration_ms, unsigned int frequency);
void clock_beep_loop(unsigned int duration_ms, unsigned int frequency);
void clock_beep(unsigned int duration_ms, unsigned int frequency);

void time2_routine() __interrupt(5);


#endif // __BUZZER_H__
