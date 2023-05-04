#include "board.h"
#include "fruit.h"
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

    pacman Pacman;
    board Board;
    Board.load();
    Board.transpose();
    Board.setItem();

    bool restart = true;
    while (restart) {
        // initialize board, pacman, ghost and item
        int count = 0;
        Pacman.resetPos();
        std::vector<std::shared_ptr<ghost>> vecGhost;
        for (int i = 0; i < 4; i++) {
            std::shared_ptr<ghost> Ghost = std::make_shared<ghost>();
            Ghost->setGhost(color(i));
            vecGhost.push_back(Ghost);
        }
        std::vector<Coordinate> vecDot = Board.getDotList();
        std::vector<Coordinate> vecPowerup = Board.getPowerupList();
        fruit Fruit;

        // display initial board
        count = draw(&windowSurf, &spriteBoard, count, Pacman, vecGhost, vecDot,
                     vecPowerup, _NONE, 0, -1, false);
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
                if (start == false) {
                    for (auto Ghost : vecGhost)
                        Ghost->setTimer();
                }
                start = true;
                currentDir = LEFT;
            } else if (keys[SDL_SCANCODE_RIGHT]) {
                if (start == false) {
                    for (auto Ghost : vecGhost)
                        Ghost->setTimer();
                }
                start = true;
                currentDir = RIGHT;
            } else if (keys[SDL_SCANCODE_UP]) {
                if (start == false) {
                    for (auto Ghost : vecGhost)
                        Ghost->setTimer();
                }
                start = true;
                currentDir = UP;
            } else if (keys[SDL_SCANCODE_DOWN]) {
                if (start == false) {
                    for (auto Ghost : vecGhost)
                        Ghost->setTimer();
                }
                start = true;
                currentDir = DOWN;
            }

            // press any key to start the game
            if (start) {
                // pacman movement management
                if (Pacman.waitSquareCenter() == true)
                    Pacman.updateDir(Board.getBoard(), currentDir);
                Pacman.updatePos();
                Pacman.updateSquare(Board.getBoard(), vecGhost, &Fruit);
                // pacman eat fruit management
                if (Fruit.updateFruit(Board.getBoard(),
                                      Pacman.getDotCounter()) == EXCEED) {
                    Pacman.resetDotCounter();
                }

                // ghost movement management
                for (auto Ghost : vecGhost) {

                    if (Ghost->waitSquareCenter() == true)
                        Ghost->updateDir(Board.getBoard(), Pacman.getPos(),
                                         Pacman.getLastDir());
                    Ghost->updatePos();
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
                    // death animation
                    for (int i = 0; i < 10; i++) {
                        count =
                            draw(&windowSurf, &spriteBoard, count, Pacman,
                                 vecGhost, vecDot, vecPowerup, Fruit.getFruit(),
                                 Pacman.getScore(), i, start);
                        SDL_UpdateWindowSurface(Window);
                        Uint64 fps_end = SDL_GetTicks();
                        float elapsed = (fps_end - fps_start) /
                                        (float)SDL_GetPerformanceFrequency() *
                                        1000.0f;

                        // Slown the animation
                        SDL_Delay(int(66.668f - elapsed));
                    }
                    // loose a life
                    Pacman.looseLife();

                    std::cout << "Remaining " << Pacman.getRemainingLife()
                              << " life(s)" << std::endl;

                    // quit the game if no more life
                    if (Pacman.getRemainingLife() == 0) {
                        std::cout << "You loose with a score of : "
                                  << Pacman.getScore() << std::endl;
                        restart = false;
                        break;
                    }

                    // restart level
                    quit = true;
                    break;
                }

                // display updated board
                count = draw(&windowSurf, &spriteBoard, count, Pacman, vecGhost,
                             vecDot, vecPowerup, Fruit.getFruit(),
                             Pacman.getScore(), -1, start);
                SDL_UpdateWindowSurface(Window);
            }

            Uint64 fps_end = SDL_GetTicks();
            float elapsed = (fps_end - fps_start) /
                            (float)SDL_GetPerformanceFrequency() * 1000.0f;

            // fps
            SDL_Delay(floor(10.000f - elapsed));
        }
    }

    SDL_Quit();
    exit(EXIT_SUCCESS);
}
