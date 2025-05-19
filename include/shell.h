#pragma once

#define MAX_COMMAND_LEN 100
#define MAX_ARG_NR      50

#include "pl_readline.h"

typedef struct builtin_cmd {
    const char *name;
    void (*func)(int, char **);
} builtin_cmd_t;

extern const int builtin_cmd_num;
extern builtin_cmd_t builtin_cmds[];

pl_readline_t setup_readline();

// 内建命令
void print_help();

void shell_exit();
