#include "LLRB.h"
#include "LLRB_ops.h"

#include <assert.h>

NodePtr llrb_put_impl(NodePtr head, Key key, Value val) {
    // identical to BSTPut()
    if (head == NULL) {
        // Новий вузол додаємо червоним, так LLRB і будується знизу.
        return createRBNode(key, val, RED);
    }

    if (less(key, head->key)) {
        head->left = llrb_put_impl(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = llrb_put_impl(head->right, key, val);
    } else {
        head->val = val; // Update existing key
    }

    // Якщо червоне ребро дивиться вправо, вирівнюємо його вліво.
    if (isRed(head->right) && !isRed(head->left)) {
        head = rotateLeft(head);
    }

    // Якщо зліва вийшов ланцюжок з двох червоних, підкручуємо вправо.
    if (isRed(head->left) && isRed(head->left->left)) {
        head = rotateRight(head);
    }

    // Обидва діти червоні: це тимчасовий 4-вузол, його треба розділити.
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
    // Корінь у red-black дереві завжди має бути чорний.
    new_head->color = BLACK;
    return new_head;
}
