#ifndef DYNAMIC_CONNECTIVITY_H  // Prevent multiple inclusion of this header.
#define DYNAMIC_CONNECTIVITY_H  // Mark the header as already included.

#include <stdbool.h>  // Provides the bool type.

// Maximum number of elements supported by the structure.
#define CAPACITY 100000

// Store parent links and subtree sizes for union-find.
typedef struct {
    int id[CAPACITY];  // Parent link for each element.
    int sz[CAPACITY];  // Size of the tree rooted at each element.
} DynamicConnectivity;

/**
 * Initialize the dynamic connectivity structure.
 *
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param n  Number of elements to initialize.
 */
void init_dynamic_connectivity(DynamicConnectivity* dc, int n);

/**
 * Find the root of element i using path compression.
 *
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param i  Element whose root should be found.
 * @return The root of element i.
 */
int root(DynamicConnectivity* dc, int i);

/**
 * Check whether elements p and q are connected.
 *
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param p  First element.
 * @param q  Second element.
 * @return True if p and q are connected, otherwise false.
 */
bool connected(DynamicConnectivity* dc, int p, int q);

/**
 * Merge the components containing p and q.
 *
 * @param dc Pointer to the DynamicConnectivity structure.
 * @param p  First element.
 * @param q  Second element.
 */
void add_union(DynamicConnectivity* dc, int p, int q);

#endif  // DYNAMIC_CONNECTIVITY_H
