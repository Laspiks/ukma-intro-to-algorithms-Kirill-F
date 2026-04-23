#include "percolation.h"  // Public declarations for the percolation API.

#include "dynamic_connectivity.h"  // Union-find helpers used for connectivity tracking.
#include <stdlib.h>                // Memory allocation functions.

// Keep the full structure definition private inside the implementation file.
struct Percolation {
    int n;                   // Grid size, meaning the board is n by n.
    int opened_count;        // Number of sites that are currently open.
    bool* grid;              // Flat array that stores open or blocked state.
    DynamicConnectivity dc;  // Union-find structure for connectivity queries.
    int virtual_top;         // Extra node connected to all open sites in the top row.
    int virtual_bottom;      // Extra node connected to all open sites in the bottom row.
};

// Convert 2D coordinates into a 1D array index.
static int index_for(const Percolation* pc, int i, int j) {
    return i * pc->n + j;  // Use row-major order.
}

// Check whether coordinates belong to the grid.
static bool in_bounds(const Percolation* pc, int i, int j) {
    return i >= 0 && i < pc->n && j >= 0 && j < pc->n;  // Accept only valid rows and columns.
}

// Create and initialize a new percolation object.
Percolation* create_percolation(int n) {
    // Reject invalid grid sizes.
    if (n <= 0) {
        return NULL;
    }

    int total_sites = n * n;  // Count all real sites in the grid.
    // Reserve room for two additional virtual nodes.
    if (total_sites + 2 > CAPACITY) {
        return NULL;
    }

    Percolation* pc = (Percolation*)malloc(sizeof(Percolation));  // Allocate the main structure.
    // Stop if memory allocation failed.
    if (pc == NULL) {
        return NULL;
    }

    pc->n = n;  // Store the grid dimension.
    pc->opened_count = 0;  // No sites are open at the beginning.
    pc->grid = (bool*)calloc((size_t)total_sites, sizeof(bool));  // Start with all sites blocked.
    // Clean up and fail if the grid array could not be allocated.
    if (pc->grid == NULL) {
        free(pc);
        return NULL;
    }

    pc->virtual_top = total_sites;  // Put the virtual top after the last real site.
    pc->virtual_bottom = total_sites + 1;  // Put the virtual bottom after the virtual top.
    init_dynamic_connectivity(&pc->dc, total_sites + 2);  // Initialize union-find for all nodes.

    return pc;  // Return the prepared object.
}

// Destroy the percolation object and release its memory.
void destroy_percolation(Percolation* pc) {
    // Allow safe destruction of a NULL pointer.
    if (pc == NULL) {
        return;
    }
    free(pc->grid);  // Free the site-state array.
    free(pc);        // Free the structure itself.
}

// Return how many sites are currently open.
int get_opened_count(Percolation* pc) {
    // Return zero for an invalid object.
    if (pc == NULL) {
        return 0;
    }
    return pc->opened_count;  // Return the stored counter.
}

// Open one cell and connect it with adjacent open cells.
void open_coordinate(Percolation* pc, int i, int j) {
    // Ignore invalid objects and out-of-range coordinates.
    if (pc == NULL || !in_bounds(pc, i, j)) {
        return;
    }

    int idx = index_for(pc, i, j);  // Translate the coordinates to a flat index.
    // Stop if the site is already open.
    if (pc->grid[idx]) {
        return;
    }

    pc->grid[idx] = true;  // Mark the site as open.
    pc->opened_count += 1; // Increase the open-site counter.

    // Connect top-row sites to the virtual top node.
    if (i == 0) {
        add_union(&pc->dc, idx, pc->virtual_top);
    }
    // Connect bottom-row sites to the virtual bottom node.
    if (i == pc->n - 1) {
        add_union(&pc->dc, idx, pc->virtual_bottom);
    }

    // Connect to the open site directly above.
    if (in_bounds(pc, i - 1, j) && is_opened(pc, i - 1, j)) {
        add_union(&pc->dc, idx, index_for(pc, i - 1, j));
    }
    // Connect to the open site directly below.
    if (in_bounds(pc, i + 1, j) && is_opened(pc, i + 1, j)) {
        add_union(&pc->dc, idx, index_for(pc, i + 1, j));
    }
    // Connect to the open site on the left.
    if (in_bounds(pc, i, j - 1) && is_opened(pc, i, j - 1)) {
        add_union(&pc->dc, idx, index_for(pc, i, j - 1));
    }
    // Connect to the open site on the right.
    if (in_bounds(pc, i, j + 1) && is_opened(pc, i, j + 1)) {
        add_union(&pc->dc, idx, index_for(pc, i, j + 1));
    }
}

// Check whether a given cell is open.
bool is_opened(Percolation* pc, int i, int j) {
    // Invalid objects and invalid coordinates are treated as blocked.
    if (pc == NULL || !in_bounds(pc, i, j)) {
        return false;
    }
    return pc->grid[index_for(pc, i, j)];  // Return the stored site state.
}

// Check whether the system has a path from the top to the bottom.
bool percolates(Percolation* pc) {
    // A missing object cannot percolate.
    if (pc == NULL) {
        return false;
    }
    return connected(&pc->dc, pc->virtual_top, pc->virtual_bottom);  // Percolation means virtual nodes are connected.
}
