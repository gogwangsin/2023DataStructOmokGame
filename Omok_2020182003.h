#pragma once
#include<time.h>
#include<stdlib.h>
#include <stdio.h>
#include<math.h>

#define BLACK -1
#define WHITE 1
#define NONE_2020182003 0

#define BLANCK_4_2020182003 9900 // 00x00 공격우선 
#define FULL_4_2020182003 9800 // x0000x 공격우선 
#define BLANCK_3_2020182003 8900
#define FULL_3_2020182003 8900 // 3공격 방어는 우선순위 같게 햇음 -> 변경 가능  


#define ATACK44_2020182003 100 
#define ATACK43_2020182003 900
#define Attack33_2020182003 800
#define Attack22_2020182003 500

/*=====전역변수================================================================================================== */

typedef struct LIST_2020182003 {

	int state;
	int Y, X;
	int combo;
	int max; // 콤보끊겼을때 최대값 저장 -> 한줄씩 비교 

}LIST_2020182003;
typedef struct INDEX_2020182003 {

	int y, x;
	struct INDEX_2020182003* next;

}INDEX_2020182003;

int board_2020182003[19][19];

/*======함수선언================================================================================================ */

INDEX_2020182003* Make_SL_2020182003(INDEX_2020182003* head, int x, int y);
void Free_SL_2020182003(INDEX_2020182003** head);
void weight_2020182003(int weight[][19], int Game[][19]);
void Rand_SL_2020182003(INDEX_2020182003* head, int* x, int* y);
int Black_Gard_Weight_2020182003(int weight[][19]);
int White_Gard_Weight_2020182003(int weight[][19]);
void init_stone_2020182003(int weight_max, int* x, int* y, int Game[][19]);
void CheckAindex_2020182003(int weight[][19], int Game[][19]);
void CheckBindex_2020182003(int weight[][19], int Game[][19]);
void CheckRTindex_2020182003(int weight[][19], int Game[][19]);
void CheckLBindex_2020182003(int weight[][19], int Game[][19]);
void CheckRBindex_2020182003(int weight[][19], int Game[][19]);
void CheckLTindex_2020182003(int weight[][19], int Game[][19]);
int PlusCompare_2020182003(int weight[][19]);
int MinusCompare_2020182003(int weight[][19]);


/*======메인함수=============================================================================================== */

void WhiteAttack_2020182003(int* x, int* y)
{
	srand((unsigned)time(NULL));

	int Whelp_2020182003[19][19] = { 0 };

	weight_2020182003(Whelp_2020182003, board_2020182003);

	CheckAindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckBindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckRTindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckLBindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckRBindex_2020182003(Whelp_2020182003, board_2020182003);
	CheckLTindex_2020182003(Whelp_2020182003, board_2020182003);

	int plusWhite = PlusCompare_2020182003(Whelp_2020182003); // (+)더하기 -> 백돌 공격 구간  
	int minusBlack = MinusCompare_2020182003(Whelp_2020182003); // (-)더하기 -> 흑돌 위험도  

	int weight_max = 0;

	if (plusWhite == -1 || minusBlack == -1) // 뭔가 위험한게 있다는 증거 
	{
		int attack = Black_Gard_Weight_2020182003(Whelp_2020182003); // 4공격 (+)인거 중 젤 큰거  
		int gard = White_Gard_Weight_2020182003(Whelp_2020182003); // 4 방어 (-)인거 중 젤 큰거 

		if (attack == BLANCK_4_2020182003 || attack == FULL_4_2020182003) // 빈칸 4 공격 
		{
			weight_max = attack;
		}
		else if (gard == -BLANCK_4_2020182003 || gard == -FULL_4_2020182003) // 공격우선 4에 대입 공격 때문 아니면 방어에 대입 
		{
			weight_max = gard;
		}
	}
	else if (plusWhite == -2 || minusBlack == -2) // 뭔가 위험한게 있다는 증거 
	{
		int attack = Black_Gard_Weight_2020182003(Whelp_2020182003); // 4공격 (+)인거 중 젤 큰거  
		int gard = White_Gard_Weight_2020182003(Whelp_2020182003); // 4 방어 (-)인거 중 젤 큰거 

		if (attack == BLANCK_3_2020182003) // 빈칸 4 공격 
		{
			weight_max = attack;
		}
		else if (gard == -BLANCK_3_2020182003) // 공격우선 4에 대입 공격 때문 아니면 방어에 대입 
		{
			weight_max = gard;
		}
	}
	else if (plusWhite == 0 && minusBlack == 0) // 둘다 가중치 없음 -> 합이 0인거임 < 기본 돌 값 > 
	{
		weight_max = 0;
	}
	else if (plusWhite != 0 || minusBlack != 0)// 둘중 한명은 값이 있는데 -1이 아니니까 비교할 수 있는거 
	{
		int compare = 0;

		if (abs(plusWhite) > abs(minusBlack)) // plus가 (+)젤 큰거 공격값이 더 큰 경우 
		{
			weight_max = Black_Gard_Weight_2020182003(Whelp_2020182003); //blackgard -> (+)젤큰거 리턴 -> 공격 
		}
		else if (abs(plusWhite) < abs(minusBlack)) // minus 절대값이 더 큰경우 -> 흑돌 위험도 < 방어해야할 타이밍 > 
		{
			weight_max = White_Gard_Weight_2020182003(Whelp_2020182003); // (-)가 더 크면 방어해야할 타이밍 
		}
		else
		{
			weight_max = Black_Gard_Weight_2020182003(Whelp_2020182003); // 무슨일이 벌어질지 모르지만 기본으로 막기 무슨 예외가 있을지 모를땐 막는거 

			if (weight_max == 0)
			{
				weight_max = White_Gard_Weight_2020182003(Whelp_2020182003);
			}
		}
	}



	INDEX_2020182003* head = NULL;

	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (board_2020182003[y][x] == NONE_2020182003 && weight_max != 0 && Whelp_2020182003[y][x] == weight_max) // 가중치가 고정인데 -> 가중치 비교함수 만들어서 비교 
			{
				head = Make_SL_2020182003(head, x, y);
			}
		}
	}

	Rand_SL_2020182003(head, &(*x), &(*y)); // 돌 두는 좌표의 주소 
	Free_SL_2020182003(&head);
	init_stone_2020182003(weight_max, &(*x), &(*y), board_2020182003);

	board_2020182003[*y][*x] = WHITE;
}

