/**
 COMPILATION:
    g++ test_files_searcher.cpp -o files_searcher.out FilesSearcher_Linux/FilesSearcher.cpp FilesSearcher_Linux/FileContent.cpp
**/

#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "../FilesSearcher/FilesSearcher.h"

#define SIZE_SEARCH_MATRIX 0x6
#define SIZE_EXTS_ARRAY 0x1

int main(){
    using namespace std;

    std::vector<std::string> matrix  = {"test", "prova", "lol", "asd", "lmao", "rotfl"};
    std::vector<std::string> exts = {"txt"};

    FilesSearcher fs = FilesSearcher(matrix, exts);
    
    std::string home_path = fs.get_home_path() + "/Scrivania/prova2";
    cout << "[+] Home Path: " << home_path << endl;
    
    fs.parse_files(home_path);
    
    std::cout << "\n\n\n\n\nprinting files found...\n\n\n\n\n";
    if(fs.get_found_files().size() > 0x0){
        std::cout << "HERE" << std::endl;
        for(FileContent *fc : fs.get_found_files()){
            std::cout << "file path == " << fc->get_path() << " file content == " << fc->get_content() << std::endl;
            delete fc;
        }
    }
}
