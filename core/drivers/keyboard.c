#include <core/drivers/keymap.h>

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