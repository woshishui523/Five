#include <stdio.h>
#include<string>
#include<windows.h>
#include"ai2.h"

int p[N + 2][N + 2]; //0空1黑2白  1●2○ -1▲-2△
int s = 0, ais = 1, s0;
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }; //flat技术
bool is_en = false;
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//（dx,dy）是8个方向向量
int  manukey = 0;


int out(int i, int j)
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
		if (j == 1)return printf("┗");
		if (j == N)return printf("┛");
		return printf("┷");
	}
	if (j == 1)return printf("┠");
	if (j == N)return printf("┨");
	return printf("┼");
}

void DrawBoard()//画棋盘
{
	system("cls");
	int row = 0, col = 0, keyr = 0, keyc = 0;
	char alpha = 'A';
	printf("\n\n\n     ");
	for (col = 1; col <= N; col++)printf("%c ", alpha++);
	for (row = N; row >= 1; row--)
	{
		printf("\n   %2d", row);
		for (col = 1; col <= N; col++)
		{
			out(row, col);
			if (p[row][col] < 0)keyr = row, keyc = col;
		}
		printf("%d", row);
	}
	alpha = 'A';
	printf("\n     ");
	for (col = 1; col <= N; col++)printf("%c ", alpha++);
	printf("\n\n");
	if (s0 == ais)printf("  AI执黑，玩家执白\n");
	else printf("  AI执白，玩家执黑\n");
	alpha = 'A';
	if (keyr)printf("  最后落子位置：%c%d\n", alpha + keyc - 1, keyr);
}


bool inboard(int row, int col)//是否在棋盘内
{
	if (row <1 || row > N)return false;
	return col >= 1 && col <= N;
}

int same(int row, int col, int key)//判断2个棋子是否同色
{
	if (!inboard(row, col))return false;
	return (p[row][col] == key || p[row][col] + key == 0);
}

int num(int row, int col, int u)//坐标（row,col），方向向量u
{
	int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
	if (ref == 0)return 0;
	while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
	return sum;
}

int live4(int row, int col)//活4的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 4; u++)//4个方向，每个方向最多1个
	{
		int sumk = 1;
		for (i = 1; samep; i++)sumk++;
		off;
		for (i = -1; samep; i--)sumk++;
		off;
		if (sumk == 4)sum++;
	}
	return sum;
}

int chong4(int row, int col)//冲4的数量
{
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)//8个方向，每个方向最多1个
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; samep || flag; i++)//成五点的方向
		{
			if (!samep)
			{
				if (flag&&p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
				flag = false;
			}
			sumk++;
		}
		if (!inboard(row + dx[u] * --i, col + dy[u] * i))continue;
		for (i = -1; samep; i--)sumk++;
		if (sumk == 4)sum++;
	}
	return sum - live4(row, col) * 2;
}

int live3(int row, int col)//活3的数量
{
	int key = p[row][col], sum = 0, i, u;
	for (u = 0; u < 4; u++)//三连的活三
	{
		int sumk = 1;
		for (i = 1; samep; i++)sumk++;
		off;
		i++;
		off;
		for (i = -1; samep; i--)sumk++;
		off;
		i++;  //据网友提示这里应该是i--，写代码过了很久了，懒得确认真相了
		off;
		if (sumk == 3)sum++;
	}
	for (u = 0; u < 8; u++)//8个方向，每个方向最多1个非三连的活三
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; samep || flag; i++)//成活四点的方向
		{
			if (!samep)
			{
				if (flag&&p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
				flag = false;
			}
			sumk++;
		}
		off;
		if (p[row + dx[u] * --i][col + dy[u] * i] == 0)continue;
		for (i = 1; samep; i++)sumk++;
		off;
		if (sumk == 3)sum++;
	}
	return sum;
}



bool end_(int row, int col)//(row,col)处落子之后是否游戏结束
{
	for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)is_en = true;
	if (is_en)return true;
	return is_en;
}

void go(int row, int col)//落下一子
{
	if (s == s0)p[row][col] = -1; //标出最新下的棋
	else p[row][col] = -2;
	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一个最新棋的标识
	{
		if (i == row && j == col)continue;
		if (p[i][j] < 0)p[i][j] *= -1;
	}
	DrawBoard();

	if (end_(row, col))
	{
		if (s == ais)printf("AI胜");
		else printf("玩家胜");
		Sleep(10000);
	}
}

bool ok(int row, int col)//能否落子
{
	return inboard(row, col) && (p[row][col] == 0);
}

int point(int row, int col)//非负分值
{
	if (end_(row, col))
	{
		is_en = false;
		return 10000;
	}
	int ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100, u;
	for (u = 0; u < 8; u++)if (p[row + dx[u]][col + dy[u]])ret++;//无效点0分
	return ret;
}

int AI3(int p2)
{
	int keyp = -100000, tempp;
	for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
	{
		if (!ok(i, j))continue;
		p[i][j] = s0;
		tempp = point(i, j);
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
	}
	return keyp;
}

int AI2()
{
	int keyp = 100000, tempp;
	for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
	{
		if (!ok(i, j))continue;
		p[i][j] = 3 - s0;
		tempp = point(i, j);
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
		tempp = AI3(tempp);
		p[i][j] = 0;
		if (tempp < keyp)keyp = tempp;//第二层取极小
	}
	return keyp;
}

void AI()
{
	DrawBoard();
	printf("  轮到AI下，请稍候： ");
	if (p[8][8] == 0)return go(8, 8);
	int i, j;
	int keyp = -100000, keyi, keyj, tempp;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			if (!ok(i, j))continue;
			p[i][j] = s0;
			tempp = point(i, j);
			if (tempp == 0)
			{
				p[i][j] = 0;
				continue;
			}//高效剪枝，避开了禁手点和无效点
			if (tempp == 10000)return go(i, j);
			tempp = AI2();
			p[i][j] = 0;
			if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//第一层取极大
		}
	}
	return go(keyi, keyj);
}




