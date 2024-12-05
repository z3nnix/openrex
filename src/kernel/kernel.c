#include "idt.c"

#include "./drivers/keyboard.c"
#include "./drivers/vga.c"

#include <string.h>
#include <stddef.h>

#include "./fs/ramfs.c"

void kmain() {
    print("NovariaOS. 0.0.2 indev build. TG: ", 15);
    println("@NovariaOS", 9);

    test_ramfs();

    while (true) {
        print("# ", 7);
        char sometext[MAX_TEXT_SIZE];
        scanf(sometext, sizeof(sometext));
        
        if (strlen(sometext) == 0) {
            continue;
        }
        
        println(sometext, 15);
    }
}
