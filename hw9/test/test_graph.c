#include "../graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void test_shortest_bfs_basic(void) {
    GraphPtr g = GraphInit(6);
    assert(g != NULL);

    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 0, 3);
    GraphAddEdge(g, 3, 4);
    GraphAddEdge(g, 4, 5);
    GraphAddEdge(g, 2, 5);

    int path_len = 0;
    int visited_count = 0;
    vertex_t *path = GraphShortestBFSStats(g, 0, 5, &path_len, &visited_count);

    assert(path != NULL);
    assert(path_len == 4);
    assert(path[0] == 0);
    assert(path[1] == 1);
    assert(path[2] == 2);
    assert(path[3] == 5);
    assert(visited_count >= path_len);

    free(path);
    GraphDestroy(g);
}

static void test_shortest_bfs_same_start_end(void) {
    GraphPtr g = GraphInit(3);
    assert(g != NULL);

    int path_len = 0;
    int visited_count = 0;
    vertex_t *path = GraphShortestBFSStats(g, 1, 1, &path_len, &visited_count);

    assert(path != NULL);
    assert(path_len == 1);
    assert(path[0] == 1);
    assert(visited_count == 1);

    free(path);
    GraphDestroy(g);
}

static void test_shortest_bfs_no_path(void) {
    GraphPtr g = GraphInit(4);
    assert(g != NULL);

    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 2, 3);

    int path_len = 0;
    int visited_count = 0;
    vertex_t *path = GraphShortestBFSStats(g, 0, 3, &path_len, &visited_count);

    assert(path == NULL);
    assert(path_len == 0);
    assert(visited_count == 2);

    GraphDestroy(g);
}

static void test_shortest_bfs_any_picks_nearest_target(void) {
    GraphPtr g = GraphInit(7);
    assert(g != NULL);

    GraphAddEdge(g, 0, 1);
    GraphAddEdge(g, 1, 2);
    GraphAddEdge(g, 2, 3);
    GraphAddEdge(g, 0, 4);
    GraphAddEdge(g, 4, 5);
    GraphAddEdge(g, 5, 6);

    vertex_t targets[] = {3, 2, 6};
    int path_len = 0;
    int visited_count = 0;
    vertex_t *path = GraphShortestBFSAnyStats(g, 0, targets, 3, &path_len, &visited_count);

    assert(path != NULL);
    assert(path_len == 3);
    assert(path[0] == 0);
    assert(path[1] == 1);
    assert(path[2] == 2);
    assert(visited_count >= 3);

    free(path);
    GraphDestroy(g);
}

int main(void) {
    test_shortest_bfs_basic();
    test_shortest_bfs_same_start_end();
    test_shortest_bfs_no_path();
    test_shortest_bfs_any_picks_nearest_target();

    printf("All BFS tests passed.\n");
    return 0;
}
