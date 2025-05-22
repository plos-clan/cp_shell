#include "string.h"
#define STB_SPRINTF_IMPLEMENTATION
#include "posix.h"
#include "sprintf.h"
#include "stdio.h"
#include "stdlib.h"

extern int main(int argc, char **argv, char **envp);

#ifdef __cplusplus
extern "C" {
#endif

extern void init_heap();

int stdout;
int stdin;

void puts(const char *s) {
    write(stdout, (uint8_t *)s, strlen(s));
    char cp = '\n';
    write(stdout, (uint8_t *)&cp, 1);
}

void putc(const char c) {
    char cp = c;
    write(stdout, (uint8_t *)&cp, 1);
}

void putchar(const char c) {
    char cp = c;
    write(stdout, (uint8_t *)&cp, 1);
}

int getchar() {
    char c;
    read(stdin, (uint8_t *)&c, 1);
    char buf[2] = {0};
    buf[0]      = c;
    debug_print(&buf);
    return c;
}

void _libc_cp_kernel_start(int argc,char **argv,char **envp) {
    stdin = 0;
    stdout = 1;
    init_heap();

    int exit_code = main(argc, argv, envp);
    exit(exit_code);
}

__attribute__((naked)) void _start() {
    __asm__ volatile(
            "mov (%rsp), %rdi\n\t"
            "lea 8(%rsp), %rsi\n\t"

            "mov (%rsp), %rax\n\t"
            "inc %rax\n\t"
            "shl $3, %rax\n\t"
            "add %rax, %rsp\n\t"
            "mov %rsp, %rdx\n\t"

            "mov %rsi, %rsp\n\t"
            "call _libc_cp_kernel_start\n\t"
            "jmp .\n\t"
            ".L1:\n\t"
            "ret\n\t");
}

#ifdef __cplusplus
}
#endif
