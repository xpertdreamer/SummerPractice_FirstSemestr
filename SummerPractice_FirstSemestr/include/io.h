#ifndef IO_H
#define IO_H
#define MAX_BUFFER 4096

#include <stdio.h>

int readArrayFromFile(const char* filename, int** array, int* size);
int writeArrayToFile(const char* filename, int* array, int size);

#endif // !IO_H
