#include "percolation.h"

#include "dynamic_connectivity.h"
#include <stdlib.h>

struct Percolation {
    int n;
    int opened_count;
    bool* grid;
    DynamicConnectivity dc;
    int virtual_top;
    int virtual_bottom;
};

static int index_for(const Percolation* pc, int i, int j) {
    return i * pc->n + j;
}

static bool in_bounds(const Percolation* pc, int i, int j) {
    return i >= 0 && i < pc->n && j >= 0 && j < pc->n;
}

Percolation* create_percolation(int n) {
    if (n <= 0) {
        return NULL;
    }

    int total_sites = n * n;
    if (total_sites + 2 > CAPACITY) {
        return NULL;
    }

    Percolation* pc = (Percolation*)malloc(sizeof(Percolation));
    if (pc == NULL) {
        return NULL;
    }

    pc->n = n;
    pc->opened_count = 0;
    pc->grid = (bool*)calloc((size_t)total_sites, sizeof(bool));
    if (pc->grid == NULL) {
        free(pc);
        return NULL;
    }

    pc->virtual_top = total_sites;
    pc->virtual_bottom = total_sites + 1;
    init_dynamic_connectivity(&pc->dc, total_sites + 2);

    return pc;
}

void destroy_percolation(Percolation* pc) {
    if (pc == NULL) {
        return;
    }
    free(pc->grid);
    free(pc);
}

int get_opened_count(Percolation* pc) {
    if (pc == NULL) {
        return 0;
    }
    return pc->opened_count;
}

void open_coordinate(Percolation* pc, int i, int j) {
    if (pc == NULL || !in_bounds(pc, i, j)) {
        return;
    }

    int idx = index_for(pc, i, j);
    if (pc->grid[idx]) {
        return;
    }

    pc->grid[idx] = true;
    pc->opened_count += 1;

    if (i == 0) {
        add_union(&pc->dc, idx, pc->virtual_top);
    }
    if (i == pc->n - 1) {
        add_union(&pc->dc, idx, pc->virtual_bottom);
    }

    // Connect to open neighbors (no diagonals)
    if (in_bounds(pc, i - 1, j) && is_opened(pc, i - 1, j)) {
        add_union(&pc->dc, idx, index_for(pc, i - 1, j));
    }
    if (in_bounds(pc, i + 1, j) && is_opened(pc, i + 1, j)) {
        add_union(&pc->dc, idx, index_for(pc, i + 1, j));
    }
    if (in_bounds(pc, i, j - 1) && is_opened(pc, i, j - 1)) {
        add_union(&pc->dc, idx, index_for(pc, i, j - 1));
    }
    if (in_bounds(pc, i, j + 1) && is_opened(pc, i, j + 1)) {
        add_union(&pc->dc, idx, index_for(pc, i, j + 1));
    }
}

bool is_opened(Percolation* pc, int i, int j) {
    if (pc == NULL || !in_bounds(pc, i, j)) {
        return false;
    }
    return pc->grid[index_for(pc, i, j)];
}

bool percolates(Percolation* pc) {
    if (pc == NULL) {
        return false;
    }
    return connected(&pc->dc, pc->virtual_top, pc->virtual_bottom);
}
