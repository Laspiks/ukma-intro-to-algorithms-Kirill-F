#include "BST.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_node(NodePtr node) {
    if (node) {
        printf("%s ", node->key);
    }
}

int main() {
    NodePtr head = create_node("S", "value for key S"); // or NodePtr head = BSTPut(NULL, "S", "value for key S");
    BSTPut(head, "E", "some value");
    BSTPut(head, "X", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "R", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "H", NULL);

    printf("Value of key 'E': '%s''\n", (char *)BSTGet(head, "E"));

    NodePtr floorNode = BSTFloor(head, "G");
    if (floorNode) {
        printf("Floor of 'G': %s\n", floorNode->key);
    }

    // printf("Rank of 'R': %d\n", BSTRank(head, "R"));

    printf("Size of BST: %d\n", BSTSize(head));

    int arraySize;
    NodePtr *nodes = BSTNodes(head, &arraySize);
    printf("All nodes in sorted order: ");
    for (int i = 0; i < arraySize; i++) {
        printf("%s ", nodes[i]->key);
    }
    free(nodes);
    printf("\n");

    printf("In-order traversal: ");
    BSTIterate(head, print_node);
    printf("\n");

    head = BSTDeleteMin(head);
    printf("BST after deleting min: ");
    BSTIterate(head, print_node);
    printf("\n");

    head = BSTDelete(head, "E");
    printf("BST after deleting 'E': ");
    BSTIterate(head, print_node);
    printf("\n");

    BSTDestroy(head);

    return 0;
}
