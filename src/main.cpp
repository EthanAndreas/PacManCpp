#include "board.h"
#include "ghost.h"
#include "graphic.h"
#include "pacman.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {

        std::cerr << "SDL initialization" << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // initialize SDL window
    SDL_Window *Window = nullptr;
    SDL_Surface *windowSurf = nullptr;
    SDL_Surface *spriteBoard = nullptr;
    dir currentDir = NONE;
    init(&Window, &windowSurf, &spriteBoard);

    // initialize board, pacman, ghost and edible
    board Board;
    Board.load();
    Board.transpose();
    Board.setItem();
    pacman Pacman;
    ghost Ghost;
    std::vector<Coordinate> vecDot = Board.getDotList();
    std::vector<Coordinate> vecPowerup = Board.getPowerupList();

    bool quit = false;
    int nbk;
    const Uint8 *keys;
    SDL_Event event;
    while (!quit) {

        // fps management
        Uint64 fps_start = SDL_GetTicks();

        // event management
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
        Pacman.updatePos();
        Pacman.updateSquare(Board.getBoard());

        // ghost movement management
        Ghost.updateDir(Board.getBoard());
        Ghost.updatePos();
        Ghost.updateSquare(Board.getBoard());

        // update item on the board
        vecDot = Board.getDotList();
        vecPowerup = Board.getPowerupList();

        // display updated board
        draw(Pacman.getLastDir(), Ghost.getLastDir(), &windowSurf, &spriteBoard,
             Pacman.getPos(), Ghost.getPos(), vecDot, vecPowerup,
             Pacman.getScore());

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
