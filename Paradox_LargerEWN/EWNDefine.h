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
	
	Board();												//constructor function
	Board(BoardArray b_arr, Move b_move, short b_step);		//constructor function
	void GameMove(Loc move_loc, int piece);					//excute a move
	void GameMove(Move move);								//excute a move(overloaded)
	void SetBoard(BoardArray board_array);					//set the board
	void Print();											//print the board
	void Show();											//a simpilified print
	int Winner();											//return the winner of this board.	
	void DefineFormation(int faction, int formation);		//define the initial piece formation

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
	inline void Define(int x, int y, int value)
	{
		board[x][y] = value;
	}

private:
	void Init();											//initialized board with formation 123456
	Loc GetPieceLoc(int piece);								//return the loction of piece.
	bool GetPieceLife(int piece);							//return whether the piece alive.
	bool GetLocLegality(Loc loc);							//return whether the location is legal.
	int GetPieceFaction(int piece);							//return the faction of piece.
	int GetLargerPiece(int piece);							//return a piece with a larger number which is alive. 
	int GetSmallerPiece(int piece);							//return a piece with a smaller number which is alive. 

public:
	
	int GetAllMoves(Move Moves[6],int Piece);
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
