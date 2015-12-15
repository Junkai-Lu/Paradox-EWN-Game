#include "stdafx.h"

#include "windows.h"
#include "stdio.h"
#include "time.h"
#include <iostream>
#include <sstream>

#include "EWNdefine.h"
#include "MCTS.h"

//public
PureMC::PureMC(Board *board, sint piece)
{
	dest_board = board;
	dest_piece = piece;
}

//protected
void PureMC::RndMove(Board &dest, sint piece)
{
	int dice;
	Move moves[6];
	int move_num = dest.GetAllMoves(moves, piece);
	dice = rand() % move_num;
	dest.GameMove(moves[dice]);
}
sint PureMC::SingleSimulation(Board &dest, sint next_player)
{
	BoardArray temp_board;
	short temp_step = dest.GetStep();
	dest.CopyBoardArray(temp_board);
	int player = next_player;
	for (int i = 0; i>-1; i++)
	{
		int w = dest.Winner();
		if (w != 0)
		{
			dest.SetBoard(temp_board);
			dest.SetStep(temp_step);
			return w;
		}
		RndMove(dest, player*RndDice());
		player = -player;
	}
	dest.SetBoard(temp_board);
	return 0;
}
float PureMC::MultipleSimulation(Board &dest, sint next_player, sint winner, int times)
{
	int win_times = 0;
	for (int i = 0; i<times; i++)
	{
		if (SingleSimulation(dest, next_player) == winner)
			win_times++;
	}
	float Result = (float)win_times / (float)times;
	return Result;
}
void PureMC::MonteCarloMove(Board &dest, sint piece,bool move_msg)
{
	int f = dest.GetPieceFaction(piece);
	Move moves[6];
	int MoveNum = dest.GetAllMoves(moves, piece);
	float best_val = -1;
	int best_move_num = 0;
	for (int i = 0; i<MoveNum; i++)
	{
		Board test_board = dest;
		test_board.GameMove(moves[i]);
		float val = MultipleSimulation(test_board, -f, f, MC_TIMES);
		if (val >= best_val)
		{
			best_val = val;
			best_move_num = i;
		}
	}
	dest.GameMove(moves[best_move_num]);
}


MctsNode::MctsNode(sint next_player) :Board()
{
	owner = next_player;
	winner = Winner();
	avg_value = 0;
	visited_times = 1;
}
float MctsNode::GetUCBValue(int total_times)
{
	float exploitation = sqrt((((log10((float)total_times)) * 2) / (float)visited_times));
	return avg_value + exploitation;
}
