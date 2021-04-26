#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>
#include "display.h"
#include "board.h"
#include "gameplay.h"
#include "button.h"
#include "menu.h"

using namespace std;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 700;

SDL_Window* window = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gScreenMenu = NULL;
TTF_Font *font = NULL;

board B;

void init()
{
    TTF_Init();
    window = SDL_CreateWindow( "Project: Cờ cá ngựa", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    //gScreenSurface = SDL_GetWindowSurface(window);
}

void load_texture()
{
    SDL_Surface *surface = SDL_LoadBMP("image/doilabekho.bmp");
    t_map = SDL_CreateTextureFromSurface(renderer, surface);
    surface = SDL_LoadBMP("image/blue.bmp");
    t_horse[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/yellow.bmp");
    t_horse[2] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/green.bmp");
    t_horse[3] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/red.bmp");
    t_horse[4] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/bluebright.bmp");
    t_bright[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/yellowbright.bmp");
    t_bright[2] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/greenbright.bmp");
    t_bright[3] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface=SDL_LoadBMP("image/redbright.bmp");
    t_bright[4] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface=SDL_LoadBMP("image/triangle.bmp");
    t_triangle[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface=SDL_LoadBMP("image/background1.bmp");
    t_background[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface=SDL_LoadBMP("image/menubackground1.bmp");
    t_background[2] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface=SDL_LoadBMP("image/meme.bmp");
    t_meme[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/skip.bmp");
    t_skipbutton[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/start_screen.bmp");
    t_menu[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/button.bmp");
    t_menu_button[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/Dice.bmp");
    t_dice[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/victory.bmp");
    t_victory[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/roll_button.bmp");
    t_rollbutton[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/roll_button_bright.bmp");
    t_rollbutton[2] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("image/khung.bmp");
    t_khung[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

int main(int argc, char* args[])
{
    srand(time(0));
    init();
    load_texture();
    int showmenu = show_menu();
    if (showmenu == 1) return 0;
    while (showmenu == 0)
    {
        start_game();
    }
}
