
#include <p18cxxx.h>   /* C18 General Include File */

// LCD.H
void lcd_init();
void lcd_goto(unsigned char pos);
void lcd_puts(const char * s);
void lcd_putch(char c);
void lcd_clear(void);

