#include <mcs51reg.h>
#include "delay.h"
unsigned char key_pressed = 0;

unsigned char get_key()
{
    unsigned char tmp = 0;

    if (key_pressed)
    {
        EA = 0;
        tmp = key_pressed;
        // 必须要在key_pressed不为0时再给key_pressed置0
        // 如果当key_pressed无效时, 还给key_pressed置0, 会出现:
        // tmp = 0(key_pressed == 0) 此时主程序中断
        // key_pressed = 2 中断扫描函数扫描并置位, 之后返回主函数
        // key_pressed = 0 主函数置0, 此时按键扫描结果被清除
        // 要解决这个问题, 需要在读取key_pressed和key_pressed复位的前后屏蔽中断, 确保这两个操作的原子性
        // 同时, 仅在key_pressed不为0时屏蔽中断, 尽量减少对全局中断性能的影响
        key_pressed = 0;
        EA = 1;
    }

    return tmp;
}

unsigned char scan_key()
{
    unsigned char key = 0;
    if (!P3_0)
        key = 2;

    if (!P3_1)
        key = 1;

    if (!P3_2)
        key = 3;
    
    if (!P3_3)
        key = 4;
    
    return key;
}


// key模块中断函数扫描入口
void key_loop(void)
{
    static unsigned char last_key, current_key;
    last_key = current_key;
    current_key = scan_key();

    // 检测下降沿
    if (last_key == 0 && current_key > 0)
        key_pressed = current_key;

}