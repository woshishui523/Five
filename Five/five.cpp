#include<iostream>
#include<string>
#include<windows.h>
#include"five.h"
#include"ai2.h"
#include<time.h>
using namespace std;

/*2020.7.25  更改日志
作者：亢佳俊
1.去除禁手规则
2.增加指定开局指定开局黑方第一子为天元，白方第一子和黑方第二子为天元周围5*5棋盘内
3.增加三手交换规则，白二下之前可以交换黑白棋
4.输入输出采用c++，cin，cout格式
5.第一层评价添加进攻变量，以调控下棋策略。
6.对于某些函数名，进行了更改便于理解
*/
/*2020.8.10  
更改人：亢佳俊
1.更改评分增加活二，眠二，活三，眠三评分
*/

int playoo = 1;
int manu[2][300];
int FiveBeat;
int ban_level;
FIVE five;
MATRIX matrix;
TRAVERSE tra;

int PrintChessboard(int i, int j)//打印棋盘
{
	if (p[i][j] == 1)return printf("●");
	if (p[i][j] == 2)return printf("○");
	if (p[i][j] == -1)return printf("▲");
	if (p[i][j] == -2)return printf("△");
	if (i == N)
	{
		if (j == 1)return printf("┏");
		if (j == N)return printf("┓");
		return printf("┯");
	}
	if (i == 1)
	{
		if (j == 1)
			return printf("┗");
		if (j == N)
			return printf("┛");
		return printf("┷");
	}
	if (j == 1)
		return printf("┠");
	if (j == N)
		return printf("┨");
	return printf("┼");
}

void DrawInterface()//打印整个游戏界面
{
	system("cls");  //清屏
	int row = 0, col = 0, keyr = 0, keyc = 0;
	char alpha = 'A';
	cout << endl << endl << endl << "     ";
	for (col = 1; col <= N; col++)
		cout << alpha++ << " "; //标注列号
	for (row = N; row >= 1; row--)
	{
		printf("\n   %2d", row);  //数字宽度为2
		for (col = 1; col <= N; col++)
		{
			PrintChessboard(row, col);  //依次在每个点构图
			if (p[row][col] < 0)
				keyr = row, keyc = col;  //确定最后位置，为三角
		}
		cout << row;
	}
	alpha = 'A';
	cout << endl << "     ";
	for (col = 1; col <= N; col++)cout << alpha++ << " ";
	cout << endl << endl;
	if (s0 == ais)cout << "  我方执黑，对方执白" << endl;
	else cout << "  我方执白，对方执黑" << endl;
	alpha = 'A';
	if (keyr)cout << "  最后落子位置：" << (char)(alpha + keyc - 1) << keyr << endl;
}

void  Initialize()//游戏开局初始化
{
	system("color f0");  //设置窗口背景为f亮白色，字体0为黑色
	cout << "输入1或者2进行选择" << endl << "1、" << "我方先行" << endl << "2、" << "对方先行" << endl;
	cin >> s;
	if (s != 1 && s != 2)
		return Initialize();
	s0 = s;
	int i, j;
	for (i = 0; i <= N + 1; i++)
		for (j = 0; j <= N + 1; j++)
			p[i][j] = 0;//以空格包围棋盘	
	DrawInterface();
	for (j = 0; j < 300; j++)
		manu[0][j] = manu[1][j] = 0;   //棋谱初始化
}

bool InBoardorNot(int row, int col)//判断(row,col)是否在棋盘内
{
	if (row <1 || row > N)return false;
	return col >= 1 && col <= N;
}

int SameorNot(int row, int col, int key)//判断2个棋子是否同色
{
	if (!InBoardorNot(row, col))return false;
	return (p[row][col] == key || p[row][col] + key == 0);
}

int number(int row, int col, int u)//坐标（row,col），方向向量u，返回该方向有多少连续同色棋子
{
	int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
	if (ref == 0)return 0;
	while (SameorNot(i, j, ref))sum++, i += dx[u], j += dy[u];
	return sum;
}

