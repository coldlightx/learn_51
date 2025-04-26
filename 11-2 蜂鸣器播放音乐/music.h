
#if !defined(__MUSIC_H__)
#define __MUSIC_H__

#define L1_FREQ 262

#define L1 0
#define L1H 1
#define L2 2
#define L2H 3
#define L3 4
#define L4 5
#define L4H 6
#define L5 7
#define L5H 8
#define L6 9
#define L6H 10
#define L7 11

#define M1 12
#define M1H 13
#define M2 14
#define M2H 15
#define M3 16
#define M4 17
#define M4H 18
#define M5 19
#define M5H 20
#define M6 21
#define M6H 22
#define M7 23


#define H1 24
#define H1H 25
#define H2 26
#define H2H 27
#define H3 28
#define H4 29
#define H4H 30
#define H5 31
#define H5H 32
#define H6 33
#define H6H 34
#define H7 35

#define _NOP 0xFE
#define STOP 0xFF


#define SPEED 600


void play_music(unsigned char (*arr)[2], unsigned char mode);

#endif // __MUSIC_H__
