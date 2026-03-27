#ifndef BST_H
#define BST_H

#include "node.h"

typedef Node* NodePtr;

NodePtr BSTPut(NodePtr, Key key, Value val); // Put key-value pair into BST (replace if such key existed)
Value BSTGet(NodePtr, Key key); // Retrieve value associated with key

NodePtr BSTFloor(NodePtr, Key key); // Find the largest key ≤ given key
NodePtr BSTCeiling(NodePtr, Key key); // Find the smallest key ≥ given key

int BSTRank(NodePtr, Key key); // Get the number of keys < given key
int BSTSize(NodePtr); // Return the number of nodes in BST

NodePtr *BSTNodes(NodePtr head, int *arraySize); // Get all nodes in sorted order
void BSTIterate(NodePtr head, void (*func)(NodePtr)); // Iterate over all elements in-order and call pointer to function

NodePtr BSTDeleteMin(NodePtr root); // Remove min element from BST
NodePtr BSTDelete(NodePtr, Key key); // Remove key from BST

Key BSTMin(NodePtr); // Find the smallest key in BST
Key BSTMax(NodePtr); // Find the largest key in BST

NodePtr BSTDeleteMax(NodePtr root); // Remove max element from BST

void BSTPrint(const NodePtr); // Print BST in-order

void BSTDestroy(NodePtr); // Destroy the tree and clean all nodes

#endif