#if !defined(__SPI_H__)
#define __SPI_H__

void spi_select();
void spi_send_byte(unsigned char data);
unsigned char spi_receive_byte();
unsigned int spi_receive_double_byte();
void spi_unselect();

#endif // __SPI_H__
