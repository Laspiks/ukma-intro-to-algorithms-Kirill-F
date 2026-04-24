#ifndef NODE_H
#define NODE_H

#include "item.h"

typedef void *Value;

typedef struct {
    Key key;
    Value val;
} KeyValue;

typedef struct Node {
    Key key;
    Value val;
    struct Node *left;
    struct Node *right;
    int count;
} Node;

Node* create_node(Key key, Value val);

#endif