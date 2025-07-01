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

    printf("Учебная практика\n");
    printf("Задание: Cортировка вставками\n");
    printf("Номер бригады: 4\n");
    printf("Выполнили: Будников А., Гурин А., Захаров А.\n");
    printf("\nНажмите любую клавишу для продолжения...");
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
            if (inputFilename(inputFile, "Введите имя исходного файла: ")) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            if (inputFilename(outputFile, "Введите имя выходного файла: ")) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            size = inputArray(inputFile, &array, &capacity);
            if (size == -1) {
                printf("Ошибка при вводе массива!\n");
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            break;
        }

        case 2: {
            if (inputFilename(inputFile, "Введите имя исходного файла: ")) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            if (inputFilename(outputFile, "Введите имя выходного файла: ")) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            size = inputInt("Введите размер массива: ");
            inputRange(&min, &max);
            array = generateRandomArray(inputFile, size, min, max);
            if (array == NULL) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }

            printf("Сгенерированный массив:");
            for (int i = 0; i < size; i++) {
                printf(" %d,", array[i]);
            }
            break;
        }

        case 3: {
            if (inputFilename(inputFile, "Введите имя исходного файла: ")) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            if (inputFilename(outputFile, "Введите имя выходного файла: ")) {
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            if ((res = readArrayFromFile(inputFile, &array, &size)) != 0) {
                fprintf(stderr, "Ошибка чтения файла\n");
                printf("Нажмите любую клавишу для продолжения...");
                _getch();
                continue;
            }
            break;
        }

        case 4:
            return 0;

        default:
            fprintf(stderr, "Неверный выбор\n");
            printf("Нажмите любую клавишу для продолжения...");
            _getch();
            continue;
        } 

        if (res = writeArrayToFile(outputFile, array, size, insertionSort(array, size))) {
            fprintf(stderr, "Ошибка записи в файл\n");
            free(array);
            printf("Нажмите любую клавишу для продолжения...");
            _getch();
            continue;
        }

        free(array);
            printf("\nСортировка завершена.\nИсходные данные сохранены в файл '%s'. Результат сохранен в файл '%s'\n", inputFile, outputFile);
            printf("Нажмите любую клавишу для продолжения...");
            _getch();
    }
    return 0;
}