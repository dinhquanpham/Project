#ifndef _GAMEPLAY_H
#define _GAMEPLAY_H
#include <bits/stdc++.h>
#include "display.h"
#include "board.h"
#include <SDL_ttf.h>
#include <SDL.h>


using namespace std;

int exitt=0;

int bonus;

extern int is_bot[4]={0,0,0,0};

int roll_dice()
{
    int z = rand() % 4 + 1;
    int num = rand() % 6 + 1;
    if(z == 1)
    {
        num = 6;
    }
     SDL_Event event;
//    while (1)
//    {
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_KEYDOWN)
//            {
//                if (event.key.keysym.sym > '9' || event.key.keysym.sym < '0') continue;
//                num = event.key.keysym.sym - '0';
//                return num;
//            }
//        }
//    }
//    render_text(to_string(num),{100,200,20,20},20);
    while(1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                if(check_click(roll_button,x,y))
                {
                    return num;
                }
            }
        }
    }

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
        //pos = nextt(i,pos);
        if (pos == 14 * (i - 1) + 1 || pos > 56)
        {
            if (pos - 56 >= n) return 0;
            while (pos - 56 < n)
            {
                for (int b = 1; b <= 4; b++)
                    if (b != j)
                        if (B.pos[i][b] == pos) return 0;
                pos = nextt(i , pos);
            }
            dest = pos;
            //// cerr << dest << endl;
        }

        else
            {
               // n--;
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
                //cerr << dest << endl;
                if (dest > 56) return 0;
            }
    }
    for (int k = 1; k <= 4; k ++)
        if (k != j && B.pos[i][k] == dest) return 0;
    return 1;
}

void player_turn(int i, board &B)
{
    /// LƯỢT CỦA NGƯỜI CHƠI
    SDL_RenderClear(renderer);
    SDL_Event event;
    SDL_Rect background_rect = {0,0,1080,700};
    SDL_RenderCopy(renderer,t_background[1], NULL, &background_rect);
    SDL_RenderCopy(renderer,t_rollbutton[1], NULL, &roll_button);
    for (int k = 1;k <= 4; k++)
        for (int j = 1;j <= 4; j++)
        B.isbright[k][j] = 0;
    B.render_board();
    int num = roll_dice();
    if (num == 6) bonus = 1; else bonus = 0;
    SDL_RenderPresent(renderer);
    for (int j = 1;j <= 4; j ++)
    {
        if (check(B,i,j,num))
        {
            B.isbright[i][j] = 1;
        }
    }
    B.render_board();
    string st = "player " + to_string(i) + ":  " + to_string(num);
    render_text(st,{100,200,50,20},20);
    SDL_RenderCopy(renderer, t_triangle[1], NULL, &B.triangle[i]);
    /// sinh xúc xắc
    SDL_Rect dice_dest = {100,250,100,80};
    SDL_Rect dice_scr = {(num - 1) * 200,0,200,200};
    SDL_RenderCopy(renderer, t_dice[1], &dice_scr, &dice_dest);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    /// phát sáng quân mã có thể di chuyển
     vector <int> V;
    for (int j = 1;j <= 4; j ++)
        if (B.isbright[i][j] == 1)
            V.push_back(j);
    for (int j = 0;j < V .size();j ++)
        for (int k = j + 1; k < V.size(); k ++)
            if (B.horse_rect[i][V[j]].y  <  B.horse_rect[i][V[k]].y) swap(V[j],V[k]);
    if (V.size() == 0) return;

    /// CHỌN QUÂN MÃ ĐỂ DI CHUYỂN
//    if(i == 1)
//    {
        while (1)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                   // cerr<< i << ' ' << x << ',' << y << endl;
                    for (int j:V)
                    {
                        if (check_click(B.horse_rect[i][j],x,y))
                        {
                            /// XUẤT CHUỒNG
                            if (B.pos[i][j] == 0)
                            {
                                B.move_next(i,j);
                                return;
                            }
                            /// LÊN GOAL
                            if (B.pos[i][j] > 56)
                            {
                                int n = 56 + num - B.pos[i][j];
                                for (int k = 1; k <= n; k ++)
                                    B.move_next(i,j);
                                return;
                            }
                            /// DI CHUYỂN THƯỜNG
                            for (int k = 1; k <= num; k++)
                            {
                                B.move_next(i,j);
                            }
                            return;
                        }
                    }
                    /// SKIP BUTTON
                    if (check_click(skip_button_rect,x,y))
                    {
                        bonus = 0;
                        return;
                    }

                }
            }
        }
//    }

    /// con BOT ngu

//    else
//    {
//        for (int j:V)
//        {
//                /// XUẤT CHUỒNG
//                if (B.pos[i][j] == 0)
//                {
//                    B.move_next(i,j);
//                    return;
//                }
//                /// LÊN GOAL
//                if (B.pos[i][j] > 56)
//                {
//                    int n = 56 + num - B.pos[i][j];
//                    for (int k = 1; k <= n; k ++)
//                        B.move_next(i,j);
//                    return;
//                }
//                /// DI CHUYỂN THƯỜNG
//                for (int k = 1; k <= num; k++)
//                {
//                    B.move_next(i,j);
//                }
//                return;
//        }
//    }
}



/*
void showtime()
{

}
*/

int check_end_game(board B,int i)
{
    int exist[7];
    memset(exist, 0, sizeof(exist));
    for (int j = 1; j <= 4; j ++)
    {
        if(B.pos[i][j] > 56) exist[B.pos[i][j] - 56] = 1;
    }
    for (int k = 3; k <= 6; k ++)
        if (exist[k] == 0) return 0;
        return 1;
//    cout << check_end[i] << " ";
}

void start_game()
{
    exitt = 0;
    board B;
    B.setup_rect();
    B.setup_board();
    B.render_board();

    SDL_RenderPresent(renderer);
    int i = 0;
    while (1)
    {
        if (bonus == 0)
        {
            i ++; if (i > 4) i = 1;
        }
        player_turn(i,B);

        if (exitt == 1) return;

        if (check_end_game(B,i) == 1)
        {
            B.endgame();
            SDL_Delay(5000);
            return;
        }
    }
}
#endif
