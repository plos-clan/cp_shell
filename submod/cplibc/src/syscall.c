#include "stdint.h"
#include "syscall.h"
#include "posix.h"

_Noreturn void exit(int code){
    __syscall(0,code);
    while (1);
}

int open(const char*path){
    __syscall(SYSCALL_OPEN,path);
}

int write(int handle,uint8_t *buf,int len){
    return __syscall(SYSCALL_WRITE,handle,buf,len);
}

int read(int handle,uint8_t *buf,int len){
    return __syscall(SYSCALL_READ,handle,buf,len);
}

void mmap(void *addr,size_t length,uint64_t prot,uint64_t flags){
    __syscall(SYSCALL_MMAP,addr,length,prot,flags);
}
