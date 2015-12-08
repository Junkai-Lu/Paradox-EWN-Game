#include "stdafx.h"
#include "windows.h"

#pragma  once

enum PIECE
{
	EMPTY = 0,
	RED = 1,
	BLUE = -1
};

#define SIZE 10
typedef short sint;
using BoardArray = sint[SIZE][SIZE];

//define basic class.
class Loc
{
public:
	sint x;
	sint y;
	virtual void Set(sint lx, sint ly)
	{
		x = lx;
		y = ly;
	}
};

class Move:Loc
{
public:
	Loc loc;
	sint piece;
	virtual void Set(sint lx, sint ly, sint lp)
	{
		loc.Set(lx, ly);
		piece = lp;
	}
	void Move::Show()
	{
		cout << "Location(" << loc.x + 1 << " " << loc.y + 1 << ") Piece ";
		if (piece>0)
			CprintNum(piece,12);
		else
			CprintNum(-piece,9);
		cout << endl;
	}
};

//define chessboard class


class Board
{
protected:
	//data
	BoardArray board;
	short step;

public:
	//constructor function
	Board();
	Board(BoardArray board_array, Move next_move, short board_step);

	
	inline void StepAdd()
	{
		step++;
	}
	inline short GetStep()
	{
		return step;
	}
	inline bool Equal(int px, int py, int p)
	{
		if (board[px][py] == p)
			return true;
		return false;
	}
	void GameMove(Loc move_loc, int piece);
	void GameMove(Move move);
	void SetBoard(BoardArray board_array);


private:
	void Init();





public:
	Loc GetPieceLoc(int Piece);
	bool GetPieceLife(int Piece);
	bool GetLocLegality(Loc pLoc);
	int GetPieceFaction(int Piece);
	int GetLargerPiece(int Piece);
	int GetSmallerPiece(int Piece);
	int GetAllMoves(Move Moves[6],int Piece);

	void Print();
	void Show();
	int Winner();
	
	void Define(int x,int y,int Piece);
	void Formation(int faction,int formation);

	bool GetLocationThreat(Loc pLoc,int faction);
	int GetPieceFilterMoves(Move Moves[3],int Piece);
	int GetFilterMoves(Move Moves[6],int Piece);

	int GetPieceFixFilterMoves(Move Moves[3],int Piece);
	int GetFixFilterMoves(Move Moves[6],int Piece);


};

//basic func
int RndDice();
int RndFormation();
bool GetFormationLegality(int asp);
void Cprintf(char* str, WORD color, ...);
void CprintNum(int num,int color);
