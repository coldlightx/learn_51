#if !defined(__AT24C02_H_)
#define __AT24C02_H_

void AT24C02_write_byte(unsigned char word_addr, unsigned char data);
unsigned char AT24C02_read_byte(unsigned char word_addr);

#endif // __AT24C02_H_
