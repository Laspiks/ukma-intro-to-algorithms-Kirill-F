#include "node.h"
#include <stdlib.h>

Node *create_node(Key key, Value val) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        return NULL; // Memory allocation failed
    }
    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->count = 1;
    return new_node;
}