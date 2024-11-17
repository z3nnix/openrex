#include "idt.c"
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "../nlibc/stdio.h"
#include "../nlibc/time.h"
#include "../nlibc/stdlib.h"

void kmain(void) {
	while(1) {
		int randColor = rand(0, 15);

		println("NovariaOS", randColor);
		sleep(1);
	}
}
