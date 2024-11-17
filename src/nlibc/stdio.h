#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

unsigned int current_loc = 0;

char *vidptr = (char*)0xb8000;

void clearscreen(void) {
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}

void scroll() {
	clearscreen();
   	unsigned int i;
    	for (i = current_loc; i < SCREENSIZE; i++) {
       		vidptr[i - current_loc] = vidptr[i];
    	}
    	
	current_loc = 0;
}

void print(const char *str, int color) {
	unsigned int i = 0;
	if (current_loc >= SCREENSIZE) {
		scroll();
	}

	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = color;
	}

	/* colors numbers:
	 		0  - black
			1  - blue
			2  - green
			3  - cyan
			4  - red
			5  - purple
			6  - brown
			7  - gray
			8  - dark gray
			9  - light blue
			10 - light green
			11 - light cyan
			12 - light red
			13 - light purple
			14 - yellow
			15 - white
	 */
}

void newline(void) {
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}


void println(const char *str, const int color) {
	print(str,color);
	newline();
}

char __getch() {
	char symbol;
	while (1) {
		if ((port_byte_in(0x64) & 0x01) == 1) {
			symbol = port_byte_in(0x60);
			if (symbol > -1) {
				return symbol;
			}
		}
	}

	
	return 0;
}


void its(int32_t i, uint8_t base, char *buf) {
	bool negative = false;

	if(i < 0) {
		negative = true;
		i *= -1;
	}

	int32_t index = 0;

	do {
		int32_t remainder = i % base;

		buf[index++] =
				(remainder > 9) ? (remainder - 10) + 'A' : remainder + '0';
		i /= base;
	} while (i > 0);
	
	if(negative) { buf[index++] = '-'; }

	buf[index] = '\0';
}
