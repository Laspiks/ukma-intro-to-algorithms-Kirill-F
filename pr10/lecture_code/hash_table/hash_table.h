#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "item.h"
#include <stdbool.h>

typedef struct HashTable *HashTablePtr;

HashTablePtr HashTableInit();
bool HashTablePut(HashTablePtr, Key, Item);
Item HashTableGet(HashTablePtr, Key);
void HashTablePrint(const HashTablePtr ht, const char *type, bool print_empty);
void HashTableDestroy(HashTablePtr);

#endif // #define HASH_TABLE_H