int FreeFourPieces(int row, int col)//落子成活4的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 4; u++)//4个方向，判断每个方向是否落子就成活4  
	{
		int sumk = 1;
		for (i = 1; same_u_i; i++)sumk++;
		if (OutOrNotEmpty)continue; //如果出界就跳过
		for (i = -1; same_u_i; i--)sumk++;
		if (OutOrNotEmpty)continue; //如果出界就跳过
		if (sumk == 4)sum++;
	}
	return sum;
}

int OnetoFivePieces(int row, int col)//成5点的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)//8个成五点的方向
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; same_u_i || flag; i++)
		{
			if (!same_u_i)//该方向的第一个不同色的点，超出边界或者对方棋子或空格
			{
				if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;//该方向的第一个不同色的点是对方棋子,没有成五点
				flag = false;  //再判断完出不同后就跳出循环
			}
			sumk++;                                                                                               
		}
		if (!InBoardorNot(row + dx[u] * --i, col + dy[u] * i))continue;//该方向的第一个不同色的点是超出边界,没有成五点
		for (i = -1; same_u_i; i--)sumk++;
		if (sumk == 4)sum++;
	}
	return sum;
}

int FourPiecesNotFree(int row, int col)//冲4的数量
{
	return OnetoFivePieces(row, col) - FreeFourPieces(row, col) * 2;
}

int SleepThreePieces(int row, int col)//落子成眠3的数量
{

	return OnetoFourPieces(row, col) - FreeThreePieces(row, col)*2;
}

int FreeThreePieces(int row, int col)//落子成活3的数量
{
	int key = p[row][col], sum = 0, i, u, flag = 2;
	for (u = 0; u < 4; u++)//三连的活三
	{
		int sumk = 1;
		for (i = 1; same_u_i; i++)sumk++;
		if (OutOrNotEmpty)continue;
		i++;
		if (OutOrNotEmpty)flag--;
		for (i = -1; same_u_i; i--)sumk++;
		if (OutOrNotEmpty)continue;
		i--;
		if (OutOrNotEmpty)flag--;
		if (sumk == 3 && flag > 0)sum++;
	}
	for (u = 0; u < 8; u++)//8个方向，每个方向最多1个非三连的活三
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; same_u_i || flag; i++)//成活四点的方向
		{
			if (!same_u_i)
			{
				if (flag&&p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
				flag = false;
			}
			sumk++;
		}
		if (OutOrNotEmpty)continue;;
		if (p[row + dx[u] * --i][col + dy[u] * i] == 0)continue;
		for (i = 1; same_u_i; i++)sumk++;
		if (OutOrNotEmpty)continue;;
		if (sumk == 3)sum++;
	}
	return sum;
}

int OnetoFourPieces(int row, int col)//成4点的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)//8个成五点的方向
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; same_u_i || flag; i++)
		{
			if (!same_u_i)//该方向的第一个不同色的点，超出边界或者对方棋子或空格
			{
				if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 8;//该方向的第一个不同色的点是对方棋子,没有成五点
				flag = false;  //再判断完出不同后就跳出循环
			}
			sumk++;
		}
		if (!InBoardorNot(row + dx[u] * --i, col + dy[u] * i))continue;//该方向的第一个不同色的点是超出边界,没有成五点
		for (i = -1; same_u_i; i--)sumk++;
		if (sumk == 3)sum++;
	}
	return sum;
}

int OnetoThreePieces(int row, int col)//成3点的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)//8个成三点的方向
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; same_u_i || flag; i++)
		{
			if (!same_u_i)//该方向的第一个不同色的点，超出边界或者对方棋子或空格
			{
				if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 6;//该方向的第一个不同色的点是对方棋子,没有成三点
				flag = false;  //再判断完出不同后就跳出循环
			}
			sumk++;
		}
		if (!InBoardorNot(row + dx[u] * --i, col + dy[u] * i))continue;//该方向的第一个不同色的点是超出边界,没有成五点
		for (i = -1; same_u_i; i--)sumk++;
		if (sumk == 2)sum++;
	}
	return sum;
}

int FreeTwoPieces(int row, int col)//落子成活2的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 4; u++)//4个方向，判断每个方向是否落子就成活2  
	{
		int sumk = 1;
		for (i = 1; same_u_i; i++)sumk++;
		if (OutOrNotEmpty)continue; //如果出界就跳过
		for (i = -1; same_u_i; i--)sumk++;
		if (OutOrNotEmpty)continue; //如果出界就跳过
		if (sumk == 2)sum++;
	}
	return sum;

}

