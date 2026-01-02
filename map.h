#ifndef MAP_H
#define MAP_H

#define ROWS 7
#define COLS 11

extern char map[ROWS][COLS];

void drawMap(void); 
int isInside(int x, int y);
int isWall(int x, int y);

int countPellets(void);

void loadLevel(int level);
int getMaxLevels(void);

#endif