void BlackAttack_2020182003(int* x, int* y)
{
	srand((unsigned)time(NULL));

	int Bhelp_2020182003[19][19] = { 0 };

	// 돌 두면 기본 가중치 
	weight_2020182003(Bhelp_2020182003, board_2020182003);
	// 위험도에 체크해서 가중치 변화
	CheckAindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckBindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckRTindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckLBindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckRBindex_2020182003(Bhelp_2020182003, board_2020182003);
	CheckLTindex_2020182003(Bhelp_2020182003, board_2020182003);

	int plusWhite = PlusCompare_2020182003(Bhelp_2020182003); // (+)더하기 -> 백돌 공격 구간  
	int minusBlack = MinusCompare_2020182003(Bhelp_2020182003); // (-)더하기 -> 흑돌 위험도  

	int weight_max = 0;

	if (plusWhite == -1 || minusBlack == -1) // 4 공격이거나 막기거나 
	{
		int attack = White_Gard_Weight_2020182003(Bhelp_2020182003);  // 백돌이 막아야할 곳 -> 흑돌에겐 공격 
		int gard = Black_Gard_Weight_2020182003(Bhelp_2020182003); // 방어값 -> (+)값 젤 큰거 

		if (attack == -BLANCK_4_2020182003 || attack == -FULL_4_2020182003) // 빈칸 4 공격 (-) 음수가 더 
		{
			weight_max = attack; // -9900이거나 -9800인 경우에 공격 
		}
		else if (gard == BLANCK_4_2020182003 || gard == FULL_4_2020182003) // 공격우선 4에 대입 공격 때문 아니면 방어에 대입 
		{
			weight_max = gard; // 뭔가 위험한데 방어해야되면 방어 
		}
	}
	else if (plusWhite == -2 || minusBlack == -2) // 3 막거나 공격 공격우선 
	{
		int attack = White_Gard_Weight_2020182003(Bhelp_2020182003);  // 백돌이 막아야할 곳 -> 흑돌에겐 공격 
		int gard = Black_Gard_Weight_2020182003(Bhelp_2020182003); // 방어값 -> (+)값 젤 큰거 

		if (attack == -BLANCK_3_2020182003) // 빈칸 4 공격 (-) 음수가 더 
		{
			weight_max = attack; // -9900이거나 -9800인 경우에 공격 
		}
		else if (gard == BLANCK_3_2020182003) // 공격우선 4에 대입 공격 때문 아니면 방어에 대입 
		{
			weight_max = gard; // 뭔가 위험한데 방어해야되면 방어 
		}
	}
	else if (plusWhite == 0 && minusBlack == 0) // 둘다 가중치 없음 -> 합이 0인거임 < 기본 돌 값 > 
	{
		weight_max = 0;
	}
	else if (plusWhite != 0 || minusBlack != 0)// 둘중 한명은 값이 있는데 -1이나 -2가 아니니까 비교할 수 있는거 
	{
		int compare = 0;

		if (abs(plusWhite) > abs(minusBlack)) // plus가 더 큼 -> 백돌 공격값이 더 크다 -> 방어하자 
		{
			weight_max = Black_Gard_Weight_2020182003(Bhelp_2020182003);
		}
		else if (abs(plusWhite) < abs(minusBlack)) // minus 절대값이 더 큰경우 -> 흑돌 위험도 < 방어해야할 타이밍 > 
		{
			weight_max = White_Gard_Weight_2020182003(Bhelp_2020182003); // 음수 젤 큰거 -> 흑돌 공격 
		}
		else // 가중치 같을때 가중치가 0이 아닌데 같은 경우 -> 디폴트값 어떻게하징? 
		{
			weight_max = White_Gard_Weight_2020182003(Bhelp_2020182003); // - 젤큰거 계싼 

			if (weight_max == 0)
			{
				weight_max = Black_Gard_Weight_2020182003(Bhelp_2020182003);
			}

		}
	}// 흰색 돌 막기로 되어있는데  가중치 같을때 가중치가 0이 아닌데 같은 경우 했는데 max치가 0이면 


	// 가중치 젤 위험 맥스치 -> 여기에 수정 

	INDEX_2020182003* head = NULL;

	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			if (board_2020182003[y][x] == NONE_2020182003 && weight_max != 0 && Bhelp_2020182003[y][x] == weight_max) // 가중치 젤 큰거(우선순위)와 같은 좌표 저장  
			{
				head = Make_SL_2020182003(head, x, y);
			}
		}
	}

	Rand_SL_2020182003(head, &(*x), &(*y)); // 돌 두는 좌표의 주소 가중치 같은 값들 
	Free_SL_2020182003(&head);
	init_stone_2020182003(weight_max, &(*x), &(*y), board_2020182003); // 가중치 0일 때 랜덤한 위치에 

	board_2020182003[*y][*x] = BLACK;
}

void WhiteDefence_2020182003(int x, int y)
{
	board_2020182003[y][x] = BLACK;
}
void BlackDefence_2020182003(int x, int y)
{
	board_2020182003[y][x] = WHITE;
}

/*======함수정의=============================================================================================== */


// 가중치 계산하는 함수, NONE일 때만 값 바뀌게 해서 가중치를 이용해 돌을 넣는 구조에서 겹칠 일이 없음
void weight_2020182003(int weight[][19], int Game[][19])
{
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == WHITE)
			{
				for (int m = -1; m < 2; m++)
				{
					for (int n = -1; n < 2; n++)
					{
						if (m + i >= 0 && m + i <= 18 && n + k >= 0 && n + k <= 18)
						{
							if (Game[m + i][n + k] == NONE_2020182003)
								weight[m + i][n + k] += 2;
						}
					}
				}
			}
			else if (Game[i][k] == BLACK)
			{
				for (int m = -1; m < 2; m++)
				{
					for (int n = -1; n < 2; n++)
					{
						if (m + i >= 0 && m + i <= 18 && n + k >= 0 && n + k <= 18)
						{
							if (Game[m + i][n + k] == NONE_2020182003)
								weight[m + i][n + k] -= 2;
						}
					}
				}
			}

		}
	}
}

// 가중치 맥스인 좌표 싱글연결리스트로 저장 
INDEX_2020182003* Make_SL_2020182003(INDEX_2020182003* head, int x, int y)
{
	INDEX_2020182003* newNODE = (INDEX_2020182003*)malloc(sizeof(INDEX_2020182003));
	if (newNODE == NULL)
	{
		printf("동적할당 실패\n");
		exit(1);
	}
	newNODE->x = x;
	newNODE->y = y;
	newNODE->next = head;

	head = newNODE;
	return head;
}

// 메모리 Free함수 
void Free_SL_2020182003(INDEX_2020182003** head)
{
	if (*head == NULL)
	{
		return;
	}

	INDEX_2020182003* cur = *head;

	while (*head != NULL)
	{
		cur = *head;
		*head = (*head)->next;
		free(cur);
	}
}

