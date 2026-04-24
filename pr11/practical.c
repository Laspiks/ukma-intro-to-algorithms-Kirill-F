#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    GraphPtr g = GraphInit(6);
    if (g == NULL) {
        fprintf(stderr, "Cannot create graph\n");
        return 1;
    }

    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 2, 4);
    GraphAddEdge(g, 3, 4);
    GraphAddEdge(g, 3, 5);
    GraphAddEdge(g, 0, 2);
    GraphAddEdge(g, 1, 0);
    GraphAddEdge(g, 3, 1);
    GraphAddEdge(g, 4, 0);

    int path_len = 0;
    vertex_t *path = GraphShortestDFS(g, 0, 5, &path_len);

    printf("Shortest path found by DFS:\n");
    printPath(path, path_len);

    free(path);
    GraphDestroy(g);
    return 0;
}
