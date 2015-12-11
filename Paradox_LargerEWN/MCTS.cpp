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