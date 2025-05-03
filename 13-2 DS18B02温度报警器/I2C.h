#if !defined(__I2C_H_)
#define __I2C_H_

void I2C_start(void);
void I2C_stop(void);
unsigned char I2C_send_byte(unsigned char byte);
unsigned char I2C_receive_byte(void);
void I2C_send_ACK(unsigned char ack);
unsigned char I2C_receive_ACK(void);


#endif // __I2C_H_
