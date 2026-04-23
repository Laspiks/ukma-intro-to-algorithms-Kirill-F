#include "stack_item.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    Item item;
    struct Node *next;
};

static struct Node *first = NULL;

void StackInit() {
    first = NULL; // No need to allocate fixed size in linked list
}

int StackEmpty(void) {
    return first == NULL;
}

void StackPush(Item item) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newNode->item = item;
    newNode->next = first;
    first = newNode;
}

Item StackPop(void) {
    if (StackEmpty()) {
        fprintf(stderr, "Stack underflow\n");
        assert(false);
        return NULL;
    }
    Item item = first->item;
    struct Node *temp = first;
    first = first->next;
    free(temp);
    return item;
}

int StackCapacity() {
    return -1;
}
