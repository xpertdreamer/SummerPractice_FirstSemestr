#define _CRT_SECURE_NO_WARNINGS

#include "include/insertionSort.h"
#include "include/io.h"
#include "include/mainMenu.h"
#include "include/utils.h"
#include <conio.h>
#include <locale.h>
#include <stdio.h>

int main() {
    setlocale(LC_ALL, "Ru");

    printf("������� ��������\n");
    printf("�������: C��������� ���������\n");
    printf("����� �������: 4\n");
    printf("���������: �������� �., ����� �., ������� �.\n");
    printf("\n������� ����� ������� ��� �����������...");
    _getch();

    int* array = NULL;
    int capacity = 0;
    int size = 0;
    int min = 0;
    int max = 1000;
    int res;
    char inputFile[MAX_FILENAME_LENGTH], outputFile[MAX_FILENAME_LENGTH];

    switch (arrowMenu()) {
    case 1:
        if (inputFilename(outputFile, "������� ��� ��������� �����: ")) return 1;
        size = inputArray(&array, &capacity);
        if (size == -1) {
            printf("������ ��� ����� �������!\n");
            return 1;
        }
        break;

    case 2:
        if (inputFilename(outputFile, "������� ��� ��������� �����: ")) return 1;
        size = inputInt("������� ������ �������: ");
        inputRange(&min, &max);
        array = generateRandomArray(size, min, max);
        if (array == NULL) {
            return 0;
        }

        printf("��������������� ������:");
        for (int i = 0; i < size; i++) {
            printf(" %d,", array[i]);
        }
        break;

    case 3:
        if (inputFilename(inputFile, "������� ��� ��������� �����: ")) return 1;
        if (inputFilename(outputFile, "������� ��� ��������� �����: ")) return 1;
        if ((res = readArrayFromFile(inputFile, &array, &size)) != 0) {
            fprintf(stderr, "������ ������ �����\n");
            return 1;
        }
        break;

    case 4:
        return 0;

    default:
        fprintf(stderr, "�������� �����\n");
        return 1;
    }

    insertionSort(array, size);

    if ((res = writeArrayToFile(outputFile, array, size)) != 0) {
        fprintf(stderr, "������ ������ � ����\n");
        free(array);
        return 1;
    }

    free(array);
    printf("\n���������� ���������. ��������� �������� � ���� '%s'\n", outputFile);
    return 0;
}
