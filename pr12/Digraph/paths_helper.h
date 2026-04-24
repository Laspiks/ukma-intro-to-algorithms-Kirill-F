#ifndef PATHS_HELPER_H
#define PATHS_HELPER_H

#include "digraph.h"
#include "paths.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct Paths {
    bool *marked;
    vertex_t *edge_to;
    vertex_t source;
    int vertices; // total number of vertices
} Paths;

static inline PathsPtr fromDigraph(const DigraphPtr g, vertex_t s) {
    int V = DigraphV(g);
    PathsPtr p = malloc(sizeof(Paths));
    if (!p)
        return NULL;

    p->marked = calloc(V, sizeof(bool));
    p->edge_to = malloc(V * sizeof(vertex_t));
    p->source = s;
    p->vertices = V;

    if (!p->marked || !p->edge_to) {
        free(p->marked);
        free(p->edge_to);
        free(p);
        return NULL;
    }

    for (int i = 0; i < V; ++i) {
        p->edge_to[i] = -1;
    }
    return p;
}

static inline void printPath(const vertex_t *path, int path_len) {
    if (path != NULL) {
        for (int i = 0; i < path_len; i++) {
            printf("%d", path[i]);
            if (i < path_len - 1)
                printf("->");
        }
        printf("\n");
    } else {
        printf("No path\n");
    }
}

#endif // PATHS_HELPER_H