// x,y 가중치 값 랜덤 변경 
void Rand_SL_2020182003(INDEX_2020182003* head, int* x, int* y)
{
	if (head == NULL)
	{
		return;
	}

	int i = 0;

	INDEX_2020182003* cur = head;

	while (cur != NULL) // 0~n-1
	{
		i++;
		cur = cur->next;
	}

	int pick = rand() % i;

	cur = head;
	i = 0;

	while (cur != NULL) // ㅇㅋ -> 
	{
		if (pick == i) break;
		i++;
		cur = cur->next;
	}

	*x = cur->x;
	*y = cur->y;

}

// 검돌 기준 가중치 최고위험 -> 흰돌 (+)양수 부호차이 weight > max 
int Black_Gard_Weight_2020182003(int weight[][19])
{
	int max = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] > max) max = weight[i][k];
		}
	}

	return max;
}

// 흰돌 기준 가중치 최고위험 -> 검돌 (-)음수  weight < max -> 작은거
int White_Gard_Weight_2020182003(int weight[][19])
{
	int max = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] < max) max = weight[i][k];
		}
	}

	return max;
}

// 가중치 0일때 랜덤한 위치 
void init_stone_2020182003(int weight_max, int* x, int* y, int Game[][19])
{
	if (weight_max != 0) return;

	while (1)
	{
		*x = rand() % 19;
		*y = rand() % 19;
		if (Game[*y][*x] != NONE_2020182003)
		{
			continue;
		}
		else break;

	}

}

// 세로선 가중치 업데이트 - 우선순위 1. 4공격공백 2. 4공백풀 3. 3같음 
void CheckAindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[k - 1][i] == BLACK)
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[k - 1][i].state = BLACK;
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == WHITE) // 맨 처음 B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1; // 스타트 
					endPoint = k - 1; // 엔드 
					list[k - 1][i].state = WHITE;
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == NONE_2020182003) // 패스 
				{
					nonePoint = k - 1;
					list[k - 1][i].state = NONE_2020182003;
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
				}
			}


			if (Game[k][i] == Game[k - 1][i]) // 이전과 같을 때 BB ++ WW 
			{
				if (Game[k][i] == BLACK)
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[k][i].state = BLACK;
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumB;

				}
				else if (Game[k][i] == WHITE)
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[k][i].state = WHITE;
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumW;
				}
				else if (Game[k][i] == NONE_2020182003) // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
				{
					if (k - 2 >= 0 && (Game[k - 2][i] == BLACK))
					{
						list[startPoint][i].max = list[k - 2][i].combo; // 2번 뒤에 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
					}
					else if (k - 2 >= 0 && (Game[k - 2][i] == WHITE))
					{
						list[startPoint][i].max = list[k - 2][i].combo;
					}
					countNone = 0; // 공백 초기화 
				}
			}
			else if (Game[k][i] != Game[k - 1][i]) // WB +B / BW +W / B+ W+
			{
				if (Game[k][i] == BLACK) // 전에 꺼 비교해서 설정해주기 
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == WHITE))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // 시작점에 stp max 백업 

						countB = 1; // 지금이 흑 / 이전이 백 
						countW = 0;
						sumB = countB;
						countNone = 0; // 공백 초기화 
						startPoint = k;
						list[k][i].state = BLACK;
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == NONE_2020182003)) // AOB BOB 
					{
						if (countNone == 1) // 공백 하나일때 연속중 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[k][i].state = BLACK;
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumB;

						}
						else if (countNone == 0)
						{
							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = k;
							list[k][i].state = BLACK;
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumB;
						}
					}
				}
				else if (Game[k][i] == WHITE)
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == BLACK))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // 이전BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[k][i].state = BLACK;
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == NONE_2020182003))
					{
						if (countNone == 1) // 공백 하나일때 연속중  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[k][i].state = WHITE;
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumW;

						}
						else if (countNone == 0) // 00A A0A0A
						{
							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = k;
							list[k][i].state = WHITE;
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumW;
						}
					}
				}
				else if (Game[k][i] == NONE_2020182003) // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // 처음 공백위치 

					if (countNone == 1)
					{
						nonePoint = k; //처음공백위치 저장 
					}
					else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[k - 1][i] == BLACK))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // 01,10일때 생각 
							k = nonePoint;
							continue;
						}
						else if (k - 1 >= 0 && (Game[k - 1][i] == WHITE))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // 이전BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[k][i].combo == 3) // 3일때  X00X0X 공백 8900 / 공백X 8800 의미가 있나?
			{
				list[startPoint][i].max = list[k][i].combo; //시작점에 최대치 기록  

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[j][i] == NONE_2020182003) //공백있을때
					{

						if (list[startPoint][i].state == BLACK)
						{
							weight[j][i] = -BLANCK_3_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
						}
						if (list[startPoint][i].state == WHITE)
						{
							weight[j][i] = BLANCK_3_2020182003; //89
						}
					}
				}

				if (list[startPoint][i].state == BLACK) //whelp 처음이 검은색일때
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // 공백일때
					{
						weight[startPoint - 1][i] = -FULL_3_2020182003; // 88!
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // 공백일때
					{
						weight[endPoint + 1][i] = -FULL_3_2020182003; // 막아!
					}
				}
				else if (list[startPoint][i].state == WHITE) // bhelp 처음이 백돌일때 
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // 돌이 없을때
					{
						weight[startPoint - 1][i] = FULL_3_2020182003; // 막아! -> B도와주는 맵 
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // 공백일때
					{
						weight[endPoint + 1][i] = FULL_3_2020182003; // 막아!
					}
				}
			}
			else if (list[k][i].combo == 4) // 콤보 3또는 4일때 
			{
				list[startPoint][i].max = list[k][i].combo; //시작점에 최대치 기록  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[j][i] == NONE_2020182003) //공백있을때 9900
					{
						blanckOn = 1;

						if (list[startPoint][i].state == BLACK)
						{
							weight[j][i] = -BLANCK_4_2020182003; // 흑돌 주변 -9900 / 흑돌이 00X00인 경우 -> 백돌 가드 가중치 (-) 
						}
						if (list[startPoint][i].state == WHITE)
						{
							weight[j][i] = BLANCK_4_2020182003; // 백돌 주변 9900
						}

					}
				}

				if (blanckOn == 0) // 공백 없을때 4 공격 9800 
				{
					if (list[startPoint][i].state == BLACK) //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // 돌이 없을때  -> 이거 안하고 NONE으로 하면 +-2인 구간에 가중치 못 넣음 
						{
							weight[startPoint - 1][i] = -FULL_4_2020182003; // 흑돌 기준 -> 시작점 양옆에 공백이면 -> -98
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // 공백일때
						{
							weight[endPoint + 1][i] = -FULL_4_2020182003; // 막아!
						}
					}
					else if (list[startPoint][i].state == WHITE) // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == NONE_2020182003)) // 공백일때
						{
							weight[startPoint - 1][i] = FULL_4_2020182003; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == NONE_2020182003)) // 공백일때
						{
							weight[endPoint + 1][i] = FULL_4_2020182003; // 막아!
						}
					}
				}

			} // 콤보
		}
	}
}

