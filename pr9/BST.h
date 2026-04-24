#ifndef BST_H
#define BST_H

#include "node.h"

NodePtr BSTPut(NodePtr head, Key key, Value val);
Value BSTGet(NodePtr head, Key key);

NodePtr BSTFloor(NodePtr head, Key key);
NodePtr BSTCeiling(NodePtr head, Key key);

int BSTRank(NodePtr head, Key key);
int BSTSize(NodePtr head);

NodePtr *BSTNodes(NodePtr head, int *arraySize);
void BSTIterate(NodePtr head, void (*func)(NodePtr));

NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDelete(NodePtr head, Key key);
NodePtr BSTDeleteMax(NodePtr root);

Key BSTMin(NodePtr head);
Key BSTMax(NodePtr head);

void BSTPrint(const NodePtr head);
void BSTDestroy(NodePtr head);

#endif
