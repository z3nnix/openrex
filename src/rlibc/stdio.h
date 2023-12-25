unsigned int current_loc = 0;

char *vidptr = (char*)0xb8000;

void clearscreen(void) {
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}

void scroll_up(void) {
	clearscreen();
    unsigned int i;
    for (i = current_loc; i < SCREENSIZE; i++) {
        vidptr[i - current_loc] = vidptr[i];
    }
    current_loc = 0;
}

void print(const char *str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
	
	if (current_loc >= SCREENSIZE) {
        	scroll_up();
	}
}

void newline(void) {
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void println(const char *str) {
	print(str);
	newline();
}
