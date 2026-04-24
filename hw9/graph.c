#include "graph.h"

#include "queue.h"

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

static bool valid_vertex(const GraphPtr g, vertex_t v) {
    return g != NULL && v >= 0 && v < g->V;
}

static int add_adjacent_vertex(Vector *list, vertex_t v) {
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity == 0 ? INITIAL_CAPACITY : list->capacity * 2;
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

static vertex_t *build_path(vertex_t start, vertex_t end, const vertex_t *edge_to, int *path_len) {
    int len = 1;
    for (vertex_t v = end; v != start; v = edge_to[v]) {
        len++;
    }

    vertex_t *path = malloc((size_t)len * sizeof(vertex_t));
    if (path == NULL) {
        return NULL;
    }

    vertex_t v = end;
    for (int i = len - 1; i >= 0; --i) {
        path[i] = v;
        if (v == start) {
            break;
        }
        v = edge_to[v];
    }

    *path_len = len;
    return path;
}

static char *build_target_mask(const GraphPtr g, const vertex_t *targets, int target_count) {
    if (g == NULL || targets == NULL || target_count <= 0) {
        return NULL;
    }

    char *is_target = calloc((size_t)GraphV(g), sizeof(char));
    if (is_target == NULL) {
        return NULL;
    }

    for (int i = 0; i < target_count; ++i) {
        if (valid_vertex(g, targets[i])) {
            is_target[targets[i]] = 1;
        }
    }

    return is_target;
}

static void shortest_dfs_recursive(const GraphPtr g, vertex_t current, vertex_t end, vertex_t *path,
                                   int path_len, vertex_t *shortest, int *shortest_len,
                                   int max_len, char *visited, char *seen_ever,
                                   int *visited_count) {
    if (path_len >= max_len) {
        return;
    }

    // If we already have shorter path, no need to go deeper.
    if (*shortest_len != -1 && path_len >= *shortest_len) {
        return;
    }

    path[path_len] = current;
    path_len++;
    visited[current] = 1;
    if (!seen_ever[current]) {
        seen_ever[current] = 1;
        (*visited_count)++;
    }

    if (current == end) {
        if (*shortest_len == -1 || path_len < *shortest_len) {
            memcpy(shortest, path, (size_t)path_len * sizeof(vertex_t));
            *shortest_len = path_len;
        }
    } else {
        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);

        for (int i = 0; i < size; ++i) {
            vertex_t next = adj[i];
            if (!visited[next]) {
                shortest_dfs_recursive(g, next, end, path, path_len, shortest, shortest_len,
                                       max_len, visited, seen_ever, visited_count);
            }
        }
    }

    // Open this vertex again for another DFS branch.
    visited[current] = 0;
}

static void shortest_dfs_any_recursive(const GraphPtr g, vertex_t current, const char *is_target,
                                       vertex_t *path, int path_len, vertex_t *shortest,
                                       int *shortest_len, int max_len, char *visited,
                                       char *seen_ever, int *visited_count) {
    if (path_len >= max_len) {
        return;
    }

    if (*shortest_len != -1 && path_len >= *shortest_len) {
        return;
    }

    path[path_len] = current;
    path_len++;
    visited[current] = 1;
    if (!seen_ever[current]) {
        seen_ever[current] = 1;
        (*visited_count)++;
    }

    if (is_target[current]) {
        if (*shortest_len == -1 || path_len < *shortest_len) {
            memcpy(shortest, path, (size_t)path_len * sizeof(vertex_t));
            *shortest_len = path_len;
        }
    } else {
        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);

        for (int i = 0; i < size; ++i) {
            vertex_t next = adj[i];
            if (!visited[next]) {
                shortest_dfs_any_recursive(g, next, is_target, path, path_len, shortest,
                                           shortest_len, max_len, visited, seen_ever,
                                           visited_count);
            }
        }
    }

    visited[current] = 0;
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
    return g == NULL ? 0 : g->V;
}

edge_t GraphE(const GraphPtr g) {
    return g == NULL ? 0 : g->E;
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

vertex_t *GraphShortestDFSStats(const GraphPtr g, vertex_t start, vertex_t end, int *path_len,
                                int *visited_count) {
    if (path_len == NULL || visited_count == NULL) {
        return NULL;
    }
    *path_len = 0;
    *visited_count = 0;

    if (!valid_vertex(g, start) || !valid_vertex(g, end)) {
        return NULL;
    }

    int max_len = GraphV(g);
    vertex_t *path = malloc((size_t)max_len * sizeof(vertex_t));
    vertex_t *shortest = malloc((size_t)max_len * sizeof(vertex_t));
    char *visited = calloc((size_t)max_len, sizeof(char));
    char *seen_ever = calloc((size_t)max_len, sizeof(char));

    if (path == NULL || shortest == NULL || visited == NULL || seen_ever == NULL) {
        free(path);
        free(shortest);
        free(visited);
        free(seen_ever);
        return NULL;
    }

    int shortest_len = -1;
    shortest_dfs_recursive(g, start, end, path, 0, shortest, &shortest_len, max_len, visited,
                           seen_ever, visited_count);

    free(path);
    free(visited);
    free(seen_ever);

    if (shortest_len == -1) {
        free(shortest);
        return NULL;
    }

    *path_len = shortest_len;
    return shortest;
}

vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len) {
    int visited_count = 0;
    return GraphShortestDFSStats(g, start, end, path_len, &visited_count);
}