int SleepTwoPieces(int row, int col)//落子成眠2的数量
{

	return OnetoThreePieces(row, col) - FreeTwoPieces(row, col)*2;

}

int FreeOnePieces(int row, int col)//落子成活1的数量
{
	int key = p[row][col], sum = 0, i, u, flag = 0;
	for (u = 0; u < 4; u++)//三连的活三
	{
		i = 1;
		if (OutOrNotEmpty)continue;
		i = -1;
		if (OutOrNotEmpty)continue;
		flag = 1;
		break;
	}
	
	return flag;
}

bool overline(int row, int col)//长连禁手
{
	for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) > 4)return true;
	return false;
}

bool ban(int row, int col)//判断落子后是否成禁手
{
	if (SameorNot(row, col, 2))return false;//白方无禁手
	return FreeThreePieces(row, col) > 1 || overline(row, col) || FreeFourPieces(row, col) + FourPiecesNotFree(row, col) > 1;
}

bool GameOverorNot(int row, int col)//(row,col)处落子之后是否游戏结束
{
	for (int u = 0; u < 4; u++)
	{
		if (number(row, col, u) + number(row, col, u + 4) >= 4) //正反两个方向求和
			is_end = true;
	}
	if (is_end)
	{
		return true;
	}
	is_end = ban(row, col);
	return is_end;
}

void Play(int row, int col)//落下一子
{
	if (s == s0)p[row][col] = -1; //标出最新下的棋（负数为最新下的棋）
	else p[row][col] = -2;
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++) //取消上一个最新棋的标识
		{
			if (i == row && j == col)continue;
			if (p[i][j] < 0)p[i][j] *= -1;
		}
	}
	DrawInterface();  //刷新屏幕
	if (GameOverorNot(row, col))
	{
		if (s == ais) cout << "我方胜";
		else cout << "对方胜";
		is_end = true;
		Sleep(10000);
	}
	manu[0][manukey] = row, manu[1][manukey++] = col;  //储存完后加一
	upgrate_traverse(row,col);
}

bool MoveinChessorNot(int row, int col)//能否落子
{
	return InBoardorNot(row, col) && (p[row][col] == 0);
}

int point(int row, int col,int play)//非负分值
{
	if (GameOverorNot(row, col))
	{
		is_end = false;
		return 10000;
	}
	int ret, u;
	if (play == 1)
		ret = FreeFourPieces(row, col) * 1000 + (FourPiecesNotFree(row, col) + FreeThreePieces(row, col)) * 100 + (SleepThreePieces(row, col) + FreeTwoPieces(row, col)) * 5 + (SleepTwoPieces(row, col) + FreeOnePieces(row, col));
	if (play == 2)
		ret = FreeFourPieces(row, col) * 50000 + (FourPiecesNotFree(row, col) + FreeThreePieces(row, col)) * 400;
	//给选定点评分 活4*50000+（冲4+活3）*400+ (眠3+活2)*20+ 眠2+ 活1
	for (u = 0; u < 8; u++)
		if (p[row + dx[u]][col + dy[u]])
			ret++;//无效点0分
	return ret;
	
}

int MinimaxAlgorithmLevel5(int p4)
{
	int keyp = -100000, tempp, i, j;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = s0;
			tempp = point(i, j, playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 1000000)
			{
				p[i][j] = 0;
				return 1000000;
			}
			p[i][j] = 0;
			if (tempp - p4 > keyp)keyp = tempp - p4 ;//第三层取极大
			//保留第二层极小值的情况下，加入第三层极大值的影响。
		}
	}
	return keyp;


}

int MinimaxAlgorithmLevel4(int p3)
{
	int keyp = -100000, tempp, i, j;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = s0;
			tempp = point(i, j, playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 1000000)
			{
				p[i][j] = 0;
				return -1000000;
			}
			old_FROM_new(trav);
			upgrate_traverse(i, j);
			tempp = MinimaxAlgorithmLevel5(tempp);  //获得第二层最小和第三层最大的混合评价参数
			new_FROM_old(trav);
			p[i][j] = 0;
			if (tempp + p3 > keyp)keyp = tempp + p3;//第三层取极大
			//保留第二层极小值的情况下，加入第三层极大值的影响。
		}
	}
	return keyp;



}


