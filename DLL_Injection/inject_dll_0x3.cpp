#include "windows.h"
#include "stdio.h"

int main(int argc, char **argv) {
    const char* buffer = "C:\\Users\\z3r0\\Desktop\\simple_dll.dll";

    /*
    * Get process handle passing in the process ID.
    */
    int procID = 2308;
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if(process == NULL) {
        printf("Error: the specified process couldn’t be found.\n");
    }

    /*
    * Get address of the LoadLibrary function.
    */
    LPVOID addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    if(addr == NULL) {
        printf("Error: the LoadLibraryA function was not found inside kernel32.dll library.\n");
    }

    /*
    * Allocate new memory region inside the process’s address space.
    */
    LPVOID arg = (LPVOID)VirtualAllocEx(process, NULL, strlen(buffer), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if(arg == NULL) {
        printf("Error: the memory could not be allocated inside the chosen process.\n");
    }

    /*
    * Write the argument to LoadLibraryA to the process’s newly allocated memory region.
    */
    int n = WriteProcessMemory(process, arg, buffer, strlen(buffer), NULL);
    if(n == 0) {
        printf("Error: there was no bytes written to the process’s address space.\n");
    }

    /*
    * Inject our DLL into the process’s address space.
    */
    HANDLE threadID = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)addr, arg, NULL, NULL);
    if(threadID == NULL) {
        printf("Error: the remote thread could not be created.\n");
    } else {
        printf("Success: the remote thread was successfully created.\n");
    }

    /*
    * Close the handle to the process, becuase we’ve already injected the DLL.
    */
    CloseHandle(process);
    getchar();

    return 0;
}