#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdbool.h>
#include <stdio.h>

typedef int vertex_t;           // Type of vertex (can be changed to any type)
typedef int edge_t;             // Type of edge (can be changed to any type)
typedef struct Digraph *DigraphPtr; // Opaque pointer to digraph structure (pimpl)

DigraphPtr DigraphInit(int num_vertices); // Creates a new digraph with num vertices
DigraphPtr DigraphInitFromFile(FILE *in); // Creates a digraph from an input stream (assumes FILE* stream)

void DigraphAddEdge(DigraphPtr g, vertex_t v, vertex_t w); // Adds an undirected edge between vertices v and w

vertex_t DigraphV(const DigraphPtr g); // Returns the number of vertices
edge_t DigraphE(const DigraphPtr g);   // Returns the number of edges

// Returns an array of vertices adjacent to v and stores the number of adjacent vertices in *size.
// Caller must NOT free the returned array
const vertex_t *DigraphAdj(const DigraphPtr g, vertex_t v, int *size);

void DigraphPrint(const DigraphPtr g); // Prints the digraph to stdout
void DigraphDestroy(DigraphPtr g);     // Frees the digraph structure

#endif // DIGRAPH_H
