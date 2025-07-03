#include "include/insertionSort.h"

long long insertionSort(int* array, int size) {
    long long swapCount = 0;
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
            swapCount++;
        }
        array[j + 1] = key;
    }
    return swapCount;
}