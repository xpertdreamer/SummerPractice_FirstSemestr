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
        fprintf(stderr, "Ошибка создания файла '%s'\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n", size); // Записываем размер массива в первую строку

    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", rand() % MAX_RANDOM_VALUE); // Числа от 0 до MAX_RANDOM_VALUE-1
    }

    fclose(file);
}

int main() {
    setlocale(LC_ALL, "Ru");

    // Заставка
    printf("Учебная практика\n");
    printf("Задание: сортировка вставками\n");
    printf("Номер бригады: 4\n");
    printf("Выполнили: Будников А., Гурин А., Захаров А.\n");
    printf("\n");

    char inputFile[MAX_FILENAME_LENGTH];
    char outputFile[MAX_FILENAME_LENGTH];
    int arraySize;

    // Ввод размера массива
    printf("Введите размер массива: ");
    if (scanf("%d", &arraySize) != 1 || arraySize <= 0) {
        fprintf(stderr, "Некорректный размер массива\n");
        return 1;
    }
    while (getchar() != '\n'); // Очистка буфера ввода

    // Ввод имени исходного файла
    printf("Введите имя исходного файла: ");
    if (fgets(inputFile, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения имени файла\n");
        return 1;
    }
    removeNewline(inputFile);

    // Ввод имени выходного файла
    printf("Введите имя выходного файла: ");
    if (fgets(outputFile, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения имени файла\n");
        return 1;
    }
    removeNewline(outputFile);

    // Генерация случайного массива в файл
    generateRandomArrayToFile(inputFile, arraySize);
    printf("Сгенерирован массив из %d случайных чисел в файле '%s'\n", arraySize, inputFile);

    int* array = NULL;
    int qt = 0;

    // Чтение массива из файла
    int res = readArrayFromFile(inputFile, &array, &qt);
    if (res != 0) {
        fprintf(stderr, "Ошибка чтения файла\n");
        return 1;
    }

    // Сортировка массива
    insertionSort(array, qt);

    // Запись отсортированного массива в файл
    res = writeArrayToFile(outputFile, array, qt);
    free(array);

    if (res != 0) {
        fprintf(stderr, "Ошибка записи в файл\n");
        return 1;
    }

    printf("Сортировка завершена. Результат сохранен в файл '%s'\n", outputFile);

    return 0;
}