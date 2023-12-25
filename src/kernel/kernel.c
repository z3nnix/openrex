#include "../rlibc/stdio.h"

void kmain(void) {
	clearscreen();
	println(":: boot..");
	println(":: kernel is start.");
	newline();
	const char *logo[7] = {
		" ______   .______    _______ .__   __.     .______       _______ ___   ___ ",
		" /  __  %  |   _  %  |   ____||  % |  |    |   _  %     |   ____|%  % /  / ",
		"|  |  |  | |  |_)  | |  |__   |   %|  |    |  |_)  |    |  |__    %  V  /  ",
		"|  |  |  | |   ___/  |   __|  |  . `  |    |      /     |   __|    >   <   ",
		"|  `--'  | |  |      |  |____ |  |%   |    |  |%  %----.|  |____  /  .  %  ",
		" %______/  | _|      |_______||__| %__|    | _| `._____||_______|/__/ %__% ",
		"                                         - by https://github.com/setscript"
	};
	
	int i = 0;
	while(i < 7) {
		println(logo[i]);
		i++;
	}
	newline();
	return;
}
