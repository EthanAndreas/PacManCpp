#include "graphic.h"
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
    dir last_dir = NONE;
    init(&Window, &windowSurf, &spriteBoard);

    bool quit = false;
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
        int nbk;
        const Uint8 *keys = SDL_GetKeyboardState(&nbk);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;
        if (keys[SDL_SCANCODE_LEFT]) {
            last_dir = LEFT;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            last_dir = RIGHT;
        }
        if (keys[SDL_SCANCODE_UP]) {
            last_dir = UP;
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            last_dir = DOWN;
        }

        // display
        draw(&last_dir, &windowSurf, &spriteBoard);
        SDL_UpdateWindowSurface(Window);

        Uint64 fps_end = SDL_GetTicks();
        float elapsed = (fps_end - fps_start) /
                        (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // 60 fps
        SDL_Delay(floor(16.666f - elapsed));
    }

    SDL_Quit();
    exit(EXIT_SUCCESS);
}
