#include "graphic.h"

SDL_Rect src_bg = {370, 3, 168, 216};
SDL_Rect bg = {4, 4 + SCORE_HEADER, 672, 864};

// Pacman logo
SDL_Rect pacmanLogo = {3, 3, 182, 49};

// PacMan
// animation
SDL_Rect pac_blank = {3, 89, 16, 16};
SDL_Rect pac_r = {20, 89, 16, 16};
SDL_Rect pac_l = {46, 89, 16, 16};
SDL_Rect pac_d = {109, 90, 16, 16};
SDL_Rect pac_u = {75, 89, 16, 16};
// position
SDL_Rect _pacman = {PACMAN_INIT_X * SCALE_PIXEL + PACMAN_CENTER_X,
                    PACMAN_INIT_Y *SCALE_PIXEL + PACMAN_CENTER_Y, SCALE_PIXEL,
                    SCALE_PIXEL};
// eaten
std::vector<SDL_Rect> eatenPacman{
    {3, 110, 17, 10}, {22, 112, 18, 8}, {41, 113, 18, 7},
    {79, 112, 18, 8}, {98, 111, 16, 9}, {115, 111, 12, 9},
    {128, 111, 8, 9}, {137, 111, 4, 9}, {142, 108, 12, 12}};
// life
SDL_Rect _life = {168, 75, 12, 14};

// Ghost
std::vector<std::vector<SDL_Rect>> initGhostSrpite() {

    // Red Ghost
    std::vector<SDL_Rect> redGhostSprite;
    // animation
    redGhostSprite.push_back({37, 123, 16, 16});  // left
    redGhostSprite.push_back({3, 123, 16, 16});   // right
    redGhostSprite.push_back({71, 123, 16, 16});  // up
    redGhostSprite.push_back({105, 123, 16, 16}); // down
    // position
    redGhostSprite.push_back({RED_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X,
                              RED_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y,
                              SCALE_PIXEL, SCALE_PIXEL});

    // Pink Ghost
    std::vector<SDL_Rect> pinkGhostSprite;
    // animation
    pinkGhostSprite.push_back({37, 141, 16, 16});
    pinkGhostSprite.push_back({3, 141, 16, 16});
    pinkGhostSprite.push_back({71, 141, 16, 16});
    pinkGhostSprite.push_back({105, 141, 16, 16});
    // position
    pinkGhostSprite.push_back({PINK_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X,
                               PINK_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y,
                               SCALE_PIXEL, SCALE_PIXEL});

    // Blue Ghost
    std::vector<SDL_Rect> blueGhostSprite;
    // animation
    blueGhostSprite.push_back({37, 159, 16, 16});
    blueGhostSprite.push_back({3, 159, 16, 16});
    blueGhostSprite.push_back({71, 159, 16, 16});
    blueGhostSprite.push_back({105, 159, 16, 16});
    // position
    blueGhostSprite.push_back({BLUE_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X,
                               BLUE_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y,
                               SCALE_PIXEL, SCALE_PIXEL});
    // Orange Ghost
    std::vector<SDL_Rect> orangeGhostSprite;
    // animation
    orangeGhostSprite.push_back({37, 177, 16, 16});
    orangeGhostSprite.push_back({3, 177, 16, 16});
    orangeGhostSprite.push_back({71, 177, 16, 16});
    orangeGhostSprite.push_back({105, 177, 16, 16});
    // position
    orangeGhostSprite.push_back(
        {ORANGE_GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X,
         ORANGE_GHOST_INIT_Y * SCALE_PIXEL + GHOST_CENTER_Y, SCALE_PIXEL,
         SCALE_PIXEL});

    std::vector<std::vector<SDL_Rect>> vecGhostSprite;
    vecGhostSprite.push_back(redGhostSprite);
    vecGhostSprite.push_back(pinkGhostSprite);
    vecGhostSprite.push_back(blueGhostSprite);
    vecGhostSprite.push_back(orangeGhostSprite);

    return vecGhostSprite;
}

SDL_Rect fearBlueGhostSprite{3, 195, 16, 16};
SDL_Rect fearWhiteGhostSprite{37, 195, 16, 16};
SDL_Rect eatenGhostSprite_r{71, 195, 16, 16};
SDL_Rect eatenGhostSprite_l{88, 195, 16, 16};
SDL_Rect eatenGhostSprite_u{105, 195, 16, 16};
SDL_Rect eatenGhostSprite_d{122, 195, 16, 16};

std::vector<std::vector<SDL_Rect>> vecGhostSprite = initGhostSrpite();

