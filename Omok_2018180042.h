#pragma once

#include <vector>
#include <algorithm>
using std::vector;
using std::sort;


#define BLACK -1
#define WHITE 1
#define DONE 0




enum class CHECKERTYPE_2018180042
{
	NONE,
	BSTONE,
	WSTONE,
	ONESPACEBLACK,
	ONESPACEWHITE

};

enum class PLACEDTYPE_2018180042
{
	NONE,
	WIDTH,
	LENGTH,
	DIAGONAL,
	OPPOSITE

};

struct Point_2018180042
{
	int x;
	int y;

	Point_2018180042()
		: x{}
		, y{}
	{};

	Point_2018180042(int x, int y)
		: x{ x }
		, y{ y }
	{}

	~Point_2018180042() {}

	void init() { x = 0, y = 0; }

	bool operator ==(const Point_2018180042& other)
	{
		if (x == other.x && y == other.y)return true;

		else return false;

	}

	bool operator !=(const Point_2018180042& other)
	{
		if (x == other.x && y == other.y)return false;

		else return true;

	}
};


struct Maxdata_2018180042
{
	int			 j_max;
	Point_2018180042		 j_point;
	CHECKERTYPE_2018180042	 j_stonetype;
	PLACEDTYPE_2018180042	 j_placetype;
	Point_2018180042		 j_blank;

	Maxdata_2018180042()
		: j_max{}
		, j_point{}
		, j_stonetype{}
		, j_placetype{}
		, j_blank{}
	{


	}

	void init()
	{
		j_max = 0;
		j_point.init();
		j_stonetype = CHECKERTYPE_2018180042::NONE;
		j_placetype = PLACEDTYPE_2018180042::NONE;
	}

	void SetValue(int max, CHECKERTYPE_2018180042 checktype, int x, int y, PLACEDTYPE_2018180042 placedtype)
	{
		j_max = max;
		j_stonetype = checktype;
		j_point = Point_2018180042(x, y);
		j_placetype = placedtype;

	}



};

struct  Checker_2018180042

{
public:
	int							j_Omockboard[19][19];
	int							j_blackcount;
	int							j_whitecount;
	CHECKERTYPE_2018180042					j_curstate;
	vector<Maxdata_2018180042>	j_Maxdata;
	Point_2018180042						j_remember;


public:
	Checker_2018180042()
		: j_blackcount{ 1 }
		, j_whitecount{ 1 }
		, j_curstate{}
		, j_Maxdata{}
		, j_remember{}
	{
		for (int i{}; i < 19; ++i)
		{
			for (int j{}; j < 19; ++j)
			{
				j_Omockboard[i][j] = DONE;
			}
		}
	}

	~Checker_2018180042() {};


	void init_2018180042() { j_curstate = CHECKERTYPE_2018180042::NONE; j_blackcount = 1; j_whitecount = 1; }

	void othertype_2018180042() { j_blackcount = 1; j_whitecount = 1; }

	void checkerclear_2018180042() {
		j_Maxdata.clear();
		j_curstate = CHECKERTYPE_2018180042::NONE;
		j_blackcount = 1;
		j_whitecount = 1;
		j_remember.init();
	}

	void sortmaxdata_2018180042()
	{
		sort(j_Maxdata.begin(), j_Maxdata.end(),
			[](Maxdata_2018180042& first, Maxdata_2018180042& second) -> bool
			{
				return first.j_max > second.j_max;
			});
	}



