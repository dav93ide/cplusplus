#include "FilesComparatorAndCopier.h"

namespace FilesComparator {

    Dir *compare_files_of_paths(std::string basePath, std::string pathToCompare){
        Dir *main = new Dir(basePath);
        compare_paths(basePath, pathToCompare, main);
        return main;
    }

    void print_formatted_results(Dir main, int deep, int modality, int levelOfDeep, int count){
        if(deep == 0x0){
            std::cout << main.mPath << std::endl;
            count = std::count(main.mPath.begin(), main.mPath.end(), '/');
        } if(deep == 0x1 && (modality == MOD_ALL || modality == MOD_ONLY_DIRS)){                // Il primo non viene stampato
            std::cout << RED;
            std::cout << main.mPath.substr(main.mPath.find_last_of("/") + 0x1, main.mPath.length()) + "/" << RESET << std::endl;
        }
        if(deep <= levelOfDeep && !main.mFiles.empty()){
            for(auto it = main.mFiles.begin(); it != main.mFiles.end(); it++){
                std::string path = static_cast<File*>(*it)->mPath;
                int type = is_regular_file_or_dir(path);
                if((type == IS_REGULAR_FILE || type == IS_UNDEFINED) && (modality == MOD_ALL || modality == MOD_ONLY_FILES)){
                    for(int i = 0x0; i < std::count(main.mPath.begin(), main.mPath.end(), '/') - count; i++){
                        std::cout << "\t";
                    }
                    std::string sub = path.substr(path.find_last_of("/") + 0x1, path.length());
                } else if(type == IS_DIRECTORY && !main.mFiles.empty()){
                    if(deep > 0x0 && (modality == MOD_ALL || modality == MOD_ONLY_DIRS)){
                        std::cout << RED;
                        for(int i = 0x0; i < std::count(main.mPath.begin(), main.mPath.end(), '/') - count; i++){
                            std::cout << "\t";
                        }
                        std::cout << path.substr(path.find_last_of("/") + 0x1, path.length()) + "/" << RESET << std::endl;
                    }
                    print_formatted_results(*static_cast<Dir*>(*it), ++deep, modality, levelOfDeep, count);   
                }
            }
        }
    }

    void copy_files(Dir main, std::string dest){
        if(!main.mFiles.empty()){
            for(auto it = main.mFiles.begin(); it != main.mFiles.end(); it++){
                std::string path = static_cast<File*>(*it)->mPath;
                int type = is_regular_file_or_dir(path);
                if(type == IS_REGULAR_FILE || type == IS_UNDEFINED){
                    std::string d = dest + path.substr(path.find_last_of("/"), path.length());
                    std::cout << RED << "[!] Copying: " << path << RESET << "\n[!] to: " << d << std::endl << std::endl;
                    copy_file(path, d);
                } else if(type == IS_DIRECTORY){
                    copy_files(*static_cast<Dir*>(*it), dest + path.substr(path.find_last_of("/"), path.length()));
                }
            }
        }
    }

    namespace {
        bool compare_paths(std::string pathOne, std::string pathTwo, Dir *main){
            struct dirent *entryOne;
            DIR *dirOne = opendir(pathOne.c_str());
            bool notFound = false;
            if(dirOne == NULL){
                return false;
            }
            while((entryOne = readdir(dirOne)) != NULL){
                struct dirent *entryTwo;
                DIR *dirTwo = opendir(pathTwo.c_str());
                if(strcmp(PATH_THIS, entryOne->d_name) != 0x0 && strcmp(PATH_PARENT, entryOne->d_name) != 0x0){
                    bool found = false;
                    while((entryTwo = readdir(dirTwo)) != NULL){
                        if(strcmp(PATH_THIS, entryTwo->d_name) != 0x0 && strcmp(PATH_PARENT, entryTwo->d_name) != 0x0 && strcmp(entryOne->d_name, entryTwo->d_name) == 0x0){
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        notFound = true;
                    }
                    std::string newPathOne = format_filepath(pathOne, entryOne->d_name);
                    int type = is_regular_file_or_dir(newPathOne);
                    if(type != IS_DIRECTORY){
                        if(!found){
                            std::string newPathTwo = format_filepath(pathTwo, entryOne->d_name);
                            File *f = new File(newPathTwo);
                            main->mFiles.push_back(f);
                        }
                    } else {
                        if(found){
                            std::string newPathTwo = format_filepath(pathTwo, entryOne->d_name);
                            Dir *d = new Dir(newPathTwo);
                            if(compare_paths(newPathOne, newPathTwo, d)){
                                main->mFiles.push_back(d);
                            }
                        } else {
                            Dir *d = new Dir(newPathOne);
                            main->mFiles.push_back(d);
                            add_all_files(newPathOne, d);
                        }
                    }
                }
                closedir(dirTwo);
            }
            closedir(dirOne);
            return notFound;
        }

        void add_all_files(std::string path, Dir *main){
            struct dirent *entry;
            DIR *dir = opendir(path.c_str());
            while((entry = readdir(dir)) != NULL){
                if(strcmp(PATH_THIS, entry->d_name) != 0x0 && strcmp(PATH_PARENT, entry->d_name) != 0x0){
                    std::string newPath = format_filepath(path, entry->d_name);
                    int type = is_regular_file_or_dir(newPath);
                    if(type != IS_DIRECTORY){
                        File *f = new File(newPath);
                        main->mFiles.push_back(f);
                    } else {
                        Dir *d = new Dir(newPath);
                        main->mFiles.push_back(d);
                        add_all_files(newPath, d);
                    }
                }
            }
        }

        std::string format_filepath(std::string base_path, std::string entry){
            std::string path(base_path);
            if(path[path.length() - 0x1] != '/' && entry[0x0] != '/'){
                char c = '/';
                path += c;
            } else if(path[path.length() - 0x1] == '/' && entry[0x0] == '/'){
                entry = entry.substr(0x1, entry.size());
            }
            path += entry;
            return path;
        }

        int is_regular_file_or_dir(std::string path){
            struct stat pathStat;
            if(stat(path.c_str(), &pathStat) != 0x0){
                return IS_UNDEFINED;
            }
            return S_ISREG(pathStat.st_mode) == 0x1 ? IS_REGULAR_FILE :
                    S_ISDIR(pathStat.st_mode) == 0x1 ? IS_DIRECTORY : 0x0;
        }

        void copy_file(std::string source, std::string dest){
            std::string dirPath = dest.substr(0x0, dest.find_last_of("/"));
            std::string cmd = "mkdir -p " + dirPath;
            std::system(cmd.c_str());
            std::ifstream s(source, std::ios::binary);
            std::ofstream d(dest, std::ios::binary);
            d << s.rdbuf();
        }
    }

}
