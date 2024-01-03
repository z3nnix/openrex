#include "idt.c"
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "../rlibc/stdio.h"
#include "../rlibc/time.h"
#include "../rinit/rinit.c"

void kmain(void) {
	clearscreen();
	rinit(1);
	rinit(2);
	
	return;
}

