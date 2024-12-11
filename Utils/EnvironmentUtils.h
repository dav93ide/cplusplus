#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <proc/readproc.h>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <streambuf>
#include <regex>
#include <blkid/blkid.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/hdreg.h>

#define PROPERTY_ACTIVE_WINDOW "_NET_ACTIVE_WINDOW"
#define PROPERTY_WM_NAME "_NET_WM_NAME"
#define PROPERTY_WM_PID "_NET_WM_PID"

#define INTERFACE_ETH0 "eth0"

#define MAX_STR 1000

namespace EnvironmentUtils {

    struct mount {
        std::string device;
        std::string destination;
        std::string fstype;
        std::string options;
        int dump;
        int pass;
    };

    double getDimensionHdd(std::string partition);

    std::string getModelHdd(std::string partition);

    std::string getCurrentPartitionName(std::string filepath);

    std::string getCurrentFilename();

    std::string getCurrentFilepath();

    std::string getStringSysInfo();

    int getNumRunningProcesses();

    std::string getStringRunningProcessesInfo();

    std::vector<std::string> getNamesRunningProcesses(); 

    pid_t getCurrentProcessPid();

    pid_t getParentProcessPid();

    std::string getParentProcessName();

    std::string getProcessName(const pid_t pid);

    std::string getMacAddress(const std::string &ifName);

    uint64_t getMacAddressUint64(const std::string &ifName);

    std::vector<std::string> getListMountedFileSystemsNames();

    std::vector<mount> getListMountedFileSystemsInfo();

    unsigned long getTotRam();

    unsigned int getNumberOfCores();

    std::string getLoggedUsername();

    std::string getPathUserHomeDir();

    std::string getComputerName();

    std::string getNameCurrentWindow();

    unsigned long getPidCurrentWindowProcess();

    namespace {

        unsigned char *getStringPropertyWindow(char *property, unsigned long window, Display *display);

        unsigned long getLongPropertyWindow(char *property, unsigned long window, Display *display);

    }

}