vertex_t *GraphShortestDFSAnyStats(const GraphPtr g, vertex_t start, const vertex_t *targets,
                                   int target_count, int *path_len, int *visited_count) {
    if (path_len == NULL || visited_count == NULL) {
        return NULL;
    }
    *path_len = 0;
    *visited_count = 0;

    if (!valid_vertex(g, start) || targets == NULL || target_count <= 0) {
        return NULL;
    }

    char *is_target = build_target_mask(g, targets, target_count);
    if (is_target == NULL) {
        return NULL;
    }

    int max_len = GraphV(g);
    vertex_t *path = malloc((size_t)max_len * sizeof(vertex_t));
    vertex_t *shortest = malloc((size_t)max_len * sizeof(vertex_t));
    char *visited = calloc((size_t)max_len, sizeof(char));
    char *seen_ever = calloc((size_t)max_len, sizeof(char));

    if (path == NULL || shortest == NULL || visited == NULL || seen_ever == NULL) {
        free(is_target);
        free(path);
        free(shortest);
        free(visited);
        free(seen_ever);
        return NULL;
    }

    int shortest_len = -1;
    shortest_dfs_any_recursive(g, start, is_target, path, 0, shortest, &shortest_len, max_len,
                               visited, seen_ever, visited_count);

    free(is_target);
    free(path);
    free(visited);
    free(seen_ever);

    if (shortest_len == -1) {
        free(shortest);
        return NULL;
    }

    *path_len = shortest_len;
    return shortest;
}

vertex_t *GraphShortestBFSStats(const GraphPtr g, vertex_t start, vertex_t end, int *path_len,
                                int *visited_count) {
    if (path_len == NULL || visited_count == NULL) {
        return NULL;
    }
    *path_len = 0;
    *visited_count = 0;

    if (!valid_vertex(g, start) || !valid_vertex(g, end)) {
        return NULL;
    }

    int vertices = GraphV(g);
    char *visited = calloc((size_t)vertices, sizeof(char));
    vertex_t *edge_to = malloc((size_t)vertices * sizeof(vertex_t));
    QueuePtr queue = QueueInit();

    if (visited == NULL || edge_to == NULL || queue == NULL) {
        free(visited);
        free(edge_to);
        QueueDestroy(queue);
        return NULL;
    }

    for (int i = 0; i < vertices; ++i) {
        edge_to[i] = -1;
    }

    // BFS visits vertices layer by layer, so first found path is shortest.
    visited[start] = 1;
    *visited_count = 1;
    enqueue(queue, start);

    while (!QueueEmpty(queue)) {
        vertex_t current = dequeue(queue);
        if (current == end) {
            break;
        }

        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);
        for (int i = 0; i < size; ++i) {
            vertex_t next = adj[i];
            if (!visited[next]) {
                visited[next] = 1;
                edge_to[next] = current;
                (*visited_count)++;
                enqueue(queue, next);
            }
        }
    }

    vertex_t *path = NULL;
    if (visited[end]) {
        path = build_path(start, end, edge_to, path_len);
    }

    QueueDestroy(queue);
    free(visited);
    free(edge_to);
    return path;
}

vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len) {
    int visited_count = 0;
    return GraphShortestBFSStats(g, start, end, path_len, &visited_count);
}

vertex_t *GraphShortestBFSAnyStats(const GraphPtr g, vertex_t start, const vertex_t *targets,
                                   int target_count, int *path_len, int *visited_count) {
    if (path_len == NULL || visited_count == NULL) {
        return NULL;
    }
    *path_len = 0;
    *visited_count = 0;

    if (!valid_vertex(g, start) || targets == NULL || target_count <= 0) {
        return NULL;
    }

    char *is_target = build_target_mask(g, targets, target_count);
    if (is_target == NULL) {
        return NULL;
    }

    int vertices = GraphV(g);
    char *visited = calloc((size_t)vertices, sizeof(char));
    vertex_t *edge_to = malloc((size_t)vertices * sizeof(vertex_t));
    QueuePtr queue = QueueInit();

    if (visited == NULL || edge_to == NULL || queue == NULL) {
        free(is_target);
        free(visited);
        free(edge_to);
        QueueDestroy(queue);
        return NULL;
    }

    for (int i = 0; i < vertices; ++i) {
        edge_to[i] = -1;
    }

    visited[start] = 1;
    *visited_count = 1;
    enqueue(queue, start);

    vertex_t found_target = -1;

    while (!QueueEmpty(queue)) {
        vertex_t current = dequeue(queue);
        if (is_target[current]) {
            found_target = current;
            break;
        }

        int size = 0;
        const vertex_t *adj = GraphAdj(g, current, &size);
        for (int i = 0; i < size; ++i) {
            vertex_t next = adj[i];
            if (!visited[next]) {
                visited[next] = 1;
                edge_to[next] = current;
                (*visited_count)++;
                enqueue(queue, next);
            }
        }
    }

    vertex_t *path = NULL;
    if (found_target != -1) {
        path = build_path(start, found_target, edge_to, path_len);
    }

    free(is_target);
    QueueDestroy(queue);
    free(visited);
    free(edge_to);
    return path;
}

void printPath(const vertex_t *path, int path_len) {
    if (path == NULL || path_len <= 0) {
        printf("(no path)\n");
        return;
    }

    for (int i = 0; i < path_len; ++i) {
        printf("%d", path[i]);
        if (i + 1 < path_len) {
            printf(" -> ");
        }
    }
    printf("\n");
}
