#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void encryptFile(std::string filePath, int key);

void encryptDirectory(std::string dirPath, int key);