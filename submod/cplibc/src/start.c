#include "string.h"
#define STB_SPRINTF_IMPLEMENTATION
#include "sprintf.h"
#include "stdio.h"
#include "stdlib.h"
#include "posix.h"

extern int main(int argc, char**argv);

#ifdef __cplusplus
extern "C" {
#endif

extern void init_heap();

int stdout;
int stdin;

void puts(const char *s) {
    write(stdout, (uint8_t *)s, strlen(s));
    char cp = '\n';
    write(stdout, (uint8_t*)&cp, 1);
}

void putc(const char c) {
    char cp = c;
    write(stdout, (uint8_t*)&cp, 1);
}

void putchar(const char c){
    char cp = c;
    write(stdout, (uint8_t*)&cp, 1);
}

int getchar(){
    char c;
    read(stdin, (uint8_t*)&c, 1);
    char buf[2] = {0};
    buf[0] = c;
    debug_print(&buf);
    return c;
}

void _start() {
    stdin = stdout = open("/dev/stdio");
    init_heap();

    int exit_code = main(0, "");
    exit(exit_code);
}

#ifdef __cplusplus
}
#endif
