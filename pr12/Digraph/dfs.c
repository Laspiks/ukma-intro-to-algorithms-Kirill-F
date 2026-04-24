#include "dfs.h"
#include "paths_helper.h"

// recursive DFS does the work
void dfs_recursive(const DigraphPtr g, PathsPtr p, vertex_t v) {
    p->marked[v] = true; // marked[v] = true if v connected to s
    int size = 0;
    const vertex_t *adj = DigraphAdj(g, v, &size);
    for (int i = 0; i < size; ++i) {
        vertex_t w = adj[i];
        if (!p->marked[w]) {
            dfs_recursive(g, p, w);
            p->edge_to[w] = v; // edge_to[w] = previous vertex on path from s to w
        }
    }
}

PathsPtr dfs(const DigraphPtr g, vertex_t s) {
    PathsPtr p = fromDigraph(g, s); // initialize data structures

    dfs_recursive(g, p, s); // find vertices connected to s
    return p;
}

static void topological_dfs(const DigraphPtr g, vertex_t v, bool *marked, vertex_t *order,
                            int *next_pos) {
    marked[v] = true;

    int size = 0;
    const vertex_t *adj = DigraphAdj(g, v, &size);
    for (int i = 0; i < size; ++i) {
        vertex_t w = adj[i];
        if (!marked[w]) {
            topological_dfs(g, w, marked, order, next_pos);
        }
    }

    order[(*next_pos)--] = v;
}

vertex_t *topological_sort(const DigraphPtr g) {
    if (g == NULL) {
        return NULL;
    }

    int vertices = DigraphV(g);
    vertex_t *order = malloc(sizeof(vertex_t) * vertices);
    bool *marked = calloc(vertices, sizeof(bool));
    if (order == NULL || marked == NULL) {
        free(order);
        free(marked);
        return NULL;
    }

    int next_pos = vertices - 1;
    for (vertex_t v = 0; v < vertices; ++v) {
        if (!marked[v]) {
            topological_dfs(g, v, marked, order, &next_pos);
        }
    }

    free(marked);
    return order;
}
