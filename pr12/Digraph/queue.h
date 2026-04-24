#ifndef QUEUE_H
#define QUEUE_H

typedef int Item;

typedef struct Queue* QueuePtr;

QueuePtr QueueInit();
int QueueEmpty(QueuePtr);
void enqueue(QueuePtr, Item);
Item dequeue(QueuePtr);
void QueueDestroy(QueuePtr);

#endif // QUEUE_H
