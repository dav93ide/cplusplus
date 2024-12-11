#include <windows.h>

void* DetourFunction64(void* pSource, void* pDestination, int dwLen)
{
    DWORD MinLen = 14;

    if (dwLen < MinLen) return NULL;

    BYTE stub[] = {
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
    };

    void* pTrampoline = VirtualAlloc(0, dwLen + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    DWORD dwOld = 0;
    VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);

    DWORD64 retto = (DWORD64)pSource + dwLen;

    // trampoline
    memcpy(stub + 6, &retto, 8);
    memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
    memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));

    // orig
    memcpy(stub + 6, &pDestination, 8);
    memcpy(pSource, stub, sizeof(stub));

    for (int i = MinLen; i < dwLen; i++)
    {
        *(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
    }

    VirtualProtect(pSource, dwLen, dwOld, &dwOld);
    return (void*)((DWORD_PTR)pTrampoline);
}

