#if 0

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BLACK 1
#define WHITE -1
#define NONE 0

typedef struct LIST {

	char state;
	int Y, X;
	int combo;
	int max; // 콤보끊겼을때 최대값 저장 -> 한줄씩 비교 

}LIST;


typedef struct STONE {

	int y, x;
	char team;

}STONE;

typedef struct STACK {

	STONE stone;
	struct STACK* next;

}STACK;

void menu(void);
void PrintGame(char Game[][19], STACK* top);
void PrintStack(STACK* stack, int count);
STACK* pushStone(STACK* push, int y, int x, char team);
STACK* popStone(STACK** pop);
STACK* deleteAll(STACK* stack, char Game[][19]);

void saveGame(STACK* top, STACK* back, int countTop, int countBack);
void loadGame(STACK** top, STACK** back, int* countTop, int* countBack, int* i, char Game[][19]);

void MakeGame(char Game[][19]);
void EveryCount(char Game[][19]);
void CheckA(char Game[][19]);
void CheckB(char Game[][19]);
void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);

void helpGame(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void printHelp(char HELP[][19]);


void CheckBindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckAindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckRTindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckLBindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckRBindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);
void CheckLTindex(char Game[][19], char Bhelp[][19], char Whelp[][19]);


int main(void)
{
	STACK* top = NULL;
	STACK* back = NULL;
	STACK* temp = NULL;

	int countTop = 0;
	int countBack = 0;

	char Game[19][19];
	char Bhelp[19][19];
	char Whelp[19][19]; // 막을곳저장하는곳

	MakeGame(Game);
	helpGame(Game, Bhelp, Whelp);


	printf("\n처음 순서는 검은 돌 입니다.\n");

	for (int i = 1; i <= 361; i++)
	{
		menu();
		int choice;
		if (scanf("%d", &choice) != 1)
		{
			printf("입력 오류\n");
			exit(1);
		}fgetc(stdin);

		switch (choice)
		{
		case 0: break;
		case 1:
			if (i % 2 == 1) // 흑돌 
			{
				printHelp(Bhelp);
				printf("검은 돌 순서 기준 막기힌트\n");
			}
			else if (i % 2 == 0)
			{
				printHelp(Whelp);
				printf("흰 돌 순서 기준 막기힌트\n");

			} i--; continue;

		case 2:
			temp = popStone(&top);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countBack++;
				countTop--;
				back = pushStone(back, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = '+';
				PrintGame(Game, top);
				printf("무르기 스택 : "); PrintStack(back, countBack);
				printf("오목 스택 : "); PrintStack(top, countTop);

				i -= 2;
				if (i < 0) i = 1;
				continue;
			}
		case 3:
			temp = popStone(&back);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countBack--;
				countTop++;
				top = pushStone(top, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = temp->stone.team;

				PrintGame(Game, top);
				printf("무르기 스택 : "); PrintStack(back, countBack);
				printf("오목 스택 : "); PrintStack(top, countTop);
				continue;
			}
		case 4: saveGame(top, back, countTop, countBack); i--; continue;
		case 5:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			i = 1;
			countTop = 0;
			countBack = 0;
			loadGame(&top, &back, &countTop, &countBack, &i, Game);
			PrintGame(Game, top);
			helpGame(Game, Bhelp, Whelp);
			CheckAindex(Game, Bhelp, Whelp);
			CheckBindex(Game, Bhelp, Whelp);
			CheckRTindex(Game, Bhelp, Whelp);
			CheckLBindex(Game, Bhelp, Whelp);
			CheckRBindex(Game, Bhelp, Whelp);
			CheckLTindex(Game, Bhelp, Whelp);
			printf("무르기 스택 : "); PrintStack(back, countBack);
			printf("오목 스택 : "); PrintStack(top, countTop);
			printf("게임 로드를 완료했습니다!\n");
			i--;
			continue;
		case 6:
		default:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			printf("게임을 종료합니다!\n");
			exit(1);

		}


		int Y, X;
		printf("\n( Y , X )가 0보다 작거나 18보다 크다면 수행을 번복합니다.\n");

		if (i % 2 == 1)
		{
			printf("\n검돌 좌표를 입력하여 주십시오 ( Y, X ) : ");
		}
		else if (i % 2 == 0)
		{
			printf("\n흰돌 좌표를 입력하여 주십시오 ( Y, X ) : ");
		}


		if (scanf("%d %d", &Y, &X) != 2) {
			printf("입력 값이 옳바르지 않습니다. 프로그램을 종료합니다.\n");
			return 0;
		} fgetc(stdin);




		if (X < 0 || Y < 0 || X > 18 || Y > 18) {
			printf("\n범위를 벗어났습니다. 다시 입력해 주세요.\n");
			i--;
			continue;
		}

		if (Game[Y][X] == 'B' || Game[Y][X] == 'W') {
			printf("\n좌표에 이미 돌이 놓여 있습니다.\n");
			i--;
			continue;
		}


		if (i % 2 == 1) {

			Game[Y][X] = 'B';
			top = pushStone(top, Y, X, 'B');
			countTop++;
			back = deleteAll(back, Game);
			countBack = 0;
			PrintGame(Game, top);
			printf("무르기 스택 : "); PrintStack(back, countBack);
			printf("오목 스택 : "); PrintStack(top, countTop);
		}
		else if (i % 2 == 0) {

			Game[Y][X] = 'W';
			top = pushStone(top, Y, X, 'W');
			countTop++;
			back = deleteAll(back, Game);
			countBack = 0;
			PrintGame(Game, top);
			printf("무르기 스택 : "); PrintStack(back, countBack);
			printf("오목 스택 : "); PrintStack(top, countTop);
		}

		helpGame(Game, Bhelp, Whelp); // 초기화되서 다시 계산하기 
		CheckAindex(Game, Bhelp, Whelp);
		CheckBindex(Game, Bhelp, Whelp);
		CheckRTindex(Game, Bhelp, Whelp);
		CheckLBindex(Game, Bhelp, Whelp);
		CheckRBindex(Game, Bhelp, Whelp);
		CheckLTindex(Game, Bhelp, Whelp);

	}

	return 0;
}



void CheckAindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	LIST list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[k - 1][i] == 'B')
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[k - 1][i].state = 'B';
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == 'W') // 맨 처음 B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1;
					endPoint = k - 1;
					list[k - 1][i].state = 'W';
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
					list[k - 1][i].combo = 1;
				}
				else if (Game[k - 1][i] == '+') // 패스 
				{
					nonePoint = k - 1;
					list[k - 1][i].state = '+';
					list[k - 1][i].Y = 0;
					list[k - 1][i].X = i;
				}
			}


			if (Game[k][i] == Game[k - 1][i]) // 이전과 같을 때 BB ++ WW 
			{
				if (Game[k][i] == 'B')
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[k][i].state = 'B';
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumB;

				}
				else if (Game[k][i] == 'W')
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[k][i].state = 'W';
					list[k][i].Y = k;
					list[k][i].X = i;
					list[k][i].combo = sumW;
				}
				else if (Game[k][i] == '+') // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
				{
					if (k - 2 >= 0 && (Game[k - 2][i] == 'B'))
					{
						list[startPoint][i].max = list[k - 2][i].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
					}
					else if (k - 2 >= 0 && (Game[k - 2][i] == 'W'))
					{
						list[startPoint][i].max = list[k - 2][i].combo;
					}
					countNone = 0; // 공백 초기화 
				}
			}
			else if (Game[k][i] != Game[k - 1][i]) // WB +B BW +W B+ W+
			{
				if (Game[k][i] == 'B') // 전에 꺼 비교해서 설정해주기 
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == 'W'))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // 시작점에 stp max 백업 

						countB = 1;
						countW = 0;
						sumB = countB;
						countNone = 0; // 공백 초기화 
						startPoint = k;
						list[k][i].state = 'B';
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == '+')) // AOB BOB 
					{
						if (countNone == 1) // 공백 하나일때 연속중 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[k][i].state = 'B';
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
							list[k][i].state = 'B';
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumB;
						}
					}
				}
				else if (Game[k][i] == 'W')
				{
					if (k - 1 >= 0 && (Game[k - 1][i] == 'B'))
					{
						list[startPoint][i].max = list[k - 1][i].combo; // 이전BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[k][i].state = 'W';
						list[k][i].Y = k;
						list[k][i].X = i;
						list[k][i].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[k - 1][i] == '+'))
					{
						if (countNone == 1) // 공백 하나일때 연속중  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[k][i].state = 'W';
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
							list[k][i].state = 'W';
							list[k][i].Y = k;
							list[k][i].X = i;
							list[k][i].combo = sumW;
						}
					}
				}
				else if (Game[k][i] == '+') // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // 처음 공백위치 

					if (countNone == 1)
					{
						nonePoint = k; //처음공백위치 저장 

					}
					else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[k - 1][i] == 'B'))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // 01,10일때 생각 
							k = nonePoint;
							continue;
						}
						else if (k - 1 >= 0 && (Game[k - 1][i] == 'W'))
						{
							list[startPoint][i].max = list[k - 1][i].combo; // 이전BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[k][i].combo == 4) // 콤보 3또는 4일때 
			{
				list[startPoint][i].max = list[k][i].combo; //시작점에 최대치 기록  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[j][i] == '+') //공백있을때
					{
						blanckOn = 1;

						if (list[startPoint][i].state == 'B')
						{
							Whelp[j][i] = 'o'; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							if (Whelp[startPoint - 1][i] == 'o') Whelp[startPoint - 1][i] = '+';
							if (Whelp[endPoint + 1][i] == 'o') Whelp[endPoint + 1][i] = '+';
						}
						if (list[startPoint][i].state == 'W')
						{
							Bhelp[j][i] = 'o'; // 부호 바꿀수도있고 구조체로 좌표 저장하게 바꿀수도 잇긴해 
							if (Bhelp[startPoint - 1][i] == 'o') Bhelp[startPoint - 1][i] = '+';
							if (Bhelp[endPoint + 1][i] == 'o') Bhelp[endPoint + 1][i] = '+';
						}

					}
				}

				if (blanckOn == 0) // 공백 없을때
				{
					if (list[startPoint][i].state == 'B') //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // 공백일때
						{
							Whelp[startPoint - 1][i] = 'o'; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // 공백일때
						{
							Whelp[endPoint + 1][i] = 'o'; // 막아!
						}
					}
					else if (list[startPoint][i].state == 'W') // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // 공백일때
						{
							Bhelp[startPoint - 1][i] = 'o'; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // 공백일때
						{
							Bhelp[endPoint + 1][i] = 'o'; // 막아!
						}
					}
				}

			} // 콤보
			else if (list[k][i].combo == 3) // 3일때 
			{
				list[startPoint][i].max = list[k][i].combo; //시작점에 최대치 기록  

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[j][i] == '+') //공백있을때
					{

						if (list[startPoint][i].state == 'B')
						{
							Whelp[j][i] = 'o'; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
						}
						if (list[startPoint][i].state == 'W')
						{
							Bhelp[j][i] = 'o';
						}
					}
				}

				if (list[startPoint][i].state == 'B') //whelp 처음이 검은색일때
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // 공백일때
					{
						Whelp[startPoint - 1][i] = 'o'; // 막아!
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // 공백일때
					{
						Whelp[endPoint + 1][i] = 'o'; // 막아!
					}
				}
				else if (list[startPoint][i].state == 'W') // bhelp 처음이 백돌일때 
				{
					if (startPoint - 1 >= 0 && (Game[startPoint - 1][i] == '+')) // 공백일때
					{
						Bhelp[startPoint - 1][i] = 'o'; // 막아! -> B도와주는 맵 
					}
					if (endPoint + 1 <= 18 && (Game[endPoint + 1][i] == '+')) // 공백일때
					{
						Bhelp[endPoint + 1][i] = 'o'; // 막아!
					}
				}
			}

		}//-------------------------------------------------------------------------------------------------

		int max = 0;

		for (int k = 0; k < 19; k++)
		{
			if (list[k][i].max > max) max = list[k][i].max; // 맨 처음 돌에 콤보 맥스치 저장해놨고 -> 콤보 끟길때 다음 돌부터 순서하면 combo바뀌니 백업
		} // 연속끊겼을때만 combo위치에 max에 백업해두는거야

		for (int k = 0; k < 19; k++)
		{
			if (max > 1 && (list[k][i].max == max))
			{
				printf("세로 %02d번째 연속 돌 좌표 ", i);  // 공백 출력 안해도 될듯 

				if (list[k][i].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k; j <= k + list[k][i].max; j++)
					{
						if (j <= 18 && (list[j][i].state == 'B')) // 공백포함 max까지하는데 돌멩이 잇을때만 출력 k=2, max=4-> 
						{
							printf("(%d,%d)", list[j][i].Y, list[j][i].X);
						}
					}
				}

				if (list[k][i].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k; j <= k + list[k][i].max; j++)
					{
						if (j <= 18 && (list[j][i].state == 'W'))
						{
							printf("(%d,%d)", list[j][i].Y, list[j][i].X);
						}
					}
				}

				if (list[k][i].state != 0) printf("\n");
			}
		}

	}


}
void CheckBindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	LIST list[19][19] = { 0 };

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0, countNone = 0;

		int startPoint = 0, endPoint = 0, nonePoint = 0; // 시작 끝 공백 위치 

		int k = 1;

		for (k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[i][k - 1] == 'B')
				{
					countB = 1;
					sumB = countB;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == 'W') // 맨 처음 B or W or +
				{
					countW = 1;
					sumW = countW;
					startPoint = k - 1;
					endPoint = k - 1;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == '+') // 패스 
				{
					nonePoint = k - 1;
					list[i][k - 1].state = '+';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}


			if (Game[i][k] == Game[i][k - 1]) // 이전과 같을 때 BB ++ WW 
			{
				if (Game[i][k] == 'B')
				{
					countB++;
					countW = 0;
					endPoint = k;
					if (countB > sumB) sumB = countB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumB;

				}
				else if (Game[i][k] == 'W')
				{
					countW++;
					countB = 0;
					endPoint = k;
					if (countW > sumW) sumW = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
				else if (Game[i][k] == '+') // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
				{
					if (k - 2 >= 0 && (Game[i][k - 2] == 'B'))
					{
						list[i][startPoint].max = list[i][k - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
					}
					else if (k - 2 >= 0 && (Game[i][k - 2] == 'W'))
					{
						list[i][startPoint].max = list[i][k - 2].combo;
					}
					countNone = 0; // 공백 초기화 
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // WB +B BW +W B+ W+
			{
				if (Game[i][k] == 'B') // 전에 꺼 비교해서 설정해주기 
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == 'W'))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // 시작점에 stp max 백업 

						countB = 1;
						countW = 0;
						sumB = countB;
						countNone = 0; // 공백 초기화 
						startPoint = k;
						list[i][k].state = 'B';
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumB;

					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == '+')) // AOB BOB 
					{
						if (countNone == 1) // 공백 하나일때 연속중 
						{
							countB++;
							countW = 0;
							endPoint = k;
							if (countB > sumB) sumB = countB;
							list[i][k].state = 'B';
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
							list[i][k].state = 'B';
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumB;
						}
					}
				}
				else if (Game[i][k] == 'W')
				{
					if (k - 1 >= 0 && (Game[i][k - 1] == 'B'))
					{
						list[i][startPoint].max = list[i][k - 1].combo; // 이전BW

						countW = 1;
						countB = 0;
						sumW = countW;
						countNone = 0;
						startPoint = k;
						list[i][k].state = 'W';
						list[i][k].Y = i;
						list[i][k].X = k;
						list[i][k].combo = sumW;
					}
					else  if (k - 1 >= 0 && (Game[i][k - 1] == '+'))
					{
						if (countNone == 1) // 공백 하나일때 연속중  A0A 
						{
							countW++;
							countB = 0;
							endPoint = k;
							if (countW > sumW) sumW = countW;
							list[i][k].state = 'W';
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
							list[i][k].state = 'W';
							list[i][k].Y = i;
							list[i][k].X = k;
							list[i][k].combo = sumW;
						}
					}
				}
				else if (Game[i][k] == '+') // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
				{
					countNone++; // 처음 공백위치 

					if (countNone == 1)
					{
						nonePoint = k; //처음공백위치 저장 

					}
					else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
					{
						countNone = 0;
						if (k - 1 >= 0 && (Game[i][k - 1] == 'B'))
						{
							list[i][startPoint].max = list[i][k - 1].combo;
							k = nonePoint;
							continue;
						}
						else if (k - 1 >= 0 && (Game[i][k - 1] == 'W'))
						{
							list[i][startPoint].max = list[i][k - 1].combo; // 이전BW
							k = nonePoint;
							continue;
						}
					}
				}

			}
			//-------------------------------------------------------------------------------------------------------

			if (list[i][k].combo == 4) // 콤보 3또는 4일때 
			{
				list[i][startPoint].max = list[i][k].combo; //시작점에 최대치 기록  

				int blanckOn = 0;

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[i][j] == '+') //공백있을때
					{
						blanckOn = 1;

						if (list[i][startPoint].state == 'B')
						{
							Whelp[i][j] = 'o'; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							if (Whelp[i][startPoint - 1] == 'o') Whelp[i][startPoint - 1] = '+';
							if (Whelp[i][endPoint + 1] == 'o') Whelp[i][endPoint + 1] = '+';
						}
						if (list[i][startPoint].state == 'W')
						{
							Bhelp[i][j] = 'o';
							if (Bhelp[i][startPoint - 1] == 'o') Bhelp[i][startPoint - 1] = '+';
							if (Bhelp[i][endPoint + 1] == 'o') Bhelp[i][endPoint + 1] = '+';
						}

					}
				}

				if (blanckOn == 0) // 공백 없을때
				{
					if (list[i][startPoint].state == 'B') //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // 공백일때
						{
							Whelp[i][startPoint - 1] = 'o'; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // 공백일때
						{
							Whelp[i][endPoint + 1] = 'o'; // 막아!
						}
					}
					else if (list[i][startPoint].state == 'W') // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // 공백일때
						{
							Bhelp[i][startPoint - 1] = 'o'; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // 공백일때
						{
							Bhelp[i][endPoint + 1] = 'o'; // 막아!
						}
					}
				}

			} // 콤보
			else if (list[i][k].combo == 3) // 3일때  3일때 한번 저장한거임 내가 볼땐 oBBOBO인데 OBBOBB
			{
				list[i][startPoint].max = list[i][k].combo; //시작점에 최대치 기록  

				for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
				{
					if (Game[i][j] == '+') //공백있을때
					{

						if (list[i][startPoint].state == 'B')
						{
							Whelp[i][j] = 'o'; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
						}
						if (list[i][startPoint].state == 'W')
						{
							Bhelp[i][j] = 'o';
						}
					}
				}

				if (list[i][startPoint].state == 'B') //whelp 처음이 검은색일때
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // 공백일때
					{
						Whelp[i][startPoint - 1] = 'o'; // 막아!
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // 공백일때
					{
						Whelp[i][endPoint + 1] = 'o'; // 막아!
					}
				}
				else if (list[i][startPoint].state == 'W') // bhelp 처음이 백돌일때 
				{
					if (startPoint - 1 >= 0 && (Game[i][startPoint - 1] == '+')) // 공백일때
					{
						Bhelp[i][startPoint - 1] = 'o'; // 막아! -> B도와주는 맵 
					}
					if (endPoint + 1 <= 18 && (Game[i][endPoint + 1] == '+')) // 공백일때
					{
						Bhelp[i][endPoint + 1] = 'o'; // 막아!
					}
				}
			}

		}//-------------------------------------------------------------------------------------------------

		int max = 0;

		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].max > max) max = list[i][k].max; // 맨 처음 돌에 콤보 맥스치 저장해놨고 -> 콤보 끟길때 다음 돌부터 순서하면 combo바뀌니 백업
		} // 연속끊겼을때만 combo위치에 max에 백업해두는거야

		for (int k = 0; k < 19; k++)
		{
			if (max > 1 && (list[i][k].max == max))
			{
				printf("가로 %02d번째 연속 돌 좌표 ", i);  // 공백 출력 안해도 될듯 

				if (list[i][k].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k; j <= k + list[i][k].max; j++)
					{
						if (j <= 18 && (list[i][j].state == 'B')) // 공백포함 max까지하는데 돌멩이 잇을때만 출력 k=2, max=4-> 
						{
							printf("(%d,%d)", list[i][j].Y, list[i][j].X);
						}
					}
				}

				if (list[i][k].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k; j <= k + list[i][k].max; j++)
					{
						if (j <= 18 && (list[i][j].state == 'W'))
						{
							printf("(%d,%d)", list[i][j].Y, list[i][j].X);
						}
					}
				}

				if (list[i][k].state != 0) printf("\n");
			}
		}

	}
}

void CheckRTindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	LIST list[19][19] = { 0 };

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
					if (Game[y - 1][i + y - 1] == 'B') // y는 1이고 y-1이 0인 상황이 맨 처음 
					{
						countB = 1;
						sumB = countB;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = 'B';
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = y + i - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == 'W')
					{
						countW = 1;
						sumW = countW;
						startPoint = y - 1;
						endPoint = y - 1;
						list[y - 1][i + y - 1].state = 'W';
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
						list[y - 1][i + y - 1].combo = 1;
					}
					else if (Game[y - 1][i + y - 1] == '+')
					{
						nonePoint = y - 1;
						list[y - 1][i + y - 1].state = '+';
						list[y - 1][i + y - 1].Y = y - 1;
						list[y - 1][i + y - 1].X = i + y - 1;
					}
				}

				if (Game[0 + y][i + y] == Game[y - 1][i + y - 1]) // 이전과 같을 때 BB ++ WW  기본형 Game[i][y].Game[0+y][i+y]
				{
					if (Game[0 + y][i + y] == 'B')
					{
						countB++;
						countW = 0;
						endPoint = y;
						if (countB > sumB) sumB = countB;
						list[y][i + y].state = 'B';
						list[y][i + y].Y = y;
						list[y][i + y].X = i + y;
						list[y][i + y].combo = sumB;

					}
					else if (Game[y][i + y] == 'W')
					{
						countW++;
						countB = 0;
						endPoint = y;
						if (countW > sumW) sumW = countW;
						list[y][i + y].state = 'W';
						list[y][i + y].Y = y;
						list[y][i + y].X = y + i;
						list[y][i + y].combo = sumW;
					}
					else if (Game[y][y + i] == '+') // 공백 2이상연속 nonepoint부터 돌멩이 나올때까지 k 조정 
					{
						if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == 'B'))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo; // 연속 공백 나오면 끊어야하는데 전에 있던거 max에 백업해야지 
						}
						else if (y - 2 >= 0 && (Game[y - 2][y + i - 2] == 'W'))
						{
							list[startPoint][startPoint + i].max = list[y - 2][y + i - 2].combo;
						}
						countNone = 0; // 공백 초기화 
					}
				}
				else if (Game[y][i + y] != Game[y - 1][y + i - 1]) // WB +B BW +W B+ W+
				{
					if (Game[y][i + y] == 'B') // 전에 꺼 비교해서 설정해주기 
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'W'))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // 시작점에 stp max 백업 

							countB = 1;
							countW = 0;
							sumB = countB;
							countNone = 0; // 공백 초기화 
							startPoint = y;
							list[y][i + y].state = 'B';
							list[y][i + y].Y = y;
							list[y][i + y].X = i + y;
							list[y][i + y].combo = sumB;

						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == '+')) // AOB BOB 
						{
							if (countNone == 1) // 공백 하나일때 연속중 
							{
								countB++;
								countW = 0;
								endPoint = y;
								if (countB > sumB) sumB = countB;
								list[y][y + i].state = 'B';
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
								list[y][y + i].state = 'B';
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumB;
							}
						}
					}
					else if (Game[y][i + y] == 'W')
					{
						if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'B'))
						{
							list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // 이전BW

							countW = 1;
							countB = 0;
							sumW = countW;
							countNone = 0;
							startPoint = y;
							list[y][y + i].state = 'W';
							list[y][y + i].Y = y;
							list[y][y + i].X = y + i;
							list[y][y + i].combo = sumW;
						}
						else  if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == '+'))
						{
							if (countNone == 1) // 공백 하나일때 연속중  A0A 
							{
								countW++;
								countB = 0;
								endPoint = y;
								if (countW > sumW) sumW = countW;
								list[y][y + i].state = 'W';
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
								list[y][y + i].state = 'W';
								list[y][y + i].Y = y;
								list[y][y + i].X = y + i;
								list[y][y + i].combo = sumW;
							}
						}
					}
					else if (Game[y][y + i] == '+') // coutnone 2면 끊어줘야하고 // BAO-c1 ABO-c1 AAO-c1 BBO-c1 OBO OAO 00A-c0 
					{
						countNone++; // 처음 공백위치 

						if (countNone == 1)
						{
							nonePoint = y; //처음공백위치 저장 

						}
						else if (countNone == 2) // 두번 만남 A0A0    AA0AA0 00AA 00A0A0 끊기조건 처음 POINT위치로 다시 세기 
						{
							countNone = 0;
							if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'B'))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo;
								y = nonePoint;
								continue;
							}
							else if (y - 1 >= 0 && (Game[y - 1][y + i - 1] == 'W'))
							{
								list[startPoint][startPoint + i].max = list[y - 1][y + i - 1].combo; // 이전BW
								y = nonePoint;
								continue;
							}
						}
					}

				}
				//-------------------------------------------------------------------------------------------------------

				if (list[y][y + i].combo == 4) // 콤보 3또는 4일때 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //시작점에 최대치 기록  

					int blanckOn = 0;

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234 // k를 j로 k는 y임 
					{
						if (Game[j][j + i] == '+') //공백있을때
						{
							blanckOn = 1;

							if (list[startPoint][startPoint + i].state == 'B')
							{
								Whelp[j][j + i] = 's'; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
								//	if (Whelp[startPoint - 1][startPoint+i-1] == 'o') Whelp[startPoint - 1][startPoint-1+i] = '+';
								if (Whelp[endPoint + 1][endPoint + 1 + i] == 'o') Whelp[endPoint + 1][endPoint + 1 + i] = '+';
							}
							if (list[startPoint][startPoint + i].state == 'W')
							{
								Bhelp[j][j + i] = 'o';
								if (Bhelp[startPoint - 1][startPoint - 1 + i] == 'o') Bhelp[startPoint - 1][startPoint - 1 + i] = '+';
								if (Bhelp[endPoint + 1][endPoint + 1 + i] == 'o') Bhelp[endPoint + 1][endPoint + 1 + i] = '+';
							}

						}
					}

					if (blanckOn == 0) // 공백 없을때
					{
						if (list[startPoint][startPoint + i].state == 'B') //whelp 처음이 검은색일때
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // 공백일때
							{
								Whelp[startPoint - 1][startPoint + i - 1] = 'o'; // 막아!
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // 공백일때
							{
								Whelp[endPoint + 1][endPoint + i + 1] = 'o'; // 막아!
							}
						}
						else if (list[startPoint][startPoint + i].state == 'W') // bhelp 처음이 백돌일때 
						{
							if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // 공백일때
							{
								Bhelp[startPoint - 1][startPoint + i - 1] = 'o'; // 막아! -> B도와주는 맵 
							}
							if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // 공백일때
							{
								Bhelp[endPoint + 1][endPoint + i + 1] = 'o'; // 막아!
							}
						}
					}

				} // 콤보
				else if (list[y][y + i].combo == 3) // 3일때 
				{
					list[startPoint][startPoint + i].max = list[y][y + i].combo; //시작점에 최대치 기록  

					for (int j = startPoint; j <= endPoint; j++) // 최대 1~5일때 10234
					{
						if (Game[j][j + i] == '+') //공백있을때
						{

							if (list[startPoint][startPoint + i].state == 'B')
							{
								Whelp[j][j + i] = 'o'; // 공백있는데 검은색일때 -> 백돌 맵에 그리기 
							}
							if (list[startPoint][startPoint + i].state == 'W')
							{
								Bhelp[j][j + i] = 'o';
							}
						}
					}

					if (list[startPoint][i + startPoint].state == 'B') //whelp 처음이 검은색일때
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // 공백일때
						{
							Whelp[startPoint - 1][startPoint + i - 1] = 'o'; // 막아!
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // 공백일때
						{
							Whelp[endPoint + 1][endPoint + i + 1] = 'o'; // 막아!
						}
					}
					else if (list[startPoint][i + startPoint].state == 'W') // bhelp 처음이 백돌일때 
					{
						if (startPoint - 1 >= 0 && (Game[startPoint - 1][startPoint + i - 1] == '+')) // 공백일때
						{
							Bhelp[startPoint - 1][startPoint + i - 1] = 'o'; // 막아! -> B도와주는 맵 
						}
						if (endPoint + 1 <= 18 && (Game[endPoint + 1][endPoint + i + 1] == '+')) // 공백일때
						{
							Bhelp[endPoint + 1][endPoint + i + 1] = 'o'; // 막아!
						}
					}
				}

			}//-------------------------------------------------------------------------------------------------

		}

		int max = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19)
			{
				if (list[y][i + y].max > max) max = list[y][y + i].max;
			}
		}

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (max > 1 && (list[y][y + i].max == max))
				{
					printf("우상단 %02d번째 연속 돌 좌표 ", k);  // 공백 출력 안해도 될듯 

					if (list[y][y + i].state == 'B')
					{
						printf("B(Y,X) : ");
						for (int j = y; j <= y + list[y][y + i].max; j++)
						{
							if (j <= 18 && (list[j][j + i].state == 'B')) // 공백포함 max까지하는데 돌멩이 잇을때만 출력 k=2, max=4-> 
							{
								printf("(%d,%d)", list[j][j + i].Y, list[j][j + i].X);
							}
						}
					}

					if (list[y][y + i].state == 'W')
					{
						printf("W(Y,X) : ");
						for (int j = y; j <= y + list[y][y + i].max; j++)
						{
							if (j <= 18 && (list[j][j + i].state == 'W'))
							{
								printf("(%d,%d)", list[j][j + i].Y, list[j][j + i].X);
							}
						}
					}

					if (list[y][y + i].state != 0) printf("\n");
				}
			}
		}
	}
}
void CheckLBindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{

}
void CheckRBindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{

}
void CheckLTindex(char Game[][19], char Bhelp[][19], char Whelp[][19])
{

}


