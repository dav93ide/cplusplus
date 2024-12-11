#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <TlHelp32.h>

typedef int(__stdcall *__MessageBoxA)(HWND, LPCSTR, LPCSTR, UINT)

class Cavedata {
    char chMessage[256];
    char chTitle[256];

    // pa = procedure address in memory
    DWORD paMessageBoxA;
}

DWORD GetProcId(char *proc){
    PROCESSENTRY32 pe;
    HANDLE hSnap;

    pe.dwSize = sizeof(PROCESSENTRY32);
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if(Process32First(hSnap, &pe)){
        do{
            if(strcmp(pe.szExeFile, proc) == 0x0)
                break;
        } while(Process32Next(hSnap, &pe));
    }
    return pe.th32ProcessID;
}

// Thread che verra` iniettato nel processo bersaglio
DWORD __stdcall RemoteThread(cavedata *cData){
    // Inizializza la funzione
    _MessageBoxA MsgBox = (_MessageBoxA)cData->paMessageBoxA;
    MsgBox(NULL, cData->chMessage, cData->chTitle, MB_ICONINFORMATION);
    return EXIT_SUCCESS;
}

int main(){
    Cavedata data;
    ZeroMemory(&data, sizeof(data));
    strcpy(data.chMessage, "Prova invio messaggio...");
    strcpy(data.chTitle, "Test");

    HINSTANCE hUserModule = LoadLibrary("user32.dll");
    data.paMessageBoxA = (DWORD) GetProcAddress(hUserModule, "MessageBoxA");

    FreeLibrary(hUserModule);

    // Apre processo bersaglio per scrittura
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcId("notepad.exe"));

    // Alloca memoria per la nostra procedura nello spazio d'indirizzamento del processo remoto
    LPVOID pRemoteThread = VirtualAllocEx(hProcess, NULL, sizeof(data), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Scrive il nostro thread nel processo bersaglio
    WriteProcessMemory(hProcess, pRemoteThread, (LPVOID)RemoteThread, sizeof(data), 0x0);

    // Alloca memoria per il Cavedata object nel processo remoto
    Cavedata *pData = (Cavedata *) VirtualAllocEx(hProcess, NULL, sizeof(Cavedata), MEM_COMMIT, PAGE_READWRITE);

    // Scrive l'oggetto Cavedata nel processo bersaglio
    WriteProcessMemory(hProcess, pData, &data, sizeof(Cavedata), NULL);

    // Lancia la nostra procedura/thread nel processo remoto
    HANDLE hThread = CreateRemoteThread(hProcess, 0x0, 0x0, (LPTHREAD_START_ROUTINE)pRemoteThread, pData, 0x0, 0x0);

    CloseHandle(hThread);

    // Libera la memoria ora non piu'utilizzata dall'heap del processo remoto
    VirtualFreeEx(hProcess, pRemoteThread, sizeof(Cavedata), MEM_RELEASE);
    CloseHandle(hProcess);
}