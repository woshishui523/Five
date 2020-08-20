#include"ai2.h"

#ifndef _FIVE_H
#define _FIVE_H

//#define N 15
#define attack 1 //攻守参数，当attack增大，策略趋近于进攻，反之，趋近于防守。
#define same_u_i SameorNot(row + dx[u] * i, col + dy[u] * i, p[row][col])//u方向i距离的点是否同色
#define OutOrNotEmpty (!InBoardorNot(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //出了棋盘或者非空格点

typedef struct
{
	int point[30] = { -10000, };
	int keyi[30] = { 0 };
	int keyj[30] = { 0 };
	int n;
}FIVE,*Five;

typedef struct
{
	int point[30] = { -10000, };
	int keyi[30][30] = { 0 };
	int keyj[30][30] = { 0 };
	int n,nb;//n 为所在层数的元素个数，nb是第一层元素个数
	int i[30] = { 0 };
	int j[30] = { 0 };


}MATRIX,*Matrix;



typedef struct
{
	int x;
	int y;

}Place;

typedef struct
{
	int i_begini[16] = { 0 };
	int i_beginj[16] = { 0 };
	int i_endi[16] = { 0 };
	int i_endj[16] = { 0 };
}TRAVERSE,*Traverse;


extern int p[N + 2][N + 2]; //0空1黑2白  1● 2○ -1▲ -2△
extern bool is_end;
extern int playoo;
extern int dx[]; //flat技术
extern int dy[];//（dx,dy）是8个方向向量
extern int manu[2][300];
extern int manukey;//棋谱
extern TRAVERSE tra;//遍历棋谱的开始和终点

//初始化
int PrintChessboard(int i, int j);//打印棋盘
void DrawInterface();//打印整个游戏界面
void Initialize();//游戏开局初始化
bool InBoardorNot(int row, int col);//判断(row,col)是否在棋盘内
int SameorNot(int row, int col, int key);//判断2个棋子是否同色
int number(int row, int col, int u);//坐标（row,col），方向向量u，返回该方向有多少连续同色棋子

//评分规则
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

//计算并判断是否结束来判断下棋位置
bool GameOverorNot(int row, int col);//(row,col)处落子之后是否游戏结束
void Play(int row, int col);//落下一子
bool MoveinChessorNot(int row, int col);//能否落子
int point(int row, int col, int play);//非负分值,1为复杂计算，2为简单计算

//暂时未用到函数
int MinimaxAlgorithmLevel5(int p4);
int MinimaxAlgorithmLevel4(int p3);
int MinimaxAlgorithmLevel3(int p2);
int MinimaxAlgorithmLevel2(int p1);
void MinimaxAlgorithmLevel1();
void print_manual(); //输出棋谱
void player();

//开始环节函数
void GeginRule();//开始环节
void BeginAI();// 开始环节AI第一层下棋
int BeginAI2();// 开始环节AI第二层下棋
int BeginAI3(int p2);// 开始环节AI第三层下棋
void change();//交换黑白棋子
void Change_pieces();//交换棋子

//五手N打函数
int Get_Nbeats(int who);//五手N打
bool whether_end();//是否进行下一局
void changeFIVE(int i, int j, int point);//修改列表中的数值
void outputFive();//输出选中的五个棋子
void ChooseFivepieces1();//选择第五步的棋子(我方黑棋)
void ChooseFivepieces2(int n);//对面黑棋的时候
void change_two(int &i, int &j);//交换两个整数
void Findfivepieces(int n);//寻找第五步

//搜索表函数
void upgrate_traverse(int i, int j);//更新搜索表
void init_traverse();//初始化搜索表
void old_FROM_new(TRAVERSE& trav);//老的赋值
void new_FROM_old(TRAVERSE trav);//新的变回老的

//广度搜索
bool Findpieces1(int n);//寻找棋子的第一层，n为寻找几个
int Findpieces2(int p1);//寻找棋子的第二层
int Findpieces3(int p2);//寻找棋子的第三层
void Get_point(int n,int j);//计算各层分数，并赋值给队列,n为个数，j为第几个
void change_list(int t);//递减改变队列
void FIGHTER();//计算得出棋子
void init_LIST();//初始化队列i，j
bool Judge_oddoroven(int n);//判断奇偶函数
void init_LIST(int n);//初始化队列分数
void changeMATRIX(int i, int j, int point);//改变matrix的排序
void Get_finalpoint(int& keyi, int&keyj, int&keypp, bool minormax);//计算得分函数
#endif // !_FIVE_H

