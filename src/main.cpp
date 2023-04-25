#include "board.h"
#include "ghost.h"
#include "graphic.h"
#include "pacman.h"

int main() {

    // initialize SDL
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

    bool restart = true;
    while (restart) {
        // initialize board, pacman, ghost and item
        board Board;
        Board.load();
        Board.transpose();
        Board.setItem();
        pacman Pacman;
        std::vector<ghost *> vecGhost;
        for (int i = 0; i < 4; i++) {
            ghost *Ghost = new ghost();
            Ghost->setGhost(color(i));
            vecGhost.push_back(Ghost);
        }
        std::vector<Coordinate> vecDot = Board.getDotList();
        std::vector<Coordinate> vecPowerup = Board.getPowerupList();

        // display initial board
        draw(&windowSurf, &spriteBoard, Pacman, vecGhost, vecDot, vecPowerup,
             0);
        SDL_UpdateWindowSurface(Window);

        bool start = false, quit = false;
        int nbk;
        const Uint8 *keys;
        SDL_Event event;
        while (!quit) {

            // fps management
            Uint64 fps_start = SDL_GetTicks();

            // event management
            if (!quit && SDL_PollEvent(&event)) {
                switch (event.type) {
                // leave the game
                case SDL_QUIT:
                    quit = true;
                    restart = false;
                    // vecDot.clear();
                    // vecPowerup.clear();
                    // for (auto Ghost : vecGhost)
                    //     Ghost->~ghost();
                    // vecGhost.clear();
                    // Pacman.~pacman();
                    // Board.~board();
                    break;
                default:
                    break;
                }
            }

            // keyboard management
            keys = SDL_GetKeyboardState(&nbk);
            if (keys[SDL_SCANCODE_ESCAPE])
                quit = true;
            else if (keys[SDL_SCANCODE_LEFT]) {
                start = true;
                currentDir = LEFT;
            } else if (keys[SDL_SCANCODE_RIGHT]) {
                start = true;
                currentDir = RIGHT;
            } else if (keys[SDL_SCANCODE_UP]) {
                start = true;
                currentDir = UP;
            } else if (keys[SDL_SCANCODE_DOWN]) {
                start = true;
                currentDir = DOWN;
            }

            // press any key to start the game
            if (start) {
                // pacman movement management
                Pacman.updateDir(Board.getBoard(), currentDir);
                Pacman.updatePos();
                Pacman.updateSquare(Board.getBoard());

                // ghost movement management
                for (auto Ghost : vecGhost) {

                    if (!Ghost->isGhostInHouse()) {
                        Ghost->updatePos();
                        Ghost->updateDir(Board.getBoard());
                    } else {
                        Ghost->leaveGhostHouse();
                        Ghost->updatePos();
                    }
                }

                // update item on the board
                vecDot = Board.getDotList();
                vecPowerup = Board.getPowerupList();

                // win statement
                if (vecDot.size() == 0 && vecPowerup.size() == 0) {
                    std::cout << "You win!" << std::endl;
                    // next level
                    quit = true;
                    break;
                }

                // loose statement
                if (Pacman.ghostCollision(vecGhost)) {
                    std::cout << "You loose!" << std::endl;
                    // restart level
                    quit = true;
                    break;
                }

                // display updated board
                draw(&windowSurf, &spriteBoard, Pacman, vecGhost, vecDot,
                     vecPowerup, Pacman.getScore());
                SDL_UpdateWindowSurface(Window);
            }

            Uint64 fps_end = SDL_GetTicks();
            float elapsed = (fps_end - fps_start) /
                            (float)SDL_GetPerformanceFrequency() * 1000.0f;

            // 120 fps
            SDL_Delay(floor(8.888f - elapsed));
        }
    }

    SDL_Quit();
    exit(EXIT_SUCCESS);
}
