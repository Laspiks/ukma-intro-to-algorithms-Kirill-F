#include "digraph.h"
#include "paths.h"
#include "paths_helper.h"
#include "dfs.h"
#include <stdio.h>
#include <stdlib.h>

void test_topological_sort();

int main() {
    {
        FILE *f = fopen("tinyDG.txt", "r");
        if (f == NULL) {
            printf("Failed to open file\n");
            return 1;
        }

        DigraphPtr g = DigraphInitFromFile(f);
        fclose(f);

        if (g == NULL) {
            printf("Failed to read digraph from file\n");
            return 1;
        }

        printf("Digraph with %d vertices and %d edges:\n", DigraphV(g), DigraphE(g));
        DigraphPrint(g);

        vertex_t source = 0;
        PathsPtr dfs_paths = PathsInit(g, source, DFS);

        printf("[DFS] Has paths from vertex %d:\n", source);
        for (int v = 0; v < DigraphV(g); ++v) {
            if (PathsHasPathTo(dfs_paths, v)) {
                printf("%d ", v);
            }
        }
        printf("\n");

        vertex_t dest = 3;
        printf("[DFS] Path from vertex %d to %d:\n", source, dest);
        int dfs_len = 0;
        vertex_t *dfs_path = PathsPathTo(dfs_paths, dest, &dfs_len); // Test with NULL size
        for (int i = 0; i < dfs_len; ++i) {
            printf("%d ", dfs_path[i]);
        }
        printf("\n");

        free(dfs_path);

        PathsDestroy(dfs_paths);
        DigraphDestroy(g);
    }

    printf("\n");

    {
        FILE *f = fopen("tinyDG2.txt", "r");
        if (f == NULL) {
            printf("Failed to open file\n");
            return 1;
        }

        DigraphPtr g = DigraphInitFromFile(f);
        fclose(f);

        if (g == NULL) {
            printf("Failed to read digraph from file\n");
            return 1;
        }

        printf("Digraph with %d vertices and %d edges:\n", DigraphV(g), DigraphE(g));
        DigraphPrint(g);

        vertex_t source = 0;
        PathsPtr bfs_paths = PathsInit(g, source, BFS);

        printf("[BFS] Has paths from vertex %d:\n", source);
        for (int v = 0; v < DigraphV(g); ++v) {
            if (PathsHasPathTo(bfs_paths, v)) {
                printf("%d ", v);
            }
        }
        printf("\n");

        vertex_t dest = 3;
        printf("[BFS] Path from vertex %d to %d:\n", source, dest);
        int bfs_len = 0;
        vertex_t *bfs_path = PathsPathTo(bfs_paths, dest, &bfs_len); // Test with NULL size
        for (int i = 0; i < bfs_len; ++i) {
            printf("%d ", bfs_path[i]);
        }
        printf("\n");
    
        free(bfs_path);

        PathsDestroy(bfs_paths);
        DigraphDestroy(g);
    }

    printf("\n");

    { 
        // For Practical session 12 
        test_topological_sort();
    }

    return 0;
}

// For Practical session 12
void test_topological_sort() {
    FILE *f = fopen("tinyDG3.txt", "r");
    if (f == NULL) {
        printf("Failed to open file\n");
        return ;
    }
    DigraphPtr g = DigraphInitFromFile(f);
    fclose(f);

    if (g == NULL) {
        printf("Failed to read digraph from file\n");
        return;
    }

    printf("[Topological sort]\n");
    vertex_t *order = topological_sort(g);
    if (order == NULL) {
        printf("Failed to compute topological order\n");
        DigraphDestroy(g);
        return;
    }

    for (int i = 0; i < DigraphV(g); ++i) {
        printf("%d ", order[i]);
    }
    printf("\n");

    free(order);
    DigraphDestroy(g);
}
