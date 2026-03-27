#ifndef DYNAMIC_CONNECTIVITY_H
#define DYNAMIC_CONNECTIVITY_H

#include <stdbool.h>

// Functions below implement Weighted quick-union with path compression improvements

// Maximum number of elements
#define CAPACITY 100000

// Structure to hold the dynamic connectivity data
typedef struct {
    int id[CAPACITY];   // Array for parent links
    int sz[CAPACITY];  // Array to track the size of each tree
} DynamicConnectivity;

/**
 * Initializes the dynamic connectivity structure.
 * 
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param n  Number of elements to initialize.
 */
void init_dynamic_connectivity(DynamicConnectivity* dc, int n);

/**
 * Finds the root of the element `i` with path compression.
 * 
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param i  Element to find the root of.
 * @return The root of element `i`.
 */
int root(DynamicConnectivity* dc, int i);

/**
 * Checks if elements `p` and `q` are connected.
 * 
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param p  First element.
 * @param q  Second element.
 * @return True if `p` and `q` are connected, otherwise false.
 */
bool connected(DynamicConnectivity* dc, int p, int q);

/**
 * Unites the components containing elements `p` and `q`.
 * 
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param p  First element.
 * @param q  Second element.
 */
void add_union(DynamicConnectivity* dc, int p, int q);

#endif // DYNAMIC_CONNECTIVITY_H