int MinimaxAlgorithmLevel3(int p2)
{
	int keyp = -100000, tempp, i, j;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = s0;
			tempp = point(i, j, playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 1000000)
			{
				p[i][j] = 0;
				return 1000000;
			}

			old_FROM_new(trav);
			upgrate_traverse(i, j);
			tempp = MinimaxAlgorithmLevel4(tempp);  //获得第二层最小和第三层最大的混合评价参数
			new_FROM_old(trav);
			p[i][j] = 0;
			
			if (tempp - p2 > keyp)keyp = tempp - p2;//第三层取极大
			//保留第二层极小值的情况下，加入第三层极大值的影响。
		}
	}
	return keyp;
}

int MinimaxAlgorithmLevel2(int p1)
{
	int keyp = 100000, tempp, i, j;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = 3 - s0;  //转换为对面棋子
			tempp = point(i, j,playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 1000000)
			{
				p[i][j] = 0;
				return -1000000;
			}

			old_FROM_new(trav);
			upgrate_traverse(i, j);
			tempp = MinimaxAlgorithmLevel3(tempp);  //获得第二层最小和第三层最大的混合评价参数
			new_FROM_old(trav);
			p[i][j] = 0;
			if (tempp + p1< keyp)keyp = tempp + p1;//第二层取极小
		}
	}
	return keyp;
}

void MinimaxAlgorithmLevel1()
{
	DrawInterface();
	cout << "  轮到我方下，请稍候： ";
	if (p[8][8] == 0)return Play(8, 8);  //首先下在天元
	int i, j;
	int keyp = -100000, keyi, keyj, tempp, temp;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))//判断是否有棋子
				continue;
			p[i][j] = s0;
			tempp = point(i, j, playoo); //计算这个点的分数
			temp = tempp;
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}//高效剪枝，避开了无效点
			if (tempp == 1000000)return Play(i, j);
			old_FROM_new(trav);
			upgrate_traverse(i, j);
			tempp = MinimaxAlgorithmLevel2(tempp);  //获得第二层最小和第三层最大的混合评价参数
			new_FROM_old(trav);
			p[i][j] = 0;
			if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//第一层取极大
		}
	}
	return Play(keyi, keyj);
}

void FIGHTER()
{
	bool ok = true;
	int begini, beginj;
	int n = 15,pp;
	DrawInterface();
	init_LIST(n);
	cout << "  轮到我方下，请稍候： ";
	if (p[8][8] == 0)return Play(8, 8);  //首先下在天元
	if (Findpieces1(4)) return;
	init_LIST();
	for (; matrix.n > 1||n>1;)
	{
		for (int i = 1; i <= matrix.n; i++)
		{
			ban_level = 17 - n;
			Get_point(matrix.nb, i);
			if (matrix.point[i] == 10000)
			{
				return Play(matrix.i[i], matrix.j[i]);
			}
			if (matrix.point[i] == -10000)
			{
				change_list(i);
				i--;
			}
			
		}
		n--;
		//for (begini = 1; begini < matrix.n; begini++)
		//{
		//	for (beginj = begini; beginj < matrix.n; beginj++)
		//	{
		//		if (matrix.point[beginj] > matrix.point[beginj + 1])
		//		{
		//			change_two(matrix.point[beginj], matrix.point[beginj + 1]);
		//			for (int num = matrix.nb; num >= matrix.n; num--)
		//			{
		//				pp = num - matrix.n + 1;
		//				change_two(matrix.keyi[pp][beginj], matrix.keyi[pp][beginj + 1]);
		//				change_two(matrix.keyj[pp][beginj], matrix.keyj[pp][beginj + 1]);
		//			}
		//			
		//			change_two(matrix.i[beginj], matrix.i[beginj + 1]);
		//			change_two(matrix.j[beginj], matrix.j[beginj + 1]);
		//			ok = false;
		//		}
		//	}
		//	if (ok == true)
		//		break;
		//	ok = true;
		//}
		//change_list();
	}

	return Play(matrix.i[1], matrix.j[1]);

}

