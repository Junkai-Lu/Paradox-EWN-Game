#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include <iostream>
#include <sstream>
#include "EWNDefine.h"

using namespace std;


void Move::Show()
{
	std::cout << "Location(" << x + 1 << " " << y + 1 << ") Piece ";
	if (piece>0)
		CprintNum(piece, 12);
	else
		CprintNum(-piece, 9);
	std::cout << std::endl;
}


//Board
Board::Board()
{
	//initialize board.
	step =0;
	Init();
}
Board::Board(BoardArray &b_arr, Move &b_move, short b_step)
{
	step = b_step;
	SetBoard(b_arr);
	GameMove(b_move);
}

//public
void Board::GameMove(Loc move_loc, int piece)
{
	step++;
	Loc old_loc = GetPieceLoc(piece);
	board[old_loc.x][old_loc.y] = EMPTY;
	board[move_loc.x][move_loc.y] = piece;
}
void Board::GameMove(Move &move)
{
	step++;
	Loc old_loc = GetPieceLoc(move.piece);
	board[old_loc.x][old_loc.y] = EMPTY;
	board[move.x][move.y] = move.piece;
}
void Board::SetBoard(BoardArray &board_array)
{
	for (int i = 0; i<SIZE; i++)
		for (int j = 0; j<SIZE; j++)
			board[j][i] = board_array[j][i];
}
void Board::Print() const
{
	Cprintf("\n┌┄┬", 15);
	for (int i = 0; i < SIZE;i++)
		Cprintf("┄┄", 15);
	Cprintf("┄┐\n┆", 15);
	if (step<10)
	{
		CprintNum(0, 14);
		CprintNum(step, 14);
	}
	else
	{
		CprintNum(step, 14);
	}

	Cprintf("┆", 15);
	for (int i = 0; i < SIZE; i++)
	{
		cout << "   ";
		CprintNum(i+1, 8);
		
	}
	cout << "  ";

	Cprintf("┆\n├┄┼", 15);
	for (int i = 0; i < SIZE; i++)
	{
		Cprintf("┄┄", 15);
	}
	Cprintf("┄┤", 15);


	Cprintf("\n┆  ┆", 15);
	for (int i = 0; i < SIZE; i++)
	{
		Cprintf("    ", 15);
	}
	Cprintf("  ┆\n", 15);


	for (int i = 0; i<SIZE; i++)
	{
		printf("┆ ");
		CprintNum(i + 1, 8);
		printf("┆  ");

		for (int j = 0; j<SIZE; j++)
		{
			if (board[j][i] == 0)
			{
				printf("  ");
			}
			else if (board[j][i]>0)
			{
				cout << " ";
				CprintNum(board[j][i], 12);
			}
			else if (board[j][i]<0)
			{
				cout << " ";
				CprintNum(-board[j][i], 9);
			}
			printf("  ");
		}
		Cprintf("┆\n",15);

		Cprintf("┆  ┆", 15);
		for (int i = 0; i < SIZE; i++)
		{
			Cprintf("    ", 15);
		}
		Cprintf("  ┆\n", 15);

	}
	Cprintf("└┄┴", 15);
	for (int i = 0; i < SIZE; i++)
	{
		Cprintf("┄┄", 15);
	}
	Cprintf("┄", 15);
	Cprintf("┘\n", 15);
}
void Board::Show() const
{
	cout << "\n--";
	for (int i = 0; i < SIZE; i++)
		cout << "---";
	cout << "\n ";
	for (int i = 0; i < SIZE; i++)
	{
		cout <<"  "<< i + 1;
	}
	cout<<"\n";

	for (int i = 0; i<SIZE; i++)
	{
		cout << i + 1;
		for (int j = 0; j<SIZE; j++)
		{
			cout << "  ";
			if (board[j][i] == 0)
				cout << " ";
			if (board[j][i]>0)
				CprintNum(board[j][i], 12);
			if (board[j][i]<0)
				CprintNum(-board[j][i], 9);
		}
		cout << "\n";
	}
	for (int i = 0; i < SIZE; i++)
		cout << "---";
	cout << "--\n ";
}
int Board::Winner() const
{
	if (board[0][0] < 0)
		return BLUE;
	if (board[SIZE - 1][SIZE - 1] > 0)
		return RED;
	int red = 0, blue = 0;
	for (int i = 0; i<SIZE; i++)
	{
		for (int j = 0; j<SIZE; j++)
		{
			if (board[j][i] >0)
				red++;
			if (board[j][i] <0)
				blue++;
		}
	}
	if (red == 0)
		return BLUE;
	if (blue == 0)
		return RED;
	return 0;
}


