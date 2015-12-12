#include "stdafx.h"
#include "EWNdefine.h"

class MctsMove :public Move
{
	MctsMove()
	{
		next_move = nullptr;
	}
	virtual void Set(sint lx, sint ly, sint lp, Move *m)
	{
		x = lx;
		y = ly;
		piece = lp;
		next_move = m;
	}
	Move *next_move;
};

class PureMC
{
public:
	sint dest_piece;
	Board *dest_board;

	PureMC(Board *board, sint piece);
	const int MC_TIMES = 20000;

protected:
	void RndMove(Board &dest, sint piece);

public:
	sint SingleSimulation(Board &dest, sint next_player);
	float MultipleSimulation(Board &dest, sint next_player, sint winner, int times);
	void MonteCarloMove(Board &dest, sint piece, bool move_msg);
};