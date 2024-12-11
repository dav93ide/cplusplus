#include "hook_function.h"

DWORD jmpBack = 0x0;

// __declspec permette di scrivere in Assembly all'interno della funzione.
__declspec(naked) void HookInstructions(){
    __asm INC [ESI]
    __asm mov [esp+0x4], a.002E0048
    __asm mov [esp], a.002DF8C0

    __asm jmp [jmpBack]
}

DWORD FlyingJmpBack = 0x0;
DWORD YaxisRegister = 0x0;
DWORD YaxisPtr;

// Funzione presa dal video di youtube. Prende l'indirizzo dalla funzione.
/*
    Per recuperare l'indirizzo della funzione:
    
    ESI+0x3C contiene y-axis, ma non e' possibile fare esi+0x3C perche' altrimenti non verrebbe accettato in memoria.
    Quindi si fa:   __asm mov YaxisRegister, esi
    e si aggiunge successivamente 0x3c.
*/
__declspec(naked) void GetPlayerYaxis(){
    __asm mov ecx, [esi+0x3C]
    __asm mov YaxisRegister, esi
    __asm mov [esi+0x8], edx

    __asm jmp [FlyingJmpBack]
}