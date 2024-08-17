#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 20
#define COLS 40

void initialize(int grid[ROWS][COLS]) {
    int glider[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i + 1][j + 1] = glider[i][j];
        }
    }
}

void printGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf(grid[i][j] ? "O" : " ");
        }
        printf("\n");
    }
}

int countNeighbors(int grid[ROWS][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS) {
                count += grid[newX][newY];
            }
        }
    }
    return count;
}

void updateGrid(int grid[ROWS][COLS], int newGrid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j]) {
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                newGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
}

int main() {
    int grid[ROWS][COLS];
    int newGrid[ROWS][COLS];

    initialize(grid);

    while (1) {
        printGrid(grid);
        updateGrid(grid, newGrid);

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                grid[i][j] = newGrid[i][j];
            }
        }

        usleep(200000); 
        printf("\033[H\033[J"); 
    }

    return 0;
}
