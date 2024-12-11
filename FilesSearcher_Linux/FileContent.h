#include <stdio.h>
#include <string.h>
#include <string>

class FileContent {
    private:
        char *mPath;
        char *mExt;
        std::string mContent;
        int mSize;

    public:
        FileContent(char *path, char *ext, std::string content, int size);
        ~FileContent();
        char *get_path();
        char *get_ext();
        std::string get_content();
        int get_size();
};