#include "idt.c"
#include "../rlibc/stdio.h"
#include "../rlibc/time.h"
#include "../rlibc/font.h"
#include "../rinit/rinit.c"

void kmain(void) {
	rinit(1);
	rinit(2);
	return;
}