void Board::DefineFormation(int faction, int formation)
{
	int px = formation;
	int six = px % 10;
	px = (px - six) / 10;
	int five = px % 10;
	px = (px - five) / 10;
	int four = px % 10;
	px = (px - four) / 10;
	int three = px % 10;
	px = (px - three) / 10;
	int two = px % 10;
	px = (px - two) / 10;
	int one = px % 10;
	if (faction == RED)
	{
		Define(0, 0, one);
		Define(1, 0, two);
		Define(2, 0, three);
		Define(0, 1, four);
		Define(1, 1, five);
		Define(0, 2, six);
	}
	else
	{
		Define(SIZE - 1, SIZE - 1, -one);
		Define(SIZE - 2, SIZE - 1, -two);
		Define(SIZE - 3, SIZE - 1, -three);
		Define(SIZE - 1, SIZE - 2, -four);
		Define(SIZE - 2, SIZE - 2, -five);
		Define(SIZE - 1, SIZE - 3, -six);
	}
}

//private
void Board::Init()
{
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			board[x][y] = EMPTY;
	//RED
	board[0][0] = 1;
	board[1][0] = 2;
	board[2][0] = 3;
	board[0][1] = 4;
	board[1][1] = 5;
	board[0][2] = 6;

	//BLUE
	board[SIZE - 1][SIZE - 1] = -1;
	board[SIZE - 2][SIZE - 1] = -2;
	board[SIZE - 3][SIZE - 1] = -3;
	board[SIZE - 1][SIZE - 2] = -4;
	board[SIZE - 2][SIZE - 2] = -5;
	board[SIZE - 1][SIZE - 3] = -6;
}
Loc Board::GetPieceLoc(int piece) const
{
	Loc new_loc;
	for(int i =0;i<SIZE;i++)
	{
		for(int j =0;j<SIZE;j++)
		{
			if(board[j][i] == piece)
			{
				new_loc.Set(j, i);
				return new_loc;
			}
		}
	}
	new_loc.Set(0, 0);
	return new_loc;
}
bool Board::GetPieceLife(int piece) const
{
	for(int i =0;i<SIZE;i++)
	{
		for(int j =0;j<SIZE;j++)
		{
			if(board[j][i] == piece)
				return true;
		}
	}
	return false;
}
bool Board::GetLocLegality(Loc loc) const
{
	if(loc.x>=0&&loc.x<=SIZE-1&&loc.y>=0&&loc.y<=SIZE-1)
		return true;
	return false;
}
int Board::GetPieceFaction(int piece) const
{
	if(piece>0)
		return RED;
	if(piece<0)
		return BLUE;
	return 0;
}
int Board::GetLargerPiece(int piece) const
{
	if(piece>0)
	{
		for(int i=piece;i<=6;i++)
		{
			if(GetPieceLife(i)==true)
			{
				return i;
			}
		}
		return 0;
	}
	else
	{
		for(int i=piece;i>=-6;i--)
		{
			if(GetPieceLife(i)==true)
			{
				return i;
			}
		}
		return 0;
	}
}
int Board::GetSmallerPiece(int piece) const
{
	if(piece>0)
	{
		for(int i=piece;i>=1;i--)
		{
			if(GetPieceLife(i)==true)
			{
				return i;
			}
		}
		return 0;
	}
	else
	{
		for(int i=piece;i<=-1;i++)
		{
			if(GetPieceLife(i)==true)
			{
				return i;
			}
		}
		return 0;
	}
}


