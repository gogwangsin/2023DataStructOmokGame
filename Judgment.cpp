#include "Judgment.h"

void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
Judgment::Judgment()
{
	ZeroMemory(mMap, sizeof(int) * sizeof(mMap) / sizeof(int));
	mPlayer = BlackPlayer;
	mTurn = true;
	mPre = 0;
	mwhiteCount = 0;
	mblackCount = 0;

}


Judgment::~Judgment()
{
}
//------ 함수 포인터를 셋팅	------
void Judgment::SetYourFunc(
	void(*pfuncBlackAttack) (int* x, int* y),
	void(*pfuncBlackDefence)(int  x, int  y),
	void(*pfuncWhiteAttack) (int* x, int* y),
	void(*pfuncWhiteDefence)(int  x, int  y))
	//--------------------------------
{
	// 흑돌 함수
	m_funcBlackAttack = pfuncBlackAttack;
	m_funcBlackDefence = pfuncBlackDefence;

	// 백돌 함수
	m_funcWhiteAttack = pfuncWhiteAttack;
	m_funcWhiteDefence = pfuncWhiteDefence;

}
int Judgment::playBlack(int x, int y)
{
	if (0 <= x && x <= MapSize)
	{
		if (0 <= y && y <= MapSize)
		{
			if (mMap[y + 10][x + 10] == 0)
			{
				mPre = BlackPlayer;
				mPlayer = BlackPlayer;

				mMap[y + 10][x + 10] = BlackPlayer;
				mCurrentPosition.first = x + 10;
				mCurrentPosition.second = y + 10;
				mTurn = !mTurn;

				if (EndGame(mCurrentPosition) == 555)
				{
					return -555;
				}
				else
				{
					mTestPosition.first = mCurrentPosition.first;
					mTestPosition.second = mCurrentPosition.second;

					return Foul();
				}
			}
			else
			{
				return -999;

			}
		}
		else
		{
			return -888;
		}
	}
	else
	{
		return -888;
	}

}

int Judgment::playWhite(int x, int y)
{
	if (0 <= x && x <= MapSize)
	{
		if (0 <= y && y <= MapSize)
		{
			if (mMap[y + 10][x + 10] == 0)
			{
				mPre = WhitePlayer;
				mMap[y + 10][x + 10] = WhitePlayer;
				mPlayer = WhitePlayer;
				mCurrentPosition.first = x + 10;
				mCurrentPosition.second = y + 10;
				mTurn = !mTurn;

				if (EndGame(mCurrentPosition) == 555)
				{
					return 555;
				}
				else
				{
					mTestPosition.first = mCurrentPosition.first;
					mTestPosition.second = mCurrentPosition.second;

					return Foul();
				}
			}
			else
			{
				return 999;

			}
		}
		else
		{
			return 888;
		}
	}
	else
	{
		return 888;
	}
}

