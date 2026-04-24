#include "maze.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pair_t *cells;
    int length;
    int visited;
} MazePathResult;

static int cell_to_vertex(int size, int x, int y) {
    return x * size + y;
}

static pair_t vertex_to_cell(int size, int vertex) {
    pair_t cell = {vertex / size, vertex % size};
    return cell;
}

static int is_open_cell(char cell) {
    return cell != OBSTACLE;
}

static GraphPtr MazeToGraph(MazePtr maze) {
    int size = MazeGetSize(maze);
    char **grid = MazeGetPoints(maze);
    GraphPtr graph = GraphInit(size * size);
    if (graph == NULL) {
        return NULL;
    }

    const int dx[2] = {1, 0};
    const int dy[2] = {0, 1};

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            if (!is_open_cell(grid[x][y])) {
                continue;
            }

            int from = cell_to_vertex(size, x, y);
            for (int dir = 0; dir < 2; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx >= size || ny < 0 || ny >= size) {
                    continue;
                }
                if (!is_open_cell(grid[nx][ny])) {
                    continue;
                }

                GraphAddEdge(graph, from, cell_to_vertex(size, nx, ny));
            }
        }
    }

    for (int i = 0; i < MazeGetPortalPairCount(maze); ++i) {
        pair_t first = {0, 0};
        pair_t second = {0, 0};
        MazeGetPortalPair(maze, i, &first, &second, NULL);
        GraphAddEdge(graph, cell_to_vertex(size, first.x, first.y),
                     cell_to_vertex(size, second.x, second.y));
    }

    return graph;
}

static pair_t *vertices_to_cells(int size, const vertex_t *vertices, int length) {
    if (vertices == NULL || length <= 0) {
        return NULL;
    }

    pair_t *cells = malloc((size_t)length * sizeof(pair_t));
    if (cells == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        cells[i] = vertex_to_cell(size, vertices[i]);
    }

    return cells;
}

static vertex_t *lamps_to_vertices(MazePtr maze) {
    int size = MazeGetSize(maze);
    const pair_t *lamps = MazeGetLamps(maze);
    int lamp_count = MazeGetLampCount(maze);
    vertex_t *targets = malloc((size_t)lamp_count * sizeof(vertex_t));
    if (targets == NULL) {
        return NULL;
    }

    for (int i = 0; i < lamp_count; ++i) {
        targets[i] = cell_to_vertex(size, lamps[i].x, lamps[i].y);
    }

    return targets;
}

static MazePathResult find_path_bfs(MazePtr maze, GraphPtr graph) {
    int size = MazeGetSize(maze);
    pair_t source = MazeGetSource(maze);
    int lamp_count = MazeGetLampCount(maze);
    vertex_t *targets = lamps_to_vertices(maze);

    int path_len = 0;
    int visited = 0;
    vertex_t *vertices = GraphShortestBFSAnyStats(graph, cell_to_vertex(size, source.x, source.y),
                                                  targets, lamp_count, &path_len, &visited);

    MazePathResult result = {vertices_to_cells(size, vertices, path_len), path_len, visited};
    free(targets);
    free(vertices);
    return result;
}

static MazePathResult find_path_dfs(MazePtr maze, GraphPtr graph) {
    int size = MazeGetSize(maze);
    pair_t source = MazeGetSource(maze);
    int lamp_count = MazeGetLampCount(maze);
    vertex_t *targets = lamps_to_vertices(maze);

    int path_len = 0;
    int visited = 0;
    vertex_t *vertices = GraphShortestDFSAnyStats(graph, cell_to_vertex(size, source.x, source.y),
                                                  targets, lamp_count, &path_len, &visited);

    MazePathResult result = {vertices_to_cells(size, vertices, path_len), path_len, visited};
    free(targets);
    free(vertices);
    return result;
}

static void print_maze_result(const char *title, MazePtr maze, MazePathResult result) {
    printf("%s\n", title);
    printf("Visited nodes: %d\n", result.visited);

    if (result.cells == NULL) {
        printf("Path does not exist.\n\n");
        return;
    }

    printf("Path length: %d\n", result.length);
    MazePrintWithPath(maze, result.cells, result.length);
    printf("\n");
}

int main(int argc, char *argv[]) {
    int maze_size = 20;
    float obstacle_density = 0.3f;
    int lamp_count = 3;
    int portal_pairs = 2;

    if (argc > 1) {
        maze_size = atoi(argv[1]);
    }
    if (argc > 2) {
        lamp_count = atoi(argv[2]);
    }
    if (argc > 3) {
        portal_pairs = atoi(argv[3]);
    }

    MazePtr maze = MazeInitAdvanced(maze_size, obstacle_density, lamp_count, portal_pairs);
    if (maze == NULL) {
        fprintf(stderr, "Cannot create maze\n");
        return 1;
    }

    GraphPtr graph = MazeToGraph(maze);
    if (graph == NULL) {
        fprintf(stderr, "Cannot convert maze to graph\n");
        MazeDestroy(maze);
        return 1;
    }

    printf("Maze size: %d\n", MazeGetSize(maze));
    printf("Lamps: %d\n", MazeGetLampCount(maze));
    printf("Portal pairs: %d\n\n", MazeGetPortalPairCount(maze));

    printf("Original maze:\n");
    MazePrint(maze);
    printf("\n");

    MazePathResult dfs_result = find_path_dfs(maze, graph);
    MazePathResult bfs_result = find_path_bfs(maze, graph);

    print_maze_result("DFS result:", maze, dfs_result);
    print_maze_result("BFS result:", maze, bfs_result);

    free(dfs_result.cells);
    free(bfs_result.cells);
    GraphDestroy(graph);
    MazeDestroy(maze);
    return 0;
}
