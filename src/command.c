#include "shell.h"
#include "stdio.h"
#include "stdlib.h"

builtin_cmd_t builtin_cmds[] = {
        {"help",     (void (*)(int, char **))print_help },
        {"exit",     (void (*)(int, char **))shell_exit},
};

const int builtin_cmd_num = sizeof(builtin_cmds) / sizeof(builtin_cmd_t);

void print_help() {
    printf("Usage <command|app_path> [argument...]\n");
    printf("help                     Get shell help info.\n");
    printf("exit                     Shutdown kernel.\n");
    printf("reboot                   Restart kernel.\n");
    printf("lspci                    List all PCI/PCIE devices.\n");
    printf("sysinfo                  Get system info.\n");
    printf("clear                    Clear screen.\n");
    printf("ps        [pcb]          List task group or all running tasks.\n");
    printf("pkill     <pid>          Kill a tasks.\n");
    printf("cd        <path>         Change shell work path.\n");
    printf("mkdir     <name>         Create a directory.\n");
    printf("ls        [path]         List all file or directory.\n");
    printf("echo      <message>      Print a message.\n");
    printf("mount     <dev> <path>   Mount a device to path.\n");
    printf("lmod      <module|list>  Load or list module.\n");
    printf("exec      <module>       Load a user application.\n");
}

void shell_exit(){
    exit(0);
}