// 가로선 가중치 업데이트
void CheckBindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[i][k - 1] == BLACK)
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = BLACK;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == WHITE) // 맨 처음 B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = WHITE;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == NONE_2020182003) // 패스 
				{
					nonePoint = k - 1;
					list[i][k - 1].state = NONE_2020182003;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}


			if (Game[i][k] == Game[i][k - 1]) // 이전과 같을 때 BB ++ WW 
			{
				if (Game[i][k] == BLACK)
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[i][k].state = BLACK;
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumB;

				}
				else if (Game[i][k] == WHITE)
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[i][k].state = WHITE;
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
				else if (Game[i][k] == NONE_2020182003) // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
				{
					if (k - 2 >= 0 && (Game[i][k - 2] == BLACK))
					{
						list[i][startPoint].max = list[i][k - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
					}
					else if (k - 2 >= 0 && (Game[i][k - 2] == WHITE))
					{
						list[i][startPoint].max = list[i][k - 2].combo;
					}
					countNone = 0; // 공백 초기화 
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // WB +B BW +W B+ W+
			{
				if (Game[i][k] == BLACK) // 전에 꺼 비교해서 설정해주기 
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == WHITE))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // 시작점에 stp max 백업 

						countB = 1;
						countW = 0;
						sumB = countB;
						countNone = 0; // 공백 초기화 
						startPoint = k;
						list[i][k].state = BLACK;
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == NONE_2020182003)) // AOB BOB 
					{
						if (countNone == 1) // 공백 하나일때 연속중 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[i][k].state = BLACK;
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumB;

						}
						else if (countNone == 0)
						{
							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = k;
							list[i][k].state = BLACK;
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumB;
						}
					}
				}
				else if (Game[i][k] == WHITE)
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == BLACK))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // 이전BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[i][k].state = WHITE;
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == NONE_2020182003))
					{
						if (countNone == 1) // 공백 하나일때 연속중  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[i][k].state = WHITE;
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumW;

						}
						else if (countNone == 0) // 00A A0A0A
						{
							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = k;
							list[i][k].state = WHITE;
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumW;
						}
					}
				}
				else if (Game[i][k] == NONE_2020182003) // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // 처음 공백위치 

					if (countNone == 1)
					{
						nonePoint = k; //처음공백위치 저장 

					}
					else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[i][k - 1] == BLACK))
						{
							list[i][startPoint].max = list[i][k - 1].combo;
							k = nonePoint; // 처음 공백위치로 다시 for문 
							continue;
						}
						else if (k - 1 >= 0 && (Game[i][k - 1] == WHITE))
						{
							list[i][startPoint].max = list[i][k - 1].combo; // 이전BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[i][k].combo == 3) // 3일때  3일때 한번 저장한거임 내가 볼땐 oBBOBO인데 OBBOBB
			{
				list[i][startPoint].max = list[i][k].combo; //시작점에 최대치 기록  

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[i][j] == NONE_2020182003) //공백있을때
					{

						if (list[i][startPoint].state == BLACK)
						{
							weight[i][j] = -BLANCK_3_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
						}
						if (list[i][startPoint].state == WHITE)
						{
							weight[i][j] = BLANCK_3_2020182003;
						}
					}
				}

				if (list[i][startPoint].state == BLACK) //whelp 처음이 검은색일때
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // 공백일때
					{
						weight[i][startPoint - 1] = -FULL_3_2020182003; // 막아!
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // 공백일때
					{
						weight[i][endPoint + 1] = -FULL_3_2020182003; // 막아!
					}
				}
				else if (list[i][startPoint].state == WHITE) // bhelp 처음이 백돌일때 
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // 공백일때
					{
						weight[i][startPoint - 1] = FULL_3_2020182003; // 막아! -> B도와주는 맵 
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // 공백일때
					{
						weight[i][endPoint + 1] = FULL_3_2020182003; // 막아!
					}
				}
			}
			else if (list[i][k].combo == 4) // 콤보 3또는 4일때 
			{
				list[i][startPoint].max = list[i][k].combo; //시작점에 최대치 기록  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[i][j] == NONE_2020182003) //공백있을때
					{
						blanckOn = 1;

						if (list[i][startPoint].state == BLACK)
						{
							weight[i][j] = -BLANCK_4_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
						}
						if (list[i][startPoint].state == WHITE)
						{
							weight[i][j] = BLANCK_4_2020182003;
						}

					}
				}

				if (blanckOn == 0) // 공백 없을때
				{
					if (list[i][startPoint].state == BLACK) //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // 공백일때
						{
							weight[i][startPoint - 1] = -FULL_4_2020182003; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // 공백일때
						{
							weight[i][endPoint + 1] = -FULL_4_2020182003; // 막아!
						}
					}
					else if (list[i][startPoint].state == WHITE) // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == NONE_2020182003)) // 공백일때
						{
							weight[i][startPoint - 1] = FULL_4_2020182003; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == NONE_2020182003)) // 공백일때
						{
							weight[i][endPoint + 1] = FULL_4_2020182003; // 막아!
						}
					}
				}

			} // 콤보
		}
	}
}