void init_LIST(int n)
{
	for (int i = 1; i <= n; i++)
	{
		matrix.point[i] = -10000;
		matrix.i[i] = 0;
		matrix.j[i] = 0;
		for (int j = 1; j <= n; j++)
		{
			matrix.keyi[i][j] = 0;
			matrix.keyj[i][j] = 0;
		}
	}



}

void init_LIST()
{
	for (int i = 1; i <= matrix.n; i++)
	{
		matrix.i[i] = matrix.keyi[1][i];
		matrix.j[i] = matrix.keyj[1][i];

	}

}

void change_list(int t)
{
	int n = matrix.nb - matrix.n + 2;
	for (int i = t; i < matrix.n; i++)
	{

		matrix.point[i] = matrix.point[i + 1];
		for (int j = 1; j <= n; j++)
		{
			matrix.keyi[j][i] = matrix.keyi[j][i + 1];
			matrix.keyj[j][i] = matrix.keyj[j][i + 1];
		}
		matrix.i[i] = matrix.i[i + 1];
		matrix.j[i] = matrix.j[i + 1];
	}
	matrix.n--;
}

void Get_point(int n,int j)//得到所在行的一个棋子
{
	int tool = 0;
	int keyi, keyj, keyp, n_now = matrix.nb - n + 1;
	bool oddOReven;
	TRAVERSE trav;
	
	if (ban_level == n_now)tool = 2;
	else tool = 0;
	if (tool == 0)//改变队列，和搜索表已经棋盘
	{
		old_FROM_new(trav);
		upgrate_traverse(matrix.keyi[n_now][j], matrix.keyj[n_now][j]);
		if (Judge_oddoroven(n_now))
			p[matrix.keyi[n_now][j]][matrix.keyj[n_now][j]] = s0;
		if (!Judge_oddoroven(n_now))
			p[matrix.keyi[n_now][j]][matrix.keyj[n_now][j]] = 3 - s0;
		Get_point(n - 1, j);
		p[matrix.keyi[n_now][j]][matrix.keyj[n_now][j]] = 0;
		new_FROM_old(trav);
	}
	

	if (tool == 2)
	{
		oddOReven = Judge_oddoroven(n_now);
		Get_finalpoint(keyi, keyj, keyp, oddOReven);
		matrix.keyi[n_now][j] = keyi; 
		matrix.keyj[n_now][j] = keyj;
		matrix.point[j] = keyp;
	}
	 

}

bool Judge_oddoroven(int n)
{
	if (n % 2 == 0)return 0;//0为偶数
	else return 1;

}



void Get_finalpoint(int& keyi,int&keyj,int&keypp,bool minormax)
{
	int tempp, keyp, i, j;
	if (minormax == 0)keyp = 1000000;
	else keyp = -1000000;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			if (minormax == 0)p[i][j] = 3 - s0;  //转换为对面棋子
			else p[i][j] = s0;
			tempp = point(i, j, playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				if (minormax == 0)keyp = -10000;
				if (minormax == 1)keyp = 10000;
				keyi = i;
				keyj = j;
				keypp = keyp;
				p[i][j] = 0;
				return;
			}
			p[i][j] = 0;
			if (-tempp < keyp&&minormax == 0)
			{
				keyp = -(tempp*4);
				keyi = i;
				keyj = j;
			}//第二层取极小
			if (tempp > keyp&&minormax == 1)
			{
				keyp = tempp, keyi = i, keyj = j;//第二层取极大
			}

		}
	}
	keypp = keyp;

}

bool Findpieces1(int n)
{
	matrix.n = n;
	matrix.nb = n;
	int i, j;
	int keyp = -100000, keyi, keyj, tempp, temp;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))//判断是否有棋子
				continue;
			p[i][j] = s0;
			tempp = point(i, j, 1); //计算这个点的分数
			temp = tempp;
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}//高效剪枝，避开了无效点
			if (tempp == 10000)
			{
				Play(i, j); 
				return true;
			}
			old_FROM_new(trav);
			upgrate_traverse(i, j);
			tempp = Findpieces2(tempp);
			if (tempp == -10000) 
			{
				return true;
			}
			new_FROM_old(trav);
			p[i][j] = 0;
			if (tempp > keyp)
			{
				keyp = tempp , keyi = i, keyj = j;//第一层取极大
				changeMATRIX(keyi, keyj, temp);
			}
		} 
	}
	return false;

}

