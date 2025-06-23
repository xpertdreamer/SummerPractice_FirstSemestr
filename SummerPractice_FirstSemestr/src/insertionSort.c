#include "insertionSort.h"

void insertionSort(int *array, int qt) {
  for (size_t i = 1; i < qt; i++) {
    int key = array[i];
    int j = (int)i - 1;

    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = key;
  }
}
