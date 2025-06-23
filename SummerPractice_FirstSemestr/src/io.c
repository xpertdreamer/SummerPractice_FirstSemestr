#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readArrayFromFile(const char *filename, int **array, int *size) {
  FILE *inputFile = fopen(filename, "r");
  char buffer[MAX_BUFFER];
  int count = 0;

  if (!inputFile) {
    fprintf(stderr, "Error reading input file %s\n", filename);
    return 1;
  }

  if (!fgets(buffer, MAX_BUFFER, inputFile) ||
      sscanf(buffer, "%d", size) != 1 || *size <= 0) {
    fprintf(stderr, "Error reading input file %s\n", filename);
    fclose(inputFile);
    return 2;
  }

  *array = malloc(*size * sizeof(int));

  if (!*array) {
    fprintf(stderr, "Memory allocation error\n");
    fclose(inputFile);
    return 3;
  }

  while (count < *size && fgets(buffer, MAX_BUFFER, inputFile)) {
    char *token = strtok(buffer, " \t\n");
    while (token && count < *size) {
      if (sscanf(token, "%d", &(*array)[count]) != 1) {
        fprintf(stderr, "Error reading line #%d from file %s\n", count + 1, filename);
        free(*array);
        fclose(inputFile);
        return 4;
      }
      count++;
      token = strtok(NULL, " \t\n");
    }
  }

  fclose(inputFile);

  if (count != *size) {
    fprintf(stderr, "Error: expected %d numbers but read %d from file %s\n", *size, count, filename);
    free(*array);
    return 5;
  }

  return 0;
}

int writeArrayToFile(const char *filename, int *array, int size) {
  FILE *outputFile = fopen(filename, "w");

  if (!outputFile) {
    fprintf(stderr, "Error reading input file %s\n", filename);
    return 1;
  }

  fprintf(outputFile, "Sorted array: \n");
  for (int i = 0; i < size; i++) {
    fprintf(outputFile, "%d ", array[i]);
  }
  fprintf(outputFile, "\n");

  fclose(outputFile);

  return 0;
}
