#ifndef _GAMEPLAY_H
#define _GAMEPLAY_H
#include <bits/stdc++.h>
#include "display.h"
#include "board.h"
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;
int bonus;
int roll_dice()
{
    int z = rand() % 4 + 1;
    int num = rand() % 6 + 1;
    if(z == 1) num = 6;
    render_text(to_string(num),{100,200,20,20},20);
    return num;
}
int check(board B, int i, int j, int n)
{
    int pos = B.pos[i][j];
    int dest;
    if (pos == 0)
    {
        if (n < 6) return 0;
        dest = (i - 1) * 14 + 2;
    }
    else
    {
        pos = nextt(i,pos);
        if (pos == 14 * (i - 1) + 1 || pos > 56)
        {
            while (pos - 56 < n)
            {
                for (int a = 1; a <= 4; a++)
                    for (int b = 1; b <= 4; b++)
                        if (a != i || b !=j)
                            if (B.pos[a][b] == pos) return 0;
                pos = nextt(i , pos);
            }
            dest = pos;
        }
        else
            {
                n--;
                while (n > 0)
                {
                    for (int a = 1; a <= 4; a++)
                        for (int b = 1; b <= 4; b++)
                            if (a != i || b != j)
                                if (B.pos[a][b] == pos) return 0;
                    pos = nextt(i, pos);
                    n --;
                }
                dest = pos;
                if (dest > 56) return 0;
            }
    }
    for (int k = 1; k <= 4; k ++)
        if (k != j && B.pos[i][k] == dest) return 0;
    return 1;
}
void player_turn(int i, board &B)
{
    // lượt của người chơi
    for (int k = 1;k <= 4; k++)
        for (int j = 1;j <= 4; j++)
        B.isbright[k][j] = 0;

    B.render_board();
    int num = roll_dice();
    if (num == 6) bonus = 1; else bonus = 0;
    SDL_RenderPresent(renderer);
    for (int j = 1;j <= 4; j++)
    {
        if (check(B,i,j,num))
        {
            B.isbright[i][j] = 1;
        }
    }
    B.render_board();
    string st = "player "+to_string(i)+":  "+to_string(num);
    render_text(st,{100,200,50,20},20);
    SDL_RenderCopy(renderer, t_triangle[1],NULL, &B.triangle[i]);
     SDL_RenderPresent(renderer);
     SDL_Delay(1000);
     vector <int> V;
    for (int j = 1;j <= 4; j++)
        if (B.isbright[i][j] == 1)
            V.push_back(j);
    for (int j = 0;j <V .size();j++)
        for (int k = j+1; k < V.size(); k++)
            if (B.horse_rect[i][V[j]].y < B.horse_rect[i][V[k]].y) swap(V[j],V[k]);
    SDL_Event event;
    if (V.size() == 0) return;
    while (1)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                cerr<< i << ' ' << x << ',' << y << endl;
                for (int j:V)
                {
                    if (check_click(B.horse_rect[i][j],x,y))
                    {
                        if (B.pos[i][j] == 0)
                        {
                            B.move_next(i,j);
                            return;
                        }
                        for (int k = 1;k <= num;k++)
                        {
                            B.move_next(i,j);
                        }
                        return;
                    }
                }
                     //B.move_next(1,1);
            }
        }
}
int check_end_game(board B)
{
    return 0;
}
void skip()
{

}
void endgame(board B)
{

}
void start_game()
{
    board B;
    B.setup_rect();
    B.setup_board();
    B.render_board();
    SDL_RenderPresent(renderer);
    int i=0;
    while (1)
    {
        if (bonus == 0)
        {
            i ++; if (i > 4) i = 1;
        }
        player_turn(i,B);
        if (check_end_game(B))
        {
            endgame(B);
            return;
        }
    }
}
#endif
