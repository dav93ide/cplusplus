#include <string>
#include <string.h>
#include <pwd.h>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <boost/filesystem.hpp>

#define RESET "\033[0m"
#define RED "\033[31m"

#define IS_UNDEFINED 0x0
#define IS_REGULAR_FILE 0x1
#define IS_DIRECTORY 0x2

#define PATH_THIS "."
#define PATH_PARENT ".."

#define MOD_ALL 0x1
#define MOD_ONLY_FILES 0x2
#define MOD_ONLY_DIRS 0x3
#define MOD_COPY_FILES 0x4

class File {
    public:
        File(std::string path) : mPath(path) {};
        std::string mPath;
};

class Dir : public File {
    public:
        Dir(std::string path) : File(path) {};
        std::vector<File*> mFiles;
};

namespace FilesComparator {

    Dir *compare_files_of_paths(std::string pathOne, std::string pathTwo);

    void print_formatted_results(Dir main, int deep, int modality, int levelOfDeep, int count);

    void copy_files(Dir main, std::string dest);

    namespace {
        bool compare_paths(std::string pathOne, std::string pathTwo, Dir *main);

        void add_all_files(std::string path, Dir *main);

        std::string format_filepath(std::string base_path, std::string entry);

        int is_regular_file_or_dir(std::string path);
        
        void copy_file(std::string source, std::string dest);
    }

}