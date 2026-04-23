#ifndef QUEUE_V2_H
#define QUEUE_V2_H

#include "item.h"

typedef struct Queue* QueuePtr;

QueuePtr QueueInit();
int QueueEmpty(QueuePtr);
void enqueue(QueuePtr, Item);
Item dequeue(QueuePtr);
void QueueDestroy(QueuePtr);

#endif // QUEUE_V2_H
