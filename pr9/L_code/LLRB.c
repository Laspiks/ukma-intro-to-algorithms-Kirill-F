#include "LLRB.h"
#include "LLRB_ops.h"

#include <assert.h>

NodePtr llrb_put_impl(NodePtr head, Key key, Value val) {
    // identical to BSTPut()
    if (head == NULL) {
        // --- ToDo: Create a new RED node ---
    }

    if (less(key, head->key)) {
        head->left = llrb_put_impl(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = llrb_put_impl(head->right, key, val);
    } else {
        head->val = val; // Update existing key
    }

    // --- ToDo:Fix right-leaning red links ---

    // --- ToDo: Fix two consecutive left-leaning red links ---

    // --- ToDo: Split temporary 4-node ---

    // identical to BSTPut()
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);

    // Optional debug assertion: right-leaning reds shouldn't exist
    assert(!isRed(head->right));

    return head;
}

NodePtr LLRBPut(NodePtr head, Key key, Value val) {
    NodePtr new_head = llrb_put_impl(head, key, val);
    // --- ToDo:  Root must always be black ---
    return new_head;
}