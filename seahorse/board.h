#ifndef _BOARD_H
#define _BOARD_H
#include <bits/stdc++.h>
#include "display.h"
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;
typedef pair <int,int> pp;
bool cmp(const pair <SDL_Rect,pp> a,const pair <SDL_Rect,pp> b)
{
    return (a.first.y < b.first.y);
}
int nextt(int i,int pos)
{
    if (pos == 56+6) return pos;
    if (pos == 0) return (i - 1) * 14 + 2;
    if (pos == 56) return 1;
    if (pos == (i-1)*14+1) return 57;
    return pos + 1;
}
struct board
{
    //vi tri 16 con ma
    int pos[5][5],isbright[5][5];
    SDL_Rect start[5][5],goal[5][7],tile[100],horse_rect[5][5],triangle[5];
    void setup_rect()
    {
          // ô di chuyển của mã xanh dương
        tile[1] = {699,46,55,85};
        tile[2] = {645,46,55,85};
        for (int i = 2 ; i <= 8; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].y = tile[i].y + 33;
        }
        for (int i = 8; i <= 14; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].x = tile[i].x - 33;
        }
        // ô di chuyển của mã vàng
        tile[15]={447,301,55,85};
        tile[16]={447,351,55,85};
        for (int i = 16 ;i <= 22; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].x = tile[i].x + 33;
        }
        for (int i = 22; i <= 28; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].y = tile[i].y + 33;
        }
        // ô di chuyển của mã xanh lá cây
        tile[29]={695,549,55,85};
        tile[30]={749,549,55,85};
        for (int i = 30; i <= 36; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].y = tile[i].y - 33;
        }
        for (int i = 36; i <= 42; i++)
        {
            tile [i + 1] = tile[i];
            tile [i + 1].x = tile[i].x + 33;
        }
        // ô di chuyển của mã đỏ
        tile[43]={948,297,55,85};
        tile[44]={948,244,55,85};
        for (int i = 44; i <= 50; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].x = tile[i].x - 33;
        }
        for (int i = 50; i <= 56; i++)
        {
            tile[i + 1] = tile[i];
            tile[i + 1].y = tile[i].y - 33;
        }
        // tọa độ các con mã trong chuồng xanh dương
        start[1][1] = {513,120,55,85};
        start[1][2] = {570,120,55,85};
        start[1][3] = {513,180,55,85};
        start[1][4] = {570,180,55,85};
        // tọa độ các con mã trong chuồng vàng
        start[2][1] = {513,440,55,85};
        start[2][2] = {570,440,55,85};
        start[2][3] = {513,490,55,85};
        start[2][4] = {570,490,55,85};
        // tọa độ các con mã trong chuồng xanh lá
        start[3][1] = {825,440,55,85};
        start[3][2] = {882,440,55,85};
        start[3][3] = {825,490,55,85};
        start[3][4] = {882,490,55,85};
        // tọa độ các con mã trong chuồng đỏ
        start[4][1] = {825,120,55,85};
        start[4][2] = {882,120,55,85};
        start[4][3] = {825,180,55,85};
        start[4][4] = {885,180,55,85};
        // tọa độ lên chuồng xanh dương
        goal[1][1] = {699,79,55,85};
        for (int i = 1; i < 6; i++)
        {
            goal[1][i+1] = goal[1][i];
            goal[1][i+1].y = goal[1][i].y + 33;
        }
        // tọa độ lên chuồng vàng
        goal[2][1]={480,301,55,85};
        for (int i = 1; i < 6; i++)
        {
            goal[2][i+1] = goal[2][i];
            goal[2][i+1].x = goal[2][i].x + 33;
        }
        // tọa độ lên chuồng xanh lá
        goal[3][1] = {695,516,55,85};
        for (int i = 1; i < 6; i++)
        {
            goal[3][i+1] = goal[3][i];
            goal[3][i+1].y = goal[3][i].y - 33;
        }
        // tọa độ lên chuồng đỏ
        goal[4][1] = {915,297,55,85};
         for (int i = 1; i < 6; i++)
        {
            goal[4][i+1] = goal[4][i];
            goal[4][i+1].x = goal[4][i].x - 33;
        }
        // tọa độ triangle button
        triangle[1] = {515,77,30,30};
        triangle[2] = {515,589,30,30};
        triangle[3] = {830,589,30,30};
        triangle[4] = {830,77,30,30};
    }
    // tạo bàn cờ
    void setup_board()
    {
        for (int i = 1; i <= 4; i ++)
            for (int j = 1; j <= 4; j ++)
            {
                pos[i][j] = isbright[i][j]=0;
                horse_rect[i][j] = start[i][j];
            }
    }
    void render_board()
    {
        SDL_RenderClear(renderer);
        SDL_Rect z={0,0,1080,700};
        SDL_RenderCopy(renderer, t_background[1], NULL,&z);
        SDL_Rect r={428,50,600,600};
        SDL_RenderCopy(renderer, t_map, NULL, &r);
        vector <pair <SDL_Rect,pp > > V;
        for (int i=1; i<=4; i++)
        {
            for (int j=1; j<=4; j++)
                V.push_back({horse_rect[i][j],{i,j}});
        }
        sort(V.begin(),V.end(),cmp);
        // in mã ra màn hình
        for (int k = 0; k < V.size() ;k++)
        {
            int i = V[k].second.first;
            int j = V[k].second.second;
            if (isbright[i][j] == 0) SDL_RenderCopy(renderer, t_horse[i],NULL, &horse_rect[i][j]);
            else SDL_RenderCopy(renderer, t_bright[i],NULL, &horse_rect[i][j]);
        }
        SDL_RenderPresent(renderer);

    }
    void move_next(int i, int j)
    {
        SDL_Rect a = horse_rect[i][j];
        SDL_Rect b;
        if (pos[i][j] - 56 == 6) return;
        pos[i][j] = nextt(i, pos[i][j]);
        if (pos[i][j] == 0) b = start[i][j];
            else
                if (pos[i][j] > 56) b = goal[i][pos[i][j] - 56];
                else b = tile[pos[i][j]];

        int num = 20;
        while (num > 0)
        {
            int dx = (b.x - a.x)/num;
            int dy=(b.y - a.y)/num;
            a.x += dx; a.y += dy;
            horse_rect[i][j] = a;
            render_board();
            SDL_Delay(5);
            num--;
        }
        for (int p = 1;p <= 4; p++)
            if (p != i)
        /// đang bị sai
        for (int k = 1;k <= 4; k++)
            if (pos[p][k] == pos[i][j])
            {
                pos[p][k] = 0;
                SDL_Rect a = horse_rect[p][k];
                SDL_Rect b = start[p][k];
                int num = 20;
                while (num > 0)
                {
                    int dx = (b.x - a.x)/num;
                    int dy=(b.y - a.y)/num;
                    a.x += dx;a.y += dy;
                    horse_rect[p][k] = a;
                    render_board();
                    SDL_Delay(5);
                    num --;
                }
            }
    }
    void move_horse(int i, int j, int num)
    {
        while (num --)
        {
            move_next(i,j);
        }
    }

    //more
    void endgame()
    {

    }
};
#endif
