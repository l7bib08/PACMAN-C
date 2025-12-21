#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x;
    int y;
    int score;
} Player;

void movePlayer(Player *p, char move);

#endif