// 우상단 대각선 가중치 업데이트 
void CheckRTindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		for (int y = 1; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y가 증가하는 줄 
			{
				if (y - 1 == 0) // 맨 처음일때 
				{
					if (Game[y - 1][i + y - 1] == BLACK) // y는 1이고 y-1이 0인 상황이 맨 처음 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = BLACK;
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = y + i - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = WHITE;
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[y - 1][i + y - 1].state = NONE_2020182003;
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
					}
				}

				if (Game[0 + y][i + y] == Game[y - 1][i + y - 1]) // 이전과 같을 때 BB ++ WW  기본형 Game[i][y].Game[0+y][i+y]
				{
					if (Game[0 + y][i + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[y][i + y].state = BLACK;
						list[y][i + y].Y = y;
						list[y][i + y].X = i + y;
						list[y][i + y].combo = sumB;

					}
					else if (Game[y][i + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[y][i + y].state = WHITE;
						list[y][i + y].Y = y;
						list[y][i + y].X = y + i;
						list[y][i + y].combo = sumW;
					}
					else if (Game[y][y + i] == NONE_2020182003) // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
					{
						if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == BLACK))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
						}
						else if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == WHITE))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo;
						}
						countNone = 0; // 공백 초기화 
					}
				}
				else if (Game[y][i + y] != Game[y - 1][y + i - 1]) // WB +B BW +W B+ W+
				{
					if (Game[y][i + y] == BLACK) // 전에 꺼 비교해서 설정해주기 
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == WHITE))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // 시작점에 stp max 백업 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = y;
							list[y][i + y].state = BLACK;
							list[y][i + y].Y = y;
							list[y][i + y].X = i + y;
							list[y][i + y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // 공백 하나일때 연속중 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[y][y + i].state = BLACK;
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // 공백 초기화 
								startPoint = y;
								list[y][y + i].state = BLACK;
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumB;
							}
						}
					}
					else if (Game[y][i + y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == BLACK))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // 이전BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[y][y + i].state = WHITE;
							list[y][y + i].Y = y;
							list[y][y + i].X = y + i;
							list[y][y + i].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == NONE_2020182003))
						{
							if (countNone == 1) // 공백 하나일때 연속중  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[y][y + i].state = WHITE;
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[y][y + i].state = WHITE;
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumW;
							}
						}
					}
					else if (Game[y][y + i] == NONE_2020182003) // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // 처음 공백위치 

						if (countNone == 1)
						{
							nonePoint = y; //처음공백위치 저장 

						}
						else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == BLACK))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == WHITE))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // 이전BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // 콤보
				if (list[y][y + i].combo == 3) // 3일때 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //시작점에 최대치 기록  

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
					{
						if (Game[j][j + i] == NONE_2020182003) //공백있을때
						{

							if (list[startPoint][startPoint + i].state == BLACK)
							{
								weight[j][j + i] = -BLANCK_3_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[startPoint][startPoint + i].state == WHITE)
							{
								weight[j][j + i] = BLANCK_3_2020182003;
							}
						}
					}

					if (list[startPoint][i + startPoint].state == BLACK) //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
						{
							weight[startPoint - 1][startPoint + i - 1] = -FULL_3_2020182003; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
						{
							weight[endPoint + 1][endPoint + i + 1] = -FULL_3_2020182003; // 막아!
						}
					}
					else if (list[startPoint][i + startPoint].state == WHITE) // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
						{
							weight[startPoint - 1][startPoint + i - 1] = FULL_3_2020182003; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
						{
							weight[endPoint + 1][endPoint + i + 1] = FULL_3_2020182003; // 막아!
						}
					}
				}
				else if (list[y][y + i].combo == 4) // 콤보 3또는 4일때 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //시작점에 최대치 기록  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234 // k를 j로 k는 y임 
					{
						if (Game[j][j + i] == NONE_2020182003) //공백있을때
						{
							blanckOn = 1;

							if (list[startPoint][startPoint + i].state == BLACK)
							{
								weight[j][j + i] = -BLANCK_4_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[startPoint][startPoint + i].state == WHITE)
							{
								weight[j][j + i] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // 공백 없을때
					{
						if (list[startPoint][startPoint + i].state == BLACK) //whelp 처음이 검은색일때
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
							{
								weight[startPoint - 1][startPoint + i - 1] = -FULL_4_2020182003; // 막아!
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
							{
								weight[endPoint + 1][endPoint + i + 1] = -FULL_4_2020182003; // 막아!
							}
						}
						else if (list[startPoint][startPoint + i].state == WHITE) // bhelp 처음이 백돌일때 
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
							{
								weight[startPoint - 1][startPoint + i - 1] = FULL_4_2020182003; // 막아! -> B도와주는 맵 
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
							{
								weight[endPoint + 1][endPoint + i + 1] = FULL_4_2020182003; // 막아!
							}
						}
					}
				}
			}
		}
	}
}

// 좌하단 대각선 가중치 업데이트 
void CheckLBindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		for (int y = 1; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y가 증가하는 줄 
			{
				if (y - 1 == 0) // 맨 처음일때 
				{
					if (Game[i + y - 1][y - 1] == BLACK) // y는 1이고 y-1이 0인 상황이 맨 처음 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[i + y - 1][y - 1].state = BLACK;
						list[i + y - 1][y - 1].Y = y - 1 + i;
						list[i + y - 1][y - 1].X = y - 1;
						list[i + y - 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[i + y - 1][y - 1].state = WHITE;
						list[i + y - 1][y - 1].Y = i + y - 1;
						list[i + y - 1][y - 1].X = y - 1;
						list[i + y - 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[i + y - 1][y - 1].state = NONE_2020182003;
						list[i + y - 1][y - 1].Y = i + y - 1;
						list[i + y - 1][y - 1].X = y - 1;
					}
				}

				if (Game[i + y][0 + y] == Game[i + y - 1][y - 1]) // 이전과 같을 때 BB ++ WW  기본형 Game[i][y].Game[0+y][i+y]
				{
					if (Game[i + y][0 + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[i + y][y].state = BLACK;
						list[i + y][y].Y = y + i;
						list[i + y][y].X = y;
						list[i + y][y].combo = sumB;

					}
					else if (Game[y + i][0 + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[i + y][y].state = WHITE;
						list[i + y][y].Y = y + i;
						list[i + y][y].X = y;
						list[i + y][y].combo = sumW;
					}
					else if (Game[y + i][y + 0] == NONE_2020182003) // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
					{
						if (y - 2 >= 0 && (Game[y - 2 + i][y - 2] == BLACK))
						{
							list[startPoint + i][startPoint].max = list[y - 2 + i][y - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
						}
						else if (y - 2 >= 0 && (Game[y - 2 + i][y - 2] == WHITE))
						{
							list[startPoint + i][startPoint].max = list[y - 2 + i][y - 2].combo;
						}
						countNone = 0; // 공백 초기화 
					}
				}
				else if (Game[y + i][y] != Game[y - 1 + i][y - 1]) // WB +B BW +W B+ W+
				{
					if (Game[y + i][y] == BLACK) // 전에 꺼 비교해서 설정해주기 
					{
						if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == WHITE))
						{
							list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo; // 시작점에 stp max 백업 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = y;
							list[y + i][y].state = BLACK;
							list[y + i][y].Y = y + i;
							list[y + i][y].X = y;
							list[y + i][y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // 공백 하나일때 연속중 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[y + i][y].state = BLACK;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // 공백 초기화 
								startPoint = y;
								list[y + i][y].state = BLACK;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumB;
							}
						}
					}
					else if (Game[y + i][y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == BLACK))
						{
							list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo; // 이전BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[y + i][y].state = WHITE;
							list[y + i][y].Y = y + i;
							list[y + i][y].X = y;
							list[y + i][y].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == NONE_2020182003))
						{
							if (countNone == 1) // 공백 하나일때 연속중  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[y + i][y].state = WHITE;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[y + i][y].state = WHITE;
								list[y + i][y].Y = y + i;
								list[y + i][y].X = y;
								list[y + i][y].combo = sumW;
							}
						}
					}
					else if (Game[y + i][y] == NONE_2020182003) // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // 처음 공백위치 

						if (countNone == 1)
						{
							nonePoint = y; //처음공백위치 저장 

						}
						else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == BLACK))
							{
								list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[y - 1 + i][y - 1] == WHITE))
							{
								list[startPoint + i][startPoint].max = list[y - 1 + i][y - 1].combo; // 이전BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // 콤보
				if (list[y + i][y].combo == 3) // 3일때 
				{
					list[startPoint + i][startPoint].max = list[y + i][y].combo; //시작점에 최대치 기록  

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
					{
						if (Game[j + i][j] == NONE_2020182003) //공백있을때
						{

							if (list[startPoint + i][startPoint].state == BLACK)
							{
								weight[j + i][j] = -BLANCK_3_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[startPoint + i][startPoint].state == WHITE)
							{
								weight[j + i][j] = BLANCK_3_2020182003;
							}
						}
					}

					if (list[startPoint + i][startPoint].state == BLACK) //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // 공백일때
						{
							weight[startPoint - 1 + i][startPoint - 1] = -FULL_3_2020182003; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // 공백일때
						{
							weight[endPoint + 1 + i][endPoint + 1] = -FULL_3_2020182003; // 막아!
						}
					}
					else if (list[startPoint + i][startPoint].state == WHITE) // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // 공백일때
						{
							weight[startPoint - 1 + i][startPoint - 1] = FULL_3_2020182003; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // 공백일때
						{
							weight[endPoint + 1 + i][endPoint + 1] = FULL_3_2020182003; // 막아!
						}
					}
				}
				else if (list[y + i][y].combo == 4) // 콤보 3또는 4일때 
				{
					list[startPoint + i][startPoint].max = list[y + i][y].combo; //시작점에 최대치 기록  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234 // k를 j로 k는 y임 
					{
						if (Game[j + i][j] == NONE_2020182003) //공백있을때
						{
							blanckOn = 1;

							if (list[startPoint + i][startPoint].state == BLACK)
							{
								weight[j + i][j] = -BLANCK_4_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[startPoint + i][startPoint].state == WHITE)
							{
								weight[j + i][j] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // 공백 없을때
					{
						if (list[startPoint + i][startPoint].state == BLACK) //whelp 처음이 검은색일때
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // 공백일때
							{
								weight[startPoint - 1 + i][startPoint - 1] = -FULL_4_2020182003; // 막아!
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // 공백일때
							{
								weight[endPoint + 1 + i][endPoint + 1] = -FULL_4_2020182003; // 막아!
							}
						}
						else if (list[startPoint + i][startPoint].state == WHITE) // bhelp 처음이 백돌일때 
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1 + i][startPoint - 1] == NONE_2020182003)) // 공백일때
							{
								weight[startPoint - 1 + i][startPoint - 1] = FULL_4_2020182003; // 막아! -> B도와주는 맵 
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1 + i][endPoint + 1] == NONE_2020182003)) // 공백일때
							{
								weight[endPoint + 1 + i][endPoint + 1] = FULL_4_2020182003; // 막아!
							}
						}
					}
				}
			}

		}
	}
}

