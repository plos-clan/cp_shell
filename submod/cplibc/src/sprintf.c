#include "stdarg.h"
#include "stdlib.h"
#include "sprintf.h"
#include "posix.h"

extern int stdout;
extern int stdin;

int sprintf(char *buf, char const *fmt, ...) {
    int     result;
    va_list va;
    va_start(va, fmt);
    result = STB_SPRINTF_DECORATE(vsprintfcb)(0, 0, buf, fmt, va);
    va_end(va);
    return result;
}

int printf(const char *fmt, ...) {
    char buf[2048];
    va_list args;
    va_start(args, fmt);
    int len = stbsp_vsprintf(buf, fmt, args);
    va_end(args);
    write(stdout, buf, len);
    return len;
}
