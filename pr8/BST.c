#include "BST.h"
#include "node.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Value BSTGet(NodePtr head, Key key) {
    NodePtr x = head;
    while (x != NULL) {
        if (less(key, x->key)) {
            x = x->left;
        } else if (greater(key, x->key)) {
            x = x->right;
        } else {
            return x->val;
        }
    }
    return NULL;
}

NodePtr BSTPut(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return create_node(key, val);
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
    NodePtr t = BSTFloor(head->right, key);
    return (t != NULL) ? t : head;
}

int BSTSize(NodePtr head) { return (head != NULL) ? head->count : 0; }

void inorderNodes(NodePtr head, NodePtr *arr, int *index) {
    if (head != NULL) {
        inorderNodes(head->left, arr, index);
        arr[(*index)++] = head; // Store node instead of key
        inorderNodes(head->right, arr, index);
    }
}

NodePtr *BSTNodes(NodePtr head, int *arraySize) {
    if (head == NULL) {
        *arraySize = 0;
        return NULL;
    }

    *arraySize = head->count;
    NodePtr *nodesArray = (NodePtr*)malloc((*arraySize) * sizeof(NodePtr));
    if (!nodesArray) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int size = 0;
    inorderNodes(head, nodesArray, &size);
    return nodesArray;
}

// Helper recursive function to delete the minimum key
NodePtr deleteMin(NodePtr head) {
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);          // Free memory of the deleted node
        return rightSubtree; // Return the right child
    }

    head->left = deleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMin(NodePtr head) {
    if (head == NULL)
        return NULL;
    
    return deleteMin(head);
}

// Helper function to find the minimum node in a subtree 
NodePtr min(NodePtr head) {
    while (head->left != NULL) {
        head = head->left;
    }
    return head;
}

// Recursive function to delete a key from BST
NodePtr BSTDelete(NodePtr head, Key key) {
    if (head == NULL)
        return NULL; // Key not found

    if (less(key, head->key)) {
        head->left = BSTDelete(head->left, key);
    } else if (greater(key, head->key)) {
        head->right = BSTDelete(head->right, key);
    } else {
        // Node with only one child or no child
        if (head->right == NULL) {
            NodePtr leftSubtree = head->left;
            free(head);
            return leftSubtree;
        }
        if (head->left == NULL) {
            NodePtr rightSubtree = head->right;
            free(head);
            return rightSubtree;
        }

        // Node with two children: Get the inorder successor (smallest in right subtree)
        NodePtr temp = min(head->right);

        // Copy successor's key and value to this node
        head->key = temp->key;
        head->val = temp->val;

        // Delete the inorder successor
        head->right = deleteMin(head->right);
    }

    // Update count of nodes
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTDestroy(NodePtr head) {
    if (head == NULL)
        return;

    BSTDestroy(head->left);  // Free left subtree
    BSTDestroy(head->right); // Free right subtree
    free(head); // Free current node
}

void BSTIterate(NodePtr head, void (*func)(NodePtr)) {
    if (head == NULL)
        return;

    BSTIterate(head->left, func);
    func(head);
    BSTIterate(head->right, func);
}

void BSTPrint(const NodePtr head) {
    if (head == NULL) {
        return;
    }

    BSTPrint(head->left);
    // Друкуємо ключі in-order, щоб бачити відсортований порядок.
    printf("%s ", head->key);
    BSTPrint(head->right);
}
