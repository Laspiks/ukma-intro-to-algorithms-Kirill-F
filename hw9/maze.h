#ifndef MAZE_H
#define MAZE_H

#include<stdbool.h>

#define OBSTACLE '#'
#define PASSAGE '.'
#define PATH '*'
#define SOURCE 'S'
#define DEST 'D'
#define FIRST_PORTAL 'a'

typedef struct {
    int x;
    int y;
} pair_t;

typedef struct Maze Maze;
typedef Maze *MazePtr;

// Initializes the maze with the given size and obstacle density.
// Randomly generates source and destination coordinates.
MazePtr MazeInit(int size, float obstacles);
MazePtr MazeInitAdvanced(int size, float obstacles, int lamp_count, int portal_pairs);

// Returns a 2D array of maze points (either open or closed)
char **MazeGetPoints(MazePtr maze);

// Returns the size of the maze (both width and height)
int MazeGetSize(MazePtr maze);

// Returns the source point of the maze
pair_t MazeGetSource(MazePtr maze);

// Returns the destination point of the maze
pair_t MazeGetDest(MazePtr maze);
const pair_t *MazeGetLamps(MazePtr maze);
int MazeGetLampCount(MazePtr maze);
int MazeGetPortalPairCount(MazePtr maze);
bool MazeGetPortalPair(MazePtr maze, int index, pair_t *first, pair_t *second, char *label);

// Updates the source and destination to new positions given by the arguments.
// Returns false if the source or destination is out of bounds or on an obstacle.
bool MazeUpdateSourceDest(MazePtr m, pair_t source, pair_t dest);

// Prints the current state of the maze
void MazePrint(MazePtr maze);

// Prints the maze with the given path (in red as '*').
// The path is an array of pair_t, representing (x, y) positions.
void MazePrintWithPath(MazePtr maze, pair_t *path, int length);

// Frees the allocated memory for the maze
void MazeDestroy(MazePtr maze);

#endif
