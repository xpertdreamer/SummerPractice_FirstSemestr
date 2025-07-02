#define _CRT_SECURE_NO_WARNINGS
#ifndef IO_H
#define IO_H
#define MAX_BUFFER 4096

#include <stdio.h>

int readArrayFromFile(const char* filename, int** array, int* size);
int writeArrayToFile(const char* filename, int* array, int size, int swapCount, double time);
int inputArray(const char* filename, int **array, int *capacity);
int *generateRandomArray(const char* filename, int size, int min, int max);

#endif // !IO_H