#include "queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    Item item;
    struct Node *next;
} Node;

struct Queue {
    Node *first;
    Node *last;
};

QueuePtr QueueInit(void) {
    QueuePtr q = malloc(sizeof(struct Queue));
    if (q == NULL) {
        fprintf(stderr, "Cannot allocate queue\n");
        return NULL;
    }

    q->first = NULL;
    q->last = NULL;
    return q;
}

int QueueEmpty(QueuePtr q) {
    return q == NULL || q->first == NULL;
}

void enqueue(QueuePtr q, Item item) {
    if (q == NULL) {
        return;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Cannot allocate queue node\n");
        return;
    }

    node->item = item;
    node->next = NULL;

    if (q->last == NULL) {
        q->first = node;
        q->last = node;
        return;
    }

    q->last->next = node;
    q->last = node;
}

Item dequeue(QueuePtr q) {
    if (QueueEmpty(q)) {
        fprintf(stderr, "Queue underflow\n");
        assert(0);
        return 0;
    }

    Node *node = q->first;
    Item item = node->item;
    q->first = node->next;
    if (q->first == NULL) {
        q->last = NULL;
    }

    free(node);
    return item;
}

void QueueDestroy(QueuePtr q) {
    if (q == NULL) {
        return;
    }

    while (!QueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}
