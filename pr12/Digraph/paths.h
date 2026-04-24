#ifndef PATHS_H
#define PATHS_H

#include "digraph.h"
#include <stdbool.h>

typedef struct Paths *PathsPtr;

typedef enum { DFS, BFS } type_t;

// Constructor: finds all paths from source vertex s
PathsPtr PathsInit(const DigraphPtr g, vertex_t s, type_t type);

// Check if there's a path from s to vertex v
bool PathsHasPathTo(const PathsPtr p, vertex_t v);

// Get path from s to v (returns dynamically allocated array, caller must free)
vertex_t *PathsPathTo(const PathsPtr p, vertex_t v, int *size);

// Clean up
void PathsDestroy(PathsPtr p);

#endif // PATHS_H
