#include <math.h>
#include <stdio.h>
#include "serial_log.h"
#include "music.h"
#include "buzzer.h"
#include "delay.h"

unsigned int get_frequency_for_key(unsigned char key)
{
    unsigned int freq = L1_FREQ * powf(2, (key-L1)/12.0);
    // printf_fast("frequency for %d is %d\n", key, freq);
    return freq;
}


/*
    播放arr指定的音乐
    Args:
        arr: 二维数组, 第一列代表键值, 第二列代表音符时长, \
        以16分音符为基准1, 八分音符为2, 四分音符为4, 2分音符为8, 1分音符为16
        STOP为停止标志
    Return:
        无
*/
void play_music(unsigned char (*arr)[2], unsigned char mode)
{
    unsigned char key, duration_number;
    unsigned int duration;
    unsigned int i = 0;

    while (arr[i][0] != STOP)
    {
        
        
        key = arr[i][0];
        duration_number = arr[i][1];
        i++;
        
        duration = SPEED / 4 * duration_number;
        
        if (key == _NOP)
        {
            delay(duration);
            continue;
        }
        
        if (mode == 'G')
        {
            key += 4;
        }

        delay(20);
        
        clock_beep(duration, get_frequency_for_key(key));
    }
}
