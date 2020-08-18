#include"ai2.h"

#ifndef _FIVE_H
#define _FIVE_H

//#define N 15
#define attack 1 //���ز�������attack���󣬲��������ڽ�������֮�������ڷ��ء�
#define same_u_i SameorNot(row + dx[u] * i, col + dy[u] * i, p[row][col])//u����i����ĵ��Ƿ�ͬɫ
#define OutOrNotEmpty (!InBoardorNot(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //�������̻��߷ǿո��

typedef struct
{
	int point[30] = { -10000, };
	int keyi[30] = { 0 };
	int keyj[30] = { 0 };
	int n;
	int i[30] = { 0 };
	int j[30] = { 0 };
}FIVE,*Five;



typedef struct
{
	int x;
	int y;

}Place;

typedef struct
{
	int i_begini[16] = { 0 };
	int i_beginj[16] = { 0 };
	int i_endi[16] = { 0 };;
	int i_endj[16] = { 0 };
}TRAVERSE,*Traverse;


extern int p[N + 2][N + 2]; //0��1��2��  1�� 2�� -1�� -2��
extern bool is_end;
extern int playoo;
extern int dx[]; //flat����
extern int dy[];//��dx,dy����8����������
extern int manu[2][300];
extern int manukey;//����
extern TRAVERSE tra;//�������׵Ŀ�ʼ���յ�

//��ʼ��
int PrintChessboard(int i, int j);//��ӡ����
void DrawInterface();//��ӡ������Ϸ����
void Initialize();//��Ϸ���ֳ�ʼ��
bool InBoardorNot(int row, int col);//�ж�(row,col)�Ƿ���������
int SameorNot(int row, int col, int key);//�ж�2�������Ƿ�ͬɫ
int number(int row, int col, int u);//���꣨row,col������������u�����ظ÷����ж�������ͬɫ����

//���ֹ���
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

//���㲢�ж��Ƿ�������ж�����λ��
bool GameOverorNot(int row, int col);//(row,col)������֮���Ƿ���Ϸ����
void Play(int row, int col);//����һ��
bool MoveinChessorNot(int row, int col);//�ܷ�����
int point(int row, int col, int play);//�Ǹ���ֵ,1Ϊ���Ӽ��㣬2Ϊ�򵥼���
int MinimaxAlgorithmLevel5(int p4);
int MinimaxAlgorithmLevel4(int p3);
int MinimaxAlgorithmLevel3(int p2);
int MinimaxAlgorithmLevel2(int p1);
void MinimaxAlgorithmLevel1();
void print_manual(); //�������
void player();

//��ʼ���ں���
void GeginRule();//��ʼ����
void BeginAI();// ��ʼ����AI��һ������
int BeginAI2();// ��ʼ����AI�ڶ�������
int BeginAI3(int p2);// ��ʼ����AI����������
void change();//�����ڰ�����
void player_ai2();//ai2����
void Change_pieces();//��������

//����N����
int Get_Nbeats(int who);//����N��
bool whether_end();//�Ƿ������һ��
void changeFIVE(int i, int j, int point);//�޸��б��е���ֵ
void outputFive();//���ѡ�е��������
void ChooseFivepieces1();//ѡ����岽������(�ҷ�����)
void ChooseFivepieces2(int n);//��������ʱ��
void change_two(int &i, int &j);//������������
void Findfivepieces(int n);//Ѱ�ҵ��岽

//��������
void upgrate_traverse(int i, int j);//����������
void init_traverse();//��ʼ��������
void old_FROM_new(TRAVERSE& trav);//�ϵĸ�ֵ
void new_FROM_old(TRAVERSE trav);//�µı���ϵ�

//�������
void Findpieces1(int n);//Ѱ�����ӵĵ�һ�㣬nΪѰ�Ҽ���
int Findpieces2(int p1);//Ѱ�����ӵĵڶ���
void Get_point(int i, int j, int n);//����������������ֵ������
void change_list();//�ݼ��ı����
void FIGHTER();//����ó�����
void init_LIST();//��ʼ������

#endif // !_FIVE_H

