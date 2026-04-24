#include "maze.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED "\033[1;31m"
#define PURPLE "\033[1;35m"
#define RESET "\033[0m"

typedef struct {
    pair_t first;
    pair_t second;
    char label;
} portal_pair_t;

struct Maze {
    char **grid;
    int size;
    pair_t source;
    pair_t *lamps;
    int lamp_count;
    portal_pair_t *portals;
    int portal_pair_count;
};

static void add_obstacles(MazePtr m, float density) {
    int total_cells = m->size * m->size;
    int reserved = 1 + m->lamp_count + 2 * m->portal_pair_count;
    int obstacles = (int)(total_cells * density);
    if (obstacles > total_cells - reserved) {
        obstacles = total_cells - reserved;
    }
    if (obstacles < 0) {
        obstacles = 0;
    }
    int count = 0;

    while (count < obstacles) {
        int x = rand() % m->size;
        int y = rand() % m->size;
        if (m->grid[x][y] == PASSAGE) {
            m->grid[x][y] = OBSTACLE;
            count++;
        }
    }
}

static pair_t random_free_cell(MazePtr m) {
    pair_t cell = {-1, -1};

    do {
        cell.x = rand() % m->size;
        cell.y = rand() % m->size;
    } while (m->grid[cell.x][cell.y] != PASSAGE);

    return cell;
}

static void add_source(MazePtr m) {
    m->source = random_free_cell(m);
    m->grid[m->source.x][m->source.y] = SOURCE;
}

static void add_lamps(MazePtr m) {
    for (int i = 0; i < m->lamp_count; ++i) {
        m->lamps[i] = random_free_cell(m);
        m->grid[m->lamps[i].x][m->lamps[i].y] = DEST;
    }
}

static void add_portals(MazePtr m) {
    for (int i = 0; i < m->portal_pair_count; ++i) {
        char label = (char)(FIRST_PORTAL + i);
        m->portals[i].label = label;
        m->portals[i].first = random_free_cell(m);
        m->grid[m->portals[i].first.x][m->portals[i].first.y] = label;

        m->portals[i].second = random_free_cell(m);
        m->grid[m->portals[i].second.x][m->portals[i].second.y] = label;
    }
}

static bool is_portal_cell(char cell) {
    return cell >= FIRST_PORTAL && cell <= 'z';
}

MazePtr MazeInit(int size, float obstacles_density) {
    return MazeInitAdvanced(size, obstacles_density, 1, 0);
}

MazePtr MazeInitAdvanced(int size, float obstacles_density, int lamp_count, int portal_pairs) {
    srand(time(NULL));
    if (size <= 0) {
        return NULL;
    }

    int total_cells = size * size;
    int normalized_lamps = lamp_count > 0 ? lamp_count : 1;
    int normalized_portals = portal_pairs > 0 ? portal_pairs : 0;
    int max_portal_labels = 'z' - FIRST_PORTAL + 1;
    if (normalized_portals > max_portal_labels) {
        normalized_portals = max_portal_labels;
    }

    while (1 + normalized_lamps + 2 * normalized_portals > total_cells && normalized_portals > 0) {
        normalized_portals--;
    }
    while (1 + normalized_lamps > total_cells && normalized_lamps > 1) {
        normalized_lamps--;
    }
    if (1 + normalized_lamps > total_cells) {
        return NULL;
    }

    MazePtr m = malloc(sizeof(struct Maze));
    if (m == NULL) {
        return NULL;
    }

    m->size = size;
    m->lamp_count = normalized_lamps;
    m->portal_pair_count = normalized_portals;
    m->lamps = malloc((size_t)m->lamp_count * sizeof(pair_t));
    m->portals = malloc((size_t)(m->portal_pair_count > 0 ? m->portal_pair_count : 1) *
                        sizeof(portal_pair_t));

    if (m->lamps == NULL || m->portals == NULL) {
        free(m->lamps);
        free(m->portals);
        free(m);
        return NULL;
    }

    m->grid = malloc(size * sizeof(char *));
    if (m->grid == NULL) {
        free(m->lamps);
        free(m->portals);
        free(m);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        m->grid[i] = malloc(size);
        if (m->grid[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(m->grid[j]);
            }
            free(m->grid);
            free(m->lamps);
            free(m->portals);
            free(m);
            return NULL;
        }
        for (int j = 0; j < size; j++) {
            m->grid[i][j] = PASSAGE;
        }
    }

    add_obstacles(m, obstacles_density);
    add_source(m);
    add_lamps(m);
    add_portals(m);
    return m;
}