void Judgment::GamePlay()
{
	int result = 0;
	int posX, posY;
	bool game = 1;
	vector<pair<int, int>> positions;
	vector<int> stones;

	int key2 = 0;

	while (game)
	{

		game = 0;
		if (mTurn)
			stones.push_back(WhitePlayer);
		else
			stones.push_back(BlackPlayer);
		if (mTurn)
		{
			/* 흑돌 차례 */
			gotoxy(0, 0);
			cout << "흑돌 차례" << endl << endl << endl;;
			auto start = high_resolution_clock::now();

			m_funcBlackAttack(&posX, &posY);

			auto duration = high_resolution_clock::now() - start;
			cout << "제한시간 " << Timeout / 1000.0f << "초 중  " << duration_cast<milliseconds>(duration).count();
			cout << " msec 만큼 사용                                  " << endl;

			m_funcWhiteDefence(posX, posY);
			if (duration_cast<milliseconds>(duration).count() >= Timeout)
				result = -3000;
			else
				result = playBlack(posX, posY);

			mblackCount++;

		}
		else
		{
			/* 백돌 차례 */
			gotoxy(0, 0);
			cout << "백돌 차례" << endl << endl << endl;;
			auto start = high_resolution_clock::now();

			m_funcWhiteAttack(&posX, &posY);

			auto duration = high_resolution_clock::now() - start;
			cout << "제한시간 " << Timeout / 1000.0f << "초 중  " << duration_cast<milliseconds>(duration).count();
			cout << " msec 만큼 사용                           " << endl;
			m_funcBlackDefence(posX, posY);

			if (duration_cast<milliseconds>(duration).count() >= Timeout)
				result = 3000;
			else
				result = playWhite(posX, posY);
			mwhiteCount++;

		}

		gotoxy(0, 4);

		positions.push_back(make_pair(posX, posY));
		displayMap();

		if (key2 != 27)
		{
			gotoxy(35, 0);
			cout << "스킵을 원하시면 ESC " << endl;
			cout << "다음 수를 보려면 아무키나 누르세요.";
			key2 = _getch();
		}
		else
		{
			gotoxy(27, 0);
			cout << "                                                                  " << endl;
		}
		gotoxy(0, 24);
		switch (result)
		{
		case 33:
			cout << "흑 삼삼 반칙 패." << endl;
			break;
		case 44:
			cout << "흑 사사 반칙 패." << endl;
			break;
		case -66:
			cout << "흑 육목 반칙 패." << endl;
			break;
		case 66:
			cout << "백 육목 승." << endl;
			break;
		case 555:
			cout << "백 승." << endl;
			break;
		case -555:
			cout << "흑 승." << endl;
			break;
		case -999:
			cout << "흑돌이 이미 다른돌이 있는 자리에 놓았기 때문에 패배." << endl;
			break;
		case -888:
			cout << "흑돌이 바둑판 밖에다 놓았기 때문에 패배." << endl;
			break;
		case 999:
			cout << "백돌이 이미 다른돌이 있는 자리에 놓았기 때문에 패배." << endl;
			break;
		case 888:
			cout << "백돌이 바둑판 밖에다 놓았기 때문에 패배." << endl;
			break;
		case -3000:
			cout << "흑돌이 시간 제한을 넘겨 패배." << endl;
			break;
		case 3000:
			cout << "흑돌이 시간 제한을 넘겨 패배." << endl;
			break;
		default:
			game = 1;
			break;
		}
	}

	int key = 1;
	int count = positions.size() - 1;
	int preStone;

	pair<int, int> temp = positions[count];;

	gotoxy(0, 26);
	cout << " ← : 이전 수 보기  , → : 다음 수 보기" << endl;

	if (stones[count] == BlackPlayer)
		mMap[temp.second + 10][temp.first + 10] = 3;

	if (stones[count] == WhitePlayer)
		mMap[temp.second + 10][temp.first + 10] = 4;

	gotoxy(0, 27);
	displayMap();

	mMap[temp.second + 10][temp.first + 10] = 0;

	while (key != 27)
	{
		fflush(stdin);
		key = _getch();


		if (key == 77)
		{
			count++;
			if (count >= positions.size())
			{
				count = positions.size() - 1;

			}
			else
				mTurn = !mTurn;
		}
		else if (key == 75)
		{
			count--;
			if (count <= 0)
			{
				count = 0;

			}
			else
				mTurn = !mTurn;

		}
		if (key == 77)
		{
			cout << count << endl;

			mMap[temp.second + 10][temp.first + 10] = stones[count];
		}
		if (key == 75)
		{
			mMap[temp.second + 10][temp.first + 10] = 0;
		}

		temp = positions[count];

		if (stones[count] == BlackPlayer)
			mMap[temp.second + 10][temp.first + 10] = 3;

		if (stones[count] == WhitePlayer)
			mMap[temp.second + 10][temp.first + 10] = 4;

		gotoxy(0, 27);
		displayMap();

		cout << count << " / " << positions.size() - 1 << "                     " << endl;


	}
}
int Judgment::Foul()
{
	int foul = 0;

	foul = Foul66(mTestPosition, 1);
	if (mPlayer == BlackPlayer)
	{
		if (0 == foul)
			foul = Foul44(mTestPosition, 1);

		if (0 == foul)
			foul = Foul33(mTestPosition, 1);
	}
	return foul;
}

