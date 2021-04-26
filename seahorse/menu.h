#ifndef _MENU_H
#define _MENU_H

#include <SDL.h>
#include <iostream>

using namespace std;

int show_menu()
{
//    font = TTF_OpenFont("font.ttf", 50);
    SDL_Rect menu_background = {0,0,1080,700};
    /// thiết lập tọa độ các nút trên menu
    // nút play
    SDL_Rect Play_button_Dest = {500,360,120,60};
    SDL_Rect Play_button_Scr = {0,0,120,60};
    // nút play sáng
    SDL_Rect Play_button_bright_Scr = {0,60,120,60};
    //nút option
    SDL_Rect Option_button_Dest = {500,420,120,60};
    SDL_Rect Option_button_Scr = {120,0,120,60};
    //nút option sáng
    SDL_Rect Option_button_bright_Scr = {120,60,120,60};
    //nút exit
    SDL_Rect Exit_button_Dest = {500,480,120,60};
    SDL_Rect Exit_button_Scr = {240,0,120,60};
    //nút exit sáng
    SDL_Rect Exit_button_bright_Scr = {240,60,120,60};
    /// in ảnh lên màn hình
    SDL_RenderCopy(renderer, t_background[2], NULL, &menu_background);
    SDL_RenderCopy(renderer, t_menu_button[1], &Play_button_Scr, &Play_button_Dest);
    SDL_RenderCopy(renderer, t_menu_button[1], &Option_button_Scr, &Option_button_Dest);
    SDL_RenderCopy(renderer, t_menu_button[1], &Exit_button_Scr, &Exit_button_Dest);
    int x , y;
    bool selected[2] = {0,0};
    SDL_Rect Pos_menu[2];
    Pos_menu[0] = Play_button_Dest;
    Pos_menu[1] = Exit_button_Dest;
    SDL_Event event;
    while (1)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 1;
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                x = event.motion.x;
                y = event.motion.y;
                    if (check_click(Pos_menu[0],x,y))
                    {
                        if (!selected[0])
                        {
                            selected[0] = 1;
                            SDL_RenderCopy(renderer, t_menu_button[1],&Play_button_bright_Scr, &Play_button_Dest);
                        }
                    }
                    else
                    {
                        if(selected[0])
                        {
                            selected[0] = 0;
                            SDL_RenderCopy(renderer, t_menu_button[1], &Play_button_Scr, &Play_button_Dest);
                        }

                    }
                    if (check_click(Pos_menu[1],x,y))
                    {
                        if (!selected[1])
                        {
                            selected[1] = 1;
                            SDL_RenderCopy(renderer, t_menu_button[1], &Exit_button_bright_Scr, &Exit_button_Dest);
                        }
                    }
                    else
                    {
                        if(selected[1])
                        {
                            selected[1] = 0;
                            SDL_RenderCopy(renderer, t_menu_button[1], &Exit_button_Scr, &Exit_button_Dest);
                        }

                    }
            }
            x = event.button.x;
            y = event.button.y;
            for (int i = 0; i <= 2; i++)
                if (check_click(Pos_menu[i],x,y))
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                    return i;
        }
        SDL_RenderPresent(renderer);
    }
    return 1;
}
#endif

