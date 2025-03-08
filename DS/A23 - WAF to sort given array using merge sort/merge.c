#include "main.h"


void merge(int *array, int narray, int *left, int nleft, int *right, int nright) {
    int i = 0, j = 0, k = 0;

    while (i < nleft && j < nright) {
        if (left[i] <= right[j]) {  
            array[k++] = left[i++];
        } else {
            array[k++] = right[j++];
        }
    }

    while (i < nleft) {
        array[k++] = left[i++];
    }

    while (j < nright) {
        array[k++] = right[j++];
    }
}