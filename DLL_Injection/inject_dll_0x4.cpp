#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <strsafe.h>

#define PROCESS_PID 2308

void displayError(DWORD dw, LPTSTR lpszFunction){
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
}

int main(int argc, char *argv[]) {
	HANDLE processHandle;
	PVOID remoteBuffer;
	const wchar_t dllPath[] = L"C:\\Users\\Desktop\\simple_dll.dll";
	
	printf("Injecting DLL to PID: %i\n", PROCESS_PID);
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(PROCESS_PID));

    DWORD err = GetLastError();
    displayError(err, "[1]");

	remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof dllPath, MEM_COMMIT, PAGE_READWRITE);	

    err = GetLastError();
    displayError(err, "[2]");

	WriteProcessMemory(processHandle, remoteBuffer, (LPVOID)dllPath, sizeof dllPath, NULL);

    err = GetLastError();
    displayError(err, "[3]");

	PTHREAD_START_ROUTINE threatStartRoutineAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");

    err = GetLastError();
    displayError(err, "[4]");

	CreateRemoteThread(processHandle, NULL, 0, threatStartRoutineAddress, remoteBuffer, 0, NULL);

    err = GetLastError();
    displayError(err, "[5]");

	CloseHandle(processHandle); 
	
    int test;
    std::cin >> test;

	return 0;
}