#include "idt.c"
#include "../rlibc/stdio.h"
#include "../rlibc/time.h"
#include "../rinit/rinit.c"

void kmain(void) {
	rinit(1);
	rinit(2);

	println("###",15);
	println("###",1);
	println("###",4);
	return;
}
