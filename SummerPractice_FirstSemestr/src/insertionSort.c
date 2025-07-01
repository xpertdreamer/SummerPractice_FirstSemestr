#include "include/insertionSort.h"

int insertionSort(int* array, int qt) {
    int swapCount = 0;

    for (size_t i = 1; i < qt; i++) {
        int key = array[i];
        int j = (int)i - 1;

        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
            swapCount++;
        }
        array[j + 1] = key;
    }

    return swapCount;
}