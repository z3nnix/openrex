#!/bin/sh
# Assembler compilation
nasm -f elf32 src/kernel/kernel.asm -o kasm.o
# Compile the C file with stack protection disabled and the flag for unexecutable stack.
gcc -I./include -fno-stack-protector -m32 -c src/kernel/kernel.c -o kc.o
# Compose with flag for non-executable stack
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o -z noexecstack
# Move the compiled kernel to the correct directory
mv kernel build/boot/kernel.bin

# Get the current date in YYYY-MM-DD format
DATE=$(date +%Y-%m-%d)

# Create an ISO image with the date in the filename
grub-mkrescue -o "build_${DATE}.iso" build

# Delete temporary files
rm kasm.o kc.o
# Run QEMU with the created ISO image
qemu-system-i386 -m 40M -cdrom "build_${DATE}.iso"
