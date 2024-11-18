#include "idt.c"
#include "../nlibc/stdio.h"
#include "../nlibc/time.h"
#include "../nlibc/stdbool.h"
#include "../nlibc/stdlib.h"

void kmain() {
    char sometext[MAX_NAME_LENGTH];
    while (true) {
        print("# ", 7);
        scanf(sometext, sizeof(sometext));
        
        if (strlen(sometext) == 0) {
        } else {
            println(sometext, 15);
        }
    }
}
