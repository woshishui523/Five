#pragma once
#include""
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
void out_manual();
void player();


