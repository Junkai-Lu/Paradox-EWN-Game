#include "stdafx.h"
#include "EWNdefine.h"

#pragma  once

#define MC_CONSTANT 30000				//蒙特卡罗模拟常数
#define GUMC_CONSTANT 10000				//蒙特卡罗评估常数
#define ESTIMATE_CONSTANT 10000			//开局测试常数
#define FILTER_MC_CONSTANT 10000		//FILTER算法常数
#define FIX_FILTER_MC_CONSTANT 10000	//FILTER算法常数
#define BOARD_TEST_CONSTANT 20000		//开局测试常数

#define UCT_MC_TIMES 1					//UCT中的MC评价常数
#define UCT_TIMES 10000000				//UCT迭代的次数
#define UCT_LIMIT 120					//UCT算法允许的时间

//MC

void RndMove(Board &CB,int Piece);
int GetMCWinner(Board &CB,int NextPlayer);
float GetMCEvalution(Board &CB, int NextPlayer, int Winner, int times);
void MonteCarloMove(Board &CB,int Piece);

//Filter

void RndFilterMove(Board &CB,int Piece);
int GetFilterMCWinner(Board &CB,int NextPlayer);
float GetFilterMCEvalution(Board &CB,int NextPlayer,int Winner,int times);
void FilterMCMove(Board &CB,int Piece);

//FixFilter

void RndFixFilterMove(Board &CB,int Piece);
int GetFixFilterMCWinner(Board &CB,int NextPlayer);
float GetFixFilterMCEvalution(Board &CB, int NextPlayer, int Winner, int times);
void FixFilterMCMove(Board &CB,int Piece);

//GreedUtilityMC
int GetFMCWinnerByFirstDice(Board &CB,int NextPlayer,int FirstPiece);
float GetGUMCEvalution(Board &CB, int NextPlayer, int Winner, int times);
void GreedUtilityMCMove(Board &CB,int Piece);

//FilterBoardEvalution
int GetFilterBoardEvalution(Board &CB,int NextPlayer,int Winner,int times);



//UCT For EWN
class UCTBoard:public Board
{
public:
	UCTBoard();//构造函数。一般是为了复制
	UCTBoard(int Player,int Array[SIZE][SIZE],int step);//构造函数。一般用来创造根节点
	UCTBoard(int Player,int Array[SIZE][SIZE],int Piece,Loc mLoc,int step);//构造函数，一般用来创建子节点

	//固定信息
	int Owner;//UCTBoard的所属玩家
	int Times;//被尝试过的次数
	int BoardWinner;//这个局面的胜利者
	bool PieceLife[7];//六个子的生存状态
	int ExistChildNum[7];//每个概率节点下已存在的子节点的数量，ChildNodes[N]从0到ChildNum[N]-1均有指向。需要初始化，R代表骰子
	int TotalChildNum[7];//每个概率节点下所有子节点数目
	Move UCTMove[7][3];//存储招式。在UCTBoard生成的时候会更新一次招式列表，列表按照[某个数][招式编号]进行存储。仅存储存在的棋子的招式
	UCTBoard* ChildNodes[7][3];//指向子节点们的指针，最多有3*6 = 18个

	//收益与UCB值
	float UCBValue;//UCB值
	float AvgValue;//平均收益
	float RefreshAvgValue();//刷新本节点的收益。
	float RefreshUCBValue(int Total);//根据平均收益更新UCB值
	UCTBoard* ExpandUCTBoard(int ExpandNum,int &Total);//扩展UCT节点
};
float UCT_Iteration(UCTBoard &B, int &Total);
void UCTMove(Board &CB,int Piece);
void DeleteUCTBoard(UCTBoard* Root);
void DeleteUCTTree(UCTBoard Root);

extern UCTBoard *UCTNodes[UCT_TIMES];
extern int UCTNodeNum;

