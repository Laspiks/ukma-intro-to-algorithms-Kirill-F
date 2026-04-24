#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 10

struct PriorityQueue {
    Item items[DEFAULT_CAPACITY]; // Static array for the binary heap
    int size;
};

// Create an empty priority queue
PriorityQueuePtr PQInit() {
    printf("Binary heap implementation \n");
    PriorityQueuePtr pq = (PriorityQueuePtr)malloc(sizeof(struct PriorityQueue));
    if (!pq)
        return NULL;
    pq->size = 0;
    return pq;
}

// Helper function for swim 
void swim(PriorityQueuePtr pq, int k) {
    while (k > 1 && less(pq->items[k / 2], pq->items[k])) {
        exch(pq->items[k], pq->items[k / 2]);
        k = k / 2;
    }
}

// Helper function for sink
void sink(PriorityQueuePtr pq, int k) {
    while (2 * k <= pq->size) { // left child of k is at 2 * k
        int j = 2 * k;          // Left child
        if (j < pq->size && less(pq->items[j], pq->items[j + 1])) j++; // Right child exists and is greater, so choose the right child

        if (!less(pq->items[k], pq->items[j])) {
            break;
        }
        exch(pq->items[k], pq->items[j]);
        k = j;
    }
}

// Insert a key into the priority queue (add to the heap and swim)
void PQInsert(PriorityQueuePtr pq, Item item) {
    assert(pq->size < DEFAULT_CAPACITY && "Priority Queue is full!");
    pq->items[++pq->size] = item; // Add the new item at the end of the heap (indices start at 1)
    swim(pq, pq->size);           // Swim to maintain heap order
}

// Return and remove the largest key (root of the heap), sink the new root
Item PQDelMax(PriorityQueuePtr pq) {
    if (pq->size == 0)
        return NULL;

    Item max = pq->items[1];                   // Root is at index 1
    exch(pq->items[1], pq->items[pq->size]);   // Move the last item to the root
    pq->size--;
    sink(pq, 1);                               // Sink the root to restore heap order
    return max;
}

// Check if the priority queue is empty
int PQIsEmpty(PriorityQueuePtr pq) { return pq->size == 0; }

// Return the largest key without removing it (the root of the heap)
Item PQMax(PriorityQueuePtr pq) {
    if (pq->size == 0)
        return NULL;

    return pq->items[1]; // Root is at index 1
}

// Get the number of entries in the priority queue
int PQSize(PriorityQueuePtr pq) { return pq->size; }

// Destroy the priority queue and free allocated memory
void PQDestroy(PriorityQueuePtr pq) { free(pq); }