int Board::GetAllMoves(Move moves[6], int piece) const
{
	int direction[3][2] = { { 1, 0 }, { 1, 1 }, { 0, 1 } };
	int move_num = 0;
	if (GetPieceLife(piece) == true)
	{
		Loc p_loc = GetPieceLoc(piece);
		int f = GetPieceFaction(piece);
		for (int i = 0; i<3; i++)
		{
			Loc new_loc;
			new_loc.x = p_loc.x + f*direction[i][0];
			new_loc.y = p_loc.y + f*direction[i][1];
			if (GetLocLegality(new_loc) == true)
			{
				moves[move_num].Set(new_loc.x, new_loc.y, piece);
				move_num++;
			}
		}
	}
	else
	{
		int s = GetSmallerPiece(piece);
		int l = GetLargerPiece(piece);
		int f = GetPieceFaction(piece);
		if (s != 0 && l != 0)
		{
			//dead s first
			Loc p_loc = GetPieceLoc(s);
			for (int i = 0; i<3; i++)
			{
				Loc new_loc;
				new_loc.x = p_loc.x + f*direction[i][0];
				new_loc.y = p_loc.y + f*direction[i][1];
				if (GetLocLegality(new_loc) == true)
				{
					moves[move_num].Set(new_loc.x, new_loc.y, s);
					move_num++;
				}
			}
			//dead l
			p_loc = GetPieceLoc(l);
			for (int i = 0; i<3; i++)
			{
				Loc new_loc;
				new_loc.x = p_loc.x + f*direction[i][0];
				new_loc.y = p_loc.y + f*direction[i][1];
				if (GetLocLegality(new_loc) == true)
				{
					moves[move_num].Set(new_loc.x, new_loc.y, l);
					move_num++;
				}
			}
		}
		if (s == 0 && l != 0)
		{
			Loc p_loc = GetPieceLoc(l);
			for (int i = 0; i<3; i++)
			{
				Loc new_loc;
				new_loc.x = p_loc.x + f*direction[i][0];
				new_loc.y = p_loc.y + f*direction[i][1];
				if (GetLocLegality(new_loc) == true)
				{
					moves[move_num].Set(new_loc.x, new_loc.y, l);
					move_num++;
				}
			}
		}
		if (s != 0 && l == 0)
		{
			Loc p_loc = GetPieceLoc(s);
			for (int i = 0; i<3; i++)
			{
				Loc new_loc;
				new_loc.x = p_loc.x + f*direction[i][0];
				new_loc.y = p_loc.y + f*direction[i][1];
				if (GetLocLegality(new_loc) == true)
				{
					moves[move_num].Set(new_loc.x, new_loc.y, s);
					move_num++;
				}
			}
		}
		if (s == 0 && l == 0)
			cout << "WARNING:Wrong Func<GetAllMoves>";
	}
	return move_num;
}
bool Board::GetLocationThreat(Loc p_loc, int faction) const
{
	//return whether the piece in p_loc is threatened by his opponent
	int direction[3][2] = { { 1, 0 }, { 1, 1 }, { 0, 1 } };
	for (int i = 0; i<3; i++)
	{
		Loc nLoc;
		nLoc.x = p_loc.x + (faction*direction[i][0]);
		nLoc.y = p_loc.y + (faction*direction[i][1]);
		if (GetPieceFaction(board[p_loc.x][p_loc.y]) == -faction)
		{
			return true;
		}
	}
	return false;
}

