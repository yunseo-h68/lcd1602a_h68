# lcd1602a_h68

A simple library useful for using lcd1602a

## Install

1. Install the library first.
2. Copy the files in the lib folder.
3. Paste and use in your avr project folder.

```bash
$ git clone https://github.com/ga-mang/lcd1602a_h68.git
```

## Example of using

See `lib/lcd1602a_h68.h` for more information on how to use it.

```c
// example/main.c
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602a_h68.h"

int main(void)
{
	struct lcd1602a_port port = {&DDRE, &DDRE, &PORTE, &PORTE};

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

### Execution result

[![example](https://img.youtube.com/vi/NikXlFZK3_U/0.jpg)](https://youtu.be/NikXlFZK3_U)
