#include "idt.c"
#include "../nlibc/stdio.h"
#include "../nlibc/time.h"
#include "../nlibc/stdbool.h"
#include "../nlibc/stdlib.h"

#define MAX_NAME_LENGTH 50

void kmain() {
    char name[MAX_NAME_LENGTH];
    
    clearscreen();
    println("Welcome to the Simple Input Example!", 0x07);

    scanf(name, sizeof(name));
    println("\nYou entered: ", 0x07);

	while(true) {
		println(name, rand(0, 15));
	}
}
