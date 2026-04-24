#include "priority_queue.h"

#include <assert.h>
#include <stdio.h>

// Sink окремий для heapsort, не для Priority Queue.
static void sink(Item *a, int k, int N) {
    while (2 * k <= N) { // Left child of k is at 2 * k
        int j = 2 * k;   // Left child
        if (j < N && less(a[j], a[j + 1]))
            j++; // Right child exists and is greater
        if (!less(a[k], a[j]))
            break;
        exch(a[k], a[j]);
        k = j;
    }
}

static void heapsort(Item *a, int N) {
    // Convert array into a heap (heap construction phase)
    for (int k = N / 2; k >= 1; k--) {
        sink(a, k, N);
    }

    // Repeatedly remove the largest element from the heap
    while (N > 1) {
        exch(a[1], a[N]); // Move the max element to the end
        N--;
        sink(a, 1, N);
    }
}

int main(void) {
    {
        // Черга створюється без параметрів, місткість в реалізації.
        PriorityQueuePtr pq = PQInit();

        // Insert operations
        PQInsert(pq, "P");
        PQInsert(pq, "Q");
        PQInsert(pq, "E");

        // Remove max and print
        printf("Removed max: %s\n", (char *)PQDelMax(pq));

        // Insert operations
        PQInsert(pq, "X");
        PQInsert(pq, "A");
        PQInsert(pq, "M");

        // Remove max and print
        printf("Removed max: %s\n", (char *)PQDelMax(pq));

        // Insert operations
        PQInsert(pq, "P");
        PQInsert(pq, "L");
        PQInsert(pq, "E");

        // Remove max and print
        printf("Removed max: %s\n", (char *)PQDelMax(pq));

        // Print queue size
        printf("Size: %d\n", PQSize(pq));

        // Destroy the priority queue
        PQDestroy(pq);
    }

    printf("Basic test cases to check heapsort()\n");

    {
        char *arr[] = {"",  "S", "O", "R", "T", "E",
                       "X", "A", "M", "P", "L", "E"}; // array entries are indexed 1 to N
        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N - 1);

        // Correct expected order
        char *expected[] = {"", "A", "E", "E", "L", "M", "O", "P", "R", "S", "T", "X"};
        for (int i = 0; i < N; i++) {
            assert(strcmp(arr[i], expected[i]) == 0);
        }

        printf("Test passed!\n");
    }

    {
        char *arr[] = {"", "S", "A", "F"}; // array entries are indexed 1 to N

        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N - 1);

        // Correct expected order
        char *expected[] = {"", "A", "F", "S"};
        for (int i = 0; i < N; i++) {
            assert(strcmp(arr[i], expected[i]) == 0);
        }

        printf("Test passed!\n");
    }

    {
        char *arr[] = {""}; // array entries are indexed 1 to N

        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N - 1);

        assert(strcmp(arr[0], "") == 0);

        printf("Test passed!\n");
    }

    {
        char *arr[] = {"", "X"}; // array entries are indexed 1 to N

        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N - 1);

        assert(strcmp(arr[0], "") == 0);
        assert(strcmp(arr[1], "X") == 0);

        printf("Test passed!\n");
    }

    {
        char *arr[] = {"", "X", "Y"}; // array entries are indexed 1 to N

        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N - 1);

        assert(strcmp(arr[1], "X") == 0);
        assert(strcmp(arr[2], "Y") == 0);

        printf("Test passed!\n");
    }

    {
        char *arr[] = {"", "X", "Z", "Y"}; // array entries are indexed 1 to N

        int N = sizeof(arr) / sizeof(arr[0]);

        heapsort((Item *)arr, N - 1);

        assert(strcmp(arr[1], "X") == 0);
        assert(strcmp(arr[2], "Y") == 0);
        assert(strcmp(arr[3], "Z") == 0);

        printf("Test passed!\n");
    }

    return 0;
}
