#include "string.h"
#define STB_SPRINTF_IMPLEMENTATION
#include "posix.h"
#include "sprintf.h"
#include "stdio.h"
#include "stdlib.h"

extern int main(int argc, char **argv);

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

#define MAX_ARG_NR      50

static int cmd_parse(const char *cmd_str, char **argv,
                     char token) // 用uint8_t是因为" "使用8位整数
{
    int arg_idx = 0;

    while (arg_idx < MAX_ARG_NR) {
        argv[arg_idx] = 0;
        arg_idx++;
    }
    char *next = (char *)cmd_str; // 下一个字符
    int   argc = 0;               // 这就是要返回的argc了

    while (*next) { // 循环到结束为止
        while (*next == token)
            next++;            // 多个token就只保留第一个，windows cmd就是这么处理的
        if (*next == 0) break; // 如果跳过完token之后结束了，那就直接退出
        argv[argc] = next;     // 将首指针赋值过去，从这里开始就是当前参数
        while (*next && *next != token)
            next++;      // 跳到下一个token
        if (*next) {     // 如果这里有token字符
            *next++ = 0; // 将当前token字符设为0（结束符），next后移一个
        }
        if (argc > MAX_ARG_NR) return -1; // 参数太多，超过上限了
        argc++; // argc增一，如果最后一个字符是空格时不提前退出，argc会错误地被多加1
    }
    return argc;
}

void _start() {
    stdin = stdout = open("/dev/stdio");
    init_heap();
    uint8_t *argv[MAX_ARG_NR];
    char buf[256] = {0};
    int len = cmdline((uint8_t *)buf);
    int argc = cmd_parse(buf, (char **)argv, ' ');

    int exit_code = main(argc, argv);
    exit(exit_code);
}

#ifdef __cplusplus
}
#endif
