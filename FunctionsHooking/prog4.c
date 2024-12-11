/*
    Compilazione:
        gcc -shared -ldl -fPIC prog4.c -o prog4

    Set variabile d'ambiente ed esecuzione:
        LD_PRELOAD=/home/z3r0/Scrivania/All/Programming/C++/Exercises_Linux/hook_linux_calls/hook_library_function/prog4 ./prog3

*/

#define __USE_GNU
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

extern void *__libc_dlsym(void *, const char *);

void *dlsym(void *handle, const char *symbol){
    printf("Ha Ha... dlsym() Hooked!\n");
    void *result = __libc_dlsym(handle, symbol);
    return result;
}