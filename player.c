#include "player.h"
#include "map.h"

void movePlayer(Player *p, char move) {
    int nx = p->x;
    int ny = p->y;

    if (move == 'w' || move == 'W') nx--;
    if (move == 's' || move == 'S') nx++;
    if (move == 'a' || move == 'A') ny--;
    if (move == 'd' || move == 'D') ny++;

    if (!isWall(nx, ny)) {
        if (map[nx][ny] == '*') {
            p->score++;
            map[nx][ny] = '.';
        }
        p->x = nx;
        p->y = ny;
    }
}
