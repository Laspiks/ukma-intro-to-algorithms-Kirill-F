#include "BST.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_BSTFloor() {
    {
        // Порожнє дерево: floor не існує.
        NodePtr head = NULL;
        assert(BSTFloor(head, "A") == NULL);
        BSTDestroy(head);
    }

    {
        // Одне значення: або знаходимо його, або нічого.
        NodePtr head = create_node("D", NULL);
        assert(equal(BSTFloor(head, "D")->key, "D"));
        assert(BSTFloor(head, "A") == NULL);
        BSTDestroy(head);
    }

    {
        // Один елемент зліва від кореня.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "B", NULL);

        assert(equal(BSTFloor(head, "C")->key, "B"));
        assert(equal(BSTFloor(head, "D")->key, "D"));
        BSTDestroy(head);
    }

    {
        // Один елемент справа від кореня.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "F", NULL);

        assert(equal(BSTFloor(head, "E")->key, "D"));
        assert(equal(BSTFloor(head, "Z")->key, "F"));
        BSTDestroy(head);
    }

    {
        // Кілька переходів тільки вліво.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "A", NULL);

        assert(equal(BSTFloor(head, "B")->key, "B"));
        assert(BSTFloor(head, "0") == NULL);
        BSTDestroy(head);
    }

    {
        // Кілька переходів тільки вправо.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "F", NULL);
        BSTPut(head, "H", NULL);
        BSTPut(head, "J", NULL);

        assert(equal(BSTFloor(head, "G")->key, "F"));
        assert(equal(BSTFloor(head, "K")->key, "J"));
        BSTDestroy(head);
    }

    {
        // Є і ліве, і праве піддерево.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "F", NULL);

        assert(equal(BSTFloor(head, "E")->key, "D"));
        assert(equal(BSTFloor(head, "F")->key, "F"));
        BSTDestroy(head);
    }

    {
        // Йдемо вправо кілька разів, поки шукаємо найближчий менший ключ.
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "T", NULL);
        BSTPut(head, "W", NULL);
        BSTPut(head, "Y", NULL);

        assert(equal(BSTFloor(head, "X")->key, "W"));
        BSTDestroy(head);
    }

    {
        // Йдемо вліво кілька разів і не знаходимо підхожого ключа.
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "H", NULL);
        BSTPut(head, "D", NULL);
        BSTPut(head, "B", NULL);

        assert(BSTFloor(head, "A") == NULL);
        assert(equal(BSTFloor(head, "E")->key, "D"));
        BSTDestroy(head);
    }

    {
        // Маршрут змішаний: і вліво, і вправо в різних піддеревах.
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "F", NULL);
        BSTPut(head, "T", NULL);
        BSTPut(head, "H", NULL);
        BSTPut(head, "G", NULL);
        BSTPut(head, "R", NULL);

        assert(equal(BSTFloor(head, "I")->key, "H"));
        assert(equal(BSTFloor(head, "S")->key, "R"));
        BSTDestroy(head);
    }
    
    // Completed test case: some random tree with at least 6 nodes
    {
        NodePtr head = create_node("S", 0);
        BSTPut(head, "S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "P", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);

        BSTPrint(head);
        printf("\n");

        assert(equal(BSTFloor(head, "Q")->key, "P"));
        assert(equal(BSTFloor(head, "H")->key, "H"));
        assert(equal(BSTFloor(head, "K")->key, "H"));
        assert(equal(BSTFloor(head, "Y")->key, "X"));

        BSTDestroy(head); // Free allocated memory
    }
    {
        NodePtr head = create_node("D", 0);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);

        assert(BSTFloor(head, "A") == NULL);

        BSTDestroy(head); // Free allocated memory
    }

    printf("All BSTFloor tests passed.\n");
}

void test_BSTDeleteMin() {
    {
        // Test case 1: Deleting min from an empty tree should return NULL.
        NodePtr head = NULL;
        assert(BSTDeleteMin(head) == NULL);
        BSTDestroy(head); // Free allocated memory
    }

    {
        // Test case 2: Deleting the only node in the tree should return NULL.
        NodePtr head = create_node("D", NULL);
        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == NULL);
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 3: Deleting the min node from a left-skewed tree should update the root.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == head);
        assert(BSTSize(new_head) == 2);
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 4: Deleting the root node when it is the minimum should update root to its
        // right child.
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "B"));
        assert(BSTSize(new_head) == 2);
        assert(equal(new_head->right->key, "C"));
        assert(new_head->left == NULL);
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 5: Deleting the leftmost node in a tree with both left and right subtrees.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "F", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "D"));
        assert(BSTSize(new_head) == 3);
        assert(equal(new_head->left->key, "C"));
        assert(equal(new_head->right->key, "F"));
        BSTDestroy(new_head); // Free allocated memory
    }

    {
        // Test case 6: Deleting the leftmost node from a balanced tree should update the left
        // child.
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "F", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "D"));
        assert(BSTSize(new_head) == 3);
        assert(equal(new_head->left->key, "C"));
        assert(equal(new_head->right->key, "F"));
        BSTDestroy(new_head); // Free allocated memory
    }

    // Optionally print a message if the test passes
    printf("Test passed: Minimum key deleted successfully.\n");
}

int main() {
    test_BSTFloor();
    test_BSTDeleteMin();
    
    printf("All tests passed!\n");

    return 0;
}