int Findpieces2(int p1)
{
	int keyp = 100000, tempp, i, j, keyi, keyj;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = 3 - s0;  //转换为对面棋子
			tempp = point(i, j, 1);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				p[i][j] = 0;
				Play(i, j);
				return -10000;
			}
			old_FROM_new(trav);
			upgrate_traverse(i, j);
			tempp = Findpieces3(tempp);
			new_FROM_old(trav);
			p[i][j] = 0;
			if (tempp + p1 < keyp)keyp = tempp + p1;//第二层取极小
		}

	}

	return keyp;


}

int Findpieces3(int p2)
{
	int keyp = -100000, tempp, i, j, keyi, keyj;
	TRAVERSE trav;
	for (i = 1; i <= N; i++)
	{
		for (j = tra.i_beginj[i]; j <= tra.i_endj[i]; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = s0;  //转换为对面棋子
			tempp = point(i, j, 1);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				p[i][j] = 0;
				return 10000;
			}
			p[i][j] = 0;
			if (tempp - p2 * 3 > keyp)keyp = tempp - p2 * 3;//第三层取极大eyi = i, keyj = j;//第二层取极小
		}
	}

	return keyp;


}
void Findfivepieces(int n)
{
	five.n = n;
	DrawInterface();
	cout << "  正在寻找第五步，请稍候： ";
	if (p[8][8] == 0)return Play(8, 8);  //首先下在天元
	int i, j;
	int keyp = -100000, keyi, keyj, tempp, temp;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (!MoveinChessorNot(i, j))//判断是否有棋子
				continue;
			p[i][j] = s0;
			tempp = point(i, j); //计算这个点的分数
			temp = tempp;
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}//高效剪枝，避开了无效点
			if (tempp == 1000000)return Play(i, j);
			tempp = AI2();  //获得第二层最小和第三层最大的混合评价参数
			p[i][j] = 0;
			if (tempp + temp * attack > five.point[1])
			{
				keyp = tempp + temp * attack, keyi = i, keyj = j;//第一层取极大
				changeFIVE(keyi, keyj, keyp);
			}
		}
	}
	outputFive();
}

void outputFive()
{
	char alpha = 'A';
	cout << "可选择的棋子为：" << endl;

	for (int i = 1; i <= five.n; i++)
	{
		cout << (char)(alpha + five.keyj[i] - 1) << five.keyi[i] << endl;

	}

}

void change_two(int &i, int &j)
{
	int mid;
	mid = i;
	i = j;
	j = mid;
}

void changeMATRIX(int i, int j, int point)
{
	bool ok = true;
	int n = matrix.nb - matrix.n + 1;
	int begini, beginj;
	if (point >= matrix.point[1])
	{
		matrix.point[1] = point;
		matrix.keyi[n][1] = i;
		matrix.keyj[n][1] = j;
		for (begini = 1; begini < matrix.n; begini++)
		{
			for (beginj = begini; beginj < matrix.n; beginj++)
			{
				if (matrix.point[beginj] > matrix.point[beginj + 1])
				{
					change_two(matrix.point[beginj], matrix.point[beginj + 1]);
					for (int j = 1; j <= n; j++)
					{
						change_two(matrix.keyi[j][beginj], matrix.keyi[j][beginj + 1]);
						change_two(matrix.keyj[j][beginj], matrix.keyj[j][beginj + 1]);
					}
					
					ok = false;
				}
			}
			if (ok == true)
				break;
			ok = true;
		}
	}


}

void changeFIVE(int i,int j,int point)
{
	bool ok = true;
	int begini, beginj;
	if(point>=five.point[1])
	{
		five.point[1] = point;
		five.keyi[1] = i;
		five.keyj[1] = j;
		for (begini = 1; begini < five.n; begini++)
		{
			for (beginj = begini; beginj < five.n; beginj++)
			{
				if (five.point[beginj] > five.point[beginj + 1])
				{
					change_two(five.point[beginj], five.point[beginj + 1]);
					change_two(five.keyi[beginj], five.keyi[beginj + 1]);
					change_two(five.keyj[beginj], five.keyj[beginj + 1]);
					ok = false;
				}
			}
			if (ok == true)
				break;
			ok = true;
		}
	}

}

