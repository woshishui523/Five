#pragma once
#include"five.h"
#include""


int PrintChessboard(int i, int j);//��ӡ����
void DrawInterface();//��ӡ������Ϸ����
void Initialize();//��Ϸ���ֳ�ʼ��
bool InBoardorNot(int row, int col);//�ж�(row,col)�Ƿ���������
int SameorNot(int row, int col, int key);//�ж�2�������Ƿ�ͬɫ
int number(int row, int col, int u);//���꣨row,col������������u�����ظ÷����ж�������ͬɫ����
int FreeFourPieces(int row, int col);//���ӳɻ�4������
int OnetoFivePieces(int row, int col);//��5�������
int FourPiecesNotFree(int row, int col);//��4������
int FreeThreePieces(int row, int col);//���ӳɻ�3������
int FreeOnePieces(int row, int col);//���ӳɻ�1������
int SleepTwoPieces(int row, int col);//���ӳ���2������
int FreeTwoPieces(int row, int col);//���ӳɻ�2������
int SleepThreePieces(int row, int col);	//���ӳ���3������
int OnetoFourPieces(int row, int col);//��4�������
int OnetoThreePieces(int row, int col);//��3�������
bool GameOverorNot(int row, int col);//(row,col)������֮���Ƿ���Ϸ����
void Play(int row, int col);//����һ��
bool MoveinChessorNot(int row, int col);//�ܷ�����
int point(int row, int col,int play);//�Ǹ���ֵ
int MinimaxAlgorithmLevel5(int p4);
int MinimaxAlgorithmLevel4(int p3);
int MinimaxAlgorithmLevel3(int p2);
int MinimaxAlgorithmLevel2(int p1);
void MinimaxAlgorithmLevel1();
void print_manual(); //�������
void player();
void GeginRule();//��ʼ����
void BeginAI();// ��ʼ����AI��һ������
int BeginAI2();// ��ʼ����AI�ڶ�������
int BeginAI3(int p2);// ��ʼ����AI����������
void change();//�����ڰ�����
void player_ai2();//ai2����
void Change_pieces();//��������
