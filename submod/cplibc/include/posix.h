#pragma once

int open(const char*path);
int write(int handle,uint8_t *buf,int len);
int read(int handle,uint8_t *buf,int len);
