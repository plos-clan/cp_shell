#pragma once

#include "stdint.h"
#include "stddef.h"
#include "limits.h"

int memcmp(const void *a_, const void *b_, size_t size);

void *memcpy(void *s, const void *ct, size_t n);

void *memset(void *dst, int val, size_t size);

size_t strlen(const char *str);

char *strcat(char *dest, const char *src);

int strncmp(const char *s1, const char *s2, size_t n);

char *strcpy(char *dest, const char *src);

int strcmp(const char *s1, const char *s2);

int64_t strtol(const char *str, char **endptr, int base);

char *strchrnul(const char *s, int c);

#undef isspace
int isspace(int c);

char *strchr(const char *s, int c);

char *strncpy(char *dest, const char *src, size_t n);

char *strrchr(const char *s, int c);

char *strtok(char *str, const char *delim);

char *strdup(const char *str);
