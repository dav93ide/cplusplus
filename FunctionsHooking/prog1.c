#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main(void){
    int *p;
    printf("[+] Calling from main...\n");

    p = (int *)malloc(10);
    if(!p){
        printf("[!] Allocation Error...\n");
        exit(0x1);
    }
    printf("[+] Returning to main...\n");
    free(p);
    printf("[+] Freeing memory...\n");

    return 0x0;
}