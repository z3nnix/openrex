#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "keymap.h"  // Make sure the keymap is configured correctly

unsigned int current_loc = 0;  // Current position in video memory
char *vidptr = (char*)0xb8000;  // Address of VGA video memory

// Clear the screen
void clearscreen(void) {
    unsigned int i = 0;
    while (i < SCREENSIZE) {
        vidptr[i++] = ' ';  // Fill the screen with spaces
        vidptr[i++] = 0x07; // Text color (white on black)
    }
    current_loc = 0;  // Reset cursor position
}

// Scroll the screen
void scroll() {
    for (unsigned int i = COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < SCREENSIZE; i++) {
        vidptr[i - COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT] = vidptr[i];
    }
    for (unsigned int i = SCREENSIZE - COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < SCREENSIZE; i += 2) {
        vidptr[i] = ' ';  // Clear the last line
        vidptr[i + 1] = 0x07;  // Text color
    }
    current_loc -= COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; // Move cursor up
}

// Print a string with the specified color
void print(const char *str, int color) {
    unsigned int i = 0;
    while (str[i] != '\0') {
        if (current_loc >= SCREENSIZE) {
            scroll();  // Scroll if the end of the screen is reached
        }
        vidptr[current_loc++] = str[i++];  // Character
        vidptr[current_loc++] = color;    // Character color
    }
}

// Move to the next line
void newline(void) {
    unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
    current_loc = current_loc + (line_size - current_loc % line_size);
    if (current_loc >= SCREENSIZE) {
        scroll();
    }
}

// Print a string and move to the next line
void println(const char *str, int color) {
    print(str, color);
    newline();
}

// Read a character from the keyboard
char __getch() {
    char symbol;
    while (1) {
        if ((port_byte_in(0x64) & 0x01) == 1) {  // Check for input
            symbol = port_byte_in(0x60);  // Read the character
            return symbol;
        }
    }
}

// Read a string from the keyboard
void scanf(char *buffer, int max_length) {
    int index = 0;

    while (index < max_length - 1) {  // Leave space for the terminating '\0'
        char c = __getch();

          if ((unsigned char)c < sizeof(keymap)) {
            c = keymap[(unsigned char)c];  // Convert key code to character
            if (c != '\0') {  // Ignore unsupported characters
                buffer[index++] = c;
                vidptr[current_loc++] = c;  // Output the character on the screen
                vidptr[current_loc++] = 0x07;
            }
        }

        if (c == '\n') {  // Enter key pressed
            break;
        }

        if (c == '\b') {  // Backspace key pressed
            if (index > 0) {
                index--;
                current_loc -= 2;
                vidptr[current_loc] = ' ';  // Remove the character from the screen
                vidptr[current_loc + 1] = 0x07;
            }
            continue;
        }
    }

    buffer[index] = '\0';  // Terminate the string with a null character
}
