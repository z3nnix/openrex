void sleep(const int count) {
	int x = 0;
	
	while(x != count) {
		asm volatile (
			"mov $1000000, %ecx\n"
			"1:\n"
			"rep nop\n"
			"loop 1b\n"
		);
		x++;
	}
}
