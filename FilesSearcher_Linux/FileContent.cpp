#include "FileContent.h"

FileContent::FileContent(char *path, char *ext, std::string content, int size){
    mPath = new char[1000];
    strcpy(mPath, path);
    mExt = ext;
    mContent = content;
    mSize = size;
}

FileContent::~FileContent(){
    delete mPath;
}

char *FileContent::get_path(){
    return mPath;
}

char *FileContent::get_ext(){
    return mExt;
}

std::string FileContent::get_content(){
    return mContent;
}

int FileContent::get_size(){
    return mSize;
}