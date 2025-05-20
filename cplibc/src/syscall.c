#include "syscall.h"
#include "posix.h"
#include "stdint.h"
#include "string.h"

_Noreturn void exit(int code) {
    __syscall(SYSCALL_EXIT, code);
    while (1)
        ;
}

int open(const char *path) {
    __syscall(SYSCALL_OPEN, path);
}

int write(int handle, uint8_t *buf, int len) {
    return __syscall(SYSCALL_WRITE, handle, buf, len);
}

int read(int handle, uint8_t *buf, int len) {
    return __syscall(SYSCALL_READ, handle, buf, len);
}

void *mmap(void *addr, size_t length, uint64_t prot, uint64_t flags, int fd, uint64_t offset) {
    return (void *)__syscall6(SYSCALL_MMAP, addr, length, prot, flags, fd, offset);
}

void signal_register(int sig, void (*handler)(void)) {
    __syscall(SYSCALL_SIGNAL, sig, handler);
}

void *arch_prctl(int code, void *addr) {
    return (void *)__syscall(SYSCALL_ARCH_PRCTL, code, addr);
}

void yield() {
    __syscall(SYSCALL_YIELD, 0);
}

void debug_print(char *str) {
    __syscall(SYSCALL_DEBUG_PRINT, str, strlen(str));
}

int cmdline(uint8_t *buf) {
    return __syscall(SYSCALL_CMDLINE, buf);
}
