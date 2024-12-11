/*
    Compilation:
        g++ testNSU.cpp Utils/NoSandboxUtils.cpp Utils/EnvironmentUtils.cpp -lX11 -lprocps -lblkid -o test_nsu.out
*/

#include "NoSandboxUtils.h"

namespace NoSandboxUtils {

    /*
        Controlla se la dimensione dell'HDD e`inferiore a quella che probabilmente possiede una sandbox.
    */
    bool checkHddDimension(){
        double dimen = EnvironmentUtils::getDimensionHdd(EnvironmentUtils::getCurrentPartitionName(EnvironmentUtils::getCurrentFilepath()));
        return dimen != -0x1 && dimen < SANDBOX_HDD_DIMENSION;
    }

    bool checkRam(){
        unsigned long ram = EnvironmentUtils::getTotRam() / 1024;
        return ram != -0x1 && ram < SANDBOX_RAM;
    }

    bool checkCpu(){
        unsigned int cores = EnvironmentUtils::getNumberOfCores();
        return cores != -0x1 && cores < SANDBOX_CORES;
    }

    bool checkMac(){
        std::string mac = EnvironmentUtils::getMacAddress(INTERFACE_ETH0);
        return !mac.empty() && mac.find(SANDBOX_MAC_VENDOR) == std::string::npos;
    }

    bool checkFilenameRinominato(std::string original){
        std::string filename = EnvironmentUtils::getCurrentFilename();
        return !filename.empty() && filename != original;
    }

    bool checkParentProcessName(){
        std::string name = EnvironmentUtils::getParentProcessName();
        return !name.empty() && (name == SANDBOX_PROCESS_WINDBG_EXE || name == SANDBOX_PROCESS_OLLYDBG);
    }

    bool checkNameRunningProcesses(){
        std::vector<std::string> processes = EnvironmentUtils::getNamesRunningProcesses();
        for(std::vector<std::string>::iterator it = processes.begin(); it != processes.end(); it++){
            if(*it == SANDBOX_PROCESS_WIRESHARK || *it == SANDBOX_PROCESS_WINDBG_EXE || *it == SANDBOX_PROCESS_OLLYDBG){
                return true;
            }
        }
        return false;
    }

    bool checkNumRunningProcesses(){
        int running = EnvironmentUtils::getNumRunningProcesses();
        return running < SANDBOX_RUNNING_PROCESSES;
    }

    bool checkComputerName(){
        std::string name = EnvironmentUtils::getComputerName();
        return !name.empty() && name == SANDBOX_COMPUTER_NAME;
    }

    bool checkUsername(){
        std::string name = EnvironmentUtils::getLoggedUsername();
        return !name.empty() && name == SANDBOX_USERNAME;
    }
}