char **MazeGetPoints(MazePtr m) { return m->grid; }

int MazeGetSize(MazePtr m) { return m->size; }

pair_t MazeGetSource(MazePtr maze) { return maze->source; }

pair_t MazeGetDest(MazePtr maze) { return maze->lamps[0]; }

const pair_t *MazeGetLamps(MazePtr maze) { return maze->lamps; }

int MazeGetLampCount(MazePtr maze) { return maze->lamp_count; }

int MazeGetPortalPairCount(MazePtr maze) { return maze->portal_pair_count; }

bool MazeGetPortalPair(MazePtr maze, int index, pair_t *first, pair_t *second, char *label) {
    if (maze == NULL || index < 0 || index >= maze->portal_pair_count) {
        return false;
    }

    if (first != NULL) {
        *first = maze->portals[index].first;
    }
    if (second != NULL) {
        *second = maze->portals[index].second;
    }
    if (label != NULL) {
        *label = maze->portals[index].label;
    }

    return true;
}


bool MazeUpdateSourceDest(MazePtr m, pair_t source, pair_t dest) {
    // Check if source and destination are within bounds and not on obstacles
    if (source.x < 0 || source.x >= m->size || source.y < 0 || source.y >= m->size ||
        m->grid[source.x][source.y] == OBSTACLE)
        return false;
    if (dest.x < 0 || dest.x >= m->size || dest.y < 0 || dest.y >= m->size ||
        m->grid[dest.x][dest.y] == OBSTACLE)
        return false;

    // Clear the old source and the first lamp.
    m->grid[m->source.x][m->source.y] = PASSAGE;
    m->grid[m->lamps[0].x][m->lamps[0].y] = PASSAGE;

    // Only first lamp is updated here, others stay as they were.
    m->source = source;
    m->lamps[0] = dest;

    // Put new markers back.
    m->grid[m->source.x][m->source.y] = SOURCE;
    m->grid[m->lamps[0].x][m->lamps[0].y] = DEST;

    return true;
}

void MazePrint(MazePtr m) {
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            if (i == m->source.x && j == m->source.y)
                printf(RED "%c" RESET, SOURCE);
            else if (is_portal_cell(m->grid[i][j]))
                printf(PURPLE "%c" RESET, m->grid[i][j]);
            else
                putchar(m->grid[i][j]);
        }
        putchar('\n');
    }
}

void MazePrintWithPath(MazePtr m, pair_t *path, int length) {
    // Allocate a 2D boolean array to mark the path
    char **is_path = malloc(m->size * sizeof(char *));
    for (int i = 0; i < m->size; i++) {
        is_path[i] = calloc(m->size, sizeof(char));
    }

    // Mark all path points
    for (int i = 0; i < length; i++) {
        int x = path[i].x;
        int y = path[i].y;
        if (x >= 0 && x < m->size && y >= 0 && y < m->size) {
            is_path[x][y] = 1;
        }
    }

    // Print maze with path
    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            char cell = m->grid[i][j];

            if (i == m->source.x && j == m->source.y) {
                printf(RED "%c" RESET, SOURCE);
            } else if (is_path[i][j]) {
                if (cell == PASSAGE) {
                    printf(RED "%c" RESET, PATH);
                } else if (is_portal_cell(cell)) {
                    printf(PURPLE "%c" RESET, cell);
                } else {
                    printf(RED "%c" RESET, cell);
                }
            } else if (cell == DEST) {
                    printf(RED "%c" RESET, DEST);
            } else if (is_portal_cell(cell)) {
                printf(PURPLE "%c" RESET, cell);
            } else {
                printf("%c", cell);
            }
        }
        printf("\n");
    }

    // Free the temp path matrix
    for (int i = 0; i < m->size; i++) {
        free(is_path[i]);
    }
    free(is_path);
}

void MazeDestroy(MazePtr m) {
    if (m == NULL) {
        return;
    }

    for (int i = 0; i < m->size; i++) {
        free(m->grid[i]);
    }
    free(m->grid);
    free(m->lamps);
    free(m->portals);
    free(m);
}
