#include<iostream>
#include"ai2.h"
#include"five.h"
#include<time.h>
using namespace std;
int main()
{
	clock_t start, finsh;
	int Time = 0;
	float time = 0;
	bool coutinue = true;
	while (coutinue)
	{
		system("cls");
		is_end = false;
		Time++;
		init_traverse();
		Initialize();
		GeginRule();
		while (!is_end)
		{
			if (s == ais) start = clock(), FIGHTER(), finsh = clock(), time += (finsh - start) / CLOCKS_PER_SEC;
			else AI();//如果想自己下换为 player（）函数
			s = 3 - s;//换下棋方
			cout << "现在时间为" << time << endl;
		}
		
		coutinue = whether_end();
	}
	return 0;
}