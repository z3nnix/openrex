#include <stdint.h>

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define KERNEL_CS 0x08

#define ENTER_KEY_CODE 0x1C
#define MAX_TEXT_SIZE 1024

#define SYSCALL_INTERRUPT 0x80

extern char port_byte_in(int port);

typedef struct {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_2;
} __attribute__((packed)) idt_entry_t;

__attribute__((section(".data"))) idt_entry_t idt[IDT_SIZE];

extern void system_call_wrapper(void);

void set_idt_entry(int interrupt, void *handler) {
    idt_entry_t *entry = &idt[interrupt];
    uint32_t handler_addr = (uint32_t)handler;
    
    entry->offset_1 = handler_addr & 0xFFFF;
    entry->selector = KERNEL_CS;
    entry->zero = 0;
    entry->type_attr = 0x8E;
    entry->offset_2 = (handler_addr >> 16) & 0xFFFF;
}

void load_idt(void) {
    struct {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) idt_ptr = {
        .limit = (sizeof(idt_entry_t) * IDT_SIZE) - 1,
        .base = (uint32_t)&idt,
    };
    asm volatile ("lidt %0" : : "m"(idt_ptr));
}

void init_syscalls(void) {
    for (int i = 0; i < IDT_SIZE; i++) {
        set_idt_entry(i, 0);
    }
    set_idt_entry(SYSCALL_INTERRUPT, system_call_wrapper);
    load_idt();
}
