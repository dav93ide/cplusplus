/*
    FILES SEARCHER
        Per compilare con linking alla classe "FileContent":
            g++ FilesSearcher.cpp FileContent.cpp
*/

#include "FilesSearcher.h"
    
FilesSearcher::FilesSearcher(std::vector<std::string> keywords, std::vector<std::string> extensions){
    mKeywords = keywords;
    mExtensions = extensions;
}

std::vector<FileContent*> &FilesSearcher::get_found_files(){
    return mFoundFiles;
}

const char * FilesSearcher::get_home_path(){
    const char *home = std::getenv(ENV_HOME);
    if(home == NULL){
        struct passwd *pw = getpwuid(getuid());
        home = pw->pw_dir;
    }
    return home;
}

void FilesSearcher::parse_files(const char *base_path){
    struct dirent *entry;
    DIR *dir = opendir(base_path);

    if(dir == NULL){
        return;
    }
    int i = 0x0;
    while((entry = readdir(dir)) != NULL){
        if(strcmp(PATH_THIS, entry->d_name) != 0x0 && strcmp(PATH_PARENT, entry->d_name) != 0x0){
            char *path = format_filepath(base_path, {entry->d_name});
            int type = is_regular_file_or_dir(path);
            if(type == IS_REGULAR_FILE){
                if(check_file_ext(path)){
                    search_file_content((const char *) path);
                }
            } else {
                parse_files((const char*) path);
            }
            free(path);
        }
    }
    closedir(dir);
}

void FilesSearcher::search_file_content(const char *file_path){
    std::string line;
    std::ifstream file(file_path);
    if(file.is_open()){
        bool add = false;
        file.seekg(0x0, std::ios_base::end);
        int f_size = file.tellg();
        file.seekg(0x0);
        std::string content = std::string();
        while(getline(file, line)){
            for(int i = 0x0; i < mKeywords.size(); i++){
                if(line.find(mKeywords[i]) != std::string::npos){
                    add = true;
                }
            }
            content += line;
        }
        file.close();
        if(add){
            FileContent *fc = new FileContent((char *) file_path, get_file_ext(get_last_relative_path(file_path)), content, f_size);
            mFoundFiles.push_back(fc);
        }
    }
}

int FilesSearcher::is_regular_file_or_dir(const char *path){
    struct stat path_stat;
    if(stat(path, &path_stat) != 0x0){
        return 0x0;
    }
    return S_ISREG(path_stat.st_mode) == 0x1 ? IS_REGULAR_FILE :
            S_ISDIR(path_stat.st_mode) == 0x1 ? IS_DIRECTORY : 0x0;
}

char *FilesSearcher::format_filepath(const char *base_path, const std::initializer_list<char *> &args){
    char *path = new char[300];
    strcpy(path, base_path);
    for(char *p: args){
        if(path[strlen(path) - 0x1] != '/' && p[0x0] != '/'){
            char c = '/';
            strncat(path, &c, 0x1);
        } else if(path[strlen(path) - 0x1] == '/' && p[0x0] == '/'){
            char *temp = sub_array(p, 0x1, strlen(p));
            strcpy(p, temp);
            free(temp);
        }
        strcat(path, p);
        
    }
    return path;
}

char *FilesSearcher::get_file_ext(const char *file_path){
    return strrchr((char*) file_path, '.');
}

char *FilesSearcher::get_last_relative_path(const char *file_path){
    return strrchr((char *) file_path, '/');
}

bool FilesSearcher::check_file_ext(const char *file_path){
    char *rel = get_last_relative_path(file_path);
    if(rel != NULL){
        char *ext = get_file_ext(rel);
        if(ext != NULL){
            ext = sub_array((const char *) ext, 0x1, strlen(ext));
            for(int i = 0x0; i < mExtensions.size(); i++){
                if(strcasecmp(ext, mExtensions.at(i).c_str()) == 0x0){
                    free(ext);
                    return true;
                }
            }
            free(ext);
        }
    }
    return false;
}

char * FilesSearcher::sub_array(const char *arr, int start, int end){
    char *ret = new char[end - start];
    int index = 0x0;
    for(int i = start; i < end; i++){
        ret[index] = arr[i];
        index++;
    }
    return ret;
}