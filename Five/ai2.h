#include <stdio.h>
#include<string>
#include<windows.h>

#ifndef _A_H
#define _A_H

#define N 15
#define samep same(row + dx[u] * i, col + dy[u] * i, p[row][col])
#define off if(!inboard(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0)continue;


extern int p[N + 2][N + 2]; //0空1黑2白  1●2○ -1▲-2△
extern int s, ais, s0;//s是轮到谁下,s=1,2，s=1是ai下，s=2是玩家，s=s0是黑方下，否则是白方下
extern int dx[]; //flat技术
extern bool is_en;
extern int dy[];//（dx,dy）是8个方向向量
extern int  manukey;

int out(int i, int j);
void DrawBoard();//画棋盘
bool inboard(int row, int col);//是否在棋盘内
int same(int row, int col, int key);//判断2个棋子是否同色
int num(int row, int col, int u);//坐标（row,col），方向向量u
int live4(int row, int col);//活4的数量
int chong4(int row, int col);//冲4的数量
int live3(int row, int col);//活3的数量
bool end_(int row, int col);//(row,col)处落子之后是否游戏结束
void go(int row, int col);//落下一子
bool ok(int row, int col);//能否落子
int point(int row, int col);//非负分值
int AI3(int p2);
int AI2();
void AI();


#endif // !A2

