#include <stdio.h>
#include<string>
#include<windows.h>

#ifndef _A_H
#define _A_H

#define N 15
#define samep same(row + dx[u] * i, col + dy[u] * i, p[row][col])
#define off if(!inboard(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0)continue;


extern int p[N + 2][N + 2]; //0��1��2��  1��2�� -1��-2��
extern int s, ais, s0;//s���ֵ�˭��,s=1,2��s=1��ai�£�s=2����ң�s=s0�Ǻڷ��£������ǰ׷���
extern int dx[]; //flat����
extern bool is_en;
extern int dy[];//��dx,dy����8����������
extern int  manukey;

int out(int i, int j);
void DrawBoard();//������
bool inboard(int row, int col);//�Ƿ���������
int same(int row, int col, int key);//�ж�2�������Ƿ�ͬɫ
int num(int row, int col, int u);//���꣨row,col������������u
int live4(int row, int col);//��4������
int chong4(int row, int col);//��4������
int live3(int row, int col);//��3������
bool end_(int row, int col);//(row,col)������֮���Ƿ���Ϸ����
void go(int row, int col);//����һ��
bool ok(int row, int col);//�ܷ�����
int point(int row, int col);//�Ǹ���ֵ
int AI3(int p2);
int AI2();
void AI();


#endif // !A2

