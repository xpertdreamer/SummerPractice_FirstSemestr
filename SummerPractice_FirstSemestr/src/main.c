#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "utils.h"
#include "insertionSort.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Использование: %s <входной_файл> <выходной_файл>\n",
            argv[0]);
    return 1;
  }

  const char *inputFile = argv[1];
  const char *outputFile = argv[2];

  int *array = NULL;
  int qt = 0;

  int res = readArrayFromFile(inputFile, &array, &qt);
  if (res != 0) {
    return 1;
  }

  insertionSort(array, qt);

  res = writeArrayToFile(outputFile, array, qt);

  free(array);

  if (res != 0) {
    return 1;
  }

  return 0;
}