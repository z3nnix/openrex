#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "keymap.h"

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



void scanf(char *buffer, int max_length) {
    int index = 0;
    int current_loc_backup = current_loc; // Save current cursor position

    while (index < max_length - 1) { // Leave space for the null terminator
        char c = __getch(); // Read a character
        
        if (c == '\n') { // If Enter is pressed
            break; // Exit the loop
        }

        if (c == '\b') { // If Backspace is pressed
            if (index > 0) { // Check if there is something to delete
                index--; // Decrease index
                current_loc--; // Move to the previous position

                // Remove the last character from the screen
                vidptr[current_loc * 2] = ' '; // Clear the current position
                vidptr[current_loc * 2 + 1] = 0x07; // Set color (white on black)

                continue; // Go to the next iteration of the loop
            }
            continue; // If nothing to delete, continue the loop
        }

        if ((unsigned char)c < sizeof(keymap)) { 
            c = keymap[(unsigned char)c]; // Convert code to character
            
            if (c != '\0' && index < max_length - 1) { // Check for invalid character and space for new character
                buffer[index++] = c; // Save character in the array

                // Clear the current position for the new character
                vidptr[current_loc * 2] = ' '; // Clear the current position
                vidptr[current_loc * 2 + 1] = 0x07; // Set color (white on black)

                // Print the current character on the screen
                vidptr[current_loc * 2] = c; // Print new character
                vidptr[current_loc * 2 + 1] = 0x07; // Set color (white on black)

                current_loc++; // Move to the next cursor position
                
                // If reached the end of the line, move to the next line
                if (current_loc % COLUMNS_IN_LINE == 0) {
                    current_loc += COLUMNS_IN_LINE; // Move to the next line
                    current_loc -= COLUMNS_IN_LINE; // Return cursor to start of next line (this line should be removed)
                    current_loc += COLUMNS_IN_LINE; // Correctly set cursor to next line start
                }

                // Ensure that we do not exceed screen bounds
                if (current_loc >= SCREENSIZE / BYTES_FOR_EACH_ELEMENT) {
                    current_loc = SCREENSIZE / BYTES_FOR_EACH_ELEMENT - 1; // Prevent overflow
                    scroll(); // Optionally scroll if needed
                }
            }
        }
    }

    buffer[index] = '\0'; // Terminate string with a null character

    current_loc = current_loc_backup; // Restore cursor position after input
}
