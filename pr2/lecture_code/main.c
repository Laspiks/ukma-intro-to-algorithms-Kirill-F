#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool verbose = false;
static bool brute_force_implementation = true;

int binarySearch(int a[], int start,  int end, int key) {
    int lo = start, hi = end - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (key < a[mid]) {
            hi = mid - 1;
        } else if (key > a[mid]) {
            lo = mid + 1;
        } else {
            return mid;  // Key found
        }
    }

    return -1;  // Key not found
}

void swap(int* a, int*b) {
    int temp = *a;
    *a = *b;
    *b = temp; 
}

void bubbleSort(int a[], int n) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n-1-i; ++j) {
            if (a[j]> a[j+1]) {
                swap(&a[j], &a[j+1]);
            }
        }
    }
}

int three_sum_binary_search(int a[], int n) {
    printf("Three sum: binary search approach\n");
    if (n < 3) return 0;

    bubbleSort(a, n);
    
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int init_idx = j + 1;
            int num_3 = -1*(a[i]+a[j]);
            int idx = binarySearch(a, init_idx, n, num_3);
            if (idx != -1) {
                count++;
                if (verbose)
                    printf("[%d,%d,%d], ", a[i],a[j],a[idx]);
            }
        }
    }

    printf("\n");

    return count;
}

int three_sum_brute_force(int a[], int n) {
    printf("Three sum: brute force approach\n");
    if (n < 3) return 0;

    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (a[i] + a[j] + a[k] == 0) {
                    count++;
                    if (verbose)
                        printf("[%d,%d,%d], ", a[i],a[j],a[k]);
                }
            }
        }
    }

    printf("\n");

    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int n;
    if (fscanf(file, "%d", &n) != 1) {
        printf("Error: Failed to read the size of the array.\n");
        fclose(file);
        return 1;
    }

    int array[n]; // Create an array of size `n`

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &array[i]) != 1) {
            printf("Error: Failed to read element %d.\n", i);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    int count = 0;
    if (brute_force_implementation)
        count = three_sum_brute_force(array, n);
    else
        count = three_sum_binary_search(array, n);

    printf("count = %d\n", count);

    return 0;
}
