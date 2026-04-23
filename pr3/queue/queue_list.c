#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    Item item;
    struct Node *next;
};

static struct Node *first = NULL;
static struct Node *last = NULL;

void QueueInit() {
    first = last = NULL;
    printf("sizeof(Node) = %lu\n", sizeof(struct Node));
}

int QueueEmpty(void) {
    return first == NULL;
}

void enqueue(Item item) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newNode->item = item;
    newNode->next = NULL;

    if (QueueEmpty()) {
        first = last = newNode;  // First element in queue
    } else {
        last->next = newNode;  // Append at the end
        last = newNode;
    }
}

Item dequeue(void) {
    if (QueueEmpty()) {
        fprintf(stderr, "Queue underflow\n");
        assert(false);
        return NULL;
    }

    Item item = first->item;
    struct Node *temp = first;
    first = first->next;
    
    if (first == NULL) {  // If queue is empty after dequeue
        last = NULL;
    }

    free(temp);
    return item;
}
