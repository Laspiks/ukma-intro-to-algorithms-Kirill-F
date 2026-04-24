#include "graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    vertex_t *neighbors;
    int size;
    int capacity;
} Vector;

struct Graph {
    vertex_t V;
    edge_t E;
    Vector *adj;
};

#define INITIAL_CAPACITY 4

static int add_adjacent_vertex(Vector *list, vertex_t v) {
    if (list->size >= list->capacity) {
        int new_capacity = (list->capacity == 0) ? INITIAL_CAPACITY : list->capacity * 2;
        vertex_t *new_data = realloc(list->neighbors, (size_t)new_capacity * sizeof(vertex_t));
        if (new_data == NULL) {
            return 0;
        }
        list->neighbors = new_data;
        list->capacity = new_capacity;
    }

    list->neighbors[list->size++] = v;
    return 1;
}

static bool valid_vertex(const GraphPtr g, vertex_t v) {
    return g != NULL && v >= 0 && v < g->V;
}

static vertex_t *ShortestDFS(const GraphPtr g, vertex_t current, vertex_t end, vertex_t *path,
                             int path_len, vertex_t *shortest, int *shortest_len,
                             int max_len, char *visited) {
    if (path_len >= max_len) {
        return shortest;
    }

    // Якщо вже маємо кращий шлях, довший копати нема сенсу.
    if (*shortest_len != -1 && path_len >= *shortest_len) {
        return shortest;
    }

    path[path_len] = current;
    path_len++;
    visited[current] = 1;

    if (current == end) {
        if (*shortest_len == -1 || path_len < *shortest_len) {
            memcpy(shortest, path, (size_t)path_len * sizeof(vertex_t));
            *shortest_len = path_len;
            printf("Found path:\n");
            printPath(path, path_len);
        }
    } else {
        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);

        for (int i = 0; i < size; ++i) {
            vertex_t next = adj[i];
            if (!visited[next]) {
                shortest = ShortestDFS(g, next, end, path, path_len, shortest, shortest_len,
                                       max_len, visited);
            }
        }
    }

    // Повертаємось назад і відкриваємо вершину для інших гілок.
    visited[current] = 0;
    return shortest;
}

GraphPtr GraphInit(int num_vertices) {
    if (num_vertices <= 0) {
        return NULL;
    }

    GraphPtr g = malloc(sizeof(*g));
    if (g == NULL) {
        return NULL;
    }

    g->V = num_vertices;
    g->E = 0;
    g->adj = calloc((size_t)num_vertices, sizeof(Vector));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

GraphPtr GraphInitFromFile(FILE *in) {
    if (in == NULL) {
        return NULL;
    }

    int vertices = 0;
    int edges = 0;
    if (fscanf(in, "%d %d", &vertices, &edges) != 2) {
        return NULL;
    }

    GraphPtr g = GraphInit(vertices);
    if (g == NULL) {
        return NULL;
    }

    for (int i = 0; i < edges; ++i) {
        vertex_t v = 0;
        vertex_t w = 0;
        if (fscanf(in, "%d %d", &v, &w) != 2) {
            GraphDestroy(g);
            return NULL;
        }
        GraphAddEdge(g, v, w);
    }

    return g;
}

void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w) {
    if (!valid_vertex(g, v) || !valid_vertex(g, w)) {
        return;
    }

    // Лекційний API для неорієнтованого графа.
    if (!add_adjacent_vertex(&g->adj[v], w)) {
        return;
    }
    if (!add_adjacent_vertex(&g->adj[w], v)) {
        g->adj[v].size--;
        return;
    }
    g->E++;
}

vertex_t GraphV(const GraphPtr g) {
    return (g == NULL) ? 0 : g->V;
}

edge_t GraphE(const GraphPtr g) {
    return (g == NULL) ? 0 : g->E;
}

const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size) {
    if (size != NULL) {
        *size = 0;
    }
    if (!valid_vertex(g, v) || size == NULL) {
        return NULL;
    }

    *size = g->adj[v].size;
    return g->adj[v].neighbors;
}

void GraphPrint(const GraphPtr g) {
    if (g == NULL) {
        return;
    }

    for (vertex_t v = 0; v < g->V; ++v) {
        printf("%d:", v);
        for (int i = 0; i < g->adj[v].size; ++i) {
            printf(" %d", g->adj[v].neighbors[i]);
        }
        printf("\n");
    }
}

void GraphDestroy(GraphPtr g) {
    if (g == NULL) {
        return;
    }

    for (vertex_t v = 0; v < g->V; ++v) {
        free(g->adj[v].neighbors);
    }
    free(g->adj);
    free(g);
}

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len) {
    if (path_len == NULL) {
        return NULL;
    }
    *path_len = 0;

    if (!valid_vertex(g, start) || !valid_vertex(g, end)) {
        return NULL;
    }

    int max_len = GraphV(g);
    vertex_t *path = malloc((size_t)max_len * sizeof(vertex_t));
    vertex_t *shortest = malloc((size_t)max_len * sizeof(vertex_t));
    char *visited = calloc((size_t)max_len, sizeof(char));

    if (path == NULL || shortest == NULL || visited == NULL) {
        free(path);
        free(shortest);
        free(visited);
        return NULL;
    }

    int shortest_len = -1;
    ShortestDFS(g, start, end, path, 0, shortest, &shortest_len, max_len, visited);

    free(path);
    free(visited);

    if (shortest_len == -1) {
        free(shortest);
        return NULL;
    }

    *path_len = shortest_len;
    return shortest;
}

void printPath(const vertex_t *path, int path_len) {
    if (path == NULL || path_len <= 0) {
        printf("(no path)\n");
        return;
    }

    for (int i = 0; i < path_len; ++i) {
        printf("%d", path[i]);
        if (i + 1 < path_len) {
            printf("->");
        }
    }
    printf("\n");
}
