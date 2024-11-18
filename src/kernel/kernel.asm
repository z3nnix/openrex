bits 32
section .text
        align 4
        dd 0x1BADB002               ; magic
        dd 0x00                     ; flags
        dd - (0x1BADB002 + 0x00)    ; checksum

global port_byte_in
global outb
global start
extern kmain

port_byte_in:
	mov dx, [esp + 4]
	in al, dx
	ret

outb:
	mov dx, [esp + 4]   ; Get the port from the arguments
	mov al, [esp + 8]   ; Get the value from the arguments
	out dx, al          ; Write the value to the port
	ret

start:
	cli                  ; Disable interrupts
	mov esp, stack_space ; Set the stack pointer
	call kmain           ; Call the main function
	hlt                  ; Halt the processor

section .bss
resb 8192              ; 8KB for stack
stack_space:
