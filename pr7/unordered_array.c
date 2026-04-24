#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 10

       struct PriorityQueue {
    Item items[DEFAULT_CAPACITY]; // Static array
    int size;
};

// Create an empty priority queue
PriorityQueuePtr PQInit() {
    printf("Unordered array implementation \n");
    PriorityQueuePtr pq = (PriorityQueuePtr)malloc(sizeof(struct PriorityQueue));
    if (!pq)
        return NULL;
    pq->size = 0;
    return pq;
}

// Insert a key into the priority queue
void PQInsert(PriorityQueuePtr pq, Item item) {
    assert(pq->size < DEFAULT_CAPACITY && "Priority Queue is full!");
    pq->items[pq->size++] = item;
}

// Return and remove the largest key
Item PQDelMax(PriorityQueuePtr pq) {
    if (pq->size == 0)
        return NULL;

    int max = 0;
    for (int i = 1; i < pq->size; i++) {
        if (less(pq->items[max], pq->items[i])) {
            max = i;
        }
    }
    exch(pq->items[max], pq->items[pq->size - 1]);
    return pq->items[--pq->size];
}

// Check if the priority queue is empty
int PQIsEmpty(PriorityQueuePtr pq) { return pq->size == 0; }

// Return the largest key without removing it
Item PQMax(PriorityQueuePtr pq) {
    if (pq->size == 0)
        return NULL;

    int max = 0;
    for (int i = 1; i < pq->size; i++) {
        if (less(pq->items[max], pq->items[i])) {
            max = i;
        }
    }
    return pq->items[max];
}

// Get the number of entries in the priority queue
int PQSize(PriorityQueuePtr pq) { return pq->size; }

// Destroy the priority queue and free allocated memory
void PQDestroy(PriorityQueuePtr pq) { free(pq); }
