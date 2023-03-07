#include <SDL2/SDL.h>
#include <iostream>

SDL_Window *pWindow = nullptr;
SDL_Surface *win_surf = nullptr;
SDL_Surface *plancheSprites = nullptr;

SDL_Rect src_bg = {200, 3, 168, 216}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect bg = {4, 4, 672, 864};       // ici scale x4

// Red Ghost
SDL_Rect ghost_r = {3, 123, 16, 16};
SDL_Rect ghost_l = {37, 123, 16, 16};
SDL_Rect ghost_d = {105, 123, 16, 16};
SDL_Rect ghost_u = {71, 123, 16, 16};
SDL_Rect ghost = {34, 34, 32, 32}; // ici scale x2

// PacMan
SDL_Rect pac_blank = {3, 89, 16, 16};
SDL_Rect pac_r = {20, 89, 16, 16};
SDL_Rect pac_l = {46, 89, 16, 16};
SDL_Rect pac_d = {109, 90, 16, 16};
SDL_Rect pac_u = {75, 89, 16, 16};
SDL_Rect pac = {326, 484, 32, 32}; // ici scale x2
enum dir { LEFT, RIGHT, UP, DOWN, NONE };
dir last_dir = NONE;

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

SDL_Rect letter[256];
SDL_Rect letter['a'] = letter_a;
SDL_Rect letter['b'] = letter_b;

int count;

void init() {
    pWindow =
        SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);

    plancheSprites = SDL_LoadBMP("assets/pacman_sprites.bmp");
    count = 0;
}

// fonction qui met à jour la surface de la fenetre "win_surf"
void draw() {
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

    // TODO: create a function to print text using a dictionary
    // Erase score area
    SDL_Rect score_area = {4, 874, 16 * 36, 16};
    SDL_FillRect(win_surf, &score_area, 0);
    // Print score
    SDL_Rect score = {4, 874, 16, 16};
    SDL_BlitScaled(plancheSprites, &letter_s, win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &letter_c, win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &letter_o, win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &letter_r, win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &letter_e, win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &letter_blank, win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &number[1], win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &number[2], win_surf, &score);
    score.x += 16;
    SDL_BlitScaled(plancheSprites, &number[3], win_surf, &score);
    score.x += 16;

    // petit truc pour faire tourner le fantome
    SDL_Rect *ghost_in = nullptr;
    switch (count / 128) {
    case 0:
        ghost_in = &(ghost_r);
        ghost.x++;
        break;
    case 1:
        ghost_in = &(ghost_d);
        ghost.y++;
        break;
    case 2:
        ghost_in = &(ghost_l);
        ghost.x--;
        break;
    case 3:
        ghost_in = &(ghost_u);
        ghost.y--;
        break;
    }
    count = (count + 1) % (512);

    // ici on change entre les 2 sprites sources pour une jolie animation.
    SDL_Rect ghost_in2 = *ghost_in;
    if ((count / 4) % 2)
        ghost_in2.x += 17;

    // Animation du pacman
    SDL_Rect pac_in = pac_blank;
    if ((count / 4) % 2) {
        switch (last_dir) {
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

    // Deplacement du pacman
    switch (last_dir) {
    case RIGHT:
        pac.x++;
        break;
    case LEFT:
        pac.x--;
        break;
    case UP:
        pac.y--;
        break;
    case DOWN:
        pac.y++;
        break;
    case NONE:
        break;
    }

    // couleur transparente
    SDL_SetColorKey(plancheSprites, true, 0);
    // copie du sprite zoomé
    SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost);
    // copie du sprite normal
    SDL_BlitScaled(plancheSprites, &pac_in, win_surf, &pac);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError()
                  << std::endl;
        return 1;
    }

    init();
    // BOUCLE PRINCIPALE
    bool quit = false;
    while (!quit) {
        Uint64 fps_start = SDL_GetTicks64();

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

        // Gestion du clavier
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

        // AFFICHAGE
        draw();
        SDL_UpdateWindowSurface(pWindow);

        Uint64 fps_end = SDL_GetTicks64();
        float elapsed = (fps_end - fps_start) /
                        (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // LIMITE A 60 FPS
        SDL_Delay(floor(16.666f - elapsed));
    }
    SDL_Quit(); // ON SORT
    return 0;
}
