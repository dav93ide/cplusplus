/*
    Creazione oggetto condiviso "libfile.so" da "file1.c" e "file2.c":
        gcc -shared -ldl -fPIC file1.c file2.c -o libfile.so

    Compilazione:
        gcc -rdynamic -o prog3 prog3.c -ldl

*/
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

void file1(int *i);
void file2(int *i);

int main(void){

    void *handler;
    int (*fn) (int *);
    int x = 500;
    char *error;

    handler = dlopen("/home/z3r0/Scrivania/All/Programming/C++/Exercises_Linux/hook_linux_calls/hook_library_function/libfile.so", RTLD_LAZY);
    if(!handler){
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    // Ottiene un handle a "file1" attraverso "dlsym()"
    fn = dlsym(handler, "file1");
    // Controlla eventuali errori
    if((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    // Chiama "file1()" per risolvere x.
    (* fn)(&x);
    printf("[1] Il valore di x e`: %d\n", x);

    // Ottiene un handle a "file2" attraverso "dlsym()"
    fn = dlsym(handler, "file2");
    // Controlla eventuali errori
    if((error = dlerror()) != NULL){
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    // Chiama "file2()" per risolvere x.
    (* fn)(&x);
    printf("[2] Il valore di x e`: %d\n", x);

    // Chiude handle
    dlclose(handler);

    return 0x0;
}