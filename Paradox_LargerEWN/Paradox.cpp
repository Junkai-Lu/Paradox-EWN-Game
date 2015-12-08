#include "stdafx.h"
#include "EWNdefine.h"
#include "Paradox.h"
#include "windows.h"
#include "stdio.h"
#include "time.h"
#include <iostream>
#include <sstream>

using namespace std;

//MonteCarlo 基础蒙特卡罗算法
void RndMove(Board &CB,int Piece)
{
	int dice;
	Move Moves[6];
	int MoveNum = CB.GetAllMoves(Moves,Piece);
	dice = rand()%MoveNum;
	CB.Move(Moves[dice].Loc,Moves[dice].Piece);
}
int GetMCWinner(Board &CB,int NextPlayer)
{
	//复制传入的棋盘上，根据传入的骰子数列进行操作。返回一次随机移动的胜利者。
	Board NCB = CB;
	int player = NextPlayer;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
		{
			return w;
		}
		RndMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	float Result = (float)Eva / (float)times;
	return Result;
}
void MonteCarloMove(Board &CB,int Piece)
{
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetAllMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//先创建一个新棋盘
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//假设移动了第i位
		float Val = GetMCEvalution(NCB, -f, f, MC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//FilterMC 蒙特卡罗特征算法
void RndFilterMove(Board &CB,int Piece)
{
	int dice;
	Move Moves[6];
	int MoveNum = CB.GetFilterMoves(Moves,Piece);
	dice = rand()%MoveNum;
	CB.Move(Moves[dice].Loc,Moves[dice].Piece);
}
int GetFilterMCWinner(Board &CB,int NextPlayer)
{
	//复制传入的棋盘上，根据传入的骰子数列进行操作。返回一次随机移动的胜利者。
	Board NCB = CB;
	int player = NextPlayer;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
		{
			return w;
		}
		RndFilterMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetFilterMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetFilterMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	float Result = (float)Eva / (float)times;
	return Result;
}
void FilterMCMove(Board &CB,int Piece)
{
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetFilterMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//先创建一个新棋盘
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//假设移动了第i位
		float Val = GetFilterMCEvalution(NCB, -f, f, FILTER_MC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//FixFilterMC 蒙特卡罗特征算法修正案
void RndFixFilterMove(Board &CB,int Piece)
{
	int dice;
	Move Moves[6];
	int MoveNum = CB.GetFixFilterMoves(Moves,Piece);
	dice = rand()%MoveNum;
	CB.Move(Moves[dice].Loc,Moves[dice].Piece);
}
int GetFixFilterMCWinner(Board &CB,int NextPlayer)
{
	//复制传入的棋盘上，根据传入的骰子数列进行操作。返回一次随机移动的胜利者。
	Board NCB = CB;
	int player = NextPlayer;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
		{
			return w;
		}
		RndFixFilterMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetFixFilterMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetFixFilterMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	float Result = (float)Eva / (float)times;
	return Result;
}
void FixFilterMCMove(Board &CB,int Piece)
{
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetFixFilterMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//先创建一个新棋盘
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//假设移动了第i位
		float Val = GetFixFilterMCEvalution(NCB, -f, f, FIX_FILTER_MC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//GreedUtilityMC 贪婪效用蒙特卡罗算法
int GetFMCWinnerByFirstDice(Board &CB,int NextPlayer,int FirstPiece)
{
	//复制传入的棋盘上。首先移动指定的棋子，然后再开始随机移动。棋子范围为-6至6
	Board NCB = CB;
	int player = NextPlayer;
	int w = NCB.Winner();
	if(w!=0)
		return w;
	RndFilterMove(NCB,FirstPiece);
	player = -player;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
			return w;
		RndFilterMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetGUMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	//获得一个棋子的收益
	//假如某个棋子不存在，其收益为周边棋子中的最高者。
	//一个棋子的收益，为接下来是6个骰子数时的蒙特卡罗过程的平均数。

	Board NCB = CB;
	int Eva[7];
	bool PieceAlive[7];
	//首先，判别所有棋子的生存状态。
	for(int i=1;i<=6;i++)
	{
		Eva[i]=0;//顺道初始化一下Eva数组
		if(CB.GetPieceLife(NextPlayer*i))
			PieceAlive[i]=true;
		else
			PieceAlive[i]=false;
	}

	//对所有存在的棋子做一次蒙特卡罗判别，确定收益
	for(int PieceNum=1;PieceNum<=6;PieceNum++)
	{
		if(PieceAlive[PieceNum])
		{
			for(int i =0;i<times;i++)
			{
				if(GetFMCWinnerByFirstDice(NCB,NextPlayer,PieceNum)==Winner)
					Eva[PieceNum]++;
			}
		}
	}
	//确定不存在的棋子的收益
	for(int PieceNum=1;PieceNum<=6;PieceNum++)
	{
		if(PieceAlive[PieceNum]==false)
		{
			int s_Piece = CB.GetSmallerPiece(PieceNum);
			int l_Piece = CB.GetLargerPiece(PieceNum);
			if(s_Piece!=0&&l_Piece!=0)//同时存在s_Piece与l_Piece的情况下，取评估值较大的一个
			{
				if(Eva[s_Piece]>=Eva[l_Piece])
					Eva[PieceNum] = Eva[s_Piece];
				else
					Eva[PieceNum] = Eva[l_Piece];
			}
			else if(s_Piece==0&&l_Piece!=0)//只存在l_Piece的情况下，取l_Piece的值
				Eva[PieceNum] = Eva[l_Piece];
			else if(s_Piece!=0&&l_Piece==0)//只存在s_Piece的情况下，取s_Piece的值
				Eva[PieceNum] = Eva[s_Piece];
			else//都不存在的情况下
			{
				cout<<"GetFMCAvgEvalution函数出错，不存在任何棋子";
				system("pause");
			}
		}
	}
	
	//确定最终收益
	float Result = 0;
	for(int i=1;i<=6;i++)
	{
		Result += ((float)Eva[i] / (float)times) / 6;
	}
	return Result;
}
void GreedUtilityMCMove(Board &CB,int Piece)
{
	//贪婪效用蒙特卡罗
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetFilterMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//先创建一个新棋盘
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//假设移动了第i位
		float Val = GetGUMCEvalution(NCB, -f, f, GUMC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//FilterBoardEvalution
int GetFilterBoardEvalution(Board &CB,int NextPlayer,int Winner,int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetFilterMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	return Eva;
}

//UCT For EWN 爱恩斯坦UCT算法
UCTBoard::UCTBoard()
{
	for(int i=1;i<=6;i++)
	{
		ExistChildNum[i] = 0;//创建时候的子节点数目为0
		//HaveFirstTimeNode[i] = true;//创建时候所有接续节点都未曾被玩过
	}
	UCBValue =0;//创建时的UCB值为0
	AvgValue =0;//创建时候的平均收益为0
	Times=1;//被创造时候就应该算作访问一次了
}
UCTBoard::UCTBoard(int Player,int Array[SIZE][SIZE],int step)
{
	//创建棋盘
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			board[j][i] = Array[j][i];
		}
	}
	//为某些参数赋值
	Owner = Player;
	BoardWinner = Winner();
	Step = step;
	for(int i=1;i<=6;i++)
		PieceLife[i] = GetPieceLife(Owner*i);
	UCBValue =0;//创建时的UCB值为0
	AvgValue =0;//创建时候的平均收益为0
	Times=1;//被创造时候就应该算作访问一次了

	//生成所有的招式。
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//如果第N个棋子存在
		{
			TotalChildNum[i] = GetFilterMoves(UCTMove[i],Owner*i);//确定每个存在棋子下面的招式与招式总数
			ExistChildNum[i] = 0;//创建时候的子节点数目为0
			//HaveFirstTimeNode[i] = true;//创建时候所有接续节点都未曾被玩过
		}
	}
}
UCTBoard::UCTBoard(int Player,int Array[SIZE][SIZE],int Piece,Loc mLoc,int step)
{
	//创建移动后的棋盘
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			board[j][i] = Array[j][i];
		}
	}
	Step = step;
	Move(mLoc,Piece);//移动函数
	
	//为某些参数赋值
	Owner = Player;
	BoardWinner = Winner();
	for(int i=1;i<=6;i++)
		PieceLife[i] = GetPieceLife(Owner*i);
	UCBValue =0;//创建时的UCB值为0
	AvgValue =0;//创建时候的平均收益为0
	Times=1;//被创造时候就应该算作访问一次了

	//生成所有的招式。
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//如果第N个棋子存在
		{
			TotalChildNum[i] = GetFilterMoves(UCTMove[i],Owner*i);//确定每个存在棋子下面的招式与招式总数
			ExistChildNum[i] = 0;//创建时候的子节点数目为0
			//HaveFirstTimeNode[i] = true;//创建时候所有接续节点都未曾被玩过
		}
	}
}
float UCTBoard::RefreshAvgValue()
{
	/*	收益原则为：假如一个骰子对应的棋子存在。则收益为本骰子对应的子节点的平均收益。
		如果一个骰子对应的棋子不存在，如果只有一个备选棋子的情况下，为备选棋子的子节点的平均收益。
		如果存在两个备选棋子，则为这两个备选棋子的所有子节点的平均收益。
		最终收益为 Σ(N的收益/6),n ={1,2,3,4,5,6}
	*/
	float PieceValue[7];
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//假如棋子i存在
		{
			float Value = 0;
			for(int j=0;j<ExistChildNum[i];j++)
				Value+=ChildNodes[i][j]->AvgValue;
			PieceValue[i] = Value/ExistChildNum[i];
		}
	}
	float TotalValue = 0;
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//假如棋子i存在
		{
			TotalValue+= PieceValue[i];//则总收益加上这个数的收益
			//cout<<i<<" = "<<PieceValue[i]<<endl;
		}
		else//如果棋子i不存在
		{
			//首先获得备选数
			int s_i = 0;//设定s_i为比这个数小的棋子
			int l_i = 0;//设定l_i为比这个数大的棋子
			for(int p = i;p<=6;p++)
			{
				if(PieceLife[p])
				{
					l_i = p;
					break;
				}
			}
			for(int p = i;p>=1;p--)
			{
				if(PieceLife[p])
				{
					s_i = p;
					break;
				}
			}
			//然后根据备选数的情况进行判定
			if(s_i!=0&&l_i!=0)
			{
				//根据备选数的收益决定
				if(PieceValue[s_i]>PieceValue[l_i])
					TotalValue+=PieceValue[s_i];
				else
					TotalValue+=PieceValue[l_i];
				//TotalValue += (PieceValue[s_i]+PieceValue[l_i])/2;//这个数的收益周边备选数的平均平均
			}
			else if(s_i!=0&&l_i==0)
				TotalValue += PieceValue[s_i];//这个数的收益与唯一的备选数相同
			else if(s_i==0&&l_i!=0)
				TotalValue += PieceValue[l_i];//这个数的收益与唯一的备选数相同
			else
			{
				cout<<"UCTBoard::RefreshAvgValue函数出错，不存在任何棋子";
				system("pause");
			}
		}
	}
	TotalValue = TotalValue/6;
	AvgValue = 1-TotalValue;//所有决策之后的平均收益
	return AvgValue;
}
float UCTBoard::RefreshUCBValue(int Total)
{
	float t = (float)Times;
	float n = (float)Total;
	float h = (log10(n)) * 2;
	float exploitation = sqrt((h / t));
	float UCBValue = AvgValue + exploitation;
	return UCBValue;
}
UCTBoard* UCTBoard::ExpandUCTBoard(int ExpandNum,int &Total)
{
	Total++;//基准情形时，总尝试次数首先自增1
	UCTBoard *NewB = new UCTBoard(-Owner,board,UCTMove[ExpandNum][ExistChildNum[ExpandNum]].Piece,UCTMove[ExpandNum][ExistChildNum[ExpandNum]].Loc,Step);//创建一个新的棋盘
	UCTNodes[UCTNodeNum] = NewB;
	UCTNodeNum++;
	Board TestB(NewB->board,NewB->Step);//创建测试棋盘
	NewB->AvgValue = GetFilterMCEvalution(TestB,-Owner,Owner,UCT_MC_TIMES);//得到MC评价值
	return NewB;
}
float UCT_Iteration(UCTBoard &B, int &Total)
{
	B.Times++;//被探测的次数+1
	if(B.BoardWinner !=0)//如果游戏已经结束
	{
		B.AvgValue = 1;//对于父节点而言，这个节点的收益肯定是1
		Total++;
		return B.AvgValue;
	}
	if(B.Times ==2)//基准情形之一。如果某个节点不存在任何子概率树，则为其每一个子概率树都生成一个节点。
	{
		for(int i=1;i<=6;i++)
		{
			if(B.PieceLife[i]==true)//如果存在的话
			{
				B.ChildNodes[i][B.ExistChildNum[i]] = B.ExpandUCTBoard(i,Total);//扩展这个节点
				B.ExistChildNum[i]++;//存在的子节点数自增1
			}
		}
		//cout<<"Msg  Toatl UCT Times : "<<Total<<endl;
		B.RefreshAvgValue();//创建全部需要的子节点后，刷新一遍收益值。
		//cout<<"Msg : Value ="<<B.AvgValue<<endl;
		return B.AvgValue;
	}
	else
	{
		int Dice = RndDice();
		int NextNum;//下一个要走的棋子
		int SmallerNum = 0;//设定SmallerNum为比这个数小的棋子
		int LargerNum = 0;//设定LargerNum为比这个数大的棋子
		bool SinglePiece = true;//是否单选项分支。如果有两个棋子可以选择的话为双选项
		if(B.PieceLife[Dice])//如果选中的棋子存在
		{
			NextNum = Dice;
		}
		else//不存在的话需要进行筛选
		{
			for(int p = Dice;p<=6;p++)
			{
				if(B.PieceLife[p])
				{
					LargerNum = p;
					break;
				}
			}
			for(int p = Dice;p>=1;p--)
			{
				if(B.PieceLife[p])
				{
					SmallerNum = p;
					break;
				}
			}
			if(SmallerNum!=0&&LargerNum!=0)
				SinglePiece = false;
			else if(SmallerNum!=0&&LargerNum==0)
				NextNum = SmallerNum;
			else if(LargerNum!=0&&SmallerNum==0)
				NextNum = LargerNum; 
		}
		//随机层结束。SinglePiece = TRUE 情况下，NextNum为单决策棋子。为FALSE情况下，SmallerNum与LargerNum为双决策棋子

		//开始决策层
		bool SingleBaseCase = SinglePiece==true&&B.TotalChildNum[NextNum]>B.ExistChildNum[NextNum];//单选项基准情况
		bool DoubleBaseCase = SinglePiece==false&&((B.TotalChildNum[LargerNum]>B.ExistChildNum[LargerNum])||(B.TotalChildNum[SmallerNum]>B.ExistChildNum[SmallerNum]));//双选项基准情况

		if(SingleBaseCase||DoubleBaseCase)//基准情形之二。单选项扩展NextNum这个数的子概率树
		{
			if(DoubleBaseCase)//如果是双选项的话，要先根据哪一棵树拥有为尝试的节点来变成单选项
			{
				if((B.TotalChildNum[LargerNum]>B.ExistChildNum[LargerNum]))
					NextNum = LargerNum;
				else
					NextNum = SmallerNum;
			}
			B.ChildNodes[NextNum][B.ExistChildNum[NextNum]] = B.ExpandUCTBoard(NextNum,Total);//扩展NextNum的一个节点
			B.ExistChildNum[NextNum]++;//NextNum存在的子节点数自增1
			//cout<<"Msg  Toatl UCT Times : "<<Total<<endl;
			B.RefreshAvgValue();//创建全部需要的子节点后，刷新一遍收益值。
			return B.AvgValue;
		}
		else//推进,也就是说这个子概率下所有的节点都已经被尝试过了。
		{
			int BestNum=0;
			int BestNodeNum=0;
			float BestNodeUCBValue = 0;
			//首先要先选出最大的UCT值
			if(SinglePiece)//单选项
			{
				for(int i =0;i<B.ExistChildNum[NextNum];i++)//一共有ChildNum个节点，而且都已经被探索过了。寻找全部子节点中最大的UCB值。
				{
					B.ChildNodes[NextNum][i]->RefreshUCBValue(Total);//重新计算节点的UCB值
					if(B.ChildNodes[NextNum][i]->UCBValue>=BestNodeUCBValue)
					{
						BestNum=NextNum;
						BestNodeNum =i;
						BestNodeUCBValue = B.ChildNodes[NextNum][i]->UCBValue;
					}
				}
			}
			else//双选项
			{	
				for(int i =0;i<B.ExistChildNum[LargerNum];i++)//先查找LargerNum中最大的UCB。
				{
					B.ChildNodes[LargerNum][i]->RefreshUCBValue(Total);//重新计算节点的UCB值
					if(B.ChildNodes[LargerNum][i]->UCBValue>=BestNodeUCBValue)
					{
						BestNum=LargerNum;
						BestNodeNum =i;
						BestNodeUCBValue = B.ChildNodes[LargerNum][i]->UCBValue;
					}
				}
				for(int i =0;i<B.ExistChildNum[SmallerNum];i++)//再查找SmallerNum中最大的UCB。
				{
					B.ChildNodes[SmallerNum][i]->RefreshUCBValue(Total);//重新计算节点的UCB值
					if(B.ChildNodes[SmallerNum][i]->UCBValue>=BestNodeUCBValue)
					{
						BestNum = SmallerNum;
						BestNodeNum =i;
						BestNodeUCBValue = B.ChildNodes[SmallerNum][i]->UCBValue;
					}
				}
			}
			//cout<<"Msg: BestUCB is Number["<<BestNum<<"] Node["<<BestNodeNum<<"]"<<endl;
			//最佳UCB选取结束，更新这个节点的值。最佳UCB是ChildNode[BestNum][BestNodeNum]
			UCT_Iteration(*B.ChildNodes[BestNum][BestNodeNum],Total);
			B.RefreshAvgValue();//刷新了一下收益
			return B.AvgValue;
		}
	}
	return 0;
}
void UCTMove(Board &CB,int Piece)
{
	UCTNodeNum = 0;
	int f = CB.GetPieceFaction(Piece);
	UCTBoard UCTB(f,CB.board,CB.Step);//创建新的UCT节点
	if(CB.GetPieceLife(Piece))//如果这个棋子存在的话
	{
		int n = f*Piece;
		for(int i=1;i<=6;i++)
			UCTB.PieceLife[i]=false;//设定为死亡。实际是为了让根节点不会拓展除了指定的Piece之外的节点
		UCTB.PieceLife[n]=true;
	}
	else//不存在的话
	{
		int s=CB.GetSmallerPiece(Piece);
		int l=CB.GetLargerPiece(Piece);
		if(s!=0&&l==0)//只有s存在
		{
			int n = f*s;
			for(int i=1;i<=6;i++)
				UCTB.PieceLife[i]=false;//设定为死亡。实际是为了让根节点不会拓展除了指定的Piece之外的节点
			UCTB.PieceLife[n]=true;
		}
		else if(s==0&&l!=0)//只有l存在
		{
			int n = f*l;
			for(int i=1;i<=6;i++)
				UCTB.PieceLife[i]=false;//设定为死亡。实际是为了让根节点不会拓展除了指定的Piece之外的节点
			UCTB.PieceLife[n]=true;
		}
		else if(s!=0&&l!=0)//s和l都存在
		{
			int n = f*l;
			int m = f*s;
			for(int i=1;i<=6;i++)
				UCTB.PieceLife[i]=false;//设定为死亡。实际是为了让根节点不会拓展除了指定的Piece之外的节点
			UCTB.PieceLife[n]=true;
			UCTB.PieceLife[m]=true;
		}
		else
		{
			cout<<"出错啦！"<<endl;
			system("pause");
		}
	}
	
	int Total =0;
	clock_t start;	//设置计时器的变量
	start=clock();
	for(int t=0;t<UCT_TIMES;t++)
	{
		UCT_Iteration(UCTB,Total);
		double totaltime=(double)(clock()-start)/CLOCKS_PER_SEC;
		if(totaltime>=UCT_LIMIT)
			break;
	}
	int BestNum =0;
	int BestNode =0;
	int BestTimeNum = 0;
	int BestTimeNode = 0;
	float BestValue = 0;
	int BestTimeValue = 0;
	for(int p=1;p<=6;p++)//因为子节点除了可以移动的之外的棋子都被设置为“死亡”，所以检查所有子概率树就可以了。
	{
		if(UCTB.PieceLife[p])
		{
			for(int n=0;n<UCTB.ExistChildNum[p];n++)
			{
				if(UCTB.ChildNodes[p][n]->Times>=BestTimeNode)
				{
					BestTimeNum = p;
					BestTimeNode = n;
					BestTimeValue = UCTB.ChildNodes[p][n]->Times;
				}
			}
		}
	}
	Loc mLoc = UCTB.UCTMove[BestTimeNum][BestTimeNode].Loc;
	int mPiece = UCTB.UCTMove[BestTimeNum][BestTimeNode].Piece;
	CB.Move(mLoc,mPiece);
	Cprintf("========================Infomation==========================\n", 8);
	cout << "当前节点平均收益为" << 1 - UCTB.AvgValue << endl;
	cout << "最佳收益节点访问为" << UCTB.ChildNodes[BestTimeNum][BestTimeNode]->Times << endl;
	cout << "最佳收益节点收益为" << UCTB.ChildNodes[BestTimeNum][BestTimeNode]->AvgValue << endl;
	cout << "本次UCT总迭代次数为" << Total << endl;
	Cprintf("============================================================\n", 8);

	for (int i = 0; i < UCTNodeNum; i++)
		delete UCTNodes[i];
}

UCTBoard *UCTNodes[UCT_TIMES] = {NULL};
int UCTNodeNum;

void DeleteUCTBoard(UCTBoard* Root)
{
	for (int n = 1; n <= 6; n++)
	{
		if (Root->ExistChildNum[n] > 0 && Root->ExistChildNum[n] < 4)
		{
			for (int i = 0; i < Root->ExistChildNum[n]; i++)
			{
				DeleteUCTBoard(Root->ChildNodes[n][i]);
				delete Root->ChildNodes[n][i];
			}
		}
	}
}
void DeleteUCTTree(UCTBoard Root)
{
	for (int n = 1; n <= 6; n++)
	{
		for (int i = 0; i < Root.ExistChildNum[n]; i++)
		{
			DeleteUCTBoard(Root.ChildNodes[n][i]);
			//delete Root.ChildNodes[n][i];
		}
	}
}