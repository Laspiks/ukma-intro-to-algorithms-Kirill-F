#include "dynamic_connectivity.h"
#include <stddef.h>

void init_dynamic_connectivity(DynamicConnectivity* dc, int n) {
    if (dc == NULL) {
        return;
    }
    if (n < 0) {
        n = 0;
    }
    if (n > CAPACITY) {
        n = CAPACITY;
    }
    for (int i = 0; i < n; ++i) {
        dc->id[i] = i;
        dc->sz[i] = 1;
    }
}

int root(DynamicConnectivity* dc, int i) {
    while (i != dc->id[i]) {
        dc->id[i] = dc->id[dc->id[i]]; // path halving
        i = dc->id[i];
    }
    return i;
}

bool connected(DynamicConnectivity* dc, int p, int q) {
    return root(dc, p) == root(dc, q);
}

void add_union(DynamicConnectivity* dc, int p, int q) {
    int root_p = root(dc, p);
    int root_q = root(dc, q);
    if (root_p == root_q) {
        return;
    }

    if (dc->sz[root_p] < dc->sz[root_q]) {
        dc->id[root_p] = root_q;
        dc->sz[root_q] += dc->sz[root_p];
    } else {
        dc->id[root_q] = root_p;
        dc->sz[root_p] += dc->sz[root_q];
    }
}
