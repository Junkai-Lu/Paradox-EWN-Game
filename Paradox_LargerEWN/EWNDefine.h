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

//define basic class.
class Loc
{
public:
	int x;
	int y;
	virtual void Set(int lx, int ly)
	{
		x = lx;
		y = ly;
	}
};

class Move:Loc
{
public:
	Loc loc;
	int piece;
	virtual void Set(int lx, int ly, int lp)
	{
		loc.Set(lx, ly);
		piece = lp;
	}
	void Show();
};

typedef short sint;
using BoardArray = sint[SIZE][SIZE];

class Board
{
public:
	//data
	BoardArray board;
	unsigned short Step;

	//constructor function
	Board();
	Board::Board(BoardArray board_array, unsigned short step);
	Board(BoardArray board_array, Move next_move, unsigned short step);

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
	void Move(Loc mLoc,int Piece);
	void Define(int x,int y,int Piece);
	void Formation(int faction,int formation);

	bool GetLocationThreat(Loc pLoc,int faction);
	int GetPieceFilterMoves(Move Moves[3],int Piece);
	int GetFilterMoves(Move Moves[6],int Piece);

	int GetPieceFixFilterMoves(Move Moves[3],int Piece);
	int GetFixFilterMoves(Move Moves[6],int Piece);
};

//基础函数
bool GetFormationLegality(int asp);
int RndFormation();
int RndDice();

//彩色函数
void Cprintf(char* str, WORD color, ...);
void cprintNum(int color,int Num);
