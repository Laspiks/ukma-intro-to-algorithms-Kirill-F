#ifndef PERCOLATION_H  // Prevent multiple inclusion of this header.
#define PERCOLATION_H  // Mark the header as already included.

#include <stdbool.h>  // Provides the bool type.

// Forward declaration keeps implementation details hidden from users.
typedef struct Percolation Percolation;

// Create a new percolation object for an n by n grid.
Percolation* create_percolation(int n);

// Destroy the object and free all memory it owns.
void destroy_percolation(Percolation* pc);

// Return the current number of open sites.
int get_opened_count(Percolation* pc);

// Open the site at coordinates (i, j) if it is not already open.
void open_coordinate(Percolation* pc, int i, int j);

// Check whether the site at coordinates (i, j) is open.
bool is_opened(Percolation* pc, int i, int j);

// Check whether the system percolates from top to bottom.
bool percolates(Percolation* pc);

#endif  // PERCOLATION_H
