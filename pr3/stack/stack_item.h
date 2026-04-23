#ifndef STACK_ITEM_H
#define STACK_ITEM_H

#include "item.h"

void StackInit();
int StackEmpty(void);
void StackPush(Item);
Item StackPop(void);
int StackCapacity();

#endif // STACK_ITEM_H
