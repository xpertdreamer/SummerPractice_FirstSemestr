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

    printf("Учебная практика\n");
    printf("Задание: Cортировка вставками\n");
    printf("Номер бригады: 4\n");
    printf("Выполнили: Будников А., Гурин А., Захаров А.\n");
    printf("\nНажмите любую клавишу для продолжения...");
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
        if (inputFilename(outputFile, "Введите имя выходного файла: ")) return 1;
        size = inputArray(&array, &capacity);
        if (size == -1) {
            printf("Ошибка при вводе массива!\n");
            return 1;
        }
        break;

    case 2:
        if (inputFilename(outputFile, "Введите имя выходного файла: ")) return 1;
        size = inputInt("Введите размер массива: ");
        inputRange(&min, &max);
        array = generateRandomArray(size, min, max);
        if (array == NULL) {
            return 0;
        }

        printf("Сгенерированный массив:");
        for (int i = 0; i < size; i++) {
            printf(" %d,", array[i]);
        }
        break;

    case 3:
        if (inputFilename(inputFile, "Введите имя исходного файла: ")) return 1;
        if (inputFilename(outputFile, "Введите имя выходного файла: ")) return 1;
        if ((res = readArrayFromFile(inputFile, &array, &size)) != 0) {
            fprintf(stderr, "Ошибка чтения файла\n");
            return 1;
        }
        break;

    case 4:
        return 0;

    default:
        fprintf(stderr, "Неверный выбор\n");
        return 1;
    }

    insertionSort(array, size);

    if ((res = writeArrayToFile(outputFile, array, size)) != 0) {
        fprintf(stderr, "Ошибка записи в файл\n");
        free(array);
        return 1;
    }

    free(array);
    printf("\nСортировка завершена. Результат сохранен в файл '%s'\n", outputFile);
    return 0;
}
