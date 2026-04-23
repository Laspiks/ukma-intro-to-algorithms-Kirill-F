#ifndef QUEUE_ITEM_H
#define QUEUE_ITEM_H

#include "item.h"

void QueueInit();
int QueueEmpty(void); // is the queue empty?
void enqueue(Item); // insert a new Item onto queue
Item dequeue(void); // remove and return the least recently added Item

#endif // QUEUE_ITEM_H