int	Judgment::Foul33(pair<int, int> position, bool flag)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int PretempX, PretempY;
	int PosttempX, PosttempY;
	int foulLine33 = 0;

	bool empty;
	float attackPoint[8] = { 0, };
	pair<int, int> Point[8];
	pair<int, int> emptyPos;
	bool check[8] = { false, };
	float checkWeight[8] = { 0.0f, };

	/* 열린 두개의 삼삼 */
	for (int way = 0; way < 8; ++way)
	{
		tempX = position.first;
		tempY = position.second;
		empty = true;

		for (int move = 0; move < 6; ++move)
		{

			tempX += movePoint[way][0];
			tempY += movePoint[way][1];

			PosttempX = tempX + movePoint[way][0];
			PosttempY = tempY + movePoint[way][1];

			PretempX = tempX - movePoint[way][0];
			PretempY = tempY - movePoint[way][1];

			if (VirtualMapMin <= tempX && tempX <= VirtualMapMax && VirtualMapMin <= tempY && tempY <= VirtualMapMax)
			{
				/* 현재 자리에 플레이어 돌이 있다면 */
				if (mMap[tempY][tempX] == mPlayer)
				{
					/* 현재 빈칸을 지나오지 않았다면 first의 돌을 증가시킨다.*/
					if (empty)
						Point[way].first++;
					else /* 빈칸을 지나왔다면 second 증가. */
						Point[way].second++;
				}
				/* 현재 자리가 빈칸 이라면 */
				else if (mMap[tempY][tempX] == 0)
				{
					/* 아직 빈칸을 지나오지 않았다면 */
					if (empty)
					{
						/* 빈칸 자리를 저장 */
						emptyPos.first = tempX;
						emptyPos.second = tempY;

						if (flag)
						{
							/* 이 빈칸이 유효한 자리가 아니라면 숫자를 더 이상 세지 않는다. */
							if (Foul44(make_pair(tempX, tempY), 0) || Foul33(make_pair(tempX, tempY), 0) || Foul66(make_pair(tempX, tempY), 0))
							{
								checkWeight[way] = 1.0f;
								break;
							}
							/* 유효한 자리라면 그냥 빈칸을 지나왔다고 표시하고 */
							/* 다음 자리가 상대 돌 이라면 이전에 돌들이 연속되여 있다는 소리기 때문에 공격 포인트가 된다.*/
							else
							{
								//	if (mMap[PosttempY][PosttempX] != 0 && mMap[PosttempY][PosttempX] != mPlayer)
									/* 다음 자리가 벽이 아니라면 상대 돌이면 */
								if (10 <= PosttempX && PosttempX <= 27 && 10 <= PosttempY && PosttempY <= 27)
								{
									attackPoint[way] = 0.5f;
								}
								else
								{

								}
								empty = false;
							}
						}
						/* 빈자리의 유효성을 확인할때는 빈자리는 그냥 빈자리다. */
						else
							empty = false;
					}
					/* 이미 빈칸을 한번 지나왔다면 */
					else
					{
						/* 빈칸의 다음칸이 다른 플레이어라면 가중치 0.5인 막힘을 표시한다. */
						/* 다음 칸이 빈칸이나 같은 돌이라면 막히지 않았다. */
						if (flag)
						{
							if (mMap[PosttempY][PosttempX] == mPlayer && mMap[PretempY][PretempX] == mPlayer)
								mMap[emptyPos.second][emptyPos.first] = mPlayer;
							/*유효하지 않다면 막힘 체크. */
							if (Foul44(make_pair(tempX, tempY), 0) || Foul33(make_pair(tempX, tempY), 0) || Foul66(make_pair(tempX, tempY), 0))
							{
								checkWeight[way] = 1.5f;
							}
							if (mMap[PosttempY][PosttempX] == mPlayer && mMap[PretempY][PretempX] == mPlayer)
								mMap[emptyPos.second][emptyPos.first] = 0;

							if (mMap[PosttempY][PosttempX] != 0 && mMap[PosttempY][PosttempX] != mPlayer)
							{
								checkWeight[way] = 0.5f;
							}
						}
						break;

					}
				}
				/* 다른 플레이어 돌을 만났다면  */
				else
				{
					/* 이전 돌이 빈칸이라면 */
					if (mMap[PretempY][PretempX] == 0)
					{
						/* 빈칸뒤에 다른 돌인데 앞에 놓은 돌이 하나도 없다면 막기 1.5 */
						if (Point[way].first == 0)
							checkWeight[way] = 1.5f;
						else if (Point[way].first == 1)
							checkWeight[way] = 1.0f;
						else
							checkWeight[way] = 0.5f;
					}
					else
						checkWeight[way] = 1.5f;
					break;
				}
			}
			/* 칸을 넘어감. */
			else
			{
				/* 넘어가기 전 돌이 플레이어돌이라면 막힌것을 표시한다.*/
				if (mMap[PretempY][PretempX] == mPlayer)
					checkWeight[way] = 1.5f;
				else
					checkWeight[way] = 0.5f;

				break;
			}
		}
	}


	//cout << "flag  " << flag << "   weight  ";
	for (int i = 0; i < 4; ++i)
	{
		/*	if (flag)
			{
				cout << checkWeight[i] << " " << checkWeight[i + 4] << " ";
				cout << attackPoint[i] << " " << attackPoint[i + 4] << "     ";
			}*/
		if (checkWeight[i] + checkWeight[i + 4] - attackPoint[i] - attackPoint[i + 4] >= 0.5f)
			check[i] = true;
	}
	/*if (flag)
		cout << endl;*/

	int count = 0;
	int count1 = 0;
	int count2 = 0;
	int c = 0;

	for (int i = 0; i < 4; ++i)
	{
		/*	if (flag)
			{
				cout << i << "  " << Point[i].first << "  " << Point[i].second << "  " << check[i] << endl;
				cout << i << "  " << Point[i + 4].first << "  " << Point[i + 4].second << "  " << check[i + 4] << endl;
			}*/
		count = Point[i].first + Point[i + 4].first;
		if (count < 2)
		{
			count1 = Point[i].first + Point[i].second + Point[i + 4].first;
			if (2 == count1)
			{
				count = count1;


			}
			count2 = Point[i + 4].first + Point[i + 4].second + Point[i].first;
			if (2 == count2)
			{
				count = count2;

			}
		}


		if (2 == count)
		{
			if (Point[i].first + Point[i].second + Point[i + 4].first > 2)
				foulLine33--;
			else if (Point[i].first + Point[i + 4].second + Point[i + 4].first > 2)
				foulLine33--;

			foulLine33++;
			if (check[i])
				c++;
			if (check[i + 4])
				c++;
		}
	}

	if (foulLine33 - c <= 1)
		foulLine33 = 0;
	if (1 < foulLine33)
		return 33;
	else
		return 0;

}
int	Judgment::Foul44(pair<int, int> position, bool flag)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int PretempX, PretempY;
	int PosttempX, PosttempY;
	int foulLine44 = 0;

	bool empty;
	pair<int, int> Point[8];
	pair<int, int> emptyPos;

	int attackPoint[8] = { 0 , };

	bool check[8] = { false, };
	/*닫힌 44도 44다. */
	for (int way = 0; way < 8; ++way)
	{
		tempX = position.first;
		tempY = position.second;
		empty = true;
		for (int move = 0; move < 6; ++move)
		{
			tempX += movePoint[way][0];
			tempY += movePoint[way][1];

			PosttempX = tempX + movePoint[way][0];
			PosttempY = tempY + movePoint[way][1];

			PretempX = tempX - movePoint[way][0];
			PretempY = tempY - movePoint[way][1];

			if (VirtualMapMin <= tempX && tempX <= VirtualMapMax && VirtualMapMin <= tempY && tempY <= VirtualMapMax)
			{
				/* 현재 자리에 플레이어 돌이 있다면 */
				if (mMap[tempY][tempX] == mPlayer)
				{
					/* 현재 빈칸을 지나오지 않았다면 first의 돌을 증가시킨다.*/
					if (empty)
						Point[way].first++;
					else /* 빈칸을 지나왔다면 second 증가. */
						Point[way].second++;
				}
				/* 현재 자리가 빈칸 이라면 */
				else if (mMap[tempY][tempX] == 0)
				{
					/* 아직 빈칸을 지나오지 않았다면 */
					if (empty)
					{
						/* 빈칸 자리를 저장 */
						emptyPos.first = tempX;
						emptyPos.second = tempY;

						if (flag)
						{
							/* 이 빈칸이 유효한 자리가 아니라면 숫자를 더 이상 세지 않는다. */
							if (Foul44(make_pair(tempX, tempY), 0) || Foul33(make_pair(tempX, tempY), 0) || Foul66(make_pair(tempX, tempY), 0))
							{
								check[way] = true;
								break;
							}
							else
							{
								empty = false;
								/* 빈칸 다음에 플레이어 돌이 있거나 이전에 플레이어 돌이 있으면 (연속된 돌이 된다면) 공격할수 있는 자리라고 생각한다. */
								/* 두칸 연속 빈칸은 소용 없으므로 &&로 걸른다. */
								if ((mMap[PosttempY][PosttempX] == mPlayer || mMap[PretempY][PretempX] == mPlayer) && mMap[PosttempY][PosttempX] != 0)
									attackPoint[way]++;
							}
						}
						/* 빈칸이 유효한 자리라면 빈칸을 지나 왔다고 표시한다. */
						else
							empty = false;
					}
					/* 이미 빈칸을 한번 지나왔다면 */
					else
					{
						/* 이미 지나온 돌의 개수가 2개라면 빈칸에 대한 유효 검사를 해야한다. 여기에 놓을수 없게 되면 막힌걸로 친다. */
						if (Point[way].first + Point[way].second == 2)
						{
							/* 만약 두번째 빈칸 다음칸이 플레이어 돌이라면 이전에 빈칸을 플레이어의 돌로 채워 넣은뒤 검사한다. (6목을 검사하기위해) */
							/* 다음칸에 플레이어돌이 없는데 빈칸에 돌을 두고 반대편 6목으로 인해 문제가 발생할수 있음. */
							if (mMap[PosttempY][PosttempX] == mPlayer)
							{
								mMap[emptyPos.second][emptyPos.first] = mPlayer;
							}
							if (flag)
							{						/*유효하지 않다면 막힘 체크. */
								if (Foul44(make_pair(tempX, tempY), 0) || Foul33(make_pair(tempX, tempY), 0) || Foul66(make_pair(tempX, tempY), 0))
									check[way] = true;
							}
							/* 빈칸에 임시로 넣었던 돌을 다시 빈칸으로 만든다. */
							if (mMap[PosttempY][PosttempX] == mPlayer)
							{
								mMap[emptyPos.second][emptyPos.first] = 0;
							}
						}
						/* 두번째 빈칸까지 지나온 돌이 3개라면 두번째 빈칸은 유효하던 아니던 상관없다. 첫번째 빈칸의 유효 검사가 필요하다. */
						else if (Point[way].first + Point[way].second == 3)
						{
							/* 유효하지 않다면 첫번째 빈칸 뒤에 돌의 숫자는 무의미하다.*/
							if (flag)
							{
								if (Foul44(make_pair(emptyPos.first, emptyPos.second), 0) || Foul33(make_pair(emptyPos.first, emptyPos.second), 0) || Foul66(make_pair(emptyPos.first, emptyPos.second), 0))
								{
									check[way] = true;
									/* 빈칸 이후의 돌을 0으로 변경. */
									Point[way].second = 0;
								}
							}
						}
						break;
					}
				}
				/* 빈칸도 아니고 내 돌도 아니면 상대방 돌이라는 뜻*/
				else
				{
					check[way] = true;
					break;
				}

			}
			else /* 범위를 넘어간 돌 체크*/
			{
				/*44는 벽에서 한칸 떨어져있으면 굳이 막힘 표시 안해도 될듯함.
				범위를 넘어갔는데 이전에 돌이 플레이어 돌이면 막혔다고 표시한다. */
				if (mMap[PretempY][PretempX] == mPlayer)
					check[way] = true;

				/* 범위가 넘어갔으니 더이상 이동할 필요 없다. */
				break;
			}
		}
	}
	int count = 0;
	int count1 = 0;
	int count2 = 0;
	int c = 0;
	for (int i = 0; i < 4; ++i)
	{
		/*	if (flag)
			{
				cout << i << "  " << Point[i].first << "  " << Point[i].second << "  " << check[i] << endl;
				cout << i << "  " << Point[i + 4].first << "  " << Point[i + 4].second << "  " << check[i + 4] << endl;
			}*/

		count = Point[i].first + Point[i + 4].first;

		if (count < 3)
		{
			count1 = Point[i].first + Point[i].second + Point[i + 4].first;
			if (3 == count1)
			{
				foulLine44++;
				if (check[i])
					c++;
				if (check[i + 4])
					c *= 2;
				if (attackPoint[i])
					c--;
				if (attackPoint[i + 4])
					c--;
			}
			count2 = Point[i + 4].first + Point[i + 4].second + Point[i].first;
			if (3 == count2)
			{
				foulLine44++;
				if (check[i + 4])
					c++;
				if (check[i])
					c *= 2;
				if (attackPoint[i])
					c--;
				if (attackPoint[i + 4])
					c--;
			}
		}
		if (3 == count)
		{
			foulLine44++;
			if (abs((check[i] - attackPoint[i]) > 0) && abs((check[i + 4] - attackPoint[i + 4]) > 0))
			{
				foulLine44--;
			}
			else
			{
				if (check[i])
					c++;
				if (check[i + 4])
					c++;
				if (attackPoint[i])
					c--;
				if (attackPoint[i + 4])
					c--;
			}
		}
	}
	if (c < 0)
		c = 0;
	//if (flag)
