#pragma once
#include""
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
void out_manual();
void player();


