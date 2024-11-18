#include "idt.c"
#include "../nlibc/stdio.h"
#include "../nlibc/time.h"
#include "../nlibc/stdbool.h"
#include "../nlibc/stdlib.h"


void kmain(void) {
	while(true) {
		int randColor = rand(0, 15);

		// println("Привет, Россия!", 15);

		println("NovariaOS", randColor);
		sleep(1);
	}
}