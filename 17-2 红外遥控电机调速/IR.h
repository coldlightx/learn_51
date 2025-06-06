#if !defined(__IR_H__)
#define __IR_H__

#define DELTA 500

// 定义遥控器按键和键码
#define IR_POWER        0x45
#define IR_MODE         0x46
#define IR_MUTE         0x47
#define IR_STOP         0x44
#define IR_PREVIOUS     0x40
#define IR_NEXT         0x43
#define IR_EQ           0x07
#define IR_VOL_MINUS    0x15
#define IR_VOL_PLUS     0x09
#define IR_ZERO         0x16
#define IR_RPT          0x19
#define IR_U_SD         0x0D
#define IR_ONE          0x0C
#define IR_TWO          0x18
#define IR_THREE        0x5E
#define IR_FOUR         0x08
#define IR_FIVE         0x1C
#define IR_SIX          0x5A
#define IR_SEVEN        0x42
#define IR_EIGHT        0x52
#define IR_NINE         0x4A

typedef enum
{
    IDLE, // 空闲状态
    WAIT, // 等待有效指令
    RECEIVE_DATA, // 接收数据
} IRState;


typedef struct IRData
{
    IRState state;

    unsigned char data[4];
    unsigned char write_index;
    unsigned char data_received;

    unsigned char address;
    unsigned char command;

    unsigned char repeat;

    unsigned int start_time; // 记录start信号的持续时间

} IRData;


void IR_init();
unsigned char IR_data_received();
unsigned char IR_get_repeat();
unsigned char IR_get_address();
unsigned char IR_get_command();
void IR_int0_routine() __interrupt(0);


#endif // __IR_H__
