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

int stdout;
int stdin;

int printf(const char *fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    int len = stbsp_vsprintf(buf, fmt, args);
    va_end(args);
    write(stdout, buf, len);
    return len;
}

void _start() {
    stdout = open("/dev/stdout");
    stdin = open("/dev/stdin");

    int exit_code = main(0, "");
    exit(exit_code);
}

#ifdef __cplusplus
}
#endif
