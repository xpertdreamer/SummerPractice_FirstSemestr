#define _CRT_SECURE_NO_WARNINGS

#include "include/io.h"
#include "include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 4096

int readArrayFromFile(const char* filename, int** array, int* size) {
    char fullPath[256] = "inputs/"; 
    strcat(fullPath, filename);
    if (strstr(fullPath, ".csv") == NULL) {
        strcat(fullPath, ".csv");
    }

    FILE* inputFile = fopen(fullPath, "r");
    char buffer[MAX_BUFFER];
    int count = 0;

    if (!inputFile) {
        fprintf(stderr, "Ошибка чтения входного файла %s\n", filename);
        return 1;
    }

    if (!fgets(buffer, MAX_BUFFER, inputFile) ||
        sscanf(buffer, "%d", size) != 1 || *size <= 0) {
        fprintf(stderr, "Ошибка чтения входного файла %s\n", filename);
        fclose(inputFile);
        return 2;
    }

    *array = malloc(*size * sizeof(int));

    if (!*array) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        fclose(inputFile);
        return 3;
    }

    while (count < *size && fgets(buffer, MAX_BUFFER, inputFile)) {
        char* token = strtok(buffer, " \t\n");
        while (token && count < *size) {
            if (sscanf(token, "%d", &(*array)[count]) != 1) {
                fprintf(stderr, "Ошибка при чтении строки #%d из файла %s\n", count + 1, filename);
                free(*array);
                fclose(inputFile);
                return 4;
            }
            count++;
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(inputFile);

    if (count != *size) {
        fprintf(stderr, "Ошибка: ожидалось %d чисел, но прочитано %d из файла %s\n", *size, count, filename);
        free(*array);
        return 5;
    }

    return 0;
}

int writeArrayToFile(const char* filename, int* array, int size, int swapCount) {
    if (!filename || !array || size <= 0) {
        fprintf(stderr, "Некорректные входные данные\n");
        return 1;
    }

    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", "outputs/", filename);

    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".csv") != 0) {
        strncat(fullPath, ".csv", 256 - strlen(fullPath) - 1);
    }

    FILE* outputFile = fopen(fullPath, "w");
    if (!outputFile) {
        fprintf(stderr, "Ошибка чтения входного файла %s\n", filename);
        return 1;
    }

    fprintf(outputFile, "Количество перестановок: %d \n", swapCount);
    for (int i = 0; i < size; i++) {
        if (i < size - 1) {
            fprintf(outputFile, "%d,", array[i]);
        }
        else {
            fprintf(outputFile, "%d", array[i]);
        }
    }
    fprintf(outputFile, "\n");

    fclose(outputFile);

    return 0;
}

int inputArray(const char* filename, int** array, int* capacity) {
    printf("Введите элементы массива через пробел: ");

    int num;
    int size = 0;
    char buffer[MAX_BUFFER];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Ошибка ввода!\n");
        return -1;
    }

    char* token = strtok(buffer, " \t\n");
    while (token != NULL) {
        if (sscanf(token, "%d", &num) != 1) {
            printf("Ошибка: введено не число!\n");
            return -1;
        }

        if (size >= *capacity) {
            *capacity = (*capacity == 0) ? 1 : *capacity * 2;
            int *temp = (int*)realloc(*array, *capacity * sizeof(int));
            if (temp == NULL) {
                printf("Ошибка выделения памяти!\n");
                return -1;
            }
            *array = temp;
        }

        (*array)[size++] = num;
        token = strtok(NULL, " \t\n");
    }

    if (saveArrayToInputFile(size, *array, filename) == 1) {
        fprintf(stderr, "Ошибка при записи в файлы\n");
        return -1;
    }

    return size;
}

int* generateRandomArray(const char* filename, int size, int min, int max) {    
    if (size <= 0 || min >= max) {
        printf("Некорректные параметры генерации!\n");
        return NULL;
    }

    int *array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    srand(time(NULL)); 

    for (int i = 0; i < size; i++) {
        array[i] = min + rand() % (min - max + 1);
    }

    if (saveArrayToInputFile(size, array, filename) == 1) {
        fprintf(stderr, "Ошибка при записи в файлы\n");
        return NULL;
    }

    return array;
}
