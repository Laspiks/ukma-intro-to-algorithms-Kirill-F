#include "paths.h"
#include "bfs.h"
#include "dfs.h"
#include "paths_helper.h"
#include <assert.h>
#include <stdlib.h>

PathsPtr PathsInit(const DigraphPtr g, vertex_t s, type_t type) {
    if (type == DFS) {
        return dfs(g, s);
    } else if (type == BFS) {
        return bfs(g, s);
    } else {
        return NULL; // Invalid type
    }   
}

bool PathsHasPathTo(const PathsPtr p, vertex_t v) {
    if (!p)
        return false;
    
    if (v < 0 || v >= p->vertices)
        return false;
    
    return p->marked[v];
}

vertex_t *PathsPathTo(const PathsPtr p, vertex_t v, int *size) {
    if (!PathsHasPathTo(p, v)) {
        *size = 0;
        return NULL;
    }

    // Maximum size of path is number of vertices
    vertex_t *stack = malloc(sizeof(vertex_t) * p->vertices);
    if (!stack) {
        *size = 0;
        return NULL;
    }

    int count = 0;
    for (vertex_t x = v; x != p->source; x = p->edge_to[x]) {
        stack[count++] = x;
    }
    stack[count++] = p->source;

    // Reverse path
    vertex_t *path = malloc(sizeof(vertex_t) * count);
    for (int i = 0; i < count; ++i) {
        path[i] = stack[count - i - 1];
    }

    free(stack);
    *size = count;
    return path;
}

void PathsDestroy(PathsPtr p) {
    if (!p)
        return;
    free(p->marked);
    free(p->edge_to);
    free(p);
}