// items
SDL_Rect dot_in = {4, 81, 2, 2};
SDL_Rect powerup_in = {9, 79, 7, 7};
SDL_Rect cherry_in = {289, 236, 14, 14};
SDL_Rect strawberry_in = {305, 236, 14, 14};
SDL_Rect orange_in = {320, 236, 14, 14};
SDL_Rect apple_in = {337, 236, 14, 14};
SDL_Rect melon_in = {352, 234, 14, 16};
SDL_Rect galaxian_in = {369, 235, 14, 14};
SDL_Rect bell_in = {385, 235, 16, 16};
SDL_Rect key_in = {400, 235, 14, 16};

// Vector of fruits
std::vector<SDL_Rect> vecFruitSprite = {cherry_in, strawberry_in, orange_in,
                                        apple_in,  melon_in,      galaxian_in,
                                        bell_in,   key_in};

// Score
SDL_Rect score100 = {180, 133, 13, 7};
SDL_Rect score300 = {179, 142, 14, 7};
SDL_Rect score500 = {179, 151, 14, 7};
SDL_Rect score700 = {179, 160, 14, 7};
SDL_Rect score1000 = {177, 169, 16, 7};
SDL_Rect score2000 = {177, 178, 16, 7};
SDL_Rect score3000 = {177, 187, 16, 7};
SDL_Rect score5000 = {177, 196, 16, 7};
SDL_Rect score200 = {155, 176, 14, 7};
SDL_Rect score400 = {155, 185, 14, 7};
SDL_Rect score800 = {155, 194, 14, 7};
SDL_Rect score1600 = {154, 203, 15, 7};
SDL_Rect pts = {177, 204, 16, 7};
std::map<int, SDL_Rect> scoreSprite = {
    {100, score100},   {300, score300},   {500, score500},   {700, score700},
    {1000, score1000}, {2000, score2000}, {3000, score3000}, {5000, score5000},
    {200, score200},   {400, score400},   {800, score800},   {1600, score1600}};

// Letters and numbers for SDL
SDL_Rect letter_a = {12, 61, 8, 8};
SDL_Rect letter_b = {20, 61, 8, 8};
SDL_Rect letter_c = {28, 61, 8, 8};
SDL_Rect letter_d = {36, 61, 8, 8};
SDL_Rect letter_e = {44, 61, 8, 8};
SDL_Rect letter_f = {52, 61, 8, 8};
SDL_Rect letter_g = {60, 61, 8, 8};
SDL_Rect letter_h = {68, 61, 8, 8};
SDL_Rect letter_i = {76, 61, 8, 8};
SDL_Rect letter_j = {84, 61, 8, 8};
SDL_Rect letter_k = {92, 61, 8, 8};
SDL_Rect letter_l = {100, 61, 8, 8};
SDL_Rect letter_m = {108, 61, 8, 8};
SDL_Rect letter_n = {116, 61, 8, 8};
SDL_Rect letter_o = {124, 61, 8, 8};
SDL_Rect letter_p = {4, 69, 8, 8};
SDL_Rect letter_q = {12, 69, 8, 8};
SDL_Rect letter_r = {20, 69, 8, 8};
SDL_Rect letter_s = {28, 69, 8, 8};
SDL_Rect letter_t = {36, 69, 8, 8};
SDL_Rect letter_u = {44, 69, 8, 8};
SDL_Rect letter_v = {52, 69, 8, 8};
SDL_Rect letter_w = {60, 69, 8, 8};
SDL_Rect letter_x = {68, 69, 8, 8};
SDL_Rect letter_y = {76, 69, 8, 8};
SDL_Rect letter_z = {84, 69, 8, 8};
SDL_Rect letter_point = {92, 69, 8, 8};
SDL_Rect letter_0 = {4, 53, 8, 8};
SDL_Rect letter_1 = {12, 53, 8, 8};
SDL_Rect letter_2 = {20, 53, 8, 8};
SDL_Rect letter_3 = {28, 53, 8, 8};
SDL_Rect letter_4 = {36, 53, 8, 8};
SDL_Rect letter_5 = {44, 53, 8, 8};
SDL_Rect letter_6 = {52, 53, 8, 8};
SDL_Rect letter_7 = {60, 53, 8, 8};
SDL_Rect letter_8 = {68, 53, 8, 8};
SDL_Rect letter_9 = {76, 53, 8, 8};
SDL_Rect letter_blank = {108, 69, 8, 8};

