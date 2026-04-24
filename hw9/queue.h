#ifndef QUEUE_H
#define QUEUE_H

typedef int Item;

typedef struct Queue *QueuePtr;

QueuePtr QueueInit(void);
int QueueEmpty(QueuePtr q);
void enqueue(QueuePtr q, Item item);
Item dequeue(QueuePtr q);
void QueueDestroy(QueuePtr q);

#endif
