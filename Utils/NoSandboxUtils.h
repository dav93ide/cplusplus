#include "EnvironmentUtils.h"

#define SANDBOX_HDD_DIMENSION 100
#define SANDBOX_RAM 2048
#define SANDBOX_CORES 2
#define SANDBOX_MAC_VENDOR "08:00:27"
#define SANDBOX_RUNNING_PROCESSES 50
#define SANDBOX_COMPUTER_NAME "DESKTOP-"
#define SANDBOX_USERNAME "ADMIN"
#define SANDBOX_PROCESS_WINDBG_EXE "WINDBG.EXE"
#define SANDBOX_PROCESS_WIRESHARK "wireshark"
#define SANDBOX_PROCESS_OLLYDBG "ollydbg"

namespace NoSandboxUtils {

    bool checkHddDimension();

    bool checkRam();

    bool checkCpu();

    bool checkMac();

    bool checkFilenameRinominato(std::string original);

    bool checkParentProcessName();

    bool checkNameRunningProcesses();

    bool checkNumRunningProcesses();

    bool checkComputerName();

    bool checkUsername();

}