// Dictionary for letters
std::map<char, SDL_Rect> sdlChar = {
    {'a', letter_a}, {'b', letter_b}, {'c', letter_c},     {'d', letter_d},
    {'e', letter_e}, {'f', letter_f}, {'g', letter_g},     {'h', letter_h},
    {'i', letter_i}, {'j', letter_j}, {'k', letter_k},     {'l', letter_l},
    {'m', letter_m}, {'n', letter_n}, {'o', letter_o},     {'p', letter_p},
    {'q', letter_q}, {'r', letter_r}, {'s', letter_s},     {'t', letter_t},
    {'u', letter_u}, {'v', letter_v}, {'w', letter_w},     {'x', letter_x},
    {'y', letter_y}, {'z', letter_z}, {'.', letter_point}, {' ', letter_blank},
    {'1', letter_1}, {'2', letter_2}, {'3', letter_3},     {'4', letter_4},
    {'5', letter_5}, {'6', letter_6}, {'7', letter_7},     {'8', letter_8},
    {'9', letter_9}, {'0', letter_0}};

void init(SDL_Window **Window, SDL_Surface **windowSurf,
          SDL_Surface **spriteBoard) {

    *Window = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, 676, 900 + SCORE_HEADER,
                               SDL_WINDOW_SHOWN);
    *windowSurf = SDL_GetWindowSurface(*Window);
    *spriteBoard = SDL_LoadBMP("assets/pacman_sprites.bmp");
}

void intro(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int highScore) {
    SDL_SetColorKey(*spriteBoard, false, 0);

    // Area for window
    SDL_Rect windowArea = {0, 0, 676, 900 + SCORE_HEADER};
    SDL_FillRect(*windowSurf, &windowArea, 0);

    // Area for pacman logo
    SDL_Rect logoArea = {154, 80, 364, 98};
    SDL_FillRect(*windowSurf, &logoArea, 0);
    SDL_BlitScaled(*spriteBoard, &pacmanLogo, *windowSurf, &logoArea);

    // Print text
    drawString(windowSurf, spriteBoard, 178, 600, "press enter to start");

    // Print high score
    std::string highScoreStr = "high score " + std::to_string(highScore);
    drawString(windowSurf, spriteBoard, 178, 700, highScoreStr);

    // print credits
    drawString(windowSurf, spriteBoard, 38, 878 + SCORE_HEADER,
               "coded by ethan huret and thomas dumond");
}

void gameOver(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int curScore,
              int highScore) {
    SDL_SetColorKey(*spriteBoard, false, 0);

    // Area for window
    SDL_Rect windowArea = {0, 0, 676, 900 + SCORE_HEADER};
    SDL_FillRect(*windowSurf, &windowArea, 0);

    // Print text
    drawString(windowSurf, spriteBoard, 250, 450, "game over !");

    if (curScore > highScore) {
        highScore = curScore;
    }

    // Print score
    std::string scoreStr = "your score " + std::to_string(curScore);
    drawString(windowSurf, spriteBoard, 178, 600, scoreStr);

    // Print high score
    std::string highScoreStr = "high score " + std::to_string(highScore);
    drawString(windowSurf, spriteBoard, 178, 700, highScoreStr);
}

