#include "node.h"
#include <stdio.h>
#include <stdlib.h>

NodePtr createNode(Key key, Value val) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        return NULL; // Memory allocation failed
    }
    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->count = 1;
    new_node->color = BLACK;
    return new_node;
}

NodePtr createRBNode(Key key, Value val, bool color) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        return NULL; // Memory allocation failed
    }
    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->count = 1;
    new_node->color = color;
    return new_node;
}

bool isRed(const NodePtr x) {
    if (x == NULL)
        return false;
    return x->color == RED;
}

void printNode(const NodePtr node) {
    if (node) {
        printf("%s(%s) ", node->key, node->color == RED ? "R" : "B");
    }
}
