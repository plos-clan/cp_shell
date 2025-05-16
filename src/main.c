#include "stdio.h"
#include "pl_readline.h"
#include "shell.h"
#include "string.h"
#include "posix.h"

#ifndef GIT_VERSION
#    define GIT_VERSION "unknown"
#endif

int find_cmd(uint8_t *cmd) {
    for (int i = 0; i < builtin_cmd_num; ++i) {
        if (strcmp((const char *)cmd, builtin_cmds[i].name) == 0) { return i; }
    }
    return -1;
}

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

void int_handle(){
    printf("Signal Interrupt.\n");
}

extern int stdin;

int main(int argc, char**argv){
    printf("Welcome to CoolPotOS Shell (git:%s)\n", GIT_VERSION);
    printf("Type 'help' to see the list of commands.\n");
    pl_readline_t pl = setup_readline();
    uint8_t *argv0[MAX_ARG_NR];

    while (true){
        const char *cmd = pl_readline(pl, "Shell > ");
        if (cmd[0] == 0) continue;
        int argc = cmd_parse(cmd, (char **)argv0, ' ');

        if (argc == -1) {
            printf("shell: number of arguments exceed MAX_ARG_NR(30)");
            continue;
        }
        if (argc == 0) continue;

        int cmd_index = find_cmd(argv0[0]);
        if (cmd_index < 0) {
            printf("Command not found.\n\n");
        } else {
            builtin_cmds[cmd_index].func(argc, (char **)argv0);
        }
    }
    return 0;
}
