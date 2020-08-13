#include<iostream>
#include"ai2.h"
#include"five.h"

int main()
{
	Initialize();
	GeginRule();
	while (!is_end)
	{
		if (s == ais)MinimaxAlgorithmLevel1();
		else AI();
		s = 3 - s;//»»ÏÂÆå·½
	}
	return 0;
}