#include "fileUtils.h"
bool isFileExists(const char* fileName) {
    FILE *fptr = fopen(fileName, "rb");
    if (fptr) {
        fclose(fptr);
        return true;
    }

    return false;
}   

FILE* createFile(const char* fileName) {
    FILE *fptr = fopen(fileName, "w+b");
    if (fptr) {
        return fptr;
    }
    return NULL;
}

FILE* openFile(const char* fileName, const char* mode) {
    FILE *fptr = fopen(fileName, mode);
    if (fptr) {
        return fptr;
    }
    return NULL;
}
