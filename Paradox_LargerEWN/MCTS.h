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
	sint piece;
	Board *aim;

	PureMC(Board *dest, sint next_piece);
};