#include <windows.h>

bool Hook(void *toHook, void *ourFunct, int len){

    if(len < 5){
        return false;
    }

    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

    memset(toHook, 0x90, len);

    DWORD relativeAddress = ((DWORD) ourFunct - (DWORD) hook) - 5;

    *(BYTE*) toHook = 0xE9;
    *(DWORD*)((DWORD) toHook + 0x1) = relativeAddress;

    DWORD temp;
    VirtualProtect(toHook, len, curProtection, &temp);

    return true;
}

DWORD WINAPI MainThread(LPVOID param){
    while(true){
        if(GetAsyncKeyState(VK_ESCAPE))
            break;
        Sleep(50);
    }

    FreeLibraryAndExitThread((HMODULE)param, 0x0);

    return 0x0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved){
    switch(dwReason){
        case DLL_PROCESS_ATTACH:
            CreateThread(0x0, 0x0, MainThread, hModule, 0x0, 0x0);
            break;
    }

    return TRUE;
}