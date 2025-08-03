#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdio.h>
#include <stdbool.h>

bool isFileExists(const char* fileName);
FILE* createFile(const char* fileName);
FILE* openFile(const char* fileName, const char* mode);

#endif // FILEUTILS_H


