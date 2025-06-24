#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "utils.h"
#include "insertionSort.h"
#include <locale.h>

#define MAX_FILENAME_LENGTH 256

void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    //��������
    printf("������� ��������\n");
    printf("�������: ���������� ���������\n");
    printf("����� �������: 4\n");
    printf("���������: �������� �., ����� �., ������� �.\n");
    printf("\n");

    char inputFile[MAX_FILENAME_LENGTH];
    char outputFile[MAX_FILENAME_LENGTH];

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