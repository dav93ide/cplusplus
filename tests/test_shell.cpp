/*
    Compilation:
        g++ test_shell.cpp Shell/Shell.cpp
*/

#include "../Shell/Shell.h"
#include <iostream>
#include <string>

int main(){
    std::cout << "[+] Test Shell...\n\n\n\n" << "[+] Exec: ls\n";
    std::string res = Shell::exec_command("ls");
    std::cout << res << "\n\n";
}