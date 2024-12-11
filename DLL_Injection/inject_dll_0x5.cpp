#include <windows.h>
#include <stdio.h>
#include <iostream>

void PrintError(char *text, bool boh){
	printf(text);
}

int main(int argc, char **argv){
	
	HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, 2224);
	if (hProcess == NULL) {
		PrintError("OpenProcess()", TRUE);
		return 0x1;
	}
	
	LPVOID lpBaseAddress = VirtualAllocEx(hProcess, nullptr, 1 << 12, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (lpBaseAddress == nullptr) {
	  PrintError("VirtualAllocEx()", TRUE);
	  return 0x0;
	}
	
	if (!WriteProcessMemory(hProcess, lpBaseAddress, (LPCVOID) argv[2], strlen(argv[2]), nullptr)) {
	  PrintError("WriteProcessMemory()", TRUE);
	}
	
	HMODULE hKernel32 = GetModuleHandleA("Kernel32");
	if (hKernel32 == NULL) {
	  VirtualFreeEx(hProcess, lpBaseAddress, 0x0, MEM_RELEASE);
	  lpBaseAddress = nullptr;
	
	  CloseHandle(hProcess);
	  hProcess = NULL;
	
	  PrintError("GetModuleHandleA()", TRUE);
	  return 0x0;
	}
	FARPROC pLoadLibraryA = GetProcAddress(hKernel32, "LoadLibraryA");
	
	HANDLE hThread = CreateRemoteThread(hProcess, nullptr, NULL, (LPTHREAD_START_ROUTINE) pLoadLibraryA, lpBaseAddress, NULL, nullptr);
	if (hThread == NULL) {
	  VirtualFreeEx(hProcess, lpBaseAddress, 0x0, MEM_RELEASE);
	  lpBaseAddress = nullptr;
	
	  CloseHandle(hProcess);
	  hProcess = NULL;
	
	  PrintError("CreateRemoteThread()", TRUE);
	  return 0x0;
	}
	
	std::cout << "Injected DLL\n";
}