// 우하단 대각선 가중치 업데이트
void CheckRBindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		for (int y = 1; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y가 증가하는 줄 
			{
				if (y - 1 == 0) // 맨 처음일때 
				{
					if (Game[18 - y + 1][i + y - 1] == BLACK) // y는 1이고 y-1이 0인 상황이 맨 처음 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[18 - y + 1][i + y - 1].state = BLACK; // 이전꺼 
						list[18 - y + 1][i + y - 1].Y = 18 - y + 1;
						list[18 - y + 1][i + y - 1].X = y + i - 1;
						list[18 - y + 1][i + y - 1].combo = 1;
					}
					else if (Game[18 - y + 1][i + y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[18 - y + 1][i + y - 1].state = WHITE;
						list[18 - y + 1][i + y - 1].Y = 18 - y + 1;
						list[18 - y + 1][i + y - 1].X = i + y - 1;
						list[18 - y + 1][i + y - 1].combo = 1;
					}
					else if (Game[18 - y + 1][i + y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[18 - y + 1][i + y - 1].state = NONE_2020182003;
						list[18 - y + 1][i + y - 1].Y = 18 - y + 1;
						list[18 - y + 1][i + y - 1].X = i + y - 1;
					}
				}
				// 이전꺼 y는 +1 x는 -1  공식 18-y][i + y
				if (Game[18 - y][i + y] == Game[18 - y + 1][i + y - 1]) // 이전과 같을 때 BB ++ WW  기본형 Game[i][y].Game[0+y][i+y]
				{
					if (Game[18 - y][i + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[18 - y][i + y].state = BLACK;
						list[18 - y][i + y].Y = 18 - y;
						list[18 - y][i + y].X = i + y;
						list[18 - y][i + y].combo = sumB;

					}
					else if (Game[18 - y][i + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[18 - y][i + y].state = WHITE;
						list[18 - y][i + y].Y = 18 - y;
						list[18 - y][i + y].X = y + i;
						list[18 - y][i + y].combo = sumW;
					}
					else if (Game[18 - y][y + i] == NONE_2020182003) // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
					{
						if (y - 2 >= 0 && (Game[18 - y + 2][y + i - 2] == BLACK))
						{ // startpoint = y [y][y+i] = [18-y][y+i]
							list[18 - startPoint][startPoint + i].max = list[18 - y + 2][y + i - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
						}
						else if (y - 2 >= 0 && (Game[18 - y + 2][y + i - 2] == WHITE))
						{
							list[18 - startPoint][startPoint + i].max = list[18 - y + 2][y + i - 2].combo;
						}
						countNone = 0; // 공백 초기화 
					}
				}
				else if (Game[18 - y][i + y] != Game[18 - y + 1][y + i - 1]) // WB +B BW +W B+ W+
				{
					if (Game[18 - y][i + y] == BLACK) // 전에 꺼 비교해서 설정해주기 
					{
						if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == WHITE))
						{
							list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo; // 시작점에 stp max 백업 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = y;
							list[18 - y][i + y].state = BLACK;
							list[18 - y][i + y].Y = 18 - y;
							list[18 - y][i + y].X = i + y;
							list[18 - y][i + y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // 공백 하나일때 연속중 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[18 - y][y + i].state = BLACK;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // 공백 초기화 
								startPoint = y;
								list[18 - y][y + i].state = BLACK;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumB;
							}
						}
					}
					else if (Game[18 - y][i + y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == BLACK))
						{
							list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo; // 이전BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[18 - y][y + i].state = WHITE;
							list[18 - y][y + i].Y = 18 - y;
							list[18 - y][y + i].X = y + i;
							list[18 - y][y + i].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == NONE_2020182003))
						{
							if (countNone == 1) // 공백 하나일때 연속중  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[18 - y][y + i].state = WHITE;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[18 - y][y + i].state = WHITE;
								list[18 - y][y + i].Y = 18 - y;
								list[18 - y][y + i].X = y + i;
								list[18 - y][y + i].combo = sumW;
							}
						}
					}
					else if (Game[18 - y][y + i] == NONE_2020182003) // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // 처음 공백위치 

						if (countNone == 1)
						{
							nonePoint = y; //처음공백위치 저장 

						}
						else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == BLACK))
							{
								list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[18 - y + 1][y + i - 1] == WHITE))
							{
								list[18 - startPoint][startPoint + i].max = list[18 - y + 1][y + i - 1].combo; // 이전BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // 콤보
				if (list[18 - y][y + i].combo == 3) // 3일때 
				{
					list[18 - startPoint][startPoint + i].max = list[18 - y][y + i].combo; //시작점에 최대치 기록  

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
					{
						if (Game[18 - j][j + i] == NONE_2020182003) //공백있을때
						{

							if (list[18 - startPoint][startPoint + i].state == BLACK)
							{
								weight[18 - j][j + i] = -BLANCK_3_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[18 - startPoint][startPoint + i].state == WHITE) // st == y / y-1][y-1+i 
							{
								weight[18 - j][j + i] = BLANCK_3_2020182003;
							}
						}
					}
					//
					if (list[18 - startPoint][i + startPoint].state == BLACK) //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
						{
							weight[18 - startPoint + 1][startPoint + i - 1] = -FULL_3_2020182003; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
						{
							weight[18 - endPoint - 1][endPoint + i + 1] = -FULL_3_2020182003; // 막아!
						}
					}
					else if (list[18 - startPoint][i + startPoint].state == WHITE) // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
						{
							weight[18 - startPoint + 1][startPoint + i - 1] = FULL_3_2020182003; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
						{
							weight[18 - endPoint - 1][endPoint + i + 1] = FULL_3_2020182003; // 막아!
						}
					}
				}
				else if (list[18 - y][y + i].combo == 4) // 콤보 3또는 4일때 
				{
					list[18 - startPoint][startPoint + i].max = list[18 - y][y + i].combo; //시작점에 최대치 기록  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234 // k를 j로 k는 y임 
					{
						if (Game[18 - j][j + i] == NONE_2020182003) //공백있을때
						{
							blanckOn = 1;

							if (list[18 - startPoint][startPoint + i].state == BLACK)
							{
								weight[18 - j][j + i] = -BLANCK_4_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[18 - startPoint][startPoint + i].state == WHITE)
							{
								weight[18 - j][j + i] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // 공백 없을때
					{
						if (list[18 - startPoint][startPoint + i].state == BLACK) //whelp 처음이 검은색일때
						{
							if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
							{
								weight[18 - startPoint + 1][startPoint + i - 1] = -FULL_4_2020182003; // 막아!
							}
							if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
							{
								weight[18 - endPoint - 1][endPoint + i + 1] = -FULL_4_2020182003; // 막아!
							}
						}
						else if (list[18 - startPoint][18 - startPoint + i].state == WHITE) // bhelp 처음이 백돌일때 
						{
							if (startPoint - 1 >= 0 && (Game[18 - startPoint + 1][startPoint + i - 1] == NONE_2020182003)) // 공백일때
							{
								weight[18 - startPoint + 1][startPoint + i - 1] = FULL_4_2020182003; // 막아! -> B도와주는 맵 
							}
							if (endPoint + 1 <= 18 && (Game[18 - endPoint - 1][endPoint + i + 1] == NONE_2020182003)) // 공백일때
							{
								weight[18 - endPoint - 1][endPoint + i + 1] = FULL_4_2020182003; // 막아!
							}
						}
					}
				}
			}
		}
	}
}

