/*
    Compilazione:
        i686-w64-mingw32-g++ -c -static-libgcc -static-libstdc++ simple_dll.cpp

    Linking:
        i686-w64-mingw32-g++ --shared simple_dll.o -o simple_dll.dll
*/

#define BUILD_DLL
#include "simple_dll.h"
#include <fstream>
#include <iostream>

// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            SomeFunction("DLL_PROCESS_ATTACH");
            break;

        case DLL_PROCESS_DETACH:
            SomeFunction("DLL_PROCESS_DETACH");
            break;

        case DLL_THREAD_ATTACH:
            SomeFunction("DLL_THREAD_ATTACH");
            break;

        case DLL_THREAD_DETACH:
            SomeFunction("DLL_THREAD_DETACH");
            break;
    }
    std::ofstream log("C:\\Users\\z3r0\\Desktop\\test.txt", std::ofstream::app | std::ofstream::out);
    log << "TEST123";
    log.close();

    return TRUE; // succesful
}
