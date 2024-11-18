#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "keymap.h"  // Make sure the keymap is configured correctly

unsigned int current_loc = 0;  // Current position in video memory
char *video = (char*)0xb8000;   // Address of VGA video memory

void terminal_set_cursor(int x, int y) {
    uint16_t pos = y * COLUMNS_IN_LINE + x; // Corrected position calculation
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

// Clear the screen
void clearscreen(void) {
    unsigned int i = 0;
    while (i < SCREENSIZE) {
        video[i++] = ' ';  // Fill the screen with spaces
        video[i++] = 0x07; // Text color (white on black)
    }
    current_loc = 0;  // Reset cursor position
    terminal_set_cursor(0, 0); // Set cursor to top left
}

// Scroll the screen
void scroll() {
    for (unsigned int i = COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < SCREENSIZE; i++) {
        video[i - COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT] = video[i];
    }
    for (unsigned int i = SCREENSIZE - COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT; i < SCREENSIZE; i += 2) {
        video[i] = ' ';  // Clear the last line
        video[i + 1] = 0x07;  // Text color
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
        video[current_loc++] = str[i++];  // Character
        video[current_loc++] = color;      // Character color
        
        // Update cursor position after printing each character
        int x = (current_loc / BYTES_FOR_EACH_ELEMENT) % COLUMNS_IN_LINE;
        int y = (current_loc / BYTES_FOR_EACH_ELEMENT) / COLUMNS_IN_LINE;
        terminal_set_cursor(x, y);
    }
}

// Move to the next line
void newline(void) {
    unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
    current_loc += (line_size - current_loc % line_size);
    if (current_loc >= SCREENSIZE) {
        scroll();
    }
    
    // Update cursor position after moving to a new line
    int x = (current_loc / BYTES_FOR_EACH_ELEMENT) % COLUMNS_IN_LINE;
    int y = (current_loc / BYTES_FOR_EACH_ELEMENT) / COLUMNS_IN_LINE;
    terminal_set_cursor(x, y);
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

void scanf(char *buffer, int max_length) {
    int index = 0;

    while (index < max_length - 1) {  // Leave space for the terminating '\0'
        char c = __getch();

        if ((unsigned char)c < sizeof(keymap)) {
            c = keymap[(unsigned char)c];  // Map the key code to a character
            if (c != '\0') {  // Ignore unsupported characters
                if (c == '\n') {  // Enter key pressed
                    break;  // End input
                }

                if (c == '\b') {  // Backspace key pressed
                    if (index > 0) {
                        index--; // Decrease index to ignore the last character
                        current_loc -= 2; // Move back to the previous character on screen
                        video[current_loc] = ' ';  // Remove character from screen
                        video[current_loc + 1] = 0x07; // Restore background color

                        // Update cursor position after backspace
                        int x = (current_loc / BYTES_FOR_EACH_ELEMENT) % COLUMNS_IN_LINE;
                        int y = (current_loc / BYTES_FOR_EACH_ELEMENT) / COLUMNS_IN_LINE;
                        terminal_set_cursor(x, y);
                    }
                } else {  
                    buffer[index++] = c; 
                    video[current_loc++] = c;  
                    video[current_loc++] = 0x07;

                    // Update cursor position after printing each character
                    int x = (current_loc / BYTES_FOR_EACH_ELEMENT) % COLUMNS_IN_LINE;
                    int y = (current_loc / BYTES_FOR_EACH_ELEMENT) / COLUMNS_IN_LINE;
                    terminal_set_cursor(x, y);
                }
            }
        }
    }

    buffer[index] = '\0';  
    newline();
}