// 좌상단 대각선 가중치 업데이트
void CheckLTindex_2020182003(int weight[][19], int Game[][19])
{
	LIST_2020182003 list[19][19] = { 0 };

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		for (int y = 1; y < 2 * k; y++)
		{
			if (k - y >= 0 && y < 18) // Game[0+y][i+y]  i 18~0, k0 ++, y=0~2*k y가 증가하는 줄 
			{
				if (y - 1 == 0) // 맨 처음일때 
				{
					if (Game[k - y + 1][y - 1] == BLACK) // y는 1이고 y-1이 0인 상황이 맨 처음 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[k - y + 1][y - 1].state = BLACK;
						list[k - y + 1][y - 1].Y = k - y + 1;
						list[k - y + 1][y - 1].X = y - 1;
						list[k - y + 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == WHITE)
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[k - y + 1][y - 1].state = WHITE;
						list[k - y + 1][y - 1].Y = k - y + 1;
						list[k - y + 1][y - 1].X = y - 1;
						list[k - y + 1][y - 1].combo = 1;
					}
					else if (Game[i + y - 1][y - 1] == NONE_2020182003)
					{
						nonePoint = y - 1;
						list[k - y + 1][y - 1].state = NONE_2020182003;
						list[k - y + 1][y - 1].Y = k - y + 1;
						list[k - y + 1][y - 1].X = y - 1;
					}
				}

				if (Game[k - y][0 + y] == Game[k - y + 1][y - 1]) // 이전과 같을 때 BB ++ WW  기본형 Game[i][y].Game[0+y][i+y]
				{
					if (Game[k - y][0 + y] == BLACK)
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[k - y][y].state = BLACK;
						list[k - y][y].Y = k - y;
						list[k - y][y].X = y;
						list[k - y][y].combo = sumB;

					}
					else if (Game[k + i][0 + y] == WHITE)
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[k - y][y].state = WHITE;
						list[k - y][y].Y = k - y;
						list[k - y][y].X = y;
						list[k - y][y].combo = sumW;
					}
					else if (Game[k - i][y + 0] == NONE_2020182003) // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
					{
						if (y - 2 >= 0 && (Game[k - y + 2][y - 2] == BLACK))
						{
							list[k - startPoint][startPoint].max = list[k - y + 2][y - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
						}
						else if (y - 2 >= 0 && (Game[k - y + 2][y - 2] == WHITE))
						{
							list[k - startPoint][startPoint].max = list[k - y + 2][y - 2].combo;
						}
						countNone = 0; // 공백 초기화 
					}
				}
				else if (Game[k - y][y] != Game[k - y + 1][y - 1]) // WB +B BW +W B+ W+
				{
					if (Game[k - y][y] == BLACK) // 전에 꺼 비교해서 설정해주기 
					{
						if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == WHITE))
						{
							list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo; // 시작점에 stp max 백업 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = y;
							list[k - y][y].state = BLACK;
							list[k - y][y].Y = k - y;
							list[k - y][y].X = y;
							list[k - y][y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == NONE_2020182003)) // AOB BOB 
						{
							if (countNone == 1) // 공백 하나일때 연속중 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[k - y][y].state = BLACK;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumB;

							}
							else if (countNone == 0)
							{
								countB = 1;
								countW = 0;
								sumB = countB;
								countNone = 0; // 공백 초기화 
								startPoint = y;
								list[k - y][y].state = BLACK;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumB;
							}
						}
					}
					else if (Game[k - y][y] == WHITE)
					{
						if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == BLACK))
						{
							list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo; // 이전BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[k - y][y].state = WHITE;
							list[k - y][y].Y = k - y;
							list[k - y][y].X = y;
							list[k - y][y].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == NONE_2020182003))
						{
							if (countNone == 1) // 공백 하나일때 연속중  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[k - y][y].state = WHITE;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumW;

							}
							else if (countNone == 0) // 00A A0A0A
							{
								countW = 1;
								countB = 0;
								sumW = countW;
								countNone = 0;
								startPoint = y;
								list[k - y][y].state = WHITE;
								list[k - y][y].Y = k - y;
								list[k - y][y].X = y;
								list[k - y][y].combo = sumW;
							}
						}
					}
					else if (Game[k - y][y] == NONE_2020182003) // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // 처음 공백위치 

						if (countNone == 1)
						{
							nonePoint = y; //처음공백위치 저장 

						}
						else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == BLACK))
							{
								list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[k - y + 1][y - 1] == WHITE))
							{
								list[k - startPoint][startPoint].max = list[k - y + 1][y - 1].combo; // 이전BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				 // 콤보
				if (list[k - y][y].combo == 3) // 3일때 
				{
					list[k - startPoint][startPoint].max = list[k - y][y].combo; //시작점에 최대치 기록  

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
					{
						if (Game[k - j][j] == NONE_2020182003) //공백있을때
						{

							if (list[k - startPoint][startPoint].state == BLACK)
							{
								weight[k - j][j] = -BLANCK_3_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[k - startPoint][startPoint].state == WHITE)
							{
								weight[k - j][j] = BLANCK_3_2020182003;
							}
						}
					}

					if (list[k - startPoint][startPoint].state == BLACK) //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // 공백일때
						{
							weight[k - startPoint + 1][startPoint - 1] = -FULL_3_2020182003; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // 공백일때
						{
							weight[k - endPoint - 1][endPoint + 1] = -FULL_3_2020182003; // 막아!
						}//	weight[k - endPoint - 1 + i][endPoint + 1] = -FULL_3_2020182003; i를 빼보겠음

					}
					else if (list[k - startPoint][startPoint].state == WHITE) // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // 공백일때
						{
							weight[k - startPoint + 1][startPoint - 1] = FULL_3_2020182003; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // 공백일때
						{
							weight[k - endPoint - 1][endPoint + 1] = FULL_3_2020182003; // 막아!
						}
					}
				}
				else if (list[k - y][y].combo == 4) // 콤보 3또는 4일때 
				{
					list[k - startPoint][startPoint].max = list[k - y][y].combo; //시작점에 최대치 기록  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234 // k를 j로 k는 y임 
					{
						if (Game[k - j][j] == NONE_2020182003) //공백있을때
						{
							blanckOn = 1;

							if (list[k - startPoint][startPoint].state == BLACK)
							{
								weight[k - j][j] = -BLANCK_4_2020182003; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[k - startPoint][startPoint].state == WHITE)
							{
								weight[k - j][j] = BLANCK_4_2020182003;
							}

						}
					}

					if (blanckOn == 0) // 공백 없을때
					{
						if (list[k - startPoint][startPoint].state == BLACK) //whelp 처음이 검은색일때
						{
							if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // 공백일때
							{
								weight[k - startPoint + 1][startPoint - 1] = -FULL_4_2020182003; // 막아!
							}
							if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // 공백일때
							{
								weight[k - endPoint - 1][endPoint + 1] = -FULL_4_2020182003; // 막아!
							}
						}
						else if (list[k - startPoint][startPoint].state == WHITE) // bhelp 처음이 백돌일때 
						{
							if (startPoint - 1 >= 0 && (Game[k - startPoint + 1][startPoint - 1] == NONE_2020182003)) // 공백일때
							{
								weight[k - startPoint + 1][startPoint - 1] = FULL_4_2020182003; // 막아! -> B도와주는 맵 
							}
							if (endPoint + 1 <= 18 && (Game[k - endPoint - 1][endPoint + 1] == NONE_2020182003)) // 공백일때
							{
								weight[k - endPoint - 1][endPoint + 1] = FULL_4_2020182003; // 막아!
							}
						}
					}
				}
			}
		}
	}
}

