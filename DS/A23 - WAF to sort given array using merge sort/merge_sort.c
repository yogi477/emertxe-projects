#include "main.h"

int merge_sort(int *array, int narray) {
    if (narray <= 1)
        return SUCCESS;

    int mid = narray / 2;

    int *left = malloc(sizeof(int) * mid);
    if (left == NULL)
        return FAILURE;

    int *right = malloc(sizeof(int) * (narray - mid));
    if (right == NULL) {
        free(left);  
        return FAILURE;
    }

    for (int i = 0; i < mid; i++)
        left[i] = array[i];

    for (int i = mid; i < narray; i++)
        right[i - mid] = array[i];
        
    if (merge_sort(left, mid) == FAILURE || merge_sort(right, narray - mid) == FAILURE) {
        free(left);
        free(right);
        return FAILURE;
    }

    merge(array, narray, left, mid, right, narray - mid);

    free(left);
    free(right);

    return SUCCESS;
}
