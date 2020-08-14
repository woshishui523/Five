#include<iostream>
#include"ai2.h"
#include"five.h"

int main()
{
	int Time = 0;
	bool coutinue = true;
	while (coutinue)
	{
		Time++;
		Initialize();
		GeginRule();
		while (!is_end)
		{
			if (s == ais)MinimaxAlgorithmLevel1();
			else AI();
			s = 3 - s;//»»ÏÂÆå·½
		}
		coutinue = whether_end();
	}
	return 0;
}