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

    // Keyboard
    SDL_Event event;

    // initialize game
    pacman Pacman;
    board Board;
    Board.load();
    Board.transpose();
    Board.setItem();

    // Game
    bool game = true;
    bool next_level = true;
    bool menu = true;
    while (game) {

        // Intro
        while (menu) {
            // display intro
            intro(&windowSurf, &spriteBoard);
            SDL_UpdateWindowSurface(Window);

            // keyboard management
            SDL_PollEvent(&event);
            // return touch
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_RETURN)
                menu = false;
            // esc touch
            else if (event.type == SDL_KEYDOWN &&
                     event.key.keysym.sym == SDLK_ESCAPE) {
                game = false;
                menu = false;
                SDL_Quit();
                return EXIT_SUCCESS;
            }
            // close window
            else if (event.type == SDL_QUIT) {
                game = false;
                menu = false;
                SDL_Quit();
                return EXIT_SUCCESS;
            }
        }

        // Level
        int curLevel = 1;
        bool level = true;
        while (level) {

            // initialize next level
            if (next_level == true) {
                // reload all the items
                Board.setItem();
                next_level = false;
            }

            // initialize pacman and ghost
            Pacman.init();
            std::vector<std::shared_ptr<ghost>> vecGhost;
            for (int i = 0; i < 4; i++) {
                std::shared_ptr<ghost> Ghost = std::make_shared<ghost>();
                Ghost->setGhost(color(i));
                vecGhost.push_back(Ghost);
            }

            // retrieve item list
            std::vector<Coordinate> vecDot = Board.getDotList();
            std::vector<Coordinate> vecPowerup = Board.getPowerupList();
            fruit Fruit;

            // display initial board
            int count = 0;
            count = draw(&windowSurf, &spriteBoard, count, Pacman, vecGhost,
                         vecDot, vecPowerup, _NONE, Pacman.getScore(),
                         PACMAN_LIVE, false, curLevel);
            SDL_UpdateWindowSurface(Window);

            bool life = true, start = false;
            // Life
            while (life) {

                // fps management
                Uint64 fps_start = SDL_GetTicks();

                // event management
                if (life && SDL_PollEvent(&event)) {
                    switch (event.type) {
                    // leave the game
                    case SDL_QUIT:
                        // free memory
                        // vecDot.clear();
                        // vecPowerup.clear();
                        // for (auto Ghost : vecGhost)
                        //     Ghost->~ghost();
                        // vecGhost.clear();
                        // Pacman.~pacman();
                        // Board.~board();
                        // leave the game
                        life = false;
                        level = false;
                        game = false;
                        SDL_Quit();
                        exit(EXIT_SUCCESS);
                        break;
                    default:
                        break;
                    }
                }

                // keyboard management
                // esc touch
                if (event.type == SDL_KEYDOWN &&
                    event.key.keysym.sym == SDLK_ESCAPE) {
                    life = false;
                    level = false;
                    game = false;
                    SDL_Quit();
                    exit(EXIT_SUCCESS);
                }
                // left arrow touch
                else if (event.type == SDL_KEYDOWN &&
                         event.key.keysym.sym == SDLK_LEFT) {
                    start = true;
                    currentDir = LEFT;
                }
                // right arrow touch
                else if (event.type == SDL_KEYDOWN &&
                         event.key.keysym.sym == SDLK_RIGHT) {
                    start = true;
                    currentDir = RIGHT;
                }
                // up arrow touch
                else if (event.type == SDL_KEYDOWN &&
                         event.key.keysym.sym == SDLK_UP) {
                    start = true;
                    currentDir = UP;
                }
                // down arrow touch
                else if (event.type == SDL_KEYDOWN &&
                         event.key.keysym.sym == SDLK_DOWN) {
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
                                          Pacman.getDotCounter(),
                                          Pacman.getFruitEaten()) == EXCEED) {
                        Pacman.resetDotCounter();
                    }

                    // ghost movement management
                    for (auto Ghost : vecGhost) {

                        if (Ghost->waitSquareCenter() == true)
                            Ghost->updateDir(
                                Board.getBoard(),
                                Pacman.getPos().first / SCALE_PIXEL,
                                Pacman.getPos().second / SCALE_PIXEL,
                                Pacman.getLastDir(), curLevel,
                                Pacman.getDotCounterLevel(),
                                Pacman.getRemainingLife());
                        Ghost->updatePos();
                    }

                    // update item on the board
                    vecDot = Board.getDotList();
                    vecPowerup = Board.getPowerupList();

                    // win statement
                    if (vecDot.size() == 0 && vecPowerup.size() == 0) {
                        // TODO: add a win animation
                        std::cout << "You win!" << std::endl;
                        // next level
                        curLevel++;
                        next_level = true;
                        life = false;
                        level = false;
                        break;
                    }

                    // loose statement
                    if (Pacman.ghostCollision(vecGhost)) {

                        // death animation
                        int i;
                        for (i = 0; i < 10; i++) {
                            count = draw(&windowSurf, &spriteBoard, count,
                                         Pacman, vecGhost, vecDot, vecPowerup,
                                         Fruit.getFruit(), Pacman.getScore(),
                                         PACMAN_DEATH * i, start, curLevel);
                            SDL_UpdateWindowSurface(Window);
                            Uint64 fps_end = SDL_GetTicks();
                            float elapsed =
                                (fps_end - fps_start) /
                                (float)SDL_GetPerformanceFrequency() * 1000.0f;

                            // slow the animation
                            SDL_Delay(int(66.668f - elapsed));
                        }

                        // loose a life
                        Pacman.looseLife();

                        // TODO: add an animation to write this sentence in the
                        // middle of the screen
                        std::cout << "Remaining " << Pacman.getRemainingLife()
                                  << " level(s)" << std::endl;

                        // no more life, reset level and score
                        if (Pacman.getRemainingLife() == 0) {
                            // TODO: add a loose animation and add this sentence
                            // in the middle of the screen
                            std::cout << "You loose with a score of : "
                                      << Pacman.getScore() << std::endl;
                            // beginning level
                            Pacman.reset();
                            next_level = true;
                            life = false;
                            level = false;
                            menu = true;
                            break;
                        }

                        // next life
                        life = false;
                        break;
                    }

                    // display updated board
                    count =
                        draw(&windowSurf, &spriteBoard, count, Pacman, vecGhost,
                             vecDot, vecPowerup, Fruit.getFruit(),
                             Pacman.getScore(), PACMAN_LIVE, start, curLevel);
                    SDL_UpdateWindowSurface(Window);
                }

                Uint64 fps_end = SDL_GetTicks();
                float elapsed = (fps_end - fps_start) /
                                (float)SDL_GetPerformanceFrequency() * 1000.0f;

                // fps
                SDL_Delay(floor(10.000f - elapsed));
            }
        }
    }

    SDL_Quit();
    exit(EXIT_SUCCESS);
}
