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

int isWall(int x, int y) {
    return map[x][y] == '+' || map[x][y] == '-' || map[x][y] == '|';
}
