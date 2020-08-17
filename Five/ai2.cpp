#include <stdio.h>
#include<string>
#include<windows.h>
#include"ai2.h"

int p[N + 2][N + 2]; //0��1��2��  1��2�� -1��-2��
int s = 0, ais = 1, s0;
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }; //flat����
bool is_en = false;
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//��dx,dy����8����������
int  manukey = 0;


int out(int i, int j)
{
	if (p[i][j] == 1)return printf("��");
	if (p[i][j] == 2)return printf("��");
	if (p[i][j] == -1)return printf("��");
	if (p[i][j] == -2)return printf("��");
	if (i == N)
	{
		if (j == 1)return printf("��");
		if (j == N)return printf("��");
		return printf("��");
	}
	if (i == 1)
	{
		if (j == 1)return printf("��");
		if (j == N)return printf("��");
		return printf("��");
	}
	if (j == 1)return printf("��");
	if (j == N)return printf("��");
	return printf("��");
}

void DrawBoard()//������
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
	if (s0 == ais)printf("  AIִ�ڣ����ִ��\n");
	else printf("  AIִ�ף����ִ��\n");
	alpha = 'A';
	if (keyr)printf("  �������λ�ã�%c%d\n", alpha + keyc - 1, keyr);
}


bool inboard(int row, int col)//�Ƿ���������
{
	if (row <1 || row > N)return false;
	return col >= 1 && col <= N;
}

int same(int row, int col, int key)//�ж�2�������Ƿ�ͬɫ
{
	if (!inboard(row, col))return false;
	return (p[row][col] == key || p[row][col] + key == 0);
}

int num(int row, int col, int u)//���꣨row,col������������u
{
	int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
	if (ref == 0)return 0;
	while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
	return sum;
}

int live4(int row, int col)//��4������
{
	int sum = 0, i, u;
	for (u = 0; u < 4; u++)//4������ÿ���������1��
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

int chong4(int row, int col)//��4������
{
	int sum = 0, i, u;
	for (u = 0; u < 8; u++)//8������ÿ���������1��
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; samep || flag; i++)//�����ķ���
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

int live3(int row, int col)//��3������
{
	int key = p[row][col], sum = 0, i, u;
	for (u = 0; u < 4; u++)//�����Ļ���
	{
		int sumk = 1;
		for (i = 1; samep; i++)sumk++;
		off;
		i++;
		off;
		for (i = -1; samep; i--)sumk++;
		off;
		i++;  //��������ʾ����Ӧ����i--��д������˺ܾ��ˣ�����ȷ��������
		off;
		if (sumk == 3)sum++;
	}
	for (u = 0; u < 8; u++)//8������ÿ���������1���������Ļ���
	{
		int  sumk = 0;
		bool flag = true;
		for (i = 1; samep || flag; i++)//�ɻ��ĵ�ķ���
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



bool end_(int row, int col)//(row,col)������֮���Ƿ���Ϸ����
{
	for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)is_en = true;
	if (is_en)return true;
	return is_en;
}

void go(int row, int col)//����һ��
{
	if (s == s0)p[row][col] = -1; //��������µ���
	else p[row][col] = -2;
	for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //ȡ����һ��������ı�ʶ
	{
		if (i == row && j == col)continue;
		if (p[i][j] < 0)p[i][j] *= -1;
	}
	DrawBoard();

	if (end_(row, col))
	{
		if (s == ais)printf("AIʤ");
		else printf("���ʤ");
		Sleep(10000);
	}
}

bool ok(int row, int col)//�ܷ�����
{
	return inboard(row, col) && (p[row][col] == 0);
}

int point(int row, int col)//�Ǹ���ֵ
{
	if (end_(row, col))
	{
		is_en = false;
		return 10000;
	}
	int ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100, u;
	for (u = 0; u < 8; u++)if (p[row + dx[u]][col + dy[u]])ret++;//��Ч��0��
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
		if (tempp - p2 * 2 > keyp)keyp = tempp - p2 * 2;//������ȡ����
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
		if (tempp < keyp)keyp = tempp;//�ڶ���ȡ��С
	}
	return keyp;
}

void AI()
{
	DrawBoard();
	printf("  �ֵ�AI�£����Ժ� ");
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
			}//��Ч��֦���ܿ��˽��ֵ����Ч��
			if (tempp == 10000)return go(i, j);
			tempp = AI2();
			p[i][j] = 0;
			if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;//��һ��ȡ����
		}
	}
	return go(keyi, keyj);
}




