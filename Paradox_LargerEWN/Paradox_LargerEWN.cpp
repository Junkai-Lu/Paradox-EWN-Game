//This is an EWN game with larger board in order to test performance of different algorithm.
//5x5 game is too small. in which most algorithm may have approximate performance.

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <sstream>

#include "EWNDefine.h"
#include "MCTS.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Board CB;
	clock_t start, finish;	//set clock
	double totaltime;		
	srand((unsigned)time(NULL));//srand
	CB.Show();

	PureMC MC(&CB, 1);
	cout << MC.SingleSimulation(CB, RED);
	return 0;


}

