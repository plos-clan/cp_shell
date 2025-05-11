#pragma once

#define MAP_ANONYMOUS 32
#define MAP_FIXED     16

#define PROT_NONE 0x00
#define PROT_READ 0x01
#define PROT_WRITE 0x02
#define PROT_EXEC 0x04

#include "stdint.h"
#include "stddef.h"

int open(const char*path);
int write(int handle,uint8_t *buf,int len);
int read(int handle,uint8_t *buf,int len);
void mmap(void *addr,size_t length,uint64_t prot,uint64_t flags);
