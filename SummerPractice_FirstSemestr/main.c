#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "io.h"
#include "utils.h"
#include "insertionSort.h"
#include <locale.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_RANDOM_VALUE 1000

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void generateRandomArrayToFile(const char* filename, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "������ �������� ����� '%s'\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n", size); // ���������� ������ ������� � ������ ������

    srand(time(NULL)); // ������������� ���������� ��������� �����
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", rand() % MAX_RANDOM_VALUE); // ����� �� 0 �� MAX_RANDOM_VALUE-1
    }

    fclose(file);
}

int main() {
    setlocale(LC_ALL, "Ru");

    // ��������
    printf("������� ��������\n");
    printf("�������: ���������� ���������\n");
    printf("����� �������: 4\n");
    printf("���������: �������� �., ����� �., ������� �.\n");
    printf("\n");

    char inputFile[MAX_FILENAME_LENGTH];
    char outputFile[MAX_FILENAME_LENGTH];
    int arraySize;

    // ���� ������� �������
    printf("������� ������ �������: ");
    if (scanf("%d", &arraySize) != 1 || arraySize <= 0) {
        fprintf(stderr, "������������ ������ �������\n");
        return 1;
    }
    while (getchar() != '\n'); // ������� ������ �����

    // ���� ����� ��������� �����
    printf("������� ��� ��������� �����: ");
    if (fgets(inputFile, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "������ ������ ����� �����\n");
        return 1;
    }
    removeNewline(inputFile);

    // ���� ����� ��������� �����
    printf("������� ��� ��������� �����: ");
    if (fgets(outputFile, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "������ ������ ����� �����\n");
        return 1;
    }
    removeNewline(outputFile);

    // ��������� ���������� ������� � ����
    generateRandomArrayToFile(inputFile, arraySize);
    printf("������������ ������ �� %d ��������� ����� � ����� '%s'\n", arraySize, inputFile);

    int* array = NULL;
    int qt = 0;

    // ������ ������� �� �����
    int res = readArrayFromFile(inputFile, &array, &qt);
    if (res != 0) {
        fprintf(stderr, "������ ������ �����\n");
        return 1;
    }

    // ���������� �������
    insertionSort(array, qt);

    // ������ ���������������� ������� � ����
    res = writeArrayToFile(outputFile, array, qt);
    free(array);

    if (res != 0) {
        fprintf(stderr, "������ ������ � ����\n");
        return 1;
    }

    printf("���������� ���������. ��������� �������� � ���� '%s'\n", outputFile);

    return 0;
}