/*


//Filter
int Board::GetPieceFilterMoves(Move Moves[3],int Piece)
{	
	int Direction[3][2] = {{1,0},{1,1},{0,1}};
	int XDirection[2][2] = {{1,0},{1,1}};
	int YDirection[2][2] = {{0,1},{1,1}};
	int MoveNum = 0;
	Loc pLoc = GetPieceLoc(Piece);//确定棋子坐标
	int x = pLoc.x;//确定棋子坐标X
	int y = pLoc.y;//确认棋子坐标Y
	int f = GetPieceFaction(Piece);//确认棋子阵营
	if(f*x<f*y&&board[x][y+f]==EMPTY)
	{
		for(int i=0;i<2;i++)
		{
			Loc nLoc;
			nLoc.x= pLoc.x+(f*XDirection[i][0]);
			nLoc.y= pLoc.y+(f*XDirection[i][1]);
			if(GetLocLegality(nLoc)==true)
			{
				Moves[MoveNum].Loc=nLoc;
				Moves[MoveNum].Piece=Piece;
				MoveNum++;
			}
		}
	}
	else if(f*x>f*y&&board[x+f][y]==EMPTY)
	{
		for(int i=0;i<2;i++)
		{
			Loc nLoc;
			nLoc.x= pLoc.x+(f*YDirection[i][0]);
			nLoc.y= pLoc.y+(f*YDirection[i][1]);
			if(GetLocLegality(nLoc)==true)
			{
				Moves[MoveNum].Loc=nLoc;
				Moves[MoveNum].Piece=Piece;
				MoveNum++;
			}
		}
	}
	else
	{
		for(int i=0;i<3;i++)
		{
			Loc nLoc;
			nLoc.x= pLoc.x+(f*Direction[i][0]);
			nLoc.y= pLoc.y+(f*Direction[i][1]);
			if(GetLocLegality(nLoc)==true)
			{
				Moves[MoveNum].Loc=nLoc;
				Moves[MoveNum].Piece=Piece;
				MoveNum++;
			}
		}
	}
	return MoveNum;
}
int Board::GetFilterMoves(Move Moves[6],int Piece)
{
	int MoveNum = 0;
	//特殊情形1，有棋子距离终点只有1距离
	int f = GetPieceFaction(Piece);
	int Direction[3][2] = {{1,0},{1,1},{0,1}};
	Loc pLoc = GetPieceLoc(Piece);
	if(GetPieceLife(Piece))//如果棋子存活的话
	{
		if((f*pLoc.x>=f*(2+f))&&(f*pLoc.y>=f*(2+f)))//如果该棋子在禁区内的话
		{
			Loc nLoc;
			nLoc.Set(2+f+f,2+f+f);//设定Loc为f的终点
			Moves[0].Loc = nLoc;
			Moves[0].Piece = Piece;
			return 1;//只需要这一个招式
		}
	}
	else
	{
		int s_Piece = GetSmallerPiece(Piece);
		if(s_Piece!=0)
		{
			Loc sLoc = GetPieceLoc(s_Piece);
			if((f*sLoc.x>=f*(2+f))&&(f*sLoc.y>=f*(2+f)))//如果该棋子在禁区内的话
			{
				Loc nLoc;
				nLoc.Set(2+f+f,2+f+f);//设定Loc为f的终点
				Moves[0].Loc = nLoc;
				Moves[0].Piece = s_Piece;
				return 1;//只需要这一个招式
			}
		}
		int l_Piece = GetLargerPiece(Piece);
		if(l_Piece!=0)
		{
			Loc lLoc = GetPieceLoc(l_Piece);
			if((f*lLoc.x>=f*(2+f))&&(f*lLoc.y>=f*(2+f)))//如果该棋子在禁区内的话
			{
				Loc nLoc;
				nLoc.Set(2+f+f,2+f+f);//设定Loc为f的终点
				Moves[0].Loc = nLoc;
				Moves[0].Piece = l_Piece;
				return 1;//只需要这一个招式
			}
		}
	}

	//特殊情况2。对方距离我方终点为1
	if(GetPieceLife(Piece))//如果棋子存活的话
	{
		if((pLoc.x==2-f-f)&&(pLoc.y==2-f-f))//如果我方起点的话
		{
			for(int i=0;i<3;i++)
			{
				Loc nLoc;
				nLoc.x= pLoc.x+(f*Direction[i][0]);
				nLoc.y= pLoc.y+(f*Direction[i][1]);
				if(GetPieceFaction(board[nLoc.x][nLoc.y])==-f)
				{
					Moves[MoveNum].Loc=nLoc;
					Moves[MoveNum].Piece=Piece;
					MoveNum++;
				}
			}
		}
	}
	else
	{
		int s_Piece = GetSmallerPiece(Piece);
		if(s_Piece!=0)
		{
			Loc sLoc = GetPieceLoc(s_Piece);
			if((sLoc.x==2-f-f)&&(sLoc.y==2-f-f))//如果我方起点的话
			{
				for(int i=0;i<3;i++)
				{
					Loc nLoc;
					nLoc.x= sLoc.x+(f*Direction[i][0]);
					nLoc.y= sLoc.y+(f*Direction[i][1]);
					if(GetPieceFaction(board[nLoc.x][nLoc.y])==-f)
					{
						Moves[MoveNum].Loc=nLoc;
						Moves[MoveNum].Piece=s_Piece;
						MoveNum++;
					}
				}
			}
		}

		int l_Piece = GetLargerPiece(Piece);
		if(l_Piece!=0)
		{
			Loc lLoc = GetPieceLoc(l_Piece);
			if((lLoc.x==2-f-f)&&(lLoc.y==2-f-f))//如果我方起点的话
			{
				for(int i=0;i<3;i++)
				{
					Loc nLoc;
					nLoc.x= lLoc.x+(f*Direction[i][0]);
					nLoc.y= lLoc.y+(f*Direction[i][1]);
					if(GetPieceFaction(board[nLoc.x][nLoc.y])==-f)
					{
						Moves[MoveNum].Loc=nLoc;
						Moves[MoveNum].Piece=l_Piece;
						MoveNum++;
					}
				}
			}
		}
	}
	if(MoveNum!=0)
		return MoveNum;

	//正常情形
	if(GetPieceLife(Piece)==true)
	{
		Move p_Moves[3];
		MoveNum = GetPieceFilterMoves(p_Moves,Piece);
		for(int i=0;i<MoveNum;i++)
		{
			Moves[i] = p_Moves[i];
		}
		return MoveNum;
	}
	else
	{
		int s_Piece=GetSmallerPiece(Piece);
		int l_Piece=GetLargerPiece(Piece);
		if(s_Piece!=0&&l_Piece!=0)
		{
			//处理s和l的数据
			Move s_Moves[3];
			Move l_Moves[3];
			int s_MoveNum = GetPieceFilterMoves(s_Moves,s_Piece);
			int l_MoveNum = GetPieceFilterMoves(l_Moves,l_Piece);
			for(int i=0;i<s_MoveNum;i++)
			{
				Moves[i] = s_Moves[i];
			}
			for(int i=0;i<l_MoveNum;i++)
			{
				Moves[i+s_MoveNum] = l_Moves[i];
			}
			MoveNum = s_MoveNum+l_MoveNum;
			return MoveNum;
		}
		if(s_Piece==0&&l_Piece!=0)
		{
			//仅处理l的问题
			Move l_Moves[3];
			MoveNum = GetPieceFilterMoves(l_Moves,l_Piece);
			for(int i=0;i<MoveNum;i++)
			{
				Moves[i] = l_Moves[i];
			}
			return MoveNum;
		}
		if(s_Piece!=0&&l_Piece==0)
		{
			//仅处理s的问题
			Move s_Moves[3];
			MoveNum = GetPieceFilterMoves(s_Moves,s_Piece);
			for(int i=0;i<MoveNum;i++)
			{
				Moves[i] = s_Moves[i];
			}
			return MoveNum;
		}
		if(s_Piece==0&&l_Piece==0)
		{
			cout<<"GetFilterMoves函数出错，不存在任何棋子";
			system("pause");
		}
	}
	return MoveNum;
}
//FixFilter
int Board::GetPieceFixFilterMoves(Move Moves[3],int Piece)
{	
	int Direction[3][2] = {{1,0},{1,1},{0,1}};
	int XDirection[2][2] = {{1,0},{1,1}};
	int YDirection[2][2] = {{0,1},{1,1}};
	int MoveNum = 0;
	Loc pLoc = GetPieceLoc(Piece);//确定棋子坐标
	int x = pLoc.x;//确定棋子坐标X
	int y = pLoc.y;//确认棋子坐标Y
	int f = GetPieceFaction(Piece);//确认棋子阵营
	if(f*x<f*y&&board[x][y+f]==EMPTY)
	{
		for(int i=0;i<2;i++)
		{
			Loc nLoc;
			nLoc.x= pLoc.x+(f*XDirection[i][0]);
			nLoc.y= pLoc.y+(f*XDirection[i][1]);
			if(GetLocLegality(nLoc)==true)
			{
				Moves[MoveNum].Loc=nLoc;
				Moves[MoveNum].Piece=Piece;
				MoveNum++;
			}
		}
	}
	else if(f*x>f*y&&board[x+f][y]==EMPTY)
	{
		for(int i=0;i<2;i++)
		{
			Loc nLoc;
			nLoc.x= pLoc.x+(f*YDirection[i][0]);
			nLoc.y= pLoc.y+(f*YDirection[i][1]);
			if(GetLocLegality(nLoc)==true)
			{
				Moves[MoveNum].Loc=nLoc;
				Moves[MoveNum].Piece=Piece;
				MoveNum++;
			}
		}
	}
	else
	{
		for(int i=0;i<3;i++)
		{
			Loc nLoc;
			nLoc.x= pLoc.x+(f*Direction[i][0]);
			nLoc.y= pLoc.y+(f*Direction[i][1]);
			if(GetLocLegality(nLoc)==true)
			{
				Moves[MoveNum].Loc=nLoc;
				Moves[MoveNum].Piece=Piece;
				MoveNum++;
			}
		}
	}
	return MoveNum;
}
int Board::GetFixFilterMoves(Move Moves[6],int Piece)
{
	int MoveNum = 0;
	//特殊情形1，有棋子距离终点只有1距离
	int f = GetPieceFaction(Piece);
	int Direction[3][2] = {{1,0},{1,1},{0,1}};
	Loc pLoc = GetPieceLoc(Piece);
	if(GetPieceLife(Piece))//如果棋子存活的话
	{
		if((f*pLoc.x>=f*(2+f))&&(f*pLoc.y>=f*(2+f)))//如果该棋子在禁区内的话
		{
			Loc nLoc;
			nLoc.Set(2+f+f,2+f+f);//设定Loc为f的终点
			Moves[0].Loc = nLoc;
			Moves[0].Piece = Piece;
			return 1;//只需要这一个招式
		}
	}
	else
	{
		int s_Piece = GetSmallerPiece(Piece);
		if(s_Piece!=0)
		{
			Loc sLoc = GetPieceLoc(s_Piece);
			if((f*sLoc.x>=f*(2+f))&&(f*sLoc.y>=f*(2+f)))//如果该棋子在禁区内的话
			{
				Loc nLoc;
				nLoc.Set(2+f+f,2+f+f);//设定Loc为f的终点
				Moves[0].Loc = nLoc;
				Moves[0].Piece = s_Piece;
				return 1;//只需要这一个招式
			}
		}
		int l_Piece = GetLargerPiece(Piece);
		if(l_Piece!=0)
		{
			Loc lLoc = GetPieceLoc(l_Piece);
			if((f*lLoc.x>=f*(2+f))&&(f*lLoc.y>=f*(2+f)))//如果该棋子在禁区内的话
			{
				Loc nLoc;
				nLoc.Set(2+f+f,2+f+f);//设定Loc为f的终点
				Moves[0].Loc = nLoc;
				Moves[0].Piece = l_Piece;
				return 1;//只需要这一个招式
			}
		}
	}

	//正常情形
	if(GetPieceLife(Piece)==true)
	{
		Move p_Moves[3];
		MoveNum = GetPieceFixFilterMoves(p_Moves,Piece);
		for(int i=0;i<MoveNum;i++)
		{
			Moves[i] = p_Moves[i];
		}
		return MoveNum;
	}
	else
	{
		int s_Piece=GetSmallerPiece(Piece);
		int l_Piece=GetLargerPiece(Piece);
		if(s_Piece!=0&&l_Piece!=0)
		{
			//处理s和l的数据
			Move s_Moves[3];
			Move l_Moves[3];
			int s_MoveNum = GetPieceFixFilterMoves(s_Moves,s_Piece);
			int l_MoveNum = GetPieceFixFilterMoves(l_Moves,l_Piece);
			for(int i=0;i<s_MoveNum;i++)
			{
				Moves[i] = s_Moves[i];
			}
			for(int i=0;i<l_MoveNum;i++)
			{
				Moves[i+s_MoveNum] = l_Moves[i];
			}
			MoveNum = s_MoveNum+l_MoveNum;
			return MoveNum;
		}
		if(s_Piece==0&&l_Piece!=0)
		{
			//仅处理l的问题
			Move l_Moves[3];
			MoveNum = GetPieceFixFilterMoves(l_Moves,l_Piece);
			for(int i=0;i<MoveNum;i++)
			{
				Moves[i] = l_Moves[i];
			}
			return MoveNum;
		}
		if(s_Piece!=0&&l_Piece==0)
		{
			//仅处理s的问题
			Move s_Moves[3];
			MoveNum = GetPieceFixFilterMoves(s_Moves,s_Piece);
			for(int i=0;i<MoveNum;i++)
			{
				Moves[i] = s_Moves[i];
			}
			return MoveNum;
		}
		if(s_Piece==0&&l_Piece==0)
		{
			cout<<"GetFixFilterMoves函数出错，不存在任何棋子";
			system("pause");
		}
	}
	return MoveNum;
}
*/




