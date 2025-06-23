#include "insertionSort.h"
#include "io.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void printFileContents(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open file %s\n", filename);
        return;
    }
    char line[MAX_BUFFER];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);
}

int compareFiles(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    char buffer1[MAX_BUFFER], buffer2[MAX_BUFFER];

    if (!f1 || !f2) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 0;
    }

    while (1) {
        char *res1 = fgets(buffer1, MAX_BUFFER, f1);
        char *res2 = fgets(buffer2, MAX_BUFFER, f2);

        if (res1 == NULL && res2 == NULL) {
            fclose(f1);
            fclose(f2);
            return 1;
        }

        if (res1 == NULL || res2 == NULL) {
            fclose(f1);
            fclose(f2);
            return 0;
        }

        int len1 = strlen(buffer1);
        while (len1 > 0 && isspace(buffer1[len1 - 1])) {
            buffer1[--len1] = '\0';
        }

        int len2 = strlen(buffer2);
        while (len2 > 0 && isspace(buffer2[len2 - 1])) {
            buffer2[--len2] = '\0';
        }

        if (strcmp(buffer1, buffer2) != 0) {
          printf("Difference found:\n");
          printf("Actual:   '%s' (len=%d)\n", buffer1, (int)strlen(buffer1));
          printf("Expected: '%s' (len=%d)\n", buffer2, (int)strlen(buffer2));
          fclose(f1);
          fclose(f2);
          return 0;
        }

        if (strcmp(buffer1, buffer2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
}

void runTest(const char *inputFile, const char *expectedFile, int testNumber) {
    int *array = NULL;
    int size = 0;

    if (readArrayFromFile(inputFile, &array, &size) != 0) {
        printf("Test %d: ❌ Error reading input file %s\n", testNumber, inputFile);
        return;
    }

    clock_t start = clock();
    insertionSort(array, size);
    clock_t end = clock();

    double duration_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

    const char *tempFile = "temp_output.txt";
    if (writeArrayToFile(tempFile, array, size) != 0) {
        printf("Test %d: ❌ Error writing output file\n", testNumber);
        free(array);
        return;
    }

    int cmp = compareFiles(tempFile, expectedFile);

    printf("Test %d: %s | sorting time: %.3f ms\n",
           testNumber, cmp ? "✅ Success" : "❌ Failure", duration_ms);

    if (!cmp) {
        printf("=== Output file contents ===\n");
        printFileContents(tempFile);
        printf("=== Expected file contents ===\n");
        printFileContents(expectedFile);
    }

    free(array);
    remove(tempFile); 
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    const char *inputs[] = {"tests/input1.txt", "tests/input2.txt", "tests/input3.txt"};
    const char *expecteds[] = {"tests/expected1.txt", "tests/expected2.txt", "tests/expected3.txt"};
    const int numTests = sizeof(inputs) / sizeof(inputs[0]);

    printf("=== Running sorting tests ===\n");

    for (int i = 0; i < numTests; i++) {
        runTest(inputs[i], expecteds[i], i + 1);
    }

    return 0;
}
