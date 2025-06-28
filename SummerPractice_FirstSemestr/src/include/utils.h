#define _CRT_SECURE_NO_WARNINGS
#ifndef UTILS_H
#define UTILS_H

#define MAX_FILENAME_LENGTH 256

#include <stdio.h>

void removeNewline(char* str);
void createFolderIfNotExists(const char* path);
int inputInt(const char* prompt);
void inputRange(int* min, int* max);
int inputFilename(char* buffer, const char* prompt);
int saveArrayToInputFile(int size, int *array);

#endif // !UTILS_H