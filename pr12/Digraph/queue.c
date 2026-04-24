#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    Item item;
    struct Node *next;
} Node;

struct Queue {
    Node *first;
    Node *last;
};

QueuePtr QueueInit() {
    QueuePtr q = (QueuePtr)malloc(sizeof(struct Queue));
    if (q == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    q->first = q->last = NULL;
    return q;
}

void QueueDestroy(QueuePtr q) {
    while (!QueueEmpty(q))
    {
        dequeue(q);
    }

    free(q);
}

int QueueEmpty(QueuePtr q) {
    return q->first == NULL;
}

void enqueue(QueuePtr q, Item item) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_node->item = item;
    new_node->next = NULL;

    if (q->first == NULL) {
        q->first = q->last = new_node;
    } else {
        q->last->next = new_node;
        q->last = new_node;
    }
}

Item dequeue(QueuePtr q) {
    if (QueueEmpty(q)) {
        fprintf(stderr, "Queue underflow\n");
        assert(false);
        return 0;
    }

    Item item = q->first->item;
    Node* temp = q->first;
    q->first = q->first->next;
    if (q->first == NULL) {
        q->last = NULL;
    }
    free(temp);
    return item;
}