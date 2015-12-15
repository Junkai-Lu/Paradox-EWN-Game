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
	void MonteCarloMove(Board &dest, sint piece, bool move_msg);

protected:
	void RndMove(Board &dest, sint piece);
	sint SingleSimulation(Board &dest, sint next_player);
	float MultipleSimulation(Board &dest, sint next_player, sint winner, int times);

private:
	const int MC_TIMES = 20000;
};

class MctsNode :Board
{
public:
	//func
	MctsNode(sint next_player);
	MctsNode(sint next_player, BoardArray &b_arr, Move &b_move, short b_step);
	
	//data
	sint owner;					//the owner of this node, but also the player who is making decision.
	sint winner;				//the winner of this node if it is finite state.
	float avg_value;			//the avg winner rate for the parent of this node.
	MctsMove *piece_move[6];	//storage all avaliable moves.

private:
	//func
	float GetUCBValue(int total_times);

	//data
	bool piece_alive[6];		//whether the six piece of owner alive
	int visited_times;			//how manyy times this node have been visited.
	sint exist_child[6];		//existed child for each avaliable piece.
	sint maxium_child[6];		//maxium child for each avaliable piece.
	
};

class StandardMCTS :public PureMC
{
	StandardMCTS(Board *board, sint piece);
};