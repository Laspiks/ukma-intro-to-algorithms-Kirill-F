#ifndef NODE_H
#define NODE_H

#include "item.h"
#include <stdbool.h>

typedef void *Value;

typedef struct {
    Key key;
    Value val;
} KeyValue;

#define RED true
#define BLACK false

typedef struct Node {
    Key key;
    Value val;
    struct Node *left;
    struct Node *right;
    int count;
    bool color; // color of parent link
} Node;

typedef Node *NodePtr;

NodePtr createNode(Key key, Value val);
void printNode(const NodePtr node);
NodePtr createRBNode(Key key, Value val, bool color);
bool isRed(const NodePtr x);

#endif