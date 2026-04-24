// item.h
#include <string.h>

typedef void* Item;

#define key(A) (A)
#define less(A, B) (strcmp((char *)A, (char *)B) < 0)
#define exch(A, B)                                                                                 \
    {                                                                                              \
        Item t = A;                                                                                \
        A = B;                                                                                     \
        B = t;                                                                                     \
    }
    