void print_manual() //输出棋谱
{
	char alpha = 'A';
	int i;
	cout << endl << "  黑方落子位置: ";
	for (i = 0; i < manukey; i += 2)cout << (char)(alpha + manu[1][i] - 1) << (char)manu[0][i];
	cout << endl << "  白子落子位置: ";
	for (i = 1; i < manukey; i += 2)cout << (char)(alpha + manu[1][i] - 1) << (char)manu[0][i];
	Sleep(5000);
}

void player()
{
	DrawInterface();
	cout << "  轮到对方下，请输入坐标(输入=0查看棋谱)： ";
	char c = '\n';
	int row = 0, col = 0;
	while (c < '0')cin >> c >> row;
	if (c == '=')
	{
		print_manual();
		return player();
	}
	if (c < 'a')col = c - 'A' + 1;  //区分大小写，计算列数
	else col = c - 'a' + 1;
	if (!MoveinChessorNot(row, col))
	{
		cout << "此处不能下";
		Sleep(1000);
		return player();
	}
	Play(row, col);
}

void Change_pieces()
{
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			switch (p[i][j])
			{
			case  1:
				p[i][j] = 2;
			case  2:
				p[i][j] = 1;
			case  -1:
				p[i][j] = -2;
			case  -2:
				p[i][j] = -1;
			}

		}

	}

}

int BeginAI3(int p2)
{
	int keyp = -100000, tempp;
	for (int i = 6; i <= 10; i++)
	{
		for (int j = 6; j <= 10; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = s0;
			tempp = point(i, j, playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				p[i][j] = 0;
				return 10000;
			}
			p[i][j] = 0;
			if (tempp - p2 * 2 > keyp)keyp = tempp - p2 * 2;//第三层取极大
			//保留第二层极小值的情况下，加入第三层极大值的影响。
		}
	}
	return keyp;



}

int BeginAI2()
{
	int keyp = 100000, tempp;
	for (int i = 6; i <= 10; i++)
	{
		for (int j = 6; j <= 10; j++)
		{
			if (!MoveinChessorNot(i, j))continue;
			p[i][j] = 3 - s0;  //转换为对面棋子
			tempp = point(i, j, playoo);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}
			if (tempp == 10000)
			{
				p[i][j] = 0;
				return -10000;
			}
			tempp = BeginAI3(tempp);
			p[i][j] = 0;
			if (tempp < keyp)keyp = tempp;//第二层取极小
		}
	}
	return keyp;


}

void BeginAI()
{
	DrawInterface();
	cout << "开局黑方第一子为天元，白方第一子和黑方第二子为天元周围5 * 5棋盘内" << endl;
	cout << "  轮到我方下，请稍候： ";
	if (p[8][8] == 0)return Play(8, 8);  //首先下在天元
	int i, j;
	int keyp = -100000, keyi, keyj, tempp, temp;
	for (i = 6; i <= 10; i++)
	{
		for (j = 6; j <= 10; j++)
		{
			if (!MoveinChessorNot(i, j))//判断是否有棋子
				continue;
			p[i][j] = s0;
			tempp = point(i, j, playoo);  //计算这个点的分数
			temp = tempp;
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}//高效剪枝，避开无效点
			if (tempp == 10000)return Play(i, j);
			tempp = BeginAI2();  //获得第二层最小和第三层最大的混合评价参数
			p[i][j] = 0;
			if (tempp + temp * attack > keyp)keyp = tempp + temp * attack, keyi = i, keyj = j;//第一层取极大
		}
	}
	return Play(keyi, keyj);



}