	void board_check_2018180042()
	{
		for (int i{}; i < 19; ++i)
		{

			for (int j{}; j < 19; ++j)
			{
				if (BLACK == j_Omockboard[i][j])
				{
					// 이전돌이 검은돌 상태일때 

					if (1 == j_blackcount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::BSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
						j_Maxdata.push_back(maxd);
					}

					if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{

						++j_blackcount;

						if (j_blackcount == 2)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::BSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
							j_Maxdata.push_back(maxd);

						}
						// 최대값이 갱신되었을때
						else if (j_blackcount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::BSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
							j_Maxdata.push_back(maxd);

						}

						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::BSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

					// 이전돌이 한칸띄여진 검은돌 상태일때 
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_blackcount;

						// 최대값이 갱신되었을때
						if (j_blackcount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEBLACK, j, i, PLACEDTYPE_2018180042::WIDTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}


						else if (j_blackcount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, j, i, PLACEDTYPE_2018180042::WIDTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEBLACK, j, i, PLACEDTYPE_2018180042::WIDTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

				}

				else if (WHITE == j_Omockboard[i][j])
				{
					if (1 == j_whitecount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::WSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
						j_Maxdata.push_back(maxd);
					}

					// 이전돌이 흰돌 상태일때 
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{

						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::WSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::WSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::WSTONE, j, i, PLACEDTYPE_2018180042::WIDTH);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

					// 이전돌이 한칸띄여진 흰돌 상태일때 
					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						++j_whitecount;

						// 최대값이 갱신되었을때
						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEWHITE, j, i, PLACEDTYPE_2018180042::WIDTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEWHITE, j, i, PLACEDTYPE_2018180042::WIDTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEWHITE, j, i, PLACEDTYPE_2018180042::WIDTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

				}

				// 빈칸일때
				else
				{
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{
						// 앞에 돌 상태 확인 흰돌이라면 한칸띈 흰 돌상태로 되기 
						if (j < 19)
						{
							if (WHITE == j_Omockboard[i][j + 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;
								j_remember = Point_2018180042(j, i);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}
					else if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{
						if (j < 19)
						{
							if (BLACK == j_Omockboard[i][j + 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;
								j_remember = Point_2018180042(j, i);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}

					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						i = j_remember.y;
						j = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						i = j_remember.y;
						j = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
					else
					{
						j_curstate = CHECKERTYPE_2018180042::NONE;
					}
				}

			}
			init_2018180042();
		}



		for (int i{}; i < 19; ++i)
		{

			for (int j{}; j < 19; ++j)
			{
				if (BLACK == j_Omockboard[j][i])
				{
					if (1 == j_blackcount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::BSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
						j_Maxdata.push_back(maxd);
					}

					// 이전돌이 검은돌 상태일때 
					if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{

						++j_blackcount;

						// 최대값이 갱신되었을때

						if (2 == j_blackcount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::BSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
							j_Maxdata.push_back(maxd);
						}

						else if (j_blackcount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::BSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
							j_Maxdata.push_back(maxd);

						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::BSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
							j_Maxdata.push_back(maxd);

						}

						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

					// 이전돌이 한칸띄여진 검은돌 상태일때 
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_blackcount;

						// 최대값이 갱신되었을때

						if (j_blackcount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEBLACK, i, j, PLACEDTYPE_2018180042::LENGTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}

						else if (j_blackcount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, i, j, PLACEDTYPE_2018180042::LENGTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, i, j, PLACEDTYPE_2018180042::LENGTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

				}

				else if (WHITE == j_Omockboard[j][i])
				{
					if (1 == j_whitecount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::WSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
						j_Maxdata.push_back(maxd);
					}


					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{

						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::WSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::WSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::WSTONE, i, j, PLACEDTYPE_2018180042::LENGTH);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}


					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEWHITE, i, j, PLACEDTYPE_2018180042::LENGTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEWHITE, i, j, PLACEDTYPE_2018180042::LENGTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEWHITE, i, j, PLACEDTYPE_2018180042::LENGTH);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;

					}


					else
					{

						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

				}

				// 빈칸일때
				else
				{
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{
						// 앞에 돌 상태 확인 흰돌이라면 한칸띈 흰 돌상태로 되기 
						if (j < 19)
						{
							if (WHITE == j_Omockboard[j + 1][i])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;
								j_remember = Point_2018180042(i, j);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}
					else if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{
						if (j < 19)
						{
							if (BLACK == j_Omockboard[j + 1][i])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;
								j_remember = Point_2018180042(i, j);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}

					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						j = j_remember.y;
						i = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}

					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						j = j_remember.y;
						i = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
				}

			}
			init_2018180042();
		}





		// 반대각선 체크
		for (int i{}; i < 19; ++i)
		{
			int idx_x{ i }, idx_y{};

			while (true)
			{
				if (BLACK == j_Omockboard[idx_y][idx_x])
				{
					// 이전돌이 검은돌 상태일때 
					if (1 == j_blackcount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
						j_Maxdata.push_back(maxd);
					}

					if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{

						++j_blackcount;

						if (j_blackcount == 2)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);

						}
						// 최대값이 갱신되었을때
						else if (j_blackcount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);

						}

						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}


					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_blackcount;

						// 최대값이 갱신되었을때
						if (j_blackcount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}


						else if (j_blackcount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

				}

				else if (WHITE == j_Omockboard[idx_y][idx_x])
				{
					// 이전돌이 검은돌 상태일때 
					if (1 == j_whitecount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
						j_Maxdata.push_back(maxd);
					}

					// 이전돌이 흰돌 상태일때 
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{

						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_whitecount;

						// 최대값이 갱신되었을때
						if (j_whitecount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}


						else if (j_whitecount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_whitecount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;

					}

				}

				// 빈칸일때
				else
				{
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{
						// 앞에 돌 상태 확인 흰돌이라면 한칸띈 흰 돌상태로 되기 
						if (idx_y + 1 < 18 && idx_x - 1 > 0)
						{
							if (WHITE == j_Omockboard[idx_y + 1][idx_x - 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}
					else if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{
						if (idx_y + 1 < 18 && idx_x - 1 > 0)
						{
							if (BLACK == j_Omockboard[idx_y + 1][idx_x - 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}

					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
				}

				if (0 == idx_x) break;
				--idx_x;
				++idx_y;

			}

			init_2018180042();
		}

		for (int i{ 1 }; i < 19; ++i)
		{
			int idx_x{ 18 }, idx_y{ i };

			while (true)
			{
				if (BLACK == j_Omockboard[idx_y][idx_x])
				{

					if (1 == j_blackcount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
						j_Maxdata.push_back(maxd);
					}

					if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{

						++j_blackcount;

						if (j_blackcount == 2)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);

						}
						// 최대값이 갱신되었을때
						else if (j_blackcount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);

						}

						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

					// 이전돌이 한칸띄여진 검은돌 상태일때 
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_blackcount;

						// 최대값이 갱신되었을때
						if (j_blackcount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}


						else if (j_blackcount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{

						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

				}

				else if (WHITE == j_Omockboard[idx_y][idx_x])
				{
					// 이전돌이 검은돌 상태일때 
					if (1 == j_whitecount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
						j_Maxdata.push_back(maxd);
					}

					// 이전돌이 흰돌 상태일때 
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{

						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_whitecount;

						// 최대값이 갱신되었을때
						if (j_whitecount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}


						else if (j_whitecount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_whitecount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::OPPOSITE);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

				}

				// 빈칸일때
				else
				{
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{
						// 앞에 돌 상태 확인 흰돌이라면 한칸띈 흰 돌상태로 되기 
						if (idx_y + 1 < 18 && idx_x - 1 > 0)
						{
							if (WHITE == j_Omockboard[idx_y + 1][idx_x - 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}
					else if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{
						if (idx_y + 1 < 18 && idx_x - 1 > 0)
						{
							if (BLACK == j_Omockboard[idx_y + 1][idx_x - 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}

					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
				}

				if (18 == idx_y) break;
				--idx_x;
				++idx_y;

			}
			init_2018180042();

		}

		// 주대각선 체크
		for (int i{ 18 }; i >= 0; --i)
		{
			int idx_x{ i }, idx_y{ 0 };

			while (true)
			{
				if (BLACK == j_Omockboard[idx_y][idx_x])
				{
					// 이전돌이 검은돌 상태일때 
					if (1 == j_blackcount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
						j_Maxdata.push_back(maxd);
					}

					if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{

						++j_blackcount;

						if (j_blackcount == 2)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);

						}
						// 최대값이 갱신되었을때
						else if (j_blackcount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);

						}

						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}


					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_blackcount;

						// 최대값이 갱신되었을때
						if (j_blackcount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}


						else if (j_blackcount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

				}

				else if (WHITE == j_Omockboard[idx_y][idx_x])
				{
					// 이전돌이 검은돌 상태일때 
					if (1 == j_whitecount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
						j_Maxdata.push_back(maxd);
					}

					// 이전돌이 흰돌 상태일때 
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{

						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_whitecount;

						// 최대값이 갱신되었을때
						if (j_whitecount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}


						else if (j_whitecount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_whitecount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;

					}

				}

				// 빈칸일때
				else
				{
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{
						// 앞에 돌 상태 확인 흰돌이라면 한칸띈 흰 돌상태로 되기 
						if (idx_y + 1 < 19 && idx_x + 1 < 19)
						{
							if (WHITE == j_Omockboard[idx_y + 1][idx_x + 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}
					else if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{
						if (idx_y + 1 < 19 && idx_x + 1 < 19)
						{
							if (BLACK == j_Omockboard[idx_y + 1][idx_x + 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}

					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
				}

				if (18 == idx_x) break;
				++idx_x;
				++idx_y;

			}


			init_2018180042();
		}


		for (int i{ 1 }; i < 19; ++i)
		{
			int idx_x{ 0 }, idx_y{ i };


			while (true)
			{
				if (BLACK == j_Omockboard[idx_y][idx_x])
				{
					if (1 == j_blackcount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
						j_Maxdata.push_back(maxd);
					}

					if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{

						++j_blackcount;

						if (j_blackcount == 2)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);

						}
						// 최대값이 갱신되었을때
						else if (j_blackcount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);

						}

						else if (j_blackcount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::BSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

					// 이전돌이 한칸띄여진 검은돌 상태일때 
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_blackcount;

						// 최대값이 갱신되었을때
						if (j_blackcount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}


						else if (j_blackcount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
							;
						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_blackcount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEBLACK, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::BSTONE;
					}

				}

				else if (WHITE == j_Omockboard[idx_y][idx_x])
				{
					// 이전돌이 검은돌 상태일때 
					if (1 == j_whitecount)
					{
						Maxdata_2018180042 maxd{};
						maxd.SetValue(1, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
						j_Maxdata.push_back(maxd);
					}

					// 이전돌이 흰돌 상태일때 
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{

						++j_whitecount;

						if (2 == j_whitecount)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 3)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						else if (j_whitecount == 4)
						{
							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::WSTONE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						++j_whitecount;

						// 최대값이 갱신되었을때
						if (j_whitecount == 2)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(2, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}


						else if (j_whitecount == 3)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(3, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);

						}

						// 최대값과 같은 갯수의 검은돌이 또 놓여져졌을때
						else if (j_whitecount == 4)
						{

							j_Maxdata.pop_back();
							Maxdata_2018180042 maxd{};
							maxd.SetValue(4, CHECKERTYPE_2018180042::ONESPACEWHITE, idx_x, idx_y, PLACEDTYPE_2018180042::DIAGONAL);
							maxd.j_blank = j_remember;
							j_Maxdata.push_back(maxd);
						}

						j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;

					}

					// 이전돌의 상태가 검은돌, 한칸 띈 검은돌 상태가 아니었을때
					else
					{
						othertype_2018180042();
						j_curstate = CHECKERTYPE_2018180042::WSTONE;
					}

				}

				// 빈칸일때
				else
				{
					if (CHECKERTYPE_2018180042::WSTONE == j_curstate)
					{
						// 앞에 돌 상태 확인 흰돌이라면 한칸띈 흰 돌상태로 되기 
						if (idx_y + 1 < 18 && idx_x + 1 < 18)
						{
							if (WHITE == j_Omockboard[idx_y + 1][idx_x + 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEWHITE;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}
					else if (CHECKERTYPE_2018180042::BSTONE == j_curstate)
					{
						if (idx_y + 1 < 18 && idx_x + 1 < 18)
						{
							if (BLACK == j_Omockboard[idx_y + 1][idx_x + 1])
							{
								j_curstate = CHECKERTYPE_2018180042::ONESPACEBLACK;
								j_remember = Point_2018180042(idx_x, idx_y);
							}
							else
							{
								j_curstate = CHECKERTYPE_2018180042::NONE;
							}
						}
					}

					else if (CHECKERTYPE_2018180042::ONESPACEWHITE == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
					else if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_curstate)
					{
						idx_y = j_remember.y;
						idx_x = j_remember.x;
						j_curstate = CHECKERTYPE_2018180042::NONE;
						othertype_2018180042();
					}
				}

				if (18 == idx_y) break;
				++idx_x;
				++idx_y;

			}
			init_2018180042();
		}
	}



	void CBlackAttack_2018180042(int* x, int* y)
	{
		if (0 == j_Maxdata.size())
		{
			*y = 9;
			*x = 9;
		}
		else
		{
			int _x{}, _y{};

			for (int i{}; i < j_Maxdata.size(); ++i)
			{
				if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_Maxdata.at(i).j_stonetype || CHECKERTYPE_2018180042::ONESPACEWHITE == j_Maxdata.at(i).j_stonetype)
				{
					_x = j_Maxdata[i].j_blank.x;
					_y = j_Maxdata[i].j_blank.y;
					break;
				}

				else {

					if (PLACEDTYPE_2018180042::WIDTH == j_Maxdata.at(i).j_placetype)
					{
						if (j_Maxdata[i].j_point.x < 18 && j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) > 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x + 1]) {
								_x = j_Maxdata[i].j_point.x + 1;
								_y = j_Maxdata[i].j_point.y;
								break;
							}
							else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
							{
								_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y;

								break;
							}

						}
						else if (j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) == 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x + 1]) {
								_x = j_Maxdata[i].j_point.x + 1;
								_y = j_Maxdata[i].j_point.y;
								break;
							}
						}
						else if (j_Maxdata[i].j_point.x == 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
							{
								_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y;

								break;
							}
						}

					}

					else if (PLACEDTYPE_2018180042::LENGTH == j_Maxdata.at(i).j_placetype)
					{

						if (j_Maxdata[i].j_point.y < 18 && j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) > 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x]) {
								_x = j_Maxdata[i].j_point.x;
								_y = j_Maxdata[i].j_point.y + 1;
								break;
							}
							else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x])
							{
								_x = j_Maxdata[i].j_point.x;
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

								break;
							}

						}
						else if (j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) == 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x]) {
								_x = j_Maxdata[i].j_point.x;
								_y = j_Maxdata[i].j_point.y + 1;
								break;
							}
						}
						else if (j_Maxdata[i].j_point.y == 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x])
							{
								_x = j_Maxdata[i].j_point.x;
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

								break;
							}
						}
					}


					// y+1 x-1
					else if (PLACEDTYPE_2018180042::OPPOSITE == j_Maxdata.at(i).j_placetype)
					{

						if (j_Maxdata[i].j_point.y < 18
							&& j_Maxdata[i].j_point.x > 0
							&& j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) > 0
							&& j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max - 1) < 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x - 1]) {
								_x = j_Maxdata[i].j_point.x - 1;
								_y = j_Maxdata[i].j_point.y + 1;
								break;
							}
							else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max)])
							{
								_x = j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

								break;
							}
						}

						// 최대값 뺸값에 돌놓기
						else if (j_Maxdata[i].j_point.x == 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max)]) {
								_x = j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);
								break;
							}
						}

						// max 다음에 돌놓기
						else if (j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max - 1) == 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x - 1])
							{
								_x = j_Maxdata[i].j_point.x - 1;
								_y = j_Maxdata[i].j_point.y + 1;

								break;
							}
						}

						// max 다음에 돌놓기
						else if (j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) == 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x - 1]) {
								_x = j_Maxdata[i].j_point.x - 1;
								_y = j_Maxdata[i].j_point.y + 1;
								break;
							}
						}

						// 최대값 뺸값에 돌놓기
						else if (j_Maxdata[i].j_point.y == 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max)])
							{
								_x = j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

								break;
							}
						}
					}

					else if (PLACEDTYPE_2018180042::DIAGONAL == j_Maxdata.at(i).j_placetype)
					{
						if (j_Maxdata[i].j_point.y < 18
							&& j_Maxdata[i].j_point.x < 18
							&& j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) > 0
							&& j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) > 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x + 1]) {
								_x = j_Maxdata[i].j_point.x + 1;
								_y = j_Maxdata[i].j_point.y + 1;
								break;
							}
							else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
							{
								_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

								break;
							}
						}
						// max 다음에 돌놓기
						else if (j_Maxdata[i].j_point.x == 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)]) {
								_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);
								break;
							}
						}

						else if (j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) == 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x + 1])
							{
								_x = j_Maxdata[i].j_point.x + 1;
								_y = j_Maxdata[i].j_point.y + 1;

								break;
							}
						}
						// 최대값 뺸값에 돌놓기
						else if (j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) == 0)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x + 1]) {
								_x = j_Maxdata[i].j_point.x + 1;
								_y = j_Maxdata[i].j_point.y + 1;
								break;
							}
						}
						// max 다음에 돌놓기
						else if (j_Maxdata[i].j_point.y == 18)
						{
							if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
							{
								_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
								_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

								break;
							}
						}

					}
				}
			}

			*y = _y;
			*x = _x;
		}


		j_Omockboard[*y][*x] = BLACK;

	}

	void CWhiteAttack_2018180042(int* x, int* y)
	{
		int _x{}, _y{};

		for (int i{}; i < j_Maxdata.size(); ++i)
		{
			if (CHECKERTYPE_2018180042::ONESPACEBLACK == j_Maxdata.at(i).j_stonetype || CHECKERTYPE_2018180042::ONESPACEWHITE == j_Maxdata.at(i).j_stonetype)
			{
				_x = j_Maxdata[i].j_blank.x;
				_y = j_Maxdata[i].j_blank.y;
				break;
			}

			else {

				if (PLACEDTYPE_2018180042::WIDTH == j_Maxdata.at(i).j_placetype)
				{
					if (j_Maxdata[i].j_point.x < 18 && j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) > 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x + 1]) {
							_x = j_Maxdata[i].j_point.x + 1;
							_y = j_Maxdata[i].j_point.y;
							break;
						}
						else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
						{
							_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y;

							break;
						}

					}
					else if (j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) == 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x + 1]) {
							_x = j_Maxdata[i].j_point.x + 1;
							_y = j_Maxdata[i].j_point.y;
							break;
						}
					}
					else if (j_Maxdata[i].j_point.x == 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
						{
							_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y;

							break;
						}
					}

				}

				else if (PLACEDTYPE_2018180042::LENGTH == j_Maxdata.at(i).j_placetype)
				{

					if (j_Maxdata[i].j_point.y < 18 && j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) > 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x]) {
							_x = j_Maxdata[i].j_point.x;
							_y = j_Maxdata[i].j_point.y + 1;
							break;
						}
						else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x])
						{
							_x = j_Maxdata[i].j_point.x;
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

							break;
						}

					}
					else if (j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) == 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x]) {
							_x = j_Maxdata[i].j_point.x;
							_y = j_Maxdata[i].j_point.y + 1;
							break;
						}
					}
					else if (j_Maxdata[i].j_point.y == 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x])
						{
							_x = j_Maxdata[i].j_point.x;
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

							break;
						}
					}
				}


				// y+1 x-1
				else if (PLACEDTYPE_2018180042::OPPOSITE == j_Maxdata.at(i).j_placetype)
				{

					if (j_Maxdata[i].j_point.y < 18
						&& j_Maxdata[i].j_point.x > 0
						&& j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) > 0
						&& j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max - 1) < 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x - 1]) {
							_x = j_Maxdata[i].j_point.x - 1;
							_y = j_Maxdata[i].j_point.y + 1;
							break;
						}
						else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max)])
						{
							_x = j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

							break;
						}
					}

					// 최대값 뺸값에 돌놓기
					else if (j_Maxdata[i].j_point.x == 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max)]) {
							_x = j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);
							break;
						}
					}

					// max 다음에 돌놓기
					else if (j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max - 1) == 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x - 1])
						{
							_x = j_Maxdata[i].j_point.x - 1;
							_y = j_Maxdata[i].j_point.y + 1;

							break;
						}
					}

					// max 다음에 돌놓기
					else if (j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) == 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x - 1]) {
							_x = j_Maxdata[i].j_point.x - 1;
							_y = j_Maxdata[i].j_point.y + 1;
							break;
						}
					}

					// 최대값 뺸값에 돌놓기
					else if (j_Maxdata[i].j_point.y == 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max)])
						{
							_x = j_Maxdata[i].j_point.x + (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

							break;
						}
					}
				}

				else if (PLACEDTYPE_2018180042::DIAGONAL == j_Maxdata.at(i).j_placetype)
				{
					if (j_Maxdata[i].j_point.y < 18
						&& j_Maxdata[i].j_point.x < 18
						&& j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) > 0
						&& j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) > 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x + 1]) {
							_x = j_Maxdata[i].j_point.x + 1;
							_y = j_Maxdata[i].j_point.y + 1;
							break;
						}
						else if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
						{
							_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

							break;
						}
					}
					// max 다음에 돌놓기
					else if (j_Maxdata[i].j_point.x == 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)]) {
							_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);
							break;
						}
					}

					else if (j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max - 1) == 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x + 1])
						{
							_x = j_Maxdata[i].j_point.x + 1;
							_y = j_Maxdata[i].j_point.y + 1;

							break;
						}
					}
					// 최대값 뺸값에 돌놓기
					else if (j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max - 1) == 0)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y + 1][j_Maxdata[i].j_point.x + 1]) {
							_x = j_Maxdata[i].j_point.x + 1;
							_y = j_Maxdata[i].j_point.y + 1;
							break;
						}
					}
					// max 다음에 돌놓기
					else if (j_Maxdata[i].j_point.y == 18)
					{
						if (DONE == j_Omockboard[j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max)][j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max)])
						{
							_x = j_Maxdata[i].j_point.x - (j_Maxdata[i].j_max);
							_y = j_Maxdata[i].j_point.y - (j_Maxdata[i].j_max);

							break;
						}
					}

				}
			}
		}

		*y = _y;
		*x = _x;
		j_Omockboard[*y][*x] = WHITE;
	}
};




Checker_2018180042 checker_2018180042{};


void WhiteAttack_2018180042(int* x, int* y)
{

	checker_2018180042.CWhiteAttack_2018180042(x, y);
}

void WhiteDefence_2018180042(int x, int y)
{

	checker_2018180042.j_Omockboard[y][x] = BLACK;
	checker_2018180042.checkerclear_2018180042();
	checker_2018180042.board_check_2018180042();
	checker_2018180042.sortmaxdata_2018180042();
}

void BlackAttack_2018180042(int* x, int* y)
{
	checker_2018180042.CBlackAttack_2018180042(x, y);
}

void BlackDefence_2018180042(int x, int y)
{

	checker_2018180042.j_Omockboard[y][x] = WHITE;
	checker_2018180042.checkerclear_2018180042();
	checker_2018180042.board_check_2018180042();
	checker_2018180042.sortmaxdata_2018180042();
}