//Basic Func
int RndDice()
{
	int die = rand() % 6 + 1;
	return die;
}
int RndFormation()
{
	int asp, n;
	int r[6] = { 1, 2, 3, 4, 5, 6 };
	n = rand() % 6;
	asp = r[n];
	r[n] = 0;
	for (;;)
	{
		n = rand() % 6;
		if (r[n]>0)
		{
			asp = asp * 10 + r[n];
			r[n] = 0;
		}
		if (asp >= 123456 && asp <= 654321)
			break;
	}
	return asp;
}
bool GetFormationLegality(int asp)
{
	if (asp <= 654321 && asp >= 123456)
	{
		int px = asp;
		int six = px % 10;
		px = (px - six) / 10;
		int five = px % 10;
		px = (px - five) / 10;
		int four = px % 10;
		px = (px - four) / 10;
		int three = px % 10;
		px = (px - three) / 10;
		int two = px % 10;
		px = (px - two) / 10;
		int one = px % 10;
		if (1 <= one&&one <= 6 && 1 <= two&&two <= 6 && 1 <= three&&three <= 6 && 1 <= four&&four <= 6 && 1 <= five&&five <= 6 && 1 <= six&&six <= 6)
		{
			if (one != two&&one != three&&one != four&&one != five&&one != six&&two != three&&two != four&&two != five&&two != six&&three != four&&three != five&&three != six&&four != five&&four != six&&five != six)
			{
				return true;
			}
		}
	}
	return false;
}
void PrintPiece(sint piece)
{
	switch (piece)
	{
	case 1:
		Cprintf("①", 12);
		break;
	case 2:
		Cprintf("②", 12);
		break;
	case 3:
		Cprintf("③", 12);
		break;
	case 4:
		Cprintf("④", 12);
		break;
	case 5:
		Cprintf("⑤", 12);
		break;
	case 6:
		Cprintf("⑥", 12);
		break;
	case -1:
		Cprintf("①", 9);
		break;
	case -2:
		Cprintf("②", 9);
		break;
	case -3:
		Cprintf("③", 9);
		break;
	case -4:
		Cprintf("④", 9);
		break;
	case -5:
		Cprintf("⑤", 9);
		break;
	case -6:
		Cprintf("⑥", 9);
		break;
	default:
		break;
	}
}
void Cprintf(char* str, WORD color, ...) {
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(handle, color);
	cout << str;
	SetConsoleTextAttribute(handle, colorOld);
	/*
	Cprintf("H", 10);//绿色
	Cprintf("e", 9);//蓝色
	Cprintf("l", 12);//红色
	Cprintf("l", 11);//青色
	Cprintf("o", 13);//粉色
	Cprintf("W", 15);//白
	Cprintf("o", 2);//军绿
	Cprintf("r", 5);//紫
	Cprintf("l", 8);//灰
	Cprintf("d", 14);//黄
	Cprintf("!", 4);//棕
	*/
}
void CprintNum(int num, int color)
{
	char str[4];
	sprintf_s(str,"%d",num);
	Cprintf(str,color);
}