#pragma once

#define MAP_ANONYMOUS 32
#define MAP_FIXED     16

#define PROT_NONE 0x00
#define PROT_READ 0x01
#define PROT_WRITE 0x02
#define PROT_EXEC 0x04

#define SIGHUP  1  // Hangup (终端断开)
#define SIGINT  2  // Interrupt (Ctrl+C)
#define SIGQUIT 3  // Quit (Ctrl+\)
#define SIGILL  4  // Illegal instruction
#define SIGTRAP 5  // Trace trap
#define SIGABRT 6  // Abort
#define SIGBUS  7  // Bus error
#define SIGFPE  8  // Floating-point exception
#define SIGKILL 9  // Kill signal (不可捕获/屏蔽)
#define SIGUSR1 10 // User-defined signal 1
#define SIGSEGV 11 // Segmentation fault
#define SIGUSR2 12 // User-defined signal 2
#define SIGPIPE 13 // Broken pipe
#define SIGALRM 14 // Alarm clock
#define SIGTERM 15 // Termination signal
#define SIGCHLD 17 // Child stopped or terminated
#define SIGCONT 18 // Continue if stopped
#define SIGSTOP 19 // Stop process (不可捕获)
#define SIGTSTP 20 // Stop typed at terminal (Ctrl+Z)
#define SIGTTIN 21 // Background read from tty
#define SIGTTOU 22 // Background write to tty

#define ARCH_SET_FS 0x1002
#define ARCH_GET_FS 0x1003
#define ARCH_SET_GS 0x1004
#define ARCH_GET_GS 0x1005

#include "stdint.h"
#include "stddef.h"

int open(const char*path);
int write(int handle,uint8_t *buf,int len);
int read(int handle,uint8_t *buf,int len);
void mmap(void *addr,size_t length,uint64_t prot,uint64_t flags,int fd,uint64_t offset);
void signal_register(int sig,void (*handler)(void));
void *arch_prctl(int code, void *addr);
void yield();
void debug_print(char *str);
