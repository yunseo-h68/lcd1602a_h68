/*
 * example.c
 *
 * Created: 2020-06-26 오후 8:02:59
 * Author : Yunseo Hwang
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602a_h68.h"

int main(void)
{
	struct lcd1602a_port port = {&DDRC, &DDRC, &PORTC, &PORTC};
    
	set_lcd_bit(4);
	set_lcd_port(port);
	lcd_init(LCD_ROWS_MAX - 6, LCD_COLS_MAX);
	
	while (1) 
    {
		lcd_puts("12345678901234567890");
		_delay_ms(500);
		lcd_clear();
		_delay_ms(500);
    }
}

