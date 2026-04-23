#include "stack_item.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

static Item stack[CAPACITY];
static int first;

void StackInit() {
    first = 0;
}

int StackEmpty(void) {
    return first == 0;
}

void StackPush(Item item) {
    if (first < CAPACITY) {
        stack[first++] = item;
    } else {
        fprintf(stderr, "Stack overflow\n");
    }
}

Item StackPop(void) {
    if (!StackEmpty()) {
        return stack[--first];
    }
    fprintf(stderr, "Stack underflow\n");
    assert(false);
    return NULL;
}

int StackCapacity() {
    return CAPACITY;
}
