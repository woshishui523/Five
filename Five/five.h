#include"ai2.h"

#ifndef _FIVE_H
#define _FIVE_H

//#define N 15
#define attack 1 //攻守参数，当attack增大，策略趋近于进攻，反之，趋近于防守。
#define same_u_i SameorNot(row + dx[u] * i, col + dy[u] * i, p[row][col])//u方向i距离的点是否同色
#define OutOrNotEmpty (!InBoardorNot(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //出了棋盘或者非空格点

extern int p[N + 2][N + 2]; //0空1黑2白  1● 2○ -1▲ -2△
extern bool is_end;
extern int playoo;
extern int dx[]; //flat技术
extern int dy[];//（dx,dy）是8个方向向量
extern int manu[2][300];
extern int manukey;//棋谱


int PrintChessboard(int i, int j);//打印棋盘
void DrawInterface();//打印整个游戏界面
void Initialize();//游戏开局初始化
bool InBoardorNot(int row, int col);//判断(row,col)是否在棋盘内
int SameorNot(int row, int col, int key);//判断2个棋子是否同色
int number(int row, int col, int u);//坐标（row,col），方向向量u，返回该方向有多少连续同色棋子
int FreeFourPieces(int row, int col);//落子成活4的数量
int OnetoFivePieces(int row, int col);//成5点的数量
int FourPiecesNotFree(int row, int col);//冲4的数量
int FreeThreePieces(int row, int col);//落子成活3的数量
int FreeOnePieces(int row, int col);//落子成活1的数量
int SleepTwoPieces(int row, int col);//落子成眠2的数量
int FreeTwoPieces(int row, int col);//落子成活2的数量
int SleepThreePieces(int row, int col);	//落子成眠3的数量
int OnetoFourPieces(int row, int col);//成4点的数量
int OnetoThreePieces(int row, int col);//成3点的数量
bool GameOverorNot(int row, int col);//(row,col)处落子之后是否游戏结束
void Play(int row, int col);//落下一子
bool MoveinChessorNot(int row, int col);//能否落子
int point(int row, int col, int play);//非负分值
int MinimaxAlgorithmLevel5(int p4);
int MinimaxAlgorithmLevel4(int p3);
int MinimaxAlgorithmLevel3(int p2);
int MinimaxAlgorithmLevel2(int p1);
void MinimaxAlgorithmLevel1();
void print_manual(); //输出棋谱
void player();
void GeginRule();//开始环节
void BeginAI();// 开始环节AI第一层下棋
int BeginAI2();// 开始环节AI第二层下棋
int BeginAI3(int p2);// 开始环节AI第三层下棋
void change();//交换黑白棋子
void player_ai2();//ai2下棋
void Change_pieces();//交换棋子

#endif // !_FIVE_H

