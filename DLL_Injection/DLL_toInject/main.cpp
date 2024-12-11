// DLL d'esempio per DLL injection

#include "main.h"
//#include "pch.h"         // VISUAL STUDIO ONLY! - Precompiled Header - Standard Application Framework Extensions. Usare "stdafx.h" per Visual Studio 2017 o precedenti.
#include <stdio.h>
#include <windows.h>

/*
    Questa funzione viene chiamata quando la DLL e`caricata dentro lo spazio d'indirizzamento del processo.
*/
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    // Apertura file
    FILE *file;
    fopen_s(&file, "C:\\Users\\z3r0\\Desktop\\Doing\\temp.txt", "a+");

    switch(fdwReason){
        case DLL_PROCESS_ATTACH:
            fprintf(file, "DLL attach function called.\n");
            break;
        case DLL_PROCESS_DETACH:
            fprintf(file, "DLL detach function called.\n");
            break;
        case DLL_THREAD_ATTACH:
            fprintf(file, "DLL thread attach function called.\n");
            break;
        case DLL_THREAD_DETACH:
            fprintf(file, "DLL thread detach function called.\n");
            break;
    }

    // Chiusura file
    fclose(file);

    return TRUE;
}

/*
    Funzione esportata.
*/
extern "C" DLL_EXPORT int meconnect(int code, WPARAM wParam, LPARAM lParam){

    FILE *file;
    fopen_s(&file, "C:\\Users\\z3r0\\Desktop\\Doing\\function.txt", "a+");

    fprintf(file, "Function keyboard_hook called.\n");

    fclose(file);

    return (CallNextHookEx(NULL, code, wParam, lParam));
}

