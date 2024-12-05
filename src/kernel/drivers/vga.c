// Print a string with the specified color
void kprint(const char *str, int color) {
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