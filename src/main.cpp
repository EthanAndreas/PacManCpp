#include "board.h"
#include "graphic.h"
#include "pacman.h"
#include <iostream>

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError()
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Window *Window = nullptr;
    SDL_Surface *windowSurf = nullptr;
    SDL_Surface *spriteBoard = nullptr;
    dir currentDir = NONE;
    init(&Window, &windowSurf, &spriteBoard);

    board Board;
    Board.load();
    pacman Pacman;

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

        std::cout << "dir: " << currentDir << std::endl;
        // pacman movement management
        Pacman.updateDir(Board, currentDir);
        Pacman.updatePos();

        // display
        draw(Pacman.getLastDir(), &windowSurf, &spriteBoard, Pacman.getPos());

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
