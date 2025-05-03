#if !defined(__ONE_WIRE_H_)
#define __ONE_WIRE_H_

unsigned char OneWire_start(void);
void OneWire_send_bit(unsigned char bit);
unsigned char OneWire_receive_bit();
void OneWire_send_byte(unsigned char byte);
unsigned char OneWire_receive_byte(void);

#endif // __ONE_WIRE_H_
