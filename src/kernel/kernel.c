#include "idt.c"

//#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "drivers/vga.c"
#include "drivers/keyboard.c"

#include "fs/ramfs.c"

void kmain() {
    kprint("NovariaOS. 0.0.2 indev build. TG: ", 15);
    kprint("@NovariaOS", 9);
    newline();

//    test_ramfs();
}
