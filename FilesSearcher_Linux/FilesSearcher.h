#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "FileContent.h"

#define ENV_HOME    "HOME"
#define LINUX_BASE_DIR_PATH   "/"

#define IS_REGULAR_FILE 0x1
#define IS_DIRECTORY 0x2

#define PATH_THIS "."
#define PATH_PARENT ".."

class FilesSearcher {

    public:
        FilesSearcher(std::vector<std::string> keywords, std::vector<std::string> extensions);
        const char * get_home_path();
        void parse_files(const char *base_path);

        std::vector<FileContent*> &get_found_files();

    private:
        std::vector<std::string> mKeywords;
        std::vector<std::string> mExtensions;
        std::vector<FileContent*> mFoundFiles;

        void search_file_content(const char *file_path);
        int is_regular_file_or_dir(const char *path);
        char *format_filepath(const char *base, const std::initializer_list<char *> &rel);
        char *get_file_ext(const char *file_path);
        char *get_last_relative_path(const char *file_path);
        bool check_file_ext(const char *file_path);
        char *sub_array(const char* arr, int start, int end);
        void print_dir_entry_info(dirent *entry, int num_entry);

};
