#include "stdio.h"

#ifndef GIT_VERSION
#    define GIT_VERSION "unknown"
#endif

int main(int argc, char**argv){
    printf("Hello! %s","World!\n");
    return 0;
}
