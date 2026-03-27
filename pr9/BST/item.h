#ifndef ITEM_H
#define ITEM_H 

#include <string.h>

typedef void *Item;
#define less(A, B) (strcmp((char *)A, (char *)B) < 0)
#define greater(A, B) (strcmp((char *)A, (char *)B) > 0)

#define greater_int(A, B) ((intptr_t)(A) > (intptr_t)(B) ? 1 : 0)

typedef char *Key;
#define equal(key_a, key_b) (strcmp((key_a), (key_b)) == 0)

#endif
