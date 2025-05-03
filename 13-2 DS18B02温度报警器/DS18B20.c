#include <stdio.h>
#include "one_wire.h"
#include "serial_log.h"


// ROM command
#define SEARCH_ROM 0xF0
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SKIP_ROM 0xCC
#define ALARM_SEARCH 0xEC

// functional command
#define CONVERT_TEMPERATURE 0x44
#define WRITE_SCRATCHPAD 0x4E
#define READ_SCRATCHPAD 0xBE
#define COPY_SCRATCHPAD 0x48
#define RECALL_E2 0xB8
#define READ_POWER_SUPPLY 0xB4

void DS18B20_convert_temperature()
{
    OneWire_start();
    OneWire_send_byte(SKIP_ROM);
    OneWire_send_byte(CONVERT_TEMPERATURE);
}


float DS18B20_read_temperature()
{

    unsigned char LSB=0, MSB=0;

    int temp = 0;

    float temperature = 0;

    OneWire_start();
    OneWire_send_byte(SKIP_ROM);
    OneWire_send_byte(READ_SCRATCHPAD);

    LSB = OneWire_receive_byte();
    MSB = OneWire_receive_byte();

    temp |= (MSB << 8);
    temp |= LSB;

    temperature = temp / 16.0;

    return temperature;
}