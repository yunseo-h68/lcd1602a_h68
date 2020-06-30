/*
 * example3.c
 *
 * Created: 2020-06-30 오전 9:12:42
 * Author : Yunseo Hwang
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602a_h68.h"

#define LCD_CHAR_MUSIC 0

int main(void)
{
	uint8_t music[8] = {0x00, 0x0F, 0x09, 0x09, 0x0B, 0x1B, 0x18, 0x00};
	struct lcd1602a_port port = {&DDRC, &DDRC, &PORTC, &PORTC};
	
	set_lcd_bit(4);
	set_lcd_port(port);
	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	
	lcd_create_char(0, music);
	
	lcd_move(0, 0);
	lcd_puts("LCD1602A_H68");
	lcd_move(0, 1);
	lcd_puts("HELLO WORLD!");
	
    while (1) 
    {
		lcd_display_shift_str(LCD_SHIFT_RIGHT, 12);
		_delay_ms(200);
    }
}

