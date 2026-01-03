#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL3/SDL.h>

#include "game.h"
#include "map.h"
#include "player.h"
#include "ghost.h"

#define WINDOW_W 800
#define WINDOW_H 600

static int tileSize(void) {
    int tw = WINDOW_W / (COLS - 1);
    int th = WINDOW_H / ROWS;
    return (tw < th) ? tw : th;
}

static void drawFilledRect(SDL_Renderer *r, int x, int y, int w, int h) {
    SDL_FRect rect;
    rect.x = (float)x;
    rect.y = (float)y;
    rect.w = (float)w;
    rect.h = (float)h;
    SDL_RenderFillRect(r, &rect);
}

static void renderGame(SDL_Renderer *r, const Player *p, const Ghost *g, int level) {
    int t = tileSize();
    int offsetX = (WINDOW_W - (COLS - 1) * t) / 2;
    int offsetY = (WINDOW_H - ROWS * t) / 2;

    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {
            int px = offsetX + j * t;
            int py = offsetY + i * t;

            char c = map[i][j];

            if (c == '+' || c == '-' || c == '|') {
                SDL_SetRenderDrawColor(r, 0, 0, 255, 255);  
                drawFilledRect(r, px, py, t, t);
            } else {
                
                if (c == '*') {
                    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
                    int s = t / 5;
                    if (s < 2) s = 2;
                    drawFilledRect(r, px + (t - s) / 2, py + (t - s) / 2, s, s);
                }
            }
        }
    }

    
    SDL_SetRenderDrawColor(r, 255, 255, 0, 255);
    drawFilledRect(r,
        offsetX + p->y * t + 2,
        offsetY + p->x * t + 2,
        t - 4,
        t - 4
    );

    
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    drawFilledRect(r,
        offsetX + g->y * t + 2,
        offsetY + g->x * t + 2,
        t - 4,
        t - 4
    );

    SDL_RenderPresent(r);
    (void)level;
}

static char arrowToMove(SDL_Keycode key) {
    if (key == SDLK_UP) return 'w';
    if (key == SDLK_DOWN) return 's';
    if (key == SDLK_LEFT) return 'a';
    if (key == SDLK_RIGHT) return 'd';
    return 0;
}

void startGame(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return;
    }


    SDL_Window *win = SDL_CreateWindow("PACMAN SDL3", WINDOW_W, WINDOW_H, 0);
    if (!win) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    
    SDL_Renderer *ren = SDL_CreateRenderer(win, NULL);
    if (!ren) {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    srand((unsigned)time(NULL));

    Player pacman = {1, 1, 0};
    Ghost ghost = {5, 5};

    int level = 1;
    int maxLevels = getMaxLevels();
    loadLevel(level);

    int running = 1;
    Uint64 lastGhostMove = SDL_GetTicks();

    while (running) {
        SDL_Event e;

        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = 0;
            } else if (e.type == SDL_EVENT_KEY_DOWN) {
                SDL_Keycode key = e.key.key;

                if (key == SDLK_ESCAPE) running = 0;

                char mv = arrowToMove(key);
                if (mv) movePlayer(&pacman, mv);
            }
          

        
        int ghostDelay = 220 - level * 30;
        if (ghostDelay < 80) ghostDelay = 80;

        Uint64 now = SDL_GetTicks();
        if (now - lastGhostMove >= (Uint64)ghostDelay) {
            moveGhost(&ghost);
            lastGhostMove = now;
        }

        
        if (pacman.x == ghost.x && pacman.y == ghost.y) {
            running = 0;
        }

        
        if (running && countPellets() == 0) {
            level++;
            if (level > maxLevels) {
                running = 0;
            } else {
                loadLevel(level);
                pacman.x = 1; pacman.y = 1;
                ghost.x = 5;  ghost.y = 5;
            }
        }

        
        char title[128];
        snprintf(title, sizeof(title),
                 "PACMAN SDL3 | Level %d/%d | Score %d | ESC to quit",
                 level, maxLevels, pacman.score);
        SDL_SetWindowTitle(win, title);

        
        renderGame(ren, &pacman, &ghost, level);

        SDL_Delay(16);
    }

    printf("Game ended. Final Score: %d | Level reached: %d\n", pacman.score, level);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    }
}