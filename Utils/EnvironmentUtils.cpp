/*
    Compilation:
        g++ main.cpp Utils/EnvironmentUtils.cpp -lX11 -lprocps -lblkid -o test_main.out
*/

#include "EnvironmentUtils.h"
#include <cstdio>
#include <iostream>
namespace EnvironmentUtils {

    /*
        Ritorna dimensione HDD in Gb (richiede Sudo)
    */
    double getDimensionHdd(std::string partition){
        unsigned long long numBlocks = 0;
        int fd = open(partition.c_str(), O_RDONLY);
        if(fd != -0x1){
            if(ioctl(fd, BLKGETSIZE64, &numBlocks) != -0x1){
                close(fd);
                return (double) numBlocks / (1024 * 1024 * 1024);
            }
        }
        close(fd);
        return -0x1;
    }

    /*
        Ritorna il modello dell'HDD corrente (richiede Sudo)
    */
    std::string getModelHdd(std::string partition){
        struct hd_driveid hd;
        int fd;
        if((fd = open(partition.c_str(), O_RDONLY | O_NONBLOCK)) != -0x1){
            if(ioctl(fd, HDIO_GET_IDENTITY, &hd) != -0x1){
                close(fd);
                return std::string(reinterpret_cast<char*>(hd.model));
            }
        }
        close(fd);
        return "";
        
    }

    /*
        Ritorna il nome della partizione corrente
    */
    std::string getCurrentPartitionName(std::string filepath){
        struct stat s;
        if(lstat(filepath.c_str(), &s) != 0x0){
            return "";
        }
        char *c = blkid_devno_to_devname(s.st_dev);
        return c != NULL ? std::string(c) : "";
    }

    /*
        Ritorna nome dell'eseguibile corrente
    */
    std::string getCurrentFilename(){
        char selfpath[128];
        memset (selfpath, 0, sizeof (selfpath));
        if (readlink ("/proc/self/exe", selfpath, sizeof (selfpath) - 1) < 0){
            return "";
        };
        std::string path = std::string(selfpath);
        return path.substr(path.find_last_of("/") + 0x1, path.size());
    }

    /*
        Ritorna una stringa contenente il percorso dell'eseguibile attuale
    */
    std::string getCurrentFilepath(){
        char selfpath[128];
        memset (selfpath, 0, sizeof (selfpath));
        if (readlink ("/proc/self/exe", selfpath, sizeof (selfpath) - 1) < 0){
            return "";
        };
        return std::string(selfpath);
    }

    /*
        Ritorna una stringa contenente le info del sistema
    */
    std::string getStringSysInfo(){
        std::string ret = std::string();
        struct utsname uts;

        int res = uname(&uts);

        ret =   std::string("######################\n") +
                "# System Name:\t" + std::string(uts.sysname) + "\n" +
                "# Node Name:\t" + uts.nodename + "\n" +
                "# Release:\t" + uts.release + "\n" +
                "# Version:\t" + uts.version + "\n" +
                "# Machine:\t" + uts.machine + "\n" +
                "######################\n\n";
        return ret;
    }

    /*
        Ritorna il numero di processi in esecuzione
    */
    int getNumRunningProcesses(){
        int num = 0x0;
        PROCTAB* proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
        proc_t procInfo;
        memset(&procInfo, 0, sizeof(procInfo));
        while(readproc(proc, &procInfo) != NULL){
            num++;
        }
        return num;
    }

    /*
        Ritorna una stringa con tutte le info sui processi in esecuzione
    */
    std::string getStringRunningProcessesInfo(){
        PROCTAB* proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
        proc_t procInfo;
        memset(&procInfo, 0, sizeof(procInfo));

        std::string ret = "";
        while(readproc(proc, &procInfo) != NULL){
            ret +=  std::string("############################\n") +
                    "# Name:\t" + procInfo.cmd + "\n"
                    "# Task ID:\t" + std::to_string(procInfo.tid) + "\n" +
                    "# Parent PID:\t" + std::to_string(procInfo.ppid) + "\n" +
                    "###########################\n\n";
        }

        return ret;
    }

    /*
        Ritorna un vettore con tutti i nomi dei processi in esecuzione
    */
    std::vector<std::string> getNamesRunningProcesses(){
        PROCTAB* proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);
        proc_t procInfo;
        memset(&procInfo, 0, sizeof(procInfo));
        std::vector<std::string> ret = std::vector<std::string>();
        
        while(readproc(proc, &procInfo) != NULL){
            ret.push_back(procInfo.cmd);
        }

