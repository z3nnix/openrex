#include "idt.c"
#include "../rlibc/stdio.h"
#include "../rlibc/time.h"

void kmain(void) {
	const char *logo[7] = {
		" ______   .______    _______ .__   __.     .______       _______ ___   ___ ",
		" /  __  %  |   _  %  |   ____||  % |  |    |   _  %     |   ____|%  % /  / ",
		"|  |  |  | |  |_)  | |  |__   |   %|  |    |  |_)  |    |  |__    %  V  /  ",
		"|  |  |  | |   ___/  |   __|  |  . `  |    |      /     |   __|    >   <   ",
		"|  `--'  | |  |      |  |____ |  |%   |    |  |%  %----.|  |____  /  .  %  ",
		" %______/  | _|      |_______||__| %__|    | _| `._____||_______|/__/ %__% ",
		"                                           - current version: v0.1 indev"
	};
	
	int i = 0;
	while(i < 7) {
		println(logo[i]);
		i++;
	}
	newline();
	return;
}
