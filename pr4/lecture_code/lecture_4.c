#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item t = A; A = B; B = t;}
#define compexch(A, B) if (less(B, A)) exch(A, B)

int is_sorted(Item a[], int length) {
    for (int i = 1; i < length; ++i) {
        if (less(a[i], a[i - 1])) {
            return 0;
        }
    }
    return 1;
}

void sort(Item* a, int l, int r)
{
  int i, j;
  for (i = l+1; i <= r; i++)
    for (j = i; j > l; j--)
      compexch(a[j-1], a[j]);
}

void selection_sort(Item a[], int l, int r) {
    printf("Selection sort\n");

    int i, j;

    for (i = l; i < r; ++i) {
        int min = i;
        for (j = i + 1; j <= r; ++j)
            if (less(a[j], a[min]))
                min = j;
        exch(a[i], a[min]);
    }
}

void insertion_sort(Item a[], int l, int r) {
    printf("Insertion sort\n");

    int i, j;

    for (i = l; i <= r; ++i) {
        for (j = i; j > l; --j) {
            if (less(a[j], a[j - 1])) {
                exch(a[j], a[j - 1]);
            } else {
                break;
            }
        }
    }
}

void shell_sort(Item a[], int N) {
    printf("Shell sort\n");

    int h = 1;
    while (h < N / 3) {
        h = 3 * h + 1; // 3x+1 increment sequence: 1, 4, 13, 40, ...
    }

    while (h >= 1) { // Perform h-sorting
        // insertion sort with h-step
        for (int i = h; i < N; i++) {
            for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                exch(a[j], a[j - h]);
            }
        }
        h = h / 3; // move to next increment
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Not enough arguments\n");
        return -1;
    }

    int i;
    int N = atoi(argv[1]);
    int *a = malloc(N * sizeof(int));

    srand(time(NULL));

    for (i = 0; i < N; i++)
        a[i] = 1000 * (1.0 * rand() / RAND_MAX);

    printf("is_sorted: %d\n", is_sorted(a, N));

    printf("Initial: ");
    for (i = 0; i < N; i++)
        printf("%3d ", a[i]);
    printf("\n");

    shell_sort(a, N);

    printf("After: ");
    for (i = 0; i < N; i++)
        printf("%3d ", a[i]);
    printf("\n");

    printf("is_sorted: %d \n", is_sorted(a, N));
}