nasm -f elf32 src/kernel/kernel.asm -o kasm.o
gcc -fno-stack-protector -m32 -c src/kernel/kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
mv kernel build/boot/kernel.bin
grub-mkrescue -o build.iso build
rm kasm.o kc.o
qemu-system-i386 -m 40M -cdrom build.iso
