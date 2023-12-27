void rinit(const int mode) {
	if (mode == 0) {
		println(":: rinit works.",15);
	} else if(mode == 1) {
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
		println(logo[i],15);
		i++;
	}
	i = 0;
	} else if(mode == 2) {
		const char *logs[3] = {
			":: Kernel running.",
			":: IDT loaded.",
			":: Rlibc loaded.",
		};

		int i = 0;
		while(i < 3) {
			println(logs[i],15);
			sleep(1);
			i++;
		}
		i = 0;
	} else {
		println(":: unknown mode.",15);
	}

}
