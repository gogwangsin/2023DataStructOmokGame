#pragma once
#include <Windows.h>
#include <iostream>
#include <utility>
#include<conio.h>
#include<vector>

#include <chrono>

using namespace std;
using namespace chrono;


using namespace std;

#define BlackPlayer 1
#define WhitePlayer 2
#define BlackCursor 3
#define WhiteCursor 4

#define MapSize 18
#define VirtualMapMax 28
#define VirtualMapMin 10

#define Timeout 500
/*
	오목 판은 0~ 17 사이의 숫자를 이용한다.


*/
class Judgment
{
private:
	bool mTurn;
	int mblackCount;
	int mwhiteCount;
	int mPlayer;
	int mMap[40][40];
	pair<int, int> mCurrentPosition; //first : x , second : y
	pair<int, int> mTestPosition;     //first : x , second : y
	pair<int, int> mAllWays[8][6];	  //first : x , second : y
	int	mAllWaysConnectedCount[8];

	void(*m_funcBlackAttack)(int* x, int* y);	//흑돌 함수 포인터
	void(*m_funcBlackDefence)(int x, int y);

	void(*m_funcWhiteAttack)(int* x, int* y);	//백돌 함수 포인터
	void(*m_funcWhiteDefence)(int x, int y);

	pair<int, int> mAllLines[4][12];
	int	mAllLinesConnectedCount[4];

	int mPre;
	pair<int, int> mPrePos;
public:
	Judgment();
	~Judgment();
	bool getTurn() { return mTurn; }
	int Foul();

	int Foul33(pair<int, int> position, bool flag);
	int Foul44(pair<int, int> position, bool flag);
	int Foul66(pair<int, int> position, bool flag);

	int EndGame(pair<int, int> position);

	int playBlack(int x, int y);
	int playWhite(int x, int y);

	void displayMap();

	void SetYourFunc(
		void(*pfuncBlackAttack)(int* x, int* y),
		void(*pfuncBlackDefence)(int x, int y),
		void(*pfuncWhiteAttack)(int* x, int* y),
		void(*pfuncWhiteDefence)(int x, int y));

	void GamePlay();
};

