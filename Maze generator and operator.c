#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 11
#define COLS 11

char maze[ROWS][COLS];

/* Directions: Up, Right, Down, Left */
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

/* Initialize maze with walls */
void initMaze() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            maze[i][j] = '#';
}

/* Generate maze using DFS */
void generateMaze(int x, int y) {
    maze[y][x] = ' ';

    int dir[4] = {0, 1, 2, 3};

    /* Shuffle directions */
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = dir[i];
        dir[i] = dir[r];
        dir[r] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dir[i]] * 2;
        int ny = y + dy[dir[i]] * 2;

        if (nx > 0 && nx < COLS - 1 &&
            ny > 0 && ny < ROWS - 1 &&
            maze[ny][nx] == '#') {

            maze[y + dy[dir[i]]][x + dx[dir[i]]] = ' ';
            generateMaze(nx, ny);
        }
    }
}

/* Solve maze using backtracking */
int solveMaze(int x, int y) {

    /* Boundary check */
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS)
        return 0;

    /* Reached end */
    if (x == COLS - 2 && y == ROWS - 2) {
        maze[y][x] = '.';
        return 1;
    }

    /* Move only through empty spaces */
    if (maze[y][x] == ' ') {
        maze[y][x] = '.';   // Mark path

        if (solveMaze(x + 1, y) ||
            solveMaze(x - 1, y) ||
            solveMaze(x, y + 1) ||
            solveMaze(x, y - 1))
            return 1;

        maze[y][x] = ' ';   // Backtrack
    }

    return 0;
}

/* Print maze */
void printMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%c ", maze[i][j]);
        printf("\n");
    }
}

int main() {

    srand(time(NULL));

    initMaze();
    generateMaze(1, 1);

    printf("Generated Maze:\n");
    printMaze();

    solveMaze(1, 1);

    /* Mark start and end AFTER solving */
    maze[1][1] = 'S';
    maze[ROWS - 2][COLS - 2] = 'E';

    printf("\nSolved Maze:\n");
    printMaze();

    return 0;
}
