#include "graphic.h"

SDL_Rect src_bg = {370, 3, 168, 216};
SDL_Rect bg = {4, 4, 672, 864};

// Red Ghost
// animation
SDL_Rect ghost_r = {3, 123, 16, 16};
SDL_Rect ghost_l = {37, 123, 16, 16};
SDL_Rect ghost_d = {105, 123, 16, 16};
SDL_Rect ghost_u = {71, 123, 16, 16};
// position
SDL_Rect _ghost = {GHOST_INIT_X * SCALE_PIXEL + GHOST_CENTER_X,
                   GHOST_INIT_Y *SCALE_PIXEL + GHOST_CENTER_Y, 32, 32};

// PacMan
// animation
SDL_Rect pac_blank = {3, 89, 16, 16};
SDL_Rect pac_r = {20, 89, 16, 16};
SDL_Rect pac_l = {46, 89, 16, 16};
SDL_Rect pac_d = {109, 90, 16, 16};
SDL_Rect pac_u = {75, 89, 16, 16};
// position
SDL_Rect _pacman = {PACMAN_INIT_X * SCALE_PIXEL + PACMAN_CENTER_X,
                    PACMAN_INIT_Y *SCALE_PIXEL + PACMAN_CENTER_Y, 32, 32};

// items
SDL_Rect dot_in = {4, 81, 2, 2};
SDL_Rect powerup_in = {9, 79, 7, 7};

// Letters and numbers
// TODO: use a dictionary
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

SDL_Rect number[] = {letter_0, letter_1, letter_2, letter_3, letter_4,
                     letter_5, letter_6, letter_7, letter_8, letter_9};

int count;

void init(SDL_Window **Window, SDL_Surface **windowSurf,
          SDL_Surface **spriteBoard) {

    *Window =
        SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    *windowSurf = SDL_GetWindowSurface(*Window);
    *spriteBoard = SDL_LoadBMP("assets/pacman_sprites.bmp");
    count = 0;
}

void draw(SDL_Surface **windowSurf, SDL_Surface **spriteBoard, pacman Pacman,
          ghost Ghost, std::vector<Coordinate> vecDot,
          std::vector<Coordinate> vecPowerup, int cur_score) {

    SDL_SetColorKey(*spriteBoard, false, 0);
    SDL_BlitScaled(*spriteBoard, &src_bg, *windowSurf, &bg);

    // TODO: create a function to print text using a dictionary
    // Erase score area
    SDL_Rect score_area = {4, 874, 16 * 36, 16};
    SDL_FillRect(*windowSurf, &score_area, 0);

    // score display
    SDL_Rect score = {4, 874, 16, 16};
    SDL_BlitScaled(*spriteBoard, &letter_s, *windowSurf, &score);
    score.x += 16;
    SDL_BlitScaled(*spriteBoard, &letter_c, *windowSurf, &score);
    score.x += 16;
    SDL_BlitScaled(*spriteBoard, &letter_o, *windowSurf, &score);
    score.x += 16;
    SDL_BlitScaled(*spriteBoard, &letter_r, *windowSurf, &score);
    score.x += 16;
    SDL_BlitScaled(*spriteBoard, &letter_e, *windowSurf, &score);
    score.x += 16;
    SDL_BlitScaled(*spriteBoard, &letter_blank, *windowSurf, &score);
    score.x += 16;

    // get all score digits
    int score_number = cur_score;
    int digits[10];
    int i = 0;

    while (score_number > 0) {
        digits[i] = score_number % 10;
        score_number /= 10;
        i++;
    }

    // score display
    for (int j = i - 1; j >= 0; j--) {
        SDL_BlitScaled(*spriteBoard, &number[digits[j]], *windowSurf, &score);
        score.x += 16;
    }

    // dot display
    for (auto &coord : vecDot) {
        SDL_Rect dot = {coord.x * 32 + 11, coord.y * 32 + 15, 10, 10};
        SDL_BlitScaled(*spriteBoard, &dot_in, *windowSurf, &dot);
    }

    // powerup display
    for (auto &coord : vecPowerup) {
        SDL_Rect powerup = {coord.x * 32 + 6, coord.y * 32 + 10, 20, 20};
        SDL_BlitScaled(*spriteBoard, &powerup_in, *windowSurf, &powerup);
    }

    // _ghost look animation
    SDL_Rect *ghost_in = nullptr;
    switch (Ghost.getLastDir()) {
    case RIGHT:
        ghost_in = &(ghost_r);
        break;
    case DOWN:
        ghost_in = &(ghost_d);
        break;
    case LEFT:
        ghost_in = &(ghost_l);
        break;
    case UP:
        ghost_in = &(ghost_u);
        break;
    case NONE:
        // by default, _ghost looks right
        ghost_in = &(ghost_r);
        break;
    }
    count = (count + 1) % (512);

    // _ghost wave animation
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count / 4) % 2)
        ghost_in2.x += 17;

    // _ghost updated position
    _ghost.x = Ghost.getPos().first;
    _ghost.y = Ghost.getPos().second;

    // pacman animation
    SDL_Rect pac_in = pac_blank;
    if ((count / 4) % 2) {
        switch (Pacman.getLastDir()) {
        case RIGHT:
            pac_in = pac_r;
            break;
        case LEFT:
            pac_in = pac_l;
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

    // pacman updated position
    _pacman.x = Pacman.getPos().first;
    _pacman.y = Pacman.getPos().second;

    SDL_SetColorKey(*spriteBoard, true, 0);
    SDL_BlitScaled(*spriteBoard, &ghost_in2, *windowSurf, &_ghost);
    SDL_BlitScaled(*spriteBoard, &pac_in, *windowSurf, &_pacman);
}