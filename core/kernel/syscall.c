#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define SYS_WRITE 1
#define SYS_EXIT  60


uint32_t syscall_handler(uint64_t syscall_number, uint64_t arg1, uintptr_t arg2, uint64_t arg3) {
    return 0;
}
