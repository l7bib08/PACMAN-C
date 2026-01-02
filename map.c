#include <stdio.h>
#include "map.h"

char map[ROWS][COLS] = {
    "+--------+",
    "|********|",
    "|*----***|",
    "|*|..|***|",
    "|*----***|",
    "|********|",
    "+--------+"
};

void drawMap(void) {
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", map[i]);
    }
}

int isInside(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS - 1);
}

int isWall(int x, int y) {
    if (!isInside(x, y)) return 1;

    return map[x][y] == '+' || map[x][y] == '-' || map[x][y] == '|';
}

int countPellets(void) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {
            if (map[i][j] == '*') count++;
        }
    }
    return count;
}
