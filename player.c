#include "player.h"
#include "map.h"

void movePlayer(Player *p, char move) {
    int nx = p->x;
    int ny = p->y;

    if (move == 'w') nx--;
    if (move == 's') nx++;
    if (move == 'a') ny--;
    if (move == 'd') ny++;

    if (!isWall(nx, ny)) {
        if (map[nx][ny] == '*') {
            p->score++;
            map[nx][ny] = '.';
        }
        p->x = nx;
        p->y = ny;
    }
}
