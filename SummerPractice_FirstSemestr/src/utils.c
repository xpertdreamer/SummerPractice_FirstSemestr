#include "include/utils.h"
#include <windows.h>

void createFolderIfNotExists(const char* path) {
    if (CreateDirectoryW(path, NULL)) {
        printf("����� \"%s\" ������� �������.\n", path);
    }
    else {
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            return;
        }
        else {
            printf("������ ��� �������� ����� \"%s\".\n", path);
        }
    }
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
        printf("������! ������� ������� �����. ���������� �����: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return value;
}

void inputRange(int* min, int* max) {
    printf("������� ������� ��������� (min max): ");
    while (scanf("%d %d", min, max) != 2) {
        printf("������! �������� �������. ���������� �����: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
}

int inputFilename(char* buffer, const char* prompt) {
    printf("%s", prompt);
    if (fgets(buffer, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "������ ������ ����� �����\n");
        return 1;
    }
    removeNewline(buffer);
    return 0;
}

int saveArrayToInputFile(int size, int* array, const char* filename) {
    char fullPath[256];

    snprintf(fullPath, sizeof(fullPath), "%s%s", "inputs/", filename);

    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".csv") != 0) {
        strncat(fullPath, ".csv", 256 - strlen(fullPath) - 1);
    }

    FILE* file = fopen(fullPath, "w");
    if (!file) {
        fprintf(stderr, "������ ������ �������� ����� %s\n", filename);
        return 1;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        if (i < size - 1) {
            fprintf(file, "%d,", array[i]);
        }
        else
        {
            fprintf(file, "%d", array[i]);
        }
    }
    fclose(file);

    return 0;
}