#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "game.h"
#include "map.h"
#include "player.h"
#include "ghost.h"

void clearScreen(void) {
    system("cls");
}

void startGame(void) {
    Player pacman = {1, 1, 0};
    Ghost ghost = {5, 5};

    srand(time(NULL));

    char input = 0;

    while (1) {
        clearScreen();

        
        char pTemp = map[pacman.x][pacman.y];
        char gTemp = map[ghost.x][ghost.y];

        map[pacman.x][pacman.y] = 'P';
        map[ghost.x][ghost.y] = 'G';

        drawMap();
        printf("\nScore: %d\n", pacman.score);
        printf("WASD to move | Q to quit\n");

        map[pacman.x][pacman.y] = pTemp;
        map[ghost.x][ghost.y] = gTemp;

        
        if (_kbhit()) {
            input = _getch();
            if (input == 'q') break;
            movePlayer(&pacman, input);
        }

        moveGhost(&ghost);

        
        if (pacman.x == ghost.x && pacman.y == ghost.y) {
            clearScreen();
            printf("GAME OVER \nFinal Score: %d\n", pacman.score);
            Sleep(2000);
            break;
        }

        Sleep(200); 
    }
}
