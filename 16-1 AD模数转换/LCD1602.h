#if !defined(__LCD1602_H__)
#define __LCD1602_H__

void LCD_send_command(unsigned char command);
void LCD_init();
void LCD_show_char(unsigned char row, unsigned char column, char c);
void LCD_show_string(unsigned char row, unsigned char column, char * s);
void LCD_show_number(unsigned char row, unsigned char column, unsigned int number, unsigned char length);
void LCD_show_signed_number(unsigned char row, unsigned char column, int number, unsigned char length);
void LCD_show_hex_number(unsigned char row, unsigned char column, unsigned char number, unsigned char length);
void LCD_show_bin_number(unsigned char row, unsigned char column, unsigned char number, unsigned char length);
void LCD_show_float_number(unsigned char row, unsigned char column, float number, unsigned char length, unsigned char significant_digits);

#endif // __LCD1602_H__