void menu(void)
{
	printf("=========================================\n");
	printf("0. 메뉴 선택 없이 돌 두기\n");
	printf("1. 막을 곳 알려주기 맵 출력\n");
	printf("2. 무르기\n");
	printf("3. 무르기 했던 오목돌 다시 무르기\n");
	printf("4. 게임 저장하기\n");
	printf("5. 게임 로드하기\n");
	printf("6. 게임 종료하기\n");
	printf("=========================================\n");
	printf("명령어 입력 : ");

}
void MakeGame(char Game[][19])
{

	for (int i = 0; i < 19; i++) {

		for (int k = 0; k < 19; k++) {

			Game[i][k] = '+';
			printf("%c", Game[i][k]);

		}
		printf("\n");
	}
	printf("\n");
}
void PrintGame(char Game[][19], STACK* top)
{
	STACK* cur = top;
	while (cur != NULL)
	{
		Game[cur->stone.y][cur->stone.x] = cur->stone.team;
		cur = cur->next;
	}

	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {
			printf("%c", Game[i][k]);
		}
		printf("\n");
	}
	printf("\n");

}
void helpGame(char Game[][19], char Bhelp[][19], char Whelp[][19])
{
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			Bhelp[i][k] = Game[i][k];
			Whelp[i][k] = Game[i][k];
		}
	}

}
void printHelp(char HELP[][19])
{
	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {

			printf("%c", HELP[i][k]);
		}
		printf("\n");
	}
	printf("\n");
	printf("3 또는 4 공격 막을 곳을 알려주는 맵을 출력합니다.\n");
}
void PrintStack(STACK* stack, int count)
{
	for (STACK* k = stack; k != NULL; k = k->next)
	{
		printf("%c(%d,%d)->", k->stone.team, k->stone.y, k->stone.x);
	}
	printf("NULL(돌 개수: %d)\n", count);
}
STACK* pushStone(STACK* push, int y, int x, char team)
{
	STACK* new = (STACK*)malloc(sizeof(STACK));
	if (new == NULL)
	{
		printf("동적 할당에 실패했습니다!\n");
		return push;
	}

	new->stone.y = y;
	new->stone.x = x;
	new->stone.team = team;

	new->next = push;
	push = new;

	return push;
}
STACK* popStone(STACK** pop)
{
	if (*pop == NULL)
	{
		printf("스택이 비어있습니다!\n");
		return NULL;
	}
	else
	{
		STACK* temp = *pop;
		*pop = (*pop)->next;
		temp->next = NULL;
		return temp;
	}
}
STACK* deleteAll(STACK* stack, char Game[][19])
{
	if (stack == NULL)
	{
		return NULL;
	}

	STACK* temp = stack;
	while (stack != NULL)
	{
		temp = stack;
		stack = stack->next;
		Game[temp->stone.y][temp->stone.x] = '+';
		free(temp);
	}

	return stack;
}
void saveGame(STACK* top, STACK* back, int countTop, int countBack)
{
	FILE* fp = fopen("save.txt", "w");
	if (fp == NULL)
	{
		printf("파일 열기에 실패했습니다!\n");
		return;
	}

	fprintf(fp, "%d %d\n", countTop, countBack);

	for (int i = 0; i < countTop; i++)
	{
		fprintf(fp, "%d %d %c\n", top->stone.y, top->stone.x, top->stone.team);
		top = top->next;
	}

	for (int i = 0; i < countBack; i++)
	{
		fprintf(fp, "%d %d %c\n", back->stone.y, back->stone.x, back->stone.team);
		back = back->next;
	}

	printf("게임 저장을 완료했습니다!\n");
	fclose(fp);

}
void loadGame(STACK** top, STACK** back, int* countTop, int* countBack, int* i, char Game[][19])
{
	FILE* fp = fopen("save.txt", "r");
	if (fp == NULL)
	{
		printf("파일 열기에 실패했습니다!\n");
		return;
	}

	if (fscanf(fp, "%d %d", countTop, countBack) != 2)
	{
		printf("입력 오류!\n");
		exit(1);
	}

	for (int i = 0; i < *countTop; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("동적 할당에 실패했습니다!\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("입력 오류!\n");
			exit(1);
		}

		new->next = *top;
		*top = new;
		Game[new->stone.y][new->stone.x] = new->stone.team;
	}

	for (int i = 0; i < *countBack; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("동적 할당에 실패했습니다!\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("입력 오류!\n");
			exit(1);
		}

		new->next = *back;
		*back = new;
	}

	*i += *countTop;

	fclose(fp);


}



