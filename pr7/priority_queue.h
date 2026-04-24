#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "item.h"

typedef struct PriorityQueue *PriorityQueuePtr;

// Create an empty priority queue
PriorityQueuePtr PQInit();

// Insert a key into the priority queue
void PQInsert(PriorityQueuePtr pq, Item item);

// Return and remove the largest key
Item PQDelMax(PriorityQueuePtr pq);

// Check if the priority queue is empty
int PQIsEmpty(PriorityQueuePtr pq);

// Return the largest key without removing it
Item PQMax(PriorityQueuePtr pq);

// Get the number of entries in the priority queue
int PQSize(PriorityQueuePtr pq);

// Destroy the priority queue and free allocated memory
void PQDestroy(PriorityQueuePtr pq);

#endif // PRIORITY_QUEUE_H