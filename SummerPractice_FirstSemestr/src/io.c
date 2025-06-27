#define _CRT_SECURE_NO_WARNINGS

#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 4096

int readArrayFromFile(const char* filename, int** array, int* size) {
    char fullPath[256] = "inputs/"; 
    strcat(fullPath, filename);
    if (strstr(fullPath, ".txt") == NULL) {
        strcat(fullPath, ".txt");
    }

    FILE* inputFile = fopen(fullPath, "r");
    char buffer[MAX_BUFFER];
    int count = 0;

    if (!inputFile) {
        fprintf(stderr, "������ ������ �������� ����� %s\n", filename);
        return 1;
    }

    if (!fgets(buffer, MAX_BUFFER, inputFile) ||
        sscanf(buffer, "%d", size) != 1 || *size <= 0) {
        fprintf(stderr, "������ ������ �������� ����� %s\n", filename);
        fclose(inputFile);
        return 2;
    }

    *array = malloc(*size * sizeof(int));

    if (!*array) {
        fprintf(stderr, "������ ��������� ������\n");
        fclose(inputFile);
        return 3;
    }

    while (count < *size && fgets(buffer, MAX_BUFFER, inputFile)) {
        char* token = strtok(buffer, " \t\n");
        while (token && count < *size) {
            if (sscanf(token, "%d", &(*array)[count]) != 1) {
                fprintf(stderr, "������ ��� ������ ������ #%d �� ����� %s\n", count + 1, filename);
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
        fprintf(stderr, "������: ��������� %d �����, �� ��������� %d �� ����� %s\n", *size, count, filename);
        free(*array);
        return 5;
    }

    return 0;
}

int writeArrayToFile(const char* filename, int* array, int size) {
    if (!filename || !array || size <= 0) {
        fprintf(stderr, "������������ ������� ������\n");
        return 1;
    }

    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "%s%s", "outputs/", filename);

    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".txt") != 0) {
        strncat(fullPath, ".txt", 256 - strlen(fullPath) - 1);
    }

    FILE* outputFile = fopen(fullPath, "w");
    if (!outputFile) {
        fprintf(stderr, "������ ������ �������� ����� %s\n", filename);
        return 1;
    }

    fprintf(outputFile, "��������������� ������: \n");
    for (int i = 0; i < size; i++) {
        fprintf(outputFile, "%d ", array[i]);
    }
    fprintf(outputFile, "\n");

    fclose(outputFile);

    return 0;
}

int inputArray(int** array, int* capacity) {
    printf("������� �������� ������� ����� ������: ");

    int num;
    int size = 0;
    char buffer[MAX_BUFFER];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("������ �����!\n");
        return -1;
    }

    char* token = strtok(buffer, " \t\n");
    while (token != NULL) {
        if (sscanf(token, "%d", &num) != 1) {
            printf("������: ������� �� �����!\n");
            return -1;
        }

        if (size >= *capacity) {
            *capacity = (*capacity == 0) ? 1 : *capacity * 2;
            int *temp = (int*)realloc(*array, *capacity * sizeof(int));
            if (temp == NULL) {
                printf("������ ��������� ������!\n");
                return -1;
            }
            *array = temp;
        }

        (*array)[size++] = num;
        token = strtok(NULL, " \t\n");
    }

    return size;
}

int* generateRandomArray(int size, int min, int max) {
    if (size <= 0 || min >= max) {
        printf("������������ ��������� ���������!\n");
        return NULL;
    }

    int *array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("������ ��������� ������!\n");
        return 1;
    }

    srand(time(NULL)); 

    for (int i = 0; i < size; i++) {
        array[i] = min + rand() % (min - max + 1);
    }

    return array;
}