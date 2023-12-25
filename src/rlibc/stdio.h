unsigned int current_loc = 0;
int cooldown = 0; /* Note:
			cooldown is the frequency with which the screen will be
			cleared. at the moment this function does not work.
			 	> view 37-50 line
			*/


char *vidptr = (char*)0xb8000;

void print(const char *str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
}

void clearscreen(void) {
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
	//cooldown == 0; | 12 line
}

/*
void newline(void) {
	if(cooldown = LINES) {
		clearscreen();
		unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
		current_loc = current_loc + (line_size - current_loc % (line_size));
		
		cooldown == 0; //12 line
		cooldown++; // 12 line
	} else {
		unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
		current_loc = current_loc + (line_size - current_loc % (line_size));
		cooldown++; // 12 line	
	}
}
	// view 12 line
*/

void newline(void) {
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void println(const char *str) {
	print(str);
	newline();
}

