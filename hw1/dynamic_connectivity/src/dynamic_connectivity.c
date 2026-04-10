#include "dynamic_connectivity.h"  // Public declarations for the union-find module.
#include <stddef.h>                // Defines NULL.

// Initialize the structure for the first n elements.
void init_dynamic_connectivity(DynamicConnectivity* dc, int n) {
    // Ignore an invalid destination pointer.
    if (dc == NULL) {
        return;
    }
    // Negative sizes are not valid, so clamp to zero.
    if (n < 0) {
        n = 0;
    }
    // Do not allow initialization beyond the fixed capacity.
    if (n > CAPACITY) {
        n = CAPACITY;
    }
    // Every element starts in its own separate component.
    for (int i = 0; i < n; ++i) {
        dc->id[i] = i;  // Each node is initially its own parent.
        dc->sz[i] = 1;  // Each component initially contains one node.
    }
}

// Find the representative root of element i.
int root(DynamicConnectivity* dc, int i) {
    // Climb parent links until a self-parented node is reached.
    while (i != dc->id[i]) {
        dc->id[i] = dc->id[dc->id[i]];  // Compress the path by skipping one level.
        i = dc->id[i];                  // Continue moving toward the root.
    }
    return i;  // Return the root index.
}

// Check whether p and q belong to the same component.
bool connected(DynamicConnectivity* dc, int p, int q) {
    return root(dc, p) == root(dc, q);  // Equal roots mean connected nodes.
}

// Merge the components that contain p and q.
void add_union(DynamicConnectivity* dc, int p, int q) {
    int root_p = root(dc, p);  // Root of the first element.
    int root_q = root(dc, q);  // Root of the second element.
    // Stop if both nodes are already in the same component.
    if (root_p == root_q) {
        return;
    }

    // Attach the smaller tree below the larger tree.
    if (dc->sz[root_p] < dc->sz[root_q]) {
        dc->id[root_p] = root_q;          // Make root_q the new parent.
        dc->sz[root_q] += dc->sz[root_p]; // Update the merged tree size.
    } else {
        dc->id[root_q] = root_p;          // Make root_p the new parent.
        dc->sz[root_p] += dc->sz[root_q]; // Update the merged tree size.
    }
}