//		cout << "44 : " << foulLine44 << "  " << c << "   " <<   endl;
	if (abs(foulLine44 * 2 - c) <= 1)
	{
		foulLine44 = 0;
	}

	if (1 < foulLine44)
		return 44;
	else
		return 0;
}
int	Judgment::Foul66(pair<int, int> position, bool flag)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int foulLine66 = 0;

	bool empty;
	pair<int, int> Point[8];
	bool check[8] = { false, };

	for (int way = 0; way < 8; ++way)
	{
		tempX = position.first;
		tempY = position.second;
		empty = true;
		for (int move = 0; move < 6; ++move)
		{
			tempX += movePoint[way][0];
			tempY += movePoint[way][1];
			if (VirtualMapMin <= tempX && tempX <= VirtualMapMax && VirtualMapMin <= tempY && tempY <= VirtualMapMax)
			{
				if (mMap[tempY][tempX] == mPlayer)
					Point[way].first++;
				else
					break;
			}
			else
			{
				check[way] = true;
				break;
			}
		}
	}

	/* 옆에 다른 돌이 붙어있을때 0으로 만드는 것을 수정해야함. 아니면 승리 검사 함수를 따로 만들던지*/
	int count;

	int c = 0;

	for (int i = 0; i < 4; ++i)
	{
		//if (flag)
		//{
		//	cout << i << "  " << Point[i].first << "  " << Point[i].second << "  " << check[i] << endl;
		//	cout << i << "  " << Point[i + 4].first << "  " << Point[i + 4].second << "  " << check[i + 4] << endl;
		//}
		count = Point[i].first + Point[i + 4].first;
		if (5 <= count)
			break;
	}
	/*if (flag)
		cout << "66 : " << foulLine66 << "  " << c << endl;*/


	if (5 <= count)
	{
		if (mPlayer == BlackPlayer)
			return -66;
		if (mPlayer == WhitePlayer)
			return 66;

		return 0;
	}
	else
		return 0;
}

