#include "BST.h"

#include <stdio.h>
#include <stdlib.h>

Value BSTGet(NodePtr head, Key key) {
    NodePtr cur = head;

    while (cur != NULL) {
        if (less(key, cur->key)) {
            cur = cur->left;
        } else if (greater(key, cur->key)) {
            cur = cur->right;
        } else {
            return cur->val;
        }
    }

    return NULL;
}

NodePtr BSTPut(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return createNode(key, val);
    }

    if (less(key, head->key)) {
        head->left = BSTPut(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = BSTPut(head->right, key, val);
    } else {
        head->val = val;
    }

    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTFloor(NodePtr head, Key key) {
    if (head == NULL) {
        return NULL;
    }

    if (equal(key, head->key)) {
        return head;
    }

    if (less(key, head->key)) {
        return BSTFloor(head->left, key);
    }

    NodePtr maybe_floor = BSTFloor(head->right, key);
    return maybe_floor != NULL ? maybe_floor : head;
}

NodePtr BSTCeiling(NodePtr head, Key key) {
    if (head == NULL) {
        return NULL;
    }

    if (equal(key, head->key)) {
        return head;
    }

    if (greater(key, head->key)) {
        return BSTCeiling(head->right, key);
    }

    NodePtr maybe_ceiling = BSTCeiling(head->left, key);
    return maybe_ceiling != NULL ? maybe_ceiling : head;
}

int BSTSize(NodePtr head) {
    return head != NULL ? head->count : 0;
}

int BSTRank(NodePtr head, Key key) {
    if (head == NULL) {
        return 0;
    }

    if (less(key, head->key)) {
        return BSTRank(head->left, key);
    }

    if (greater(key, head->key)) {
        return 1 + BSTSize(head->left) + BSTRank(head->right, key);
    }

    return BSTSize(head->left);
}

static void inorder_nodes(NodePtr head, NodePtr *arr, int *index) {
    if (head == NULL) {
        return;
    }

    inorder_nodes(head->left, arr, index);
    arr[(*index)++] = head;
    inorder_nodes(head->right, arr, index);
}

NodePtr *BSTNodes(NodePtr head, int *arraySize) {
    if (head == NULL) {
        *arraySize = 0;
        return NULL;
    }

    *arraySize = BSTSize(head);
    NodePtr *nodes = malloc((size_t)(*arraySize) * sizeof(NodePtr));
    if (nodes == NULL) {
        return NULL;
    }

    int index = 0;
    inorder_nodes(head, nodes, &index);
    return nodes;
}

void BSTIterate(NodePtr head, void (*func)(NodePtr)) {
    if (head == NULL) {
        return;
    }

    BSTIterate(head->left, func);
    func(head);
    BSTIterate(head->right, func);
}

Key BSTMin(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }

    while (head->left != NULL) {
        head = head->left;
    }

    return head->key;
}

Key BSTMax(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }

    while (head->right != NULL) {
        head = head->right;
    }

    return head->key;
}

static NodePtr min_node(NodePtr head) {
    while (head->left != NULL) {
        head = head->left;
    }

    return head;
}

NodePtr BSTDeleteMin(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }

    if (head->left == NULL) {
        NodePtr right = head->right;
        free(head);
        return right;
    }

    head->left = BSTDeleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMax(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }

    if (head->right == NULL) {
        NodePtr left = head->left;
        free(head);
        return left;
    }

    head->right = BSTDeleteMax(head->right);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDelete(NodePtr head, Key key) {
    if (head == NULL) {
        return NULL;
    }

    if (less(key, head->key)) {
        head->left = BSTDelete(head->left, key);
    } else if (greater(key, head->key)) {
        head->right = BSTDelete(head->right, key);
    } else {
        if (head->left == NULL) {
            NodePtr right = head->right;
            free(head);
            return right;
        }

        if (head->right == NULL) {
            NodePtr left = head->left;
            free(head);
            return left;
        }

        NodePtr next = min_node(head->right);
        head->key = next->key;
        head->val = next->val;
        head->right = BSTDeleteMin(head->right);
    }

    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTPrint(const NodePtr head) {
    if (head == NULL) {
        return;
    }

    BSTPrint(head->left);
    printNode(head);
    BSTPrint(head->right);
}

void BSTDestroy(NodePtr head) {
    if (head == NULL) {
        return;
    }

    BSTDestroy(head->left);
    BSTDestroy(head->right);
    free(head);
}