// 안쓰는애들 - 업그레이드 전 버전
void EveryCount(char Game[][19])
{
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}
		printf("가로 %02d번째 돌 개수 B : %d W : %d\n", i, countB, countW);
	}
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B') countB++;
			if (Game[k][i] == 'W') countW++;
		}
		printf("세로 %02d번째 돌 개수 B : %d W : %d\n", i, countB, countW);
	}
	printf("=========================================\n");

} // 안씀
void CheckA(char Game[][19])
{
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B')
			{
				countB++;
				countW = 0;
				if (countB > sumB) sumB = countB;
			}
			else if (Game[k][i] == 'W')
			{
				countW++;
				countB = 0;
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countB = 0, countW = 0;
			}
		}

		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("세로 %02d번째 최대 연속 돌 B : %d", i, sumB);
			if (sumW > sumB) printf("세로 %02d번째 최대 연속 돌 W : %d", i, sumW);
			if (sumB == sumW) printf("세로 %02d번째 최대 연속 돌 B : %d W : %d", i, sumB, sumW);
			printf("\n");
		}
	}

} // 안씀 
void CheckB(char Game[][19])
{
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B')
			{
				countB++;
				countW = 0;
				if (countB > sumB) sumB = countB;
			}
			else if (Game[i][k] == 'W')
			{
				countW++;
				countB = 0;
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countB = 0, countW = 0;
			}
		}

		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("가로 %02d번째 최대 연속 돌 B : %d", i, sumB);
			if (sumW > sumB) printf("가로 %02d번째 최대 연속 돌 W : %d", i, sumW);
			if (sumB == sumW) printf("가로 %02d번째 최대 연속 돌 B : %d W : %d", i, sumB, sumW);
			printf("\n");
		}
	}
} // 안씀 
void CheckRTLB(char Game[][19])
{

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (Game[0 + y][i + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB)sumB = countB;
				}
				else if (Game[0 + y][i + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}
		}
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("우상단 %02d번째 최대 연속 돌 B : %d", k, sumB);
			if (sumW > sumB) printf("우상단 %02d번째 최대 연속 돌 W : %d", k, sumW);
			if (sumB == sumW) printf("우상단 %02d번째 최대 연속 돌 B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}

	}

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (Game[i + y][0 + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB)sumB = countB;
				}
				else if (Game[i + y][0 + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}
		}
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("좌하단 %02d번째 최대 연속 돌 B : %d", k, sumB);
			if (sumW > sumB) printf("좌하단 %02d번째 최대 연속 돌 W : %d", k, sumW);
			if (sumB == sumW) printf("좌하단 %02d번째 최대 연속 돌 B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}


	}


}
void CheckRBLT(char Game[][19])
{

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) {

				if (Game[18 - y][i + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB)sumB = countB;
				}
				else if (Game[18 - y][i + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}
		}
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("우하단 %02d번째 최대 연속 돌 B : %d", k, sumB);
			if (sumW > sumB) printf("우하단 %02d번째 최대 연속 돌 W : %d", k, sumW);
			if (sumB == sumW) printf("우하단 %02d번째 최대 연속 돌 B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}

	}

	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (k - y >= 0 && y < 18) {

				if (Game[k - y][0 + y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB)sumB = countB;
				}
				else if (Game[k - y][0 + y] == 'W')
				{
					countB = 0;
					countW++;
					if (countW > sumW) sumW = countW;
				}
				else
				{
					countW = 0, countB = 0;
				}
			}
		}
		if (sumB > 1 || sumW > 1)
		{
			if (sumB > sumW) printf("좌상단 %02d번째 최대 연속 돌 B : %d", k, sumB);
			if (sumW > sumB) printf("좌상단 %02d번째 최대 연속 돌 W : %d", k, sumW);
			if (sumB == sumW) printf("좌상단 %02d번째 최대 연속 돌 B : %d W : %d", k, sumB, sumW);
			printf("\n");
		}


	}

}
#endif