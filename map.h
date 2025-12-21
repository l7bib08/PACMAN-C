#ifndef MAP_H
#define MAP_H

#define ROWS 7
#define COLS 11

extern char map[ROWS][COLS];

void drawMap(void);
int isWall(int x, int y);

#endif
