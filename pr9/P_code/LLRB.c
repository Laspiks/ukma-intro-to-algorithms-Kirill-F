#include "LLRB.h"
#include "LLRB_ops.h"

#include <assert.h>

NodePtr llrb_put_impl(NodePtr head, Key key, Value val) {
    // identical to BSTPut()
    if (head == NULL) {
        return createRBNode(key, val, RED);
    }

    if (less(key, head->key)) {
        head->left = llrb_put_impl(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = llrb_put_impl(head->right, key, val);
    } else {
        head->val = val; // Update existing key
    }

    // --- ToDo:Fix right-leaning red links ---
    if (isRed(head->right) && !isRed(head->left)) {
        head = rotateLeft(head);
    }

    // --- ToDo: Fix two consecutive left-leaning red links ---
    if (isRed(head->left) && isRed(head->left->left)) {
        head = rotateRight(head);
    }

    // --- ToDo: Split temporary 4-node ---
    if (isRed(head->left) && isRed(head->right)) {
        flipColors(head);
    }

    // identical to BSTPut()
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);

    // Optional debug assertion: right-leaning reds shouldn't exist
    assert(!isRed(head->right));

    return head;
}

NodePtr LLRBPut(NodePtr head, Key key, Value val) {
    NodePtr new_head = llrb_put_impl(head, key, val);
    if (new_head != NULL) {
        new_head->color = BLACK;
    }
    return new_head;
}