        return ret;
    }

    /*
        Ritorna PID processo corrente
    */
    pid_t getCurrentProcessPid(){
        return getpid();
    }

    /*
        Ritorna PID processo padre
    */
    pid_t getParentProcessPid(){
        return getppid();
    }

    /*
        Ritorna nome del processo padre
    */
    std::string getParentProcessName(){
        return getProcessName(getParentProcessPid());
    }
    
    /*
        Ritorna nome di un processo
    */  
    std::string getProcessName(const pid_t pid){
        char procFile[BUFSIZ];
        char name[BUFSIZ];
        sprintf(procFile, "/proc/%d/cmdline", pid);
        FILE *f = fopen(procFile, "r");
        if(f){
            size_t size = fread(name, sizeof(char), sizeof(procFile), f);
            if(size > 0x0){
                if('\n' == name[size - 0x1]){
                        name[size - 0x1] = '\0';
                }
                return std::string(name);
            }
            fclose(f);
        }
        return "";
    }

    /*
        Ottiene MAC address
    */
    std::string getMacAddress(const std::string &ifName){
        std::ifstream interface("/sys/class/net/" + ifName + "/address");
        std::string str((std::istreambuf_iterator<char>(interface)), std::istreambuf_iterator<char>());
        return str;
    }

    uint64_t getMacAddressUint64(const std::string &ifName){
        std::string str = getMacAddress(ifName);
        if(str.length() > 0x0){
            std::string hex = std::regex_replace(str, std::regex(":"), "");
            return std::stoull(hex, 0, 16);
        }
        return -0x1;
    }

    /*
        Ritorna lista di nomi dei File Systems montati
    */
    std::vector<std::string> getListMountedFileSystemsNames(){
        std::vector<std::string> ret = std::vector<std::string>();
        std::ifstream mountInfo("/proc/mounts");
        while(!mountInfo.eof()){
            mount mount;
            mountInfo >> mount.device >> mount.destination >> mount.fstype >> mount.options >> mount.dump >> mount.pass;
            if(mount.device != ""){
                ret.push_back(mount.device);
            }
        }
        return ret;
    }

    /*
        Ritorna lista oggetti Mount che identificato File Systems montati
    */
    std::vector<mount> getListMountedFileSystemsInfo(){
        std::vector<mount> ret = std::vector<mount>();
        std::ifstream mountInfo("/proc/mounts");
        while(!mountInfo.eof()){
            mount mount;
            mountInfo >> mount.device >> mount.destination >> mount.fstype >> mount.options >> mount.dump >> mount.pass;
            if(mount.device != ""){
                ret.push_back(mount);
            }
        }
        return ret;
    }

    /*
        Ritorna la RAM del computer in Kb.
    */
    unsigned long getTotRam(){
        std::string token;
        std::ifstream file ("/proc/meminfo");
        while(file >> token){
            if(token == "MemTotal:"){
                unsigned long mem;
                if(file >> mem){
                    return mem;
                } else {
                    return -0x1;
                }
            }
            // Ignora resto della linea
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return -0x1;
    }

    /*
        Ritorna il numero di threads che l'hardware puo`eseguire in maniera concorrente.
    */
    unsigned int getNumberOfCores(){
        return sysconf(_SC_NPROCESSORS_CONF);
    }

    /*
        Ritorna l'username attualmente loggato nel computer.
    */
    std::string getLoggedUsername(){
        uid_t uid = geteuid();
        struct passwd *pw = getpwuid(uid);
        if(pw){
            return std::string(pw->pw_name);
        }
        return "";
    }

    /*
        Ritorna il percorso della directory home dell'utente.
    */
    std::string getPathUserHomeDir(){
        uid_t uid = geteuid();
        struct passwd *pw = getpwuid(uid);
        if(pw){
            return std::string(pw->pw_dir);
        }
        return "";
    }

    /*
        Ritorna il nome del computer.
    */
    std::string getComputerName(){
        char hostname[HOST_NAME_MAX];
        gethostname(hostname, HOST_NAME_MAX);
        return std::string(hostname);
    }

    /*
        Ritorna il nome della finestra corrente
    */
    std::string getNameCurrentWindow(){
        Display *display;
        unsigned long window;
        char *displayName = NULL;

        display = XOpenDisplay(displayName);
        if(display != NULL){
            int screen = XDefaultScreen(display);
            window = RootWindow(display, screen);
            window = getLongPropertyWindow((char *) PROPERTY_ACTIVE_WINDOW, window, display);
            return std::string(reinterpret_cast<char*>(getStringPropertyWindow((char *) PROPERTY_WM_NAME, window, display)));
        }
        return "";
    }

    /*
        Ritorna il PID della finestra corrente
    */
    unsigned long getPidCurrentWindowProcess(){
        Display *display;
        unsigned long window;
        char *displayName = NULL;

        display = XOpenDisplay(displayName);
        if(display != NULL){
            int screen = XDefaultScreen(display);
            window = RootWindow(display, screen);
            window = getLongPropertyWindow((char *) PROPERTY_ACTIVE_WINDOW, window, display);
            return getLongPropertyWindow((char *) PROPERTY_WM_PID, window, display);
        }
        return -0x1;
    }

    namespace {

        /*
            Prende info specifica proprieta`di una finestra
        */
        unsigned char *getStringPropertyWindow(char *property, unsigned long window, Display *display){
            Atom actualType, filterAtom;
            int actualFormat, status;
            unsigned long nItems, bytesAfter;
            unsigned char *prop;

            filterAtom = XInternAtom(display, property, True);
            status = XGetWindowProperty(display, window, filterAtom, 0, MAX_STR, False, AnyPropertyType, &actualType, &actualFormat, &nItems, &bytesAfter, &prop);

            return prop;
        }

        /*
            Prende info specifica proprieta`di una finestra
        */
        unsigned long getLongPropertyWindow(char *property, unsigned long window, Display *display){
            unsigned char *prop = getStringPropertyWindow(property, window, display);
            unsigned long longProperty = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
            return longProperty;
        }

    }
    
}