int draw(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int count,
         pacman Pacman, std::vector<std::shared_ptr<ghost>> vecGhost,
         std::vector<Coordinate> vecDot, std::vector<Coordinate> vecPowerup,
         typeFruit fruit, int curScore, int highScore, short death, bool start,
         int curLevel) {
    SDL_SetColorKey(*spriteBoard, false, 0);
    SDL_BlitScaled(*spriteBoard, &src_bg, *windowSurf, &bg);

    count = (count + 1) % (512);

    // clear the area for the score header
    SDL_Rect scoreHeaderArea = {0, 0, 676, SCORE_HEADER};
    SDL_FillRect(*windowSurf, &scoreHeaderArea, 0);

    // combine the score string and the score number into one string
    std::string scoreString = "score " + std::to_string(curScore);

    // print the score string
    drawString(windowSurf, spriteBoard, SCORE_HEADER / 2, SCORE_HEADER / 2,
               scoreString);

    if (curScore > highScore) {
        highScore = curScore;
    }

    // combine the score string and the score number into one string
    std::string highScoreString = "high score " + std::to_string(highScore);

    // print the score string
    drawString(windowSurf, spriteBoard, 400 - SCORE_HEADER / 2 - 144,
               SCORE_HEADER / 2, highScoreString);

    // combine the level string and the level number into one string
    std::string levelString = "level " + std::to_string(curLevel);

    // print the level string
    drawString(windowSurf, spriteBoard, 676 - SCORE_HEADER / 2 - 128,
               SCORE_HEADER / 2, levelString);

    // area for score
    SDL_Rect scoreArea = {0, 864 + SCORE_HEADER, 676, 36};
    SDL_FillRect(*windowSurf, &scoreArea, 0);

    // print the remaining life and eaten fruits
    SDL_Rect lifeArea = {4, 874 + SCORE_HEADER, 676, 20};
    // Erase the area
    SDL_FillRect(*windowSurf, &lifeArea, 0);
    for (auto i = 0; i < Pacman.getRemainingLife(); i++) {
        SDL_Rect life = {4 + i * 22, 874 + SCORE_HEADER, 20, 20};
        SDL_BlitScaled(*spriteBoard, &_life, *windowSurf, &life);
    }

    // print the eaten fruit
    for (auto i = 0; i < int(Pacman.getEatenFruit().size()); i++) {
        SDL_Rect fruit = {400 + i * 32, 874 + SCORE_HEADER, 20, 20};
        SDL_BlitScaled(*spriteBoard, &vecFruitSprite[i], *windowSurf, &fruit);
    }

    // print ready before the game starts
    if (!start)
        drawString(windowSurf, spriteBoard, 298, 492 + SCORE_HEADER, "ready");

    // dot display
    for (auto &coord : vecDot) {
        SDL_Rect dot = {coord.x * SCALE_PIXEL + 11,
                        coord.y * SCALE_PIXEL + 15 + SCORE_HEADER, 10, 10};
        SDL_BlitScaled(*spriteBoard, &dot_in, *windowSurf, &dot);
    }

    // powerup display
    if ((count / 8) % 2 == 0) {
        for (auto &coord : vecPowerup) {
            SDL_Rect powerup = {coord.x * SCALE_PIXEL + 6,
                                coord.y * SCALE_PIXEL + 10 + SCORE_HEADER, 20,
                                20};
            SDL_BlitScaled(*spriteBoard, &powerup_in, *windowSurf, &powerup);
        }
    }

    // fruit display
    if (fruit != _NONE) {
        SDL_Rect fruitSdl = {FRUIT_X * SCALE_PIXEL,
                             FRUIT_Y * SCALE_PIXEL + SCORE_HEADER, SCALE_PIXEL,
                             SCALE_PIXEL};
        SDL_BlitScaled(*spriteBoard, &vecFruitSprite[fruit - 1], *windowSurf,
                       &fruitSdl);
    }

    // score fruit display
    if (Pacman.getFruitEatenScore() != 0) {

        time_t fruitEatenTimer2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime =
            fruitEatenTimer2 - Pacman.getfruitEatenTimer();

        if (elapsedTime.count() < FRUIT_SCORE_DISPLAY_TIME) {

            // Place the area to write the score
            SDL_Rect pointArea = {FRUIT_X * SCALE_PIXEL,
                                  FRUIT_Y * SCALE_PIXEL + 10 + SCORE_HEADER, 34,
                                  20};

            // print the score
            SDL_BlitScaled(*spriteBoard,
                           &scoreSprite[Pacman.getFruitEatenScore()],
                           *windowSurf, &pointArea);
        } else
            Pacman.setFruitEatenScore(0);
    }

    // do not draw ghost if pacman is dead
    if (death == PACMAN_LIVE) {

        for (auto &Ghost : vecGhost) {
            // _ghost look animation
            SDL_Rect *ghost_in = nullptr;
            // normal mode
            switch (Ghost->getLastDir()) {
            case LEFT:
                ghost_in = &(vecGhostSprite[Ghost->getGhost()][LEFT]);
                break;
            case RIGHT:
                ghost_in = &(vecGhostSprite[Ghost->getGhost()][RIGHT]);
                break;
            case UP:
                ghost_in = &(vecGhostSprite[Ghost->getGhost()][UP]);
                break;
            case DOWN:
                ghost_in = &(vecGhostSprite[Ghost->getGhost()][DOWN]);
                break;
            case NONE:
                // by default, _ghost looks right
                ghost_in = &(vecGhostSprite[Ghost->getGhost()][RIGHT]);
                break;
            }

            // _ghost wave animation
            SDL_Rect ghost_in2 = *ghost_in;
            if ((count / 4) % 2)
                ghost_in2.x += 17;

            // fear mode
            if (Ghost->isFrightened() == true && Ghost->isInHouse() == false &&
                Ghost->isReturnHouse() == false) {

                time_t powerupTimer2 = std::chrono::steady_clock::now();
                std::chrono::duration<double> elapsedTime =
                    powerupTimer2 - Pacman.getPowerupTimer();

                if (elapsedTime.count() < POWERUP_MODE - GHOST_BLINK)
                    ghost_in = &(fearBlueGhostSprite);
                else {
                    if ((count / 8) % 2)
                        ghost_in = &(fearBlueGhostSprite);
                    else
                        ghost_in = &(fearWhiteGhostSprite);
                }

                // _ghost wave animation
                ghost_in2 = *ghost_in;
                if ((count / 4) % 2)
                    ghost_in2.x += 17;
            }
            // go back to house mode
            else if (Ghost->isReturnHouse() == true) {

                // place the area to write the score
                SDL_Rect pointArea = {0, 0, 34, 20};
                size_t lastGhostScore = 0;

                // new ghost is eaten
                if (Pacman.getGhostEatenScore() != lastGhostScore) {
                    // remove the previous score
                    SDL_FillRect(*windowSurf, &pointArea,
                                 SDL_MapRGB((*windowSurf)->format, 0, 0, 0));

                    pointArea.x = int(Ghost->getEatenPosition().first) +
                                  (GHOST_CENTER_X / 2);
                    pointArea.y = int(Ghost->getEatenPosition().second +
                                      (GHOST_CENTER_Y / 2) + SCORE_HEADER);

                    SDL_BlitScaled(*spriteBoard,
                                   &scoreSprite[Pacman.getGhostEatenScore()],
                                   *windowSurf, &pointArea);

                    lastGhostScore = Pacman.getGhostEatenScore();
                }

                switch (Ghost->getLastDir()) {
                case RIGHT:
                    ghost_in2 = eatenGhostSprite_r;
                    break;
                case LEFT:
                    ghost_in2 = eatenGhostSprite_l;
                    break;
                case UP:
                    ghost_in2 = eatenGhostSprite_u;
                    break;
                case DOWN:
                    ghost_in2 = eatenGhostSprite_d;
                    break;
                case NONE:
                    ghost_in2 = eatenGhostSprite_l;
                    break;
                }
            }

            // ghost updated position
            vecGhostSprite[Ghost->getGhost()].back().x = Ghost->getPos().first;
            vecGhostSprite[Ghost->getGhost()].back().y =
                Ghost->getPos().second + SCORE_HEADER;

            SDL_SetColorKey(*spriteBoard, true, 0);
            SDL_BlitScaled(*spriteBoard, &ghost_in2, *windowSurf,
                           &vecGhostSprite[Ghost->getGhost()].back());
        }
    }

    // pacman animation
    SDL_Rect pac_in = pac_blank;
    if (death == PACMAN_LIVE) {
        if ((count / 4) % 2) {
            switch (Pacman.getLastDir()) {
            case LEFT:
                pac_in = pac_l;
                break;
            case RIGHT:
                pac_in = pac_r;
                break;
            case UP:
                pac_in = pac_u;
                break;
            case DOWN:
                pac_in = pac_d;
                break;
            case NONE:
                break;
            }
        }
        // avoid animation when pacman is not moving
        if (Pacman.getLastDir() == NONE) {
            switch (Pacman.getOldDir()) {
            case LEFT:
                pac_in = pac_l;
                break;
            case RIGHT:
                pac_in = pac_r;
                break;
            case UP:
                pac_in = pac_u;
                break;
            case DOWN:
                pac_in = pac_d;
                break;
            case NONE:
                pac_in = pac_blank;
                break;
            }
        }
    } else {
        pac_in = eatenPacman[death];
    }

    // pacman updated position
    _pacman.x = Pacman.getPos().first;
    _pacman.y = Pacman.getPos().second + SCORE_HEADER;

    SDL_SetColorKey(*spriteBoard, true, 0);
    SDL_BlitScaled(*spriteBoard, &pac_in, *windowSurf, &_pacman);

    return count;
}

void drawString(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, int x,
                int y, std::string str) {
    // Get the string length
    int len = str.length();

    // Create a rectangle for the text
    SDL_Rect area = {x, y, 16 * (len + 2), 16};

    // Erase the area
    SDL_FillRect(*windowSurf, &area, 0);

    // Print the text
    SDL_Rect textRect = {x, y, 16, 16};
    for (auto s : str) {
        SDL_BlitScaled(*spriteBoard, &sdlChar[s], *windowSurf, &textRect);
        textRect.x += 16;
    }
}