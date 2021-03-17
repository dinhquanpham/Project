#ifndef _DISPLAY_H
#define _DISPLAY_H
#include <iostream>
#include <SDL_ttf.h>
#include <SDL.h>

using namespace std;
extern SDL_Texture *t_map = NULL, *t_horse[5]= {},*t_bright[5]={},*t_triangle[2]={},*t_background[2]={};
extern SDL_Renderer *renderer = NULL;
void render_image(string path,SDL_Rect rect)
{

    SDL_Surface *surface = SDL_LoadBMP(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);
    SDL_RenderCopy( renderer, texture, NULL, &rect );
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
}
bool check_click(SDL_Rect rect, int x, int y)
{
    return (x >= rect.x && y >= rect.y && x < rect.x + rect.w && y < rect.y + rect.h);
}
#endif
