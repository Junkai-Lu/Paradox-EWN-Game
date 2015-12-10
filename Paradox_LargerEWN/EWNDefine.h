#include "stdafx.h"
#include "windows.h"

#pragma  once

enum PIECE
{
	EMPTY = 0,
	RED = 1,
	BLUE = -1
};

#define SIZE 8
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

class Move:public Loc
{
public:
	sint piece;
	virtual void Set(sint lx, sint ly, sint lp)
	{
		x = lx;
		y = ly;
		piece = lp;
	}
	void Show();
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
	Board(BoardArray &b_arr, Move &b_move, short b_step);	//constructor function
	void GameMove(Loc move_loc, int piece);					//excute a move
	void GameMove(Move &move);								//excute a move(overloaded)
	void SetBoard(BoardArray &board_array);					//set the board
	void Print() const;										//print the board
	void Show() const;										//a simpilified print
	int Winner() const;											//return the winner of this board.	
	void DefineFormation(int faction, int formation);		//define the initial piece formation

	inline void StepAdd()
	{
		step++;
	}
	inline void Define(int x, int y, int value)
	{
		board[x][y] = value;
	}
	inline short GetStep() const
	{
		return step;
	}
	inline bool Equal(int px, int py, int p) const
	{
		if (board[px][py] == p)
			return true;
		return false;
	}
	

private:
	void Init();											//initialized board with formation 123456
	Loc GetPieceLoc(int piece) const;						//return the loction of piece.
	bool GetPieceLife(int piece) const;						//return whether the piece alive.
	bool GetLocLegality(Loc loc) const;						//return whether the location is legal.
	int GetPieceFaction(int piece) const;					//return the faction of piece.
	int GetLargerPiece(int piece) const;					//return a piece with a larger number which is alive. 
	int GetSmallerPiece(int piece) const;					//return a piece with a smaller number which is alive. 

public:
	
	int GetAllMoves(Move Moves[6],int Piece) const;
	bool GetLocationThreat(Loc pLoc,int faction) const;
	int GetPieceFilterMoves(Move Moves[3],int Piece);
	int GetFilterMoves(Move Moves[6],int Piece);
	int GetPieceFixFilterMoves(Move Moves[3],int Piece);
	int GetFixFilterMoves(Move Moves[6],int Piece);


};

//basic func
int RndDice();
int RndFormation();
bool GetFormationLegality(int asp);
void PrintPiece(sint piece);
void Cprintf(char* str, WORD color, ...);
void CprintNum(int num,int color);
