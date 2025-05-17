#pragma once

#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"

#define __syscall0(id)                                                                             \
    ({                                                                                             \
        ssize_t rets;                                                                              \
        __asm__ volatile("syscall\n\t" : "=a"(rets) : "0"(id) : "memory", "cc");                   \
        rets;                                                                                      \
    })

#define __syscall1(id, arg1)                                                                       \
    ({                                                                                             \
        ssize_t          rets;                                                                     \
        ssize_t          __arg1             = (ssize_t)(arg1);                                     \
        register ssize_t _a1 __asm__("rdi") = __arg1;                                              \
        __asm__ volatile("syscall\n\t" : "=a"(rets) : "0"(id), "r"(_a1) : "memory", "cc");         \
        rets;                                                                                      \
    })

#define __syscall2(id, arg1, arg2)                                                                 \
    ({                                                                                             \
        ssize_t          rets;                                                                     \
        ssize_t          __arg1             = (ssize_t)(arg1);                                     \
        ssize_t          __arg2             = (ssize_t)(arg2);                                     \
        register ssize_t _a2 __asm__("rsi") = __arg2;                                              \
        register ssize_t _a1 __asm__("rdi") = __arg1;                                              \
        __asm__ volatile("syscall\n\t"                                                             \
                         : "=a"(rets)                                                              \
                         : "0"(id), "r"(_a1), "r"(_a2)                                             \
                         : "memory", "cc");                                                        \
        rets;                                                                                      \
    })

#define __syscall3(id, arg1, arg2, arg3)                                                           \
    ({                                                                                             \
        ssize_t          rets;                                                                     \
        ssize_t          __arg1             = (ssize_t)(arg1);                                     \
        ssize_t          __arg2             = (ssize_t)(arg2);                                     \
        ssize_t          __arg3             = (ssize_t)(arg3);                                     \
        register ssize_t _a3 __asm__("rdx") = __arg3;                                              \
        register ssize_t _a2 __asm__("rsi") = __arg2;                                              \
        register ssize_t _a1 __asm__("rdi") = __arg1;                                              \
        __asm__ volatile("syscall\n\t"                                                             \
                         : "=a"(rets)                                                              \
                         : "0"(id), "r"(_a1), "r"(_a2), "r"(_a3)                                   \
                         : "memory", "cc");                                                        \
        rets;                                                                                      \
    })

#define __syscall4(id, arg1, arg2, arg3, arg4)                                                     \
    ({                                                                                             \
        ssize_t          rets;                                                                     \
        ssize_t          __arg1             = (ssize_t)(arg1);                                     \
        ssize_t          __arg2             = (ssize_t)(arg2);                                     \
        ssize_t          __arg3             = (ssize_t)(arg3);                                     \
        ssize_t          __arg4             = (ssize_t)(arg4);                                     \
        register ssize_t _a4 __asm__("r10") = __arg4;                                              \
        register ssize_t _a3 __asm__("rdx") = __arg3;                                              \
        register ssize_t _a2 __asm__("rsi") = __arg2;                                              \
        register ssize_t _a1 __asm__("rdi") = __arg1;                                              \
        __asm__ volatile("syscall\n\t"                                                             \
                         : "=a"(rets)                                                              \
                         : "0"(id), "r"(_a1), "r"(_a2), "r"(_a3), "r"(_a4)                         \
                         : "memory", "cc");                                                        \
        rets;                                                                                      \
    })

#define __syscall5(id, arg1, arg2, arg3, arg4, arg5)                                               \
    ({                                                                                             \
        ssize_t          rets;                                                                     \
        ssize_t          __arg1             = (ssize_t)(arg1);                                     \
        ssize_t          __arg2             = (ssize_t)(arg2);                                     \
        ssize_t          __arg3             = (ssize_t)(arg3);                                     \
        ssize_t          __arg4             = (ssize_t)(arg4);                                     \
        ssize_t          __arg5             = (ssize_t)(arg5);                                     \
        register ssize_t _a5 __asm__("r8")  = __arg5;                                              \
        register ssize_t _a4 __asm__("r10") = __arg4;                                              \
        register ssize_t _a3 __asm__("rdx") = __arg3;                                              \
        register ssize_t _a2 __asm__("rsi") = __arg2;                                              \
        register ssize_t _a1 __asm__("rdi") = __arg1;                                              \
        __asm__ volatile("syscall\n\t"                                                             \
                         : "=a"(rets)                                                              \
                         : "0"(id), "r"(_a1), "r"(_a2), "r"(_a3), "r"(_a4), "r"(_a5)               \
                         : "memory", "cc");                                                        \
        rets;                                                                                      \
    })

#define __syscall6(id, arg1, arg2, arg3, arg4, arg5, arg6)                                         \
    ({                                                                                             \
        ssize_t          rets;                                                                     \
        ssize_t          __arg1             = (ssize_t)(arg1);                                     \
        ssize_t          __arg2             = (ssize_t)(arg2);                                     \
        ssize_t          __arg3             = (ssize_t)(arg3);                                     \
        ssize_t          __arg4             = (ssize_t)(arg4);                                     \
        ssize_t          __arg5             = (ssize_t)(arg5);                                     \
        ssize_t          __arg6             = (ssize_t)(arg6);                                     \
        register ssize_t _a6 __asm__("r9")  = __arg6;                                              \
        register ssize_t _a5 __asm__("r8")  = __arg5;                                              \
        register ssize_t _a4 __asm__("r10") = __arg4;                                              \
        register ssize_t _a3 __asm__("rdx") = __arg3;                                              \
        register ssize_t _a2 __asm__("rsi") = __arg2;                                              \
        register ssize_t _a1 __asm__("rdi") = __arg1;                                              \
        __asm__ volatile("syscall\n\t"                                                             \
                         : "=a"(rets)                                                              \
                         : "0"(id), "r"(_a1), "r"(_a2), "r"(_a3), "r"(_a4), "r"(_a5), "r"(_a6)     \
                         : "memory", "cc");                                                        \
        rets;                                                                                      \
    })

#define __syscall_concat_x(a, b)                               a##b
#define __syscall_concat(a, b)                                 __syscall_concat_x(a, b)
#define __syscall_argn_private(_0, _1, _2, _3, _4, _5, n, ...) n
#define __syscall_argn(...)                                    __syscall_argn_private(0, ##__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define __syscall(id, ...)                                                                         \
    __syscall_concat(__syscall, __syscall_argn(__VA_ARGS__))(id, ##__VA_ARGS__)

// plos-clan 通用系统调用编号定义
#define SYSCALL_READ       0
#define SYSCALL_WRITE      1
#define SYSCALL_OPEN       2
#define SYSCALL_CLOSE      3
#define SYSCALL_STAT       4
#define SYSCALL_SIGNAL     6
#define SYSCALL_WAITPID    7
#define SYSCALL_MMAP       9
#define SYSCALL_SIGRET     15
#define SYSCALL_IOCTL      16
#define SYSCALL_YIELD      24
#define SYSCALL_NANO_SLEEP 35
#define SYSCALL_GETPID     39
#define SYSCALL_CLONE      56
#define SYSCALL_ABORT      59
#define SYSCALL_EXIT       60
#define SYSCALL_UNAME      63
#define SYSCALL_PRCTL      157
#define SYSCALL_ARCH_PRCTL 158

#define SYSCALL_DEBUG_PRINT 200
