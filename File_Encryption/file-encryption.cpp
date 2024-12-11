#include "file-encription.h"

// Cifra un singolo file
void encryptFile(std::string filePath, int key){
    std::fstream file, tempFile;
    std::string tempFilePath = "temp.txt";

    file.open(filePath, std::ios::in);
    tempFile.open(tempFilePath, std::ios::out);

    char byte;
    while(file >> std::noskipws >> byte){
        byte ^= key;
        tempFile << byte;
    }

    file.close();
    tempFile.close();

    file.open(filePath, std::ios::out);
    tempFile.open(tempFilePath, std::ios::in);

    while(tempFile >> std::noskipws >> byte){
        file << byte;
    }


    file.close();
    tempFile.close();

    remove(tempFilePath.c_str());
}

// Legge attraverso tutte le directories e i files in una directory. Se trova un file lo cifra, se trova una directory legge attraverso quella directory.
void encryptDirectory(std::string dirPath, int key){
    DIR *directory;
    struct dirent* entry;
    struct stat status;
    std::string path;

    if((directory == opendir(dirPath.c_str())) != NULL){
        while((entry = readdir(directory)) != NULL){
            if(strcmp(entry->d_name, ".") != 0x0 && strcmp(entry->d_name, "..") != 0x0){
                path = dirPath + "\\" + entry->d_name;
                stat(path.c_str(), &status);
                if(S_ISDIR(status.st_mode)){
                    encryptDirectory(path, key);
                } else {
                    encryptFile(path, key);
                }
            }
        }
    }
}

int main(){
    encryptFile("/home/z3r0/Scrivania/All/Programming/C++/Exercises_Linux/File_Encryption/lol.txt", 666);
}