int Judgment::EndGame(pair<int, int> position)
{
	int movePoint[8][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } };
	int tempX, tempY;
	int foulLine66 = 0;

	bool empty;
	pair<int, int> Point[8];
	bool check[8] = { false, };

	for (int way = 0; way < 8; ++way)
	{
		tempX = position.first;
		tempY = position.second;
		empty = true;
		for (int move = 0; move < 6; ++move)
		{
			tempX += movePoint[way][0];
			tempY += movePoint[way][1];
			if (10 <= tempX && tempX <= 27 && 10 <= tempY && tempY <= 27)
			{
				if (mMap[tempY][tempX] == mPlayer)
					Point[way].first++;
				else
					break;
			}
			else
			{
				check[way] = true;
				break;
			}
		}
	}

	int count;
	int result = 0;
	int c = 0;

	for (int i = 0; i < 4; ++i)
	{
		count = Point[i].first + Point[i + 4].first;

		if (4 <= count)
		{
			if (count == 4)
			{
				result = 4;
			}
		}


	}
	if (result == 4)
	{
		return 555;
	}
	else
		return 0;
}



void Judgment::displayMap()
{
	cout << "   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8" << endl;
	for (int i = 0; i <= MapSize; ++i)
	{
		cout << i % 10 << " ";
		for (int j = 0; j <= MapSize; ++j)
		{

			if (mMap[i + 10][j + 10] == 0)
			{
				cout << "╋";
			}
			else if (mMap[i + 10][j + 10] == BlackPlayer)
			{
				cout << "○";
			}
			else if (mMap[i + 10][j + 10] == WhitePlayer)
			{
				cout << "●";
			}
			else if (mMap[i + 10][j + 10] == BlackCursor)
			{
				cout << "★";
			}
			else if (mMap[i + 10][j + 10] == WhiteCursor)
			{
				cout << "☆";
			}
		}
		cout << endl;
	}
}