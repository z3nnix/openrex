# OpenREX
> a simple OS designed to put osdev knowledge into practice
## How to contribute?
To contribute to the development of OpenREX, you should follow the following points:
### Step 1:
Clone this repository and then make any changes.
### Step 2:
Submit a pull-request.
> After these steps, I'll review your pull request and accept

# How to compile?
You must download the following tools: ``qemu``, ``gcc``, ``nasm``.
Next, you need to create a ``build.sh`` file and upload the following content there:
```shell
nasm -f elf32 kernel.asm -o kasm.o
gcc -fno-stack-protector -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
rm kasm.o kc.o
```
> This file must be run from the ``src/kernel`` directory.
after a successful compilation to run OpenREX You need to write the following command in the terminal:
```shell
qemu-system-i386 -m 10M -kernel kernel -name openrex
```
> 10M is the maximum value that the OS may need.

> [!WARNING]
> It is **not** recommended to run the current operating system on real hardware, since at the moment the operating system is only a project for applying knowledge in the field of ``osdev`` in practice. The OS can also **maybe** possible only run on machines with ``x32`` processors.

# LICENSE
```

```