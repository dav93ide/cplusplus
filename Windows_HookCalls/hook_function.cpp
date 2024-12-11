#include "hook_function.h"

void InitiateHooks(){
    // Il pattern e la maschera li ho recuperati disassemblando con OllyDbg e utilizzando la funzionalita` Make Sig.
    DWORD hook = FindPattern("test_hook.exe", "\x51\x83\xEC\x14\xE8\x00\x00\x00\x00", "xxxxx????");

    // Per raggiungere l'indirizzo alla fine delle istruzioni selezionate per implementare la detour.
    hook += 5;

    MsgBoxAddy(hook);

    jmpBack = hook + 0x7;

    // Piazza un jump nell'indirizzo scelto
    PlaceJMP((BYTE *)hook, (DWORD)HookInstructions, 7)

    /*  Dal video di youtube:

        DWORD flyAddy = FindPattern("ac_client.exe", "\x88\x4E\x3C\x89\x56\x08", "xxxxxx");
        FlyingJmpBack = flyAddy + 0x6;

        PlaceJMP((BYTE *)flyAddy, (DWORD)GetPlayerYAxis, 6);


    */
}

DWORD WINAPI OverwriteValues(){
    for(;;Sleep(150)){
        /*  Dal video di youtube:

            YaxisPtr = YaxisRegister + 0x3c;

            if(GetAsyncKeyState(VK_SPACE)){
                *(float *)YaxisPtr += 8.0;
            }

            if(GetAsyncKeyState(VK_CONTROL)){
                *(float *)YaxisPtr -= 8.0;
            }
        */

    }
}

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpReserved){
    switch(fdwReason){
        case DLL_PROCESS_ATTACH:
            InitiateHooks();
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OverwriteValues, NULL, NULL, NULL);
        break;
    }
    return TRUE;
}