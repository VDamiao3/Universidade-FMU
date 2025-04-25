#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int middle, int right) {
    int i = 0, j = 0;
    int v1 = middle - left + 1;
    int v2 = right - middle;
    int *L = (int *)malloc(v1 * sizeof(int));
    /*
    if(L == NULL) {
        printf("Error while alocating memory!\n");
        exit(1);
    }
    */
    int *R = (int *)malloc(v2 * sizeof(int));
    /*
    if(R == NULL) {
        printf("Error while alocating memory!\n");
        exit(1);
    }
    */
    for(i = 0; i < v1; ++i) {
        L[i] = arr[left + i];
    }
    for(j = 0; j < v2; ++j) {
        R[j] = arr[middle + 1 + j];
    }
    i = 0;
    j = 0;
    int k = left;
    while(i < v1 && j < v2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while(i < v1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while(j < v2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
    free(L);
    free(R);
}

void mSort_iteratively(int arr[], int size) {
    for (int current_size = 1; current_size <= size - 1; current_size = 2 * current_size) {
        for (int left_start = 0; left_start < size - 1; left_start += 2 * current_size) {
            int middle = left_start + current_size - 1;
            int right_end;
            if ((left_start + 2 * current_size - 1) < (size - 1)) {
                right_end = left_start + 2 * current_size - 1;
            }
            else {
                right_end = size - 1;
            }
            merge(arr, left_start, middle, right_end);
        }
    }
}

void random_Array(int arr[], int size) {
    for(int i = 0; i < size; ++i) {
        arr[i] = rand()%1000000;
    }
}

int main(void) {

    int data_sizes[] = {100, 1000, 10000, 100000, 1000000};
    int num_sizes = sizeof(data_sizes) / sizeof(data_sizes[0]);
    int size;
    srand(time(NULL));
    for(int i = 0; i < num_sizes; ++i) {
        size = data_sizes[i];
        int *array = (int *) malloc (size * sizeof(int));
        if(array == NULL) {
            printf("Error while allocating memory!\n");
            return 1;
        }

        random_Array(array, size);

        clock_t start = clock();
        mSort_iteratively(array, size);
        clock_t end = clock();

        double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Size of the array: %d.\nExecution time: %.6f seconds.\n", size, time_taken);
        free(array);
    }
    return 0;
}