void GeginRule()/*开始环节（指定开局黑方第一子为天元，
  白方第一子和黑方第二子为天元周围5*5棋盘内,执行五手N打）*/
{
	int mid,who,FiveBeat;
	int i = 1;
	memset(five.point, -10000, sizeof(five.point));
	if (s == ais)who = 0;
	else who = 1;
	FiveBeat = Get_Nbeats(who);
	for (i = 1; i <= 3; i++)
	{
		if (s == ais)BeginAI();
		else player(); 
		s = 3 - s;//换下棋方
	}
	cout << "是否交换黑白棋(1为是，0为不是)" << endl;
	cin >> mid;
	if (mid == 1)
	{
		change();

	}
	for (; i < 5; i++)
	{
		if (s == ais)FIGHTER();
		else player();
		s = 3 - s;//换下棋方
	}
	if (s == ais)Findfivepieces(FiveBeat),ChooseFivepieces1();
	else ChooseFivepieces2(FiveBeat);

	s = 3 - s;

}

void ChooseFivepieces2(int n)
{
	int score;
	cout << "对方提供的位置为：";
	char c = '\n';
	int row = 0, col = 0;
	for (int p = 1; p<= n; p++)
	{
		cout << "第" << p << "个棋子为：";
		cin >> c >> row;
		if (c < 'a')col = c - 'A' + 1;  //区分大小写，计算列数
		else col = c - 'a' + 1;
		cout << endl;
		score = point(row, col, 1);
		changeFIVE(row, col, score);
	}
	Play(five.keyi[1], five.keyj[1]);


}

void ChooseFivepieces1()
{
	cout << "对方选择的棋子为：";
	char c = '\n';
	int row = 0, col = 0;
	while (c < '0')cin >> c >> row;
	if (c < 'a')col = c - 'A' + 1;  //区分大小写，计算列数
	else col = c - 'a' + 1;
	Play(row, col);
}

void change()
{
	s0 = 3 - s0;
	s = 3 - s;
}

int Get_Nbeats(int who)
{
	cout << "五手N打棋子数为" << endl;
	if (who == 0)//如果是我方选择
	{
		cout << "3";
		getchar();
		getchar();
		return 3;

	}
	if (who == 1)//如果是对方选择
	{
		cin >> FiveBeat;
		return FiveBeat;
	}

	return 0;
}

bool whether_end()
{
	bool coutinue;
	cout << "是否进行下一局" << "0结束，1进行下一局" << endl;
	cin >> coutinue;
	return coutinue;
}

void init_traverse()
{
	for (int i = 1; i <= 15; i++)
	{
		tra.i_begini[i] = 8;
		tra.i_beginj[i] = 8;
		tra.i_endi[i] = 8;
		tra.i_endj[i] = 8;
	}
}

void upgrate_traverse(int i,int j)
{
	Place a[11];
	a[1].x = i - 2, a[1].y = j - 2;
	a[2].x = i - 1, a[2].y = j - 1;
	a[3].x = i, a[3].y = j - 2; 
	a[4].x = i + 1, a[4].y = j - 1;
	a[5].x = i + 2, a[5].y = j - 2;
	a[6].x = i - 2, a[6].y = j + 2;
	a[7].x = i - 1, a[7].y = j + 1;
	a[8].x = i, a[8].y = j + 2;
	a[9].x = i + 1, a[9].y = j + 1;
	a[10].x = i + 2, a[10].y = j + 2;
	for (int i = 1; i <= 5; i++)
	{
		if (a[i].y < tra.i_beginj[a[i].x] && a[i].y >= 1 && a[i].x <= 15 && a[i].x >= 1)
			tra.i_beginj[a[i].x] = a[i].y;
		if (a[i + 5].y > tra.i_endj[a[i + 5].x] && a[i + 5].y <= 15 && a[i + 5].x <= 15 && a[i + 5].x >= 1)
			tra.i_endj[a[i + 5].x] = a[i + 5].y;
	}

}

void old_FROM_new(TRAVERSE& trav)//老的赋值
{
	for (int i = 1; i <= 15; i++)
	{
		trav.i_begini[i] = tra.i_begini[i];
		trav.i_beginj[i] = tra.i_beginj[i];
		trav.i_endi[i] = tra.i_endi[i];
		trav.i_endj[i] = tra.i_endj[i];

	}

}

void new_FROM_old(TRAVERSE trav)//新的变回老的
{
	for (int i = 1; i <= 15; i++)
	{
		tra.i_begini[i] = trav.i_begini[i];
		tra.i_beginj[i] = trav.i_beginj[i];
		tra.i_endi[i] = trav.i_endi[i];
		tra.i_endj[i] = trav.i_endj[i];

	}

}

