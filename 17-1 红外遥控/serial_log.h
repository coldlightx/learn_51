#if !defined(__SERIAL_LOG__)
#define __SERIAL_LOG__

/*
注意:
    printf_fast不能被中断打断, 否则会造成主函数无法再次执行, 当程序中存在中断时
    应该在printf_fast的前后屏蔽中断
*/

int putchar(int c);

#endif // __SERIAL_LOG__
