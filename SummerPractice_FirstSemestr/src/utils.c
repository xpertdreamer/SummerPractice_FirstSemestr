#include "include/utils.h"

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
        printf("������! ���������� �����: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return value;
}

void inputRange(int* min, int* max) {
    printf("������� ������� ��������� (min max): ");
    while (scanf("%d %d", min, max) != 2) {
        printf("������! ���������� �����: ");
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