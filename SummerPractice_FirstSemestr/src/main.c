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

    createFolderIfNotExists(L"inputs");
    createFolderIfNotExists(L"outputs");

    printf("������� ��������\n");
    printf("�������: C��������� ���������\n");
    printf("����� �������: 4\n");
    printf("���������: �������� �., ����� �., ������� �.\n");
    printf("\n������� ����� ������� ��� �����������...");
    _getch();

    while (1) {
        int* array = NULL;
        int capacity = 0;
        int size = 0;
        int min = 0;
        int max = 1000;
        int res;
        char inputFile[MAX_FILENAME_LENGTH], outputFile[MAX_FILENAME_LENGTH];

        switch (arrowMenu()) {
        case 1: {
            if (inputFilename(inputFile, "������� ��� ��������� �����: ")) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            if (inputFilename(outputFile, "������� ��� ��������� �����: ")) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            size = inputArray(inputFile, &array, &capacity);
            if (size == -1) {
                printf("������ ��� ����� �������!\n");
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            break;
        }

        case 2: {
            if (inputFilename(inputFile, "������� ��� ��������� �����: ")) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            if (inputFilename(outputFile, "������� ��� ��������� �����: ")) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            size = inputInt("������� ������ �������: ");
            inputRange(&min, &max);
            array = generateRandomArray(inputFile, size, min, max);
            if (array == NULL) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }

            printf("��������������� ������:");
            for (int i = 0; i < size; i++) {
                printf(" %d,", array[i]);
            }
            break;
        }

        case 3: {
            if (inputFilename(inputFile, "������� ��� ��������� �����: ")) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            if (inputFilename(outputFile, "������� ��� ��������� �����: ")) {
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            if ((res = readArrayFromFile(inputFile, &array, &size)) != 0) {
                fprintf(stderr, "������ ������ �����\n");
                printf("������� ����� ������� ��� �����������...");
                _getch();
                continue;
            }
            break;
        }

        case 4:
            return 0;

        default:
            fprintf(stderr, "�������� �����\n");
            printf("������� ����� ������� ��� �����������...");
            _getch();
            continue;
        } 

        if (res = writeArrayToFile(outputFile, array, size, insertionSort(array, size))) {
            fprintf(stderr, "������ ������ � ����\n");
            free(array);
            printf("������� ����� ������� ��� �����������...");
            _getch();
            continue;
        }

        free(array);
            printf("\n���������� ���������.\n�������� ������ ��������� � ���� '%s'. ��������� �������� � ���� '%s'\n", inputFile, outputFile);
            printf("������� ����� ������� ��� �����������...");
            _getch();
    }
    return 0;
}