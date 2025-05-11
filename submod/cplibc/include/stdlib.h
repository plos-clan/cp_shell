#ifndef _STDLIB_H
#define _STDLIB_H 1

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ssize_t
typedef unsigned long long ssize_t;
#endif

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void  free(void *ptr);

#define RAND_MAX 32767
int  rand(void);
void srand(unsigned int seed);

int       abs(int j);
long      labs(long j);
long long llabs(long long j);

int       atoi(const char *nptr);
long      atol(const char *nptr);
long long atoll(const char *nptr);
double    atof(const char *nptr);

void  abort(void) __attribute__((__noreturn__));
int   atexit(void (*func)(void));
void  exit(int status) __attribute__((__noreturn__));
char *getenv(const char *name);
int   system(const char *command);
long  strtol(const char *nptr, char **endptr, int base);

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H */
