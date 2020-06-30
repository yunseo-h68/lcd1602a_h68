# lcd1602a_h68

A simple library useful for using lcd1602a

## Install

1. Install the library first.
2. Copy the files in the lib folder.
3. Paste and use in your avr project folder.

```bash
$ git clone https://github.com/ga-mang/lcd1602a_h68.git
```

## Example

See `lib/lcd1602a_h68.h` for more information on how to use it.

- [Example 1](#example-1)
- [Example 2](#example-2)
- [Example 3](#example-3)

### Example 1

```c
// example/main.c
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
```

#### Execution result

[![example](https://img.youtube.com/vi/NikXlFZK3_U/0.jpg)](https://youtu.be/NikXlFZK3_U)

### Example 2

```c
// example2/main.c
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
```

#### Execution result

[![example 2](https://img.youtube.com/vi/667VD7jT_yA/0.jpg)](https://youtu.be/667VD7jT_yA)

### Example 3

```c
// example3/main.c
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602a_h68.h"

int main(void)
{
	struct lcd1602a_port port = {&DDRC, &DDRC, &PORTC, &PORTC};

	set_lcd_bit(4);
	set_lcd_port(port);
	lcd_init(LCD_ROWS_MAX, LCD_COLS_MAX);

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
```

#### Execution result

[![example 2](https://img.youtube.com/vi/8J4c6GphW0o/0.jpg)](https://youtu.be/8J4c6GphW0o)
