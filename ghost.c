#include <stdlib.h>
#include "ghost.h"
#include "map.h"

void moveGhost(Ghost *g) {
    int dir = rand() % 4;
    int nx = g->x;
    int ny = g->y;

    if (dir == 0) nx--;
    if (dir == 1) nx++;
    if (dir == 2) ny--;
    if (dir == 3) ny++;

    if (!isWall(nx, ny)) {
        g->x = nx;
        g->y = ny;
    }
}
