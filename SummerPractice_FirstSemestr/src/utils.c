#include "include/utils.h"

#ifdef _WIN32
#include <windows.h>
#endif

void createFolderIfNotExists(const char* path) {
#ifdef _WIN32
    if (CreateDirectoryW(path, NULL)) {
        printf("Папка \"%s\" создана успешно.\n", path);
    }
    else {
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            return;
        }
        else {
            printf("Ошибка при создании папки \"%s\".\n", path);
        }
    }
#endif
}


void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int inputInt(const char* prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Ошибка! Попробуйте снова: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return value;
}

void inputRange(int* min, int* max) {
    printf("Введите границы диапазона (min max): ");
    while (scanf("%d %d", min, max) != 2) {
        printf("Ошибка! Попробуйте снова: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
}

int inputFilename(char* buffer, const char* prompt) {
    printf("%s", prompt);
    if (fgets(buffer, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения имени файла\n");
        return 1;
    }
    removeNewline(buffer);
    return 0;
}

int saveArrayToInputFile(int size, int* array) {
    int fileNumber = 1;
    char fullPath[256];
    FILE* file = NULL;

    while (1) {
        snprintf(fullPath, sizeof(fullPath), "inputs/%s_%d.txt", "input", fileNumber);
        file = fopen(fullPath, "r");

        if (file == NULL) {
            file = fopen(fullPath, "w");
            break;
        }

        fclose(file);
        fileNumber++;
    }
    
    if (!file) {
        fprintf(stderr, "Ошибка чтения входного файла %s\n", fullPath);
        return 1;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", array[i]);
    }
    fclose(file);

    return 0;
}