#include <SDL.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>
#include "display.h"
#include "board.h"
#include "gameplay.h"
#include "button.h"
using namespace std;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 700;
SDL_Window* window = NULL;
SDL_Surface* gScreenSurface = NULL;

board B;

void init()
{
    TTF_Init();
    window = SDL_CreateWindow( "Cờ cá ngựa siêu cấp vô địch", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
}
void load_texture()
{
    SDL_Surface *surface = SDL_LoadBMP("image/doilabekho.bmp");
    t_map= SDL_CreateTextureFromSurface( renderer, surface);
    surface = SDL_LoadBMP("image/blue.bmp");
    t_horse[1]= SDL_CreateTextureFromSurface( renderer, surface);
    surface = SDL_LoadBMP("image/yellow.bmp");
    t_horse[2]= SDL_CreateTextureFromSurface( renderer, surface);
    surface = SDL_LoadBMP("image/green.bmp");
    t_horse[3] = SDL_CreateTextureFromSurface( renderer, surface);
    surface = SDL_LoadBMP("image/red.bmp");
    t_horse[4]= SDL_CreateTextureFromSurface( renderer, surface);
    surface = SDL_LoadBMP("image/bluebright.bmp");
    t_bright[1] = SDL_CreateTextureFromSurface(renderer, surface);
    surface = SDL_LoadBMP("image/yellowbright.bmp");
    t_bright[2] = SDL_CreateTextureFromSurface(renderer, surface);
    surface = SDL_LoadBMP("image/greenbright.bmp");
    t_bright[3] = SDL_CreateTextureFromSurface(renderer, surface);
    surface=SDL_LoadBMP("image/redbright.bmp");
    t_bright[4] = SDL_CreateTextureFromSurface(renderer, surface);
    surface=SDL_LoadBMP("image/triangle.bmp");
    t_triangle[1] = SDL_CreateTextureFromSurface(renderer, surface);
    surface=SDL_LoadBMP("image/background1.bmp");
    t_background[1] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
int main(int argc, char* args[])
{
    srand(time(0));
    init();
    load_texture();
    start_game();
    return 0;
    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                cerr<< x << ',' << y << endl;
                for (int i = 1; i <= 4; i++)
                    for (int j = 1;j <= 4; j++)
                    {
                        if (check_click(B.horse_rect[i][j], x, y))
                        {
                            bool ok = true;
                            for (int k = 1;k <= 4; k ++)
                                if (k != j && B.pos[i][k] == nextt(i,B.pos[i][j])) ok = false;
                            if (ok  == true)
                            B.move_next(i,j);
                        }
                    }
            }
        }
    }
}
