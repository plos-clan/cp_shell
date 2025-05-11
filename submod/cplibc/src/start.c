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
}

void putc(const char c) {
    char cp = c;
    write(stdout, (uint8_t*)&cp, 1);
}

int getchar(){
    char c;
    read(stdin, (uint8_t*)&c, 1);
    return c;
}

void _start() {
    stdout = open("/dev/stdout");
    stdin = open("/dev/stdin");
    init_heap();

    int exit_code = main(0, "");
    exit(exit_code);
}

#ifdef __cplusplus
}
#endif
