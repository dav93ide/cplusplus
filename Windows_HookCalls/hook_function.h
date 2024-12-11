#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

void MsgBoxAddy(DWORD addy){
    char szBuffer[1024];
    // %02x Significa che vogliamo che il valore venga printato in esadecimale.
    sprintf(szBuffer, "Addy: %02x", addy);
    MessageBox(NULL, szBuffer, "Title", MB_OK);
}

void PlaceJMP(BYTE *address, DWORD jumpTo, DWORD length){
    DWORD dwOldProtect, dwBkup, dwRelAddr;

    // Setta come scrivibile la memoria per l'indirizzo specificato.
    VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    // 5 byte e' la dimensione di un'istruzione di JMP.
    dwRelAddr = (DWORD) (jumpTo - (DWORD) address) - 5;

    // 0xE9 = JMP instruction
    *address = 0xE9;

    // Scriviamo l'offset a cui dobbiamo saltare in modo da ottenere un'istruzione nella forma  JMP 12345
    *((DWORD *)(address + 0x1)) = dwRelAddr;

    for(DWORD x = 0x5; x < length; x++){
        // 0x90 = nop instruction
        *(address + x) = 0x90;
    }

    VirtualProtect(address, length, dwOldProtect, &dwBkup);
}

MODULEINFO GetModuleInfo(char *module){
    MODULEINFO modInfo = {0x0};
    HMODULE hModule = GetModuleHandle(module);

    if(hModule == 0x0){
        return modInfo;
    }

    GetModuleInformation(GetCurrentProcess, hModule, &modInfo, sizeof(MODULEINFO));

    return modInfo;
}

DWORD FindPattern(char *module, char *pattern, char *mask){
    MODULEINFO mInfo = GetModuleInfo(module);

    // Ottiene la base del modulo.
    DWORD base = (DWORD) mInfo.lpBaseOfDll;
    DWORD size = (DWORD) mInfo.SizeOfImage;

    DWORD patternLength = (DWORD) strlen(mask);

    for(DWORD i = 0x0; i < size - patternLength; i++){
        bool found = true;
        for(DWORD j = 0x0; j < patternLength; j++){
            /*
                Scansiona attraverso il pattern e se matcha completamente ritorna l'inizio del pattern. Se non matcha non ritorna niente.
                I "?" vengono ignorati.
            */
            found &=mask[j] == '?' || pattern[j] == *(char *)(base + i + j);
        }

        if(found){
            return base + i;
        }

    }

    return NULL;
}