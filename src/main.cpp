#include "board.h"
#include "ghost.h"
#include "graphic.h"
#include "pacman.h"
#include <iostream>

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        std::cerr << "SDL init initialization" << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // initialize SDL window
    SDL_Window *Window = nullptr;
    SDL_Surface *windowSurf = nullptr;
    SDL_Surface *spriteBoard = nullptr;
    dir currentDir = NONE;
    init(&Window, &windowSurf, &spriteBoard);

    // initialize board and pacman
    board Board;
    Board.load();
    // transpose the board to match the sprite
    Board.transpose(); // x : col, y : row
    Board.setItem();
    pacman Pacman;
    ghost Ghost;

    // Board.display();

    bool quit = false;
    int nbk;
    const Uint8 *keys;
    while (!quit) {

        Uint64 fps_start = SDL_GetTicks();

        SDL_Event event;
        while (!quit && SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }
        }

        // keyboard management
        keys = SDL_GetKeyboardState(&nbk);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT]) {
            currentDir = LEFT;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            currentDir = RIGHT;
        }
        if (keys[SDL_SCANCODE_UP]) {
            currentDir = UP;
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            currentDir = DOWN;
        }

        // pacman movement management
        Pacman.updateDir(Board.getBoard(), currentDir);
        Pacman.updateSquare(Board.getBoard());
        Pacman.updatePos();

        // ghost movement management
        Ghost.updateDir(Board.getBoard());
        Ghost.updateSquare(Board.getBoard());
        Ghost.updatePos();

        // display updated board
        draw(Pacman.getLastDir(), &windowSurf, &spriteBoard, Pacman.getPos(),
             Ghost.getPos());

        SDL_UpdateWindowSurface(Window);

        Uint64 fps_end = SDL_GetTicks();
        float elapsed = (fps_end - fps_start) /
                        (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // 60 fps
        SDL_Delay(floor(16.666f - elapsed));
    }

    Board.~board();
    Pacman.~pacman();
    SDL_Quit();

    exit(EXIT_SUCCESS);
}
