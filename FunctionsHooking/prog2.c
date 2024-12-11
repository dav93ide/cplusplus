/*
    Per eseguire si utilizza:
        LD_PRELOAD=~/home/z3r0/Scrivania/All/Programming/C++/Exercises_Linux/hook_linux_calls/hook_library_function/prog2 ./prog1

    La variabile d'ambiente LD_PRELOAD da al loader una lista di librerie da caricare prima di qualunque altra cosa.
    Il nostro utilizzo carichera' "prog2" e lo linkera`dinamicamente con il binary di prog1.

    Compilazione:
        gcc -shared -ldl -fPIC prog2.c -o prog2
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

void lcheck(void);

void *malloc(size_t size){
    static void *(*my_malloc) (size_t) = NULL;
    printf("[+] Inside shared object...\n");

    if(!my_malloc){
        // Ritorna l'oggetto di riferimento per malloc.
        // dlsym() dice al linker dinamico di trovare il successivo riferimento alla funzione specificata, non quella che sta chiamando dlsym().
        my_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    // Chiama malloc usando il puntatore di funzione "my_malloc"
    void *p = my_malloc(size);

    printf("[+] malloc(%d) = %p\n", size, p);

    lcheck();

    printf("[+] Returning from shared object...\n");

    return p;
}

void lcheck(void){
    printf("[+] Displaying memory leaks...\n");
}