/*
 * example2.c
 *
 * Created: 2020-06-28 오후 2:34:16
 * Author : Yunseo Hwang
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602a_h68.h"

int main(void)
{
	int i = 0, n = 0;
	struct lcd1602a_port port = { &DDRE, &DDRE, &PORTE, &PORTE };
	
	uint8_t heart[2][8] = {
		{0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04,0x00 },
		{0x00, 0x0A, 0x15, 0x11, 0x11, 0x0A, 0x04,0x00 }
	};
	
	set_lcd_bit(4);
	set_lcd_port(port);
	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);
	
	lcd_create_char(0, heart[n]);
	
	for(i = 0; i < 32; i++)
		lcd_putc(0x00);
	
	while (1)
	{
		lcd_create_char(0, heart[n]);
		_delay_ms(1000);
		
		n = !n;
	}
}

