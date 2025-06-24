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
    //Заставка
    printf("Учебная практика\n");
    printf("Задание: сортировка вставками\n");
    printf("Номер бригады: 4\n");
    printf("Выполнили: Будников А., Гурин А., Захаров А.\n");
    printf("\n");

    char inputFile[MAX_FILENAME_LENGTH];
    char outputFile[MAX_FILENAME_LENGTH];

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