#include "stdint.h"
#include "syscall.h"
#include "posix.h"

_Noreturn void exit(int code){
    __syscall(0,code);
    while (1);
}

int open(const char*path){
    __syscall(8,path);
}

int write(int handle,uint8_t *buf,int len){
    return __syscall(12,handle,buf,len);
}

int read(int handle,uint8_t *buf,int len){
    return __syscall(10,handle,buf,len);
}
