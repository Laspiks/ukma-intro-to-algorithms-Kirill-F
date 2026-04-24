#ifndef DFS_H
#define DFS_H

#include "digraph.h"
#include "paths.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * Runs DFS from source vertex `s`, returns Paths struct with filled info.
 */
PathsPtr dfs(const DigraphPtr g, vertex_t s);

/**
 * Performs topological sort using DFS postorder.
 *
 * @param g The directed graph (DigraphPtr).
 * @return Pointer to an array containing the topological order (g->V elements).
 *         The caller must free the returned array.
 */
vertex_t *topological_sort(const DigraphPtr g);

#endif // DFS_H