// 절대 위험수 없을때 -> 공격할지 방어할지 int로 반환해주는 함수 -> (+)인 경우만 더해줌 
int PlusCompare_2020182003(int weight[][19])
{
	int sum = 0;

	int stop = 0;
	int stop2 = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] == FULL_4_2020182003 // 절대 위험 수 -> 발견하면 나가기 
				|| weight[i][k] == -FULL_4_2020182003
				|| weight[i][k] == BLANCK_4_2020182003
				|| weight[i][k] == -BLANCK_4_2020182003)
			{
				stop++;
				break;
			}

			if (weight[i][k] == FULL_3_2020182003 // 절대 위험 수 -> 발견하면 나가기 
				|| weight[i][k] == -FULL_3_2020182003
				|| weight[i][k] == BLANCK_3_2020182003
				|| weight[i][k] == -BLANCK_3_2020182003)
			{
				stop2++;
			}

			if (weight[i][k] > 0)
			{
				sum += weight[i][k]; // 양수일때 저장 
			}
		}
	}

	if (sum == 0)
	{
		return 0;
	}
	else if (stop != 0)
	{
		return -1;
	}
	else if (stop2 != 0)
	{
		return -2;
	}
	else
	{
		return sum;
	}
}

// 절대 위험수 없을때 -> 공격할지 방어할지 int로 반환해주는 함수 -> (-)인 경우만 더해줌 
int MinusCompare_2020182003(int weight[][19])
{
	int sum = 0;

	int stop = 0;
	int stop2 = 0;

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (weight[i][k] == FULL_4_2020182003 // 절대 위험 수 -> 발견하면 나가기 
				|| weight[i][k] == -FULL_4_2020182003
				|| weight[i][k] == BLANCK_4_2020182003
				|| weight[i][k] == -BLANCK_4_2020182003)
			{
				stop++;
				break;
			}

			if (weight[i][k] == FULL_3_2020182003 // 절대 위험 수 -> 발견하면 나가기 
				|| weight[i][k] == -FULL_3_2020182003
				|| weight[i][k] == BLANCK_3_2020182003
				|| weight[i][k] == -BLANCK_3_2020182003)
			{
				stop2++;
			}

			if (weight[i][k] < 0)
			{
				sum -= weight[i][k]; // 양수일때 저장 
			}


		}
	}

	if (sum == 0)
	{
		return 0;
	}
	else if (stop != 0)
	{
		return -1;
	}
	else if (stop2 != 0)
	{
		return -2;
	}
	else
	{
		return sum;
	}


}