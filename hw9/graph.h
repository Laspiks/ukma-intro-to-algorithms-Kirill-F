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

// Main function from task 1.
vertex_t *GraphShortestBFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

// DFS version from practical task.
vertex_t *GraphShortestDFS(const GraphPtr g, vertex_t start, vertex_t end, int *path_len);

// Same search, but also returns how many vertices were visited.
vertex_t *GraphShortestBFSStats(const GraphPtr g, vertex_t start, vertex_t end, int *path_len,
                                int *visited_count);
vertex_t *GraphShortestDFSStats(const GraphPtr g, vertex_t start, vertex_t end, int *path_len,
                                int *visited_count);
vertex_t *GraphShortestBFSAnyStats(const GraphPtr g, vertex_t start, const vertex_t *targets,
                                   int target_count, int *path_len, int *visited_count);
vertex_t *GraphShortestDFSAnyStats(const GraphPtr g, vertex_t start, const vertex_t *targets,
                                   int target_count, int *path_len, int *visited_count);

void printPath(const vertex_t *path, int path_len);

#endif
