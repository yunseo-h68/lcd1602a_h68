/*
 * lcd1602a_h68.c
 *
 * Created: 2020-06-25 오후 6:53:53
 *  Author: Yunseo Hwang
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602a_h68.h"

uint8_t lcd_bit;
uint8_t is_lcd_initial = 0;
uint8_t lcd_limit_rows;
uint8_t lcd_limit_cols;
uint8_t lcd_cursor_x = 0;
uint8_t lcd_cursor_y = 0;
struct lcd1602a_port lcd_port;

static uint8_t lcd_port_init();
static uint8_t lcd_data(uint8_t byte);
static uint8_t lcd_command(uint8_t byte);

void set_lcd_port(struct lcd1602a_port port) 
{
	lcd_port.data_ddr = port.data_ddr;
	lcd_port.data_port = port.data_port;
	lcd_port.rsrwe_ddr = port.rsrwe_ddr;
	lcd_port.rsrwe_port = port.rsrwe_port;
}

void set_lcd_bit(uint8_t bit)
{
	lcd_bit = bit;
}

uint8_t lcd_init(uint8_t rows, uint8_t cols)
{	
	lcd_port_init();
	
	lcd_limit_rows = rows - 1;
	lcd_limit_cols = cols;
	
	if (LCD_ROWS_MAX - 1 < lcd_limit_rows) {
		lcd_limit_rows = LCD_ROWS_MAX - 1;
	}
	if (LCD_COLS_MAX < lcd_limit_cols) {
		lcd_limit_cols = LCD_COLS_MAX;	
	}
	
	_delay_ms(30);
	
	if (lcd_bit == 4) {
		lcd_command(0x20);
		_delay_us(39);
	}
	
	lcd_command(0x20 | ((lcd_bit == 8) << 4) | (cols - 1) << 3);
	_delay_us(39);
	lcd_command(0x0C);
	_delay_us(39);
	lcd_command(0x01);
	_delay_ms(1.53);
	lcd_command(0x06);
	_delay_us(39);
	
	lcd_cursor_x = 0;
	lcd_cursor_y = 0;
	is_lcd_initial = 1;
	
	return 0;
}

uint8_t lcd_move(uint8_t x, uint8_t y)
{
	int i;
	
	lcd_cursor_x = x;
	lcd_cursor_y = y;
	
	if (lcd_cursor_x > lcd_limit_rows) {
		lcd_cursor_x = lcd_cursor_x % lcd_limit_rows - 1;
		lcd_cursor_y = 2;
		x = lcd_cursor_x;
		y = lcd_cursor_y;
	}
	
		
	lcd_command(0x02);
	_delay_ms(1.53);
	
	for (i = 0; i < x + (y-1) * 40; i++) {
		lcd_command(0x14);
		_delay_us(39);
	}
	
	return 0;
}

uint8_t lcd_putc(const char c)
{
	lcd_data(c);
	
	lcd_cursor_x++;
	
	if (lcd_cursor_x > lcd_limit_rows) {
		lcd_move(lcd_cursor_x, lcd_cursor_y);
	}
	
	return 0;
}

uint8_t lcd_puts(const char* str)
{
	int i = 0;
	
	for(i = 0; str[i]; i++) {
		lcd_putc(str[i]);
	}
	
	return 0;
}

uint8_t lcd_clear()
{
	lcd_command(0x01);
	_delay_ms(1.53);
	
	lcd_cursor_x = 0;
	lcd_cursor_y = 0;
	return 0;
}

static uint8_t lcd_port_init()
{
	
	*(lcd_port.rsrwe_ddr) |= 0x07;
	*(lcd_port.rsrwe_port) &= ~0x07;
	
	if (lcd_bit == 8) {
		*(lcd_port.data_ddr) = 0xFF;
		*(lcd_port.data_port) = 0x00;
		return 0;
	} else if (lcd_bit == 4) {
		*(lcd_port.data_ddr) |= 0xF0;
		*(lcd_port.data_port) &= ~0xF0;
		return 0;
	}
	
	return -1;
}

static uint8_t lcd_data(uint8_t byte)
{	
	_delay_ms(2);
	
	if (lcd_bit == 8) {
		*(lcd_port.data_port) = byte;
		*(lcd_port.rsrwe_port) &= ~0x03;
		*(lcd_port.rsrwe_port) |= 0x01; 
		_delay_us(1);
		*(lcd_port.rsrwe_port) |= 0x04;
		_delay_us(1);
		*(lcd_port.rsrwe_port) &= ~0x04;
		
		return 0;
	} else if (lcd_bit == 4) {
		*(lcd_port.data_port) &= ~0xf0;	
		*(lcd_port.data_port) |= byte & 0xf0;
		*(lcd_port.rsrwe_port) &= ~0x03;
		*(lcd_port.rsrwe_port) |= 0x01;
		_delay_us(1);
		*(lcd_port.rsrwe_port) |= 0x04;
		_delay_us(1);
		*(lcd_port.rsrwe_port) &= ~0x04;
		
		*(lcd_port.data_port) &= ~0xf0;
		*(lcd_port.data_port) |= (byte << 4) & 0xf0;
		*(lcd_port.rsrwe_port) &= ~0x03;
		*(lcd_port.rsrwe_port) |= 0x01;
		_delay_us(1);
		*(lcd_port.rsrwe_port) |= 0x04;
		_delay_us(1);
		*(lcd_port.rsrwe_port) &= ~0x04;
		
		return 0;
	}
	return -1;
}

static uint8_t lcd_command(uint8_t byte)
{	
	_delay_ms(2);
	
	if (lcd_bit == 8) {
		*(lcd_port.data_port) = byte;
		*(lcd_port.rsrwe_port) &= ~0x03;
		_delay_us(1);
		*(lcd_port.rsrwe_port) |= 0x04;
		_delay_us(1);
		*(lcd_port.rsrwe_port) &= ~0x04;
		
		return 0;
	} else if (lcd_bit == 4) {
		*(lcd_port.data_port) &= ~0xf0;
		*(lcd_port.data_port) |= byte & 0xf0;
		*(lcd_port.rsrwe_port) &= ~0x03;
		_delay_us(1);
		*(lcd_port.rsrwe_port) |= 0x04;
		_delay_us(1);
		*(lcd_port.rsrwe_port) &= ~0x04;
		
		*(lcd_port.data_port) &= ~0xf0;
		*(lcd_port.data_port) |= (byte << 4) & 0xf0;
		*(lcd_port.rsrwe_port) &= ~0x03;
		_delay_us(1);
		*(lcd_port.rsrwe_port) |= 0x04;
		_delay_us(1);
		*(lcd_port.rsrwe_port) &= ~0x04;
		
		return 0;
	}
	
	return -1;
}