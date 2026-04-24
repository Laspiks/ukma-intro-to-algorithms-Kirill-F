#include "hash_table.h"

#include "item.h"
#include "hash_code.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 97 // Number of chains

// Node structure for the linked list
typedef struct Node {
    Key key;
    Item value;
    struct Node *next;
} Node;

void printNode(const Node *node, const char *type) {
    if (node == NULL) {
        printf("NULL");
        return;
    }

    printf(" \"%s\":", node->key);

    if (strcmp(type, "int") == 0) {
        printf("%d", (int)(intptr_t)(node->value));
    } else if (strcmp(type, "char") == 0) {
        printf("'%c'", *(char *)(node->value));
    } else if (strcmp(type, "string") == 0) {
        printf("\"%s\"", (char *)(node->value));
    } else {
        printf("UNKNOWN_TYPE");
    }
}

// Hash table structure
struct HashTable {
    Node* st[M]; // Array of chains
};

// Initialize the hash table
HashTablePtr HashTableInit() {
    // printf("SCHT implementation\n");
    HashTablePtr ht = malloc(sizeof(struct HashTable));
    if (!ht)
        return NULL;
    for (int i = 0; i < M; i++) {
        ht->st[i] = NULL;
    }
    return ht;
}

bool HashTablePut(HashTablePtr ht, Key key, Item value) {
    if (!ht || !key || !value)
        return false;

    int i = hash(key, M);
    for (Node *x = ht->st[i]; x != NULL; x = x->next) {
        if (equal(key, x->key)) {
            x->value = value; // Update value if key already exists
            return true;
        }
    }

    // strdup the key here so we take ownership (is working with char* only)
    Key keyCopy = strdup(key);
    if (!keyCopy) {
        return false;
    }

    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        free(keyCopy);
        return false;
    }

    newNode->key = keyCopy;
    newNode->value = value;
    newNode->next = ht->st[i];
    ht->st[i] = newNode;
    return true;
}

// Retrieve a value by key from the hash table
Item HashTableGet(HashTablePtr ht, Key key) {
    if (!ht || !key)
        return NULL;
        
    int i = hash(key, M);
    for (Node *x = ht->st[i]; x != NULL; x = x->next) {
        if (equal(key, x->key)) {
            return x->value;
        }
    }
    return NULL; // Key not found
}

// Destroy the hash table and free memory
void HashTableDestroy(HashTablePtr ht) {
    for (int i = 0; i < M; i++) {
        Node *x = ht->st[i];
        while (x != NULL) {
            Node *temp = x;
            x = x->next;
            free(temp->key); // Free the key
            free(temp);
        }
    }
    free(ht);
}

void HashTablePrint(const HashTablePtr ht, const char *type, bool print_empty) {
    for (int i = 0; i < M; i++) {
        Node *x = ht->st[i];
        if (!x) {
            if (print_empty) {
                printf("%d: NULL\n", i);
            }
        } else {
            printf("%d:", i);
            while (x) {
                printNode(x, type);
                x = x->next;
            }
            printf("\n");
        }
    }
}
