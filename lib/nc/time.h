// Function sleep takes an integer count and creates a delay
void sleep(const int count) {
    // Initialize counter x, which will track the number of iterations
    int x = 0;

    // Loop executes until x equals count
    while(x != count) {
        // Inline assembly code to create a delay
        asm volatile (
            // Load the value 1,000,000 into the ECX register
            "mov $1000000, %ecx\n"
            "1:\n"          // Label for the start of the loop
            "rep nop\n"     // Repeat the "no operation" (NOP)
            "loop 1b\n"     // Decrement ECX and continue from label 1 until ECX is zero
        );
        // Increment counter x by 1 after the assembly code finishes
        x++;
    }
}