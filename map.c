#include <stdio.h>
#include <string.h>
#include "map.h"

char map[ROWS][COLS];

static const char level1[ROWS][COLS] = {
    "+--------+",
    "|********|",
    "|*----***|",
    "|*|..|***|",
    "|*----***|",
    "|********|",
    "+--------+"
};

static const char level2[ROWS][COLS] = {
    "+--------+",
    "|***--***|",
    "|*------*|",
    "|***..***|",
    "|*------*|",
    "|***--***|",
    "+--------+"
};

static const char level3[ROWS][COLS] = {
    "+--------+",
    "|********|",
    "|*--**--*|",
    "|*|..|***|",
    "|*--**--*|",
    "|********|",
    "+--------+"
};

static const char level4[ROWS][COLS] = {
    "+--------+",
    "|**----**|",
    "|**-**-**|",
    "|**..****|",
    "|**-**-**|",
    "|**----**|",
    "+--------+"
};

int getMaxLevels(void) { return 4; }

void loadLevel(int level) {
    const char (*src)[COLS] = level1;
    if (level == 2) src = level2;
    else if (level == 3) src = level3;
    else if (level == 4) src = level4;

    for (int i = 0; i < ROWS; i++) {
        strcpy(map[i], src[i]);
    }
}

void drawMap(void) {
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", map[i]);
    }
}

int isInside(int x, int y) {
    return (x >= 0 && x < COLS - 1 && y >= 0 && y < ROWS);
}

int isWall(int x, int y) {
    if (!isInside(x, y)) return 1;
    char c = map[y][x];
    return (c == '+' || c == '-' || c == '|');
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
