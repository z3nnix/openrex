#include "idt.c"
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "../nlibc/stdio.h"
#include "../nlibc/time.h"

void kmain(void) {
	while(1) {
		println("NovariaOS", 7);
		println("test", 7);
		sleep(2);
	}
}
