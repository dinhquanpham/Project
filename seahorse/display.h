#ifndef _DISPLAY_H
#define _DISPLAY_H
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;
extern SDL_Texture *t_map = NULL, *t_horse[5]= {NULL,NULL,NULL,NULL,NULL},*t_bright[5]={NULL, NULL, NULL, NULL, NULL};

extern SDL_Texture *t_triangle[2]={NULL, NULL},*t_background[3]={NULL,NULL}, *t_meme[2] = {NULL, NULL};

extern SDL_Texture *t_skipbutton[2] = {NULL, NULL},*t_menu[2] = {},*t_menu_button[6] = {},*t_dice[2] = {},*t_victory[2] = {NULL, NULL};

extern SDL_Texture *t_rollbutton[3] ={NULL,NULL} ,*t_khung[2] = {NULL,NULL};

extern SDL_Renderer *renderer = NULL;

extern SDL_Surface *t_image = NULL;

extern SDL_Rect skip_button_rect={353,575,75,75};

extern SDL_Rect victory_screen ={200,100,700,500};

extern SDL_Rect roll_button = {0,250,75,75};

extern SDL_Rect khung = {0,200,300,200};

void render_image(string path,SDL_Rect rect)
{
    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_RenderCopy( renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void render_text(string path , SDL_Rect rect ,int font_size)
{
    TTF_Font *font = TTF_OpenFont("font.ttf", font_size);
    TTF_SizeText(font,path.c_str(), &rect.w,&rect.h);
    SDL_Color color = {0, 125, 125, 0};
    SDL_Surface* message = TTF_RenderText_Solid(font, path.c_str(), color);
    message->w = rect.w;message->h = rect.h;
    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, message);
    SDL_RenderCopy( renderer, texture, NULL, &rect );
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
}

bool check_click(SDL_Rect rect, int x, int y)
{
    return (x >= rect.x && y >= rect.y && x < rect.x + rect.w && y < rect.y + rect.h);
}
#endif
