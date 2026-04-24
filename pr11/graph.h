#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef int vertex_t;
typedef int edge_t;
typedef struct Graph *GraphPtr;

GraphPtr GraphInit(int num_vertices);
GraphPtr GraphInitFromFile(FILE *in);
void GraphAddEdge(GraphPtr g, vertex_t v, vertex_t w);
vertex_t GraphV(const GraphPtr g);
edge_t GraphE(const GraphPtr g);
const vertex_t *GraphAdj(const GraphPtr g, vertex_t v, int *size);
void GraphPrint(const GraphPtr g);
void GraphDestroy(GraphPtr g);

// Finds shortest path from start to end using DFS.
// Returns malloc-allocated array with vertices of the path or NULL.
vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

void printPath(const vertex_t *path, int path_len);

#endif
