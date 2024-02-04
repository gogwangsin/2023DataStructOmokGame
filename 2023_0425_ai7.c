#if 1

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//#include "AI7sup.h"

typedef struct STONE {

	int y, x;
	char team;

}STONE;

typedef struct STACK {

	STONE stone;
	struct STACK* next;

}STACK;

typedef struct LIST {

	char state;
	int Y, X;
	int combo;

}LIST;

STACK* pushStone(STACK* top, int y, int x, char team, int* count);
void printStack(STACK* top, int count);
void PrintGame(char Game[][19], STACK* top);
STACK* popStone(STACK** top, int* count, char Game[][19]);


void MakeGame(char Game[][19]);
void menu(void);
void EveryCount(char Game[][19]);
void CheckA(char Game[][19]);
void CheckB(char Game[][19]);
void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);
void CheckBindex(char Game[][19]);

char Game[19][19];

STACK* push2(STACK* back)
{


	return back;
}

int main(void)
{
	MakeGame(Game);

	STACK* top = NULL;
	int count = 0;

	STACK* back = NULL; // 무르기 무르기 스택 
	STACK* temp = NULL;

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
		case 1: EveryCount(Game); i--; continue;
		case 2: CheckB(Game); CheckA(Game); i--; continue;
		case 3: CheckRTLB(Game); CheckRBLT(Game); i--; continue;
		case 4: CheckBindex(Game); i--; continue;
		case 5: exit(1);
		case 6:
			temp = popStone(&top, &count, Game); // temp 가져옴, null, 값 존재. 
			if (temp == NULL) continue;

			back = pushStone(back, temp->stone.y, temp->stone.x, temp->stone.team, &count);



			PrintGame(Game, top);
			if (back != NULL)
				printf("돌을 한 수 물렀습니다\n");
			//	printStack(top, count);
			printStack(back, count);
			i -= 2;
			if (i < 0) i = 1;
			continue;

		case 7:
			//back에 있는걸 가져와서 push top 
			/*
			top = pushStone(top, Y, X, 'B',&count);
			PrintGame(Game,top);
			printStack(top,count);
			*/

			temp = popStone(&back, &count, Game);
			if (temp == NULL) continue;
			top = pushStone(top, temp->stone.y, temp->stone.x, temp->stone.team, &count);

			PrintGame(Game, top);
			printStack(top, count);
			printStack(back, count);

			continue;

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
			top = pushStone(top, Y, X, 'B', &count);
			PrintGame(Game, top);
			printStack(top, count);
		}
		else if (i % 2 == 0) {
			top = pushStone(top, Y, X, 'W', &count);
			PrintGame(Game, top);
			printStack(top, count);

		}

	}



	return 0;
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
		Game[cur->stone.y][cur->stone.x] = cur->stone.team; // STACK 구조체에 있는 좌표 정보에 팀 정보 입력 'A' 문자형태임

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

STACK* pushStone(STACK* top, int y, int x, char team, int* count)
{
	*count += 1;

	STACK* new = (STACK*)malloc(sizeof(STACK));
	if (new == NULL)
	{
		printf("동적 할당에 실패\n");
		return top;
	}

	new->stone.y = y;
	new->stone.x = x;
	new->stone.team = team; // STACK 구조체만큼 새로운 메모리 할당해서 push할 정보 입력하고 top포인터 new로 변경하기 

	new->next = top;
	top = new;

	return top;
}

STACK* popStone(STACK** top, int* count, char Game[][19])
{
	// 이중포인터 -> *top는 주소값임
	if (*top == NULL)
	{
		printf("스택이 존재하지 않습니다\n");
		return NULL;
	}
	else
	{
		STACK* temp = *top; // 주소값 temp*에 건내주고
		*top = (*top)->next; // 다음 노드로 변경하고
		temp->next = NULL; // 빼낼거 -> next가 아무것도 가르키지 않도록 변경하고
		*count -= 1; // 전체 개수 한개 빼고
		Game[temp->stone.y][temp->stone.x] = '+'; // '+' 돌 없음 -> 무르기
		return temp;
	}

}

void printStack(STACK* top, int count)
{

	for (STACK* i = top; i != NULL; i = i->next)
	{
		printf("(%d %d):%c->", i->stone.y, i->stone.x, i->stone.team);
	}
	printf("NULL(돌 : %d개) \n", count);
}

void menu(void)
{
	printf("=========================================\n");
	printf("0. 메뉴 선택 없이 돌 두기\n");
	printf("1 모든 가로 세로 줄 돌 출력하기\n");
	printf("2. 각 가로 세로 줄 가장 연속 돌 출력\n");
	printf("3. 각 대각선 줄 가장 연속 돌 출력\n");
	printf("4. 모든 가로줄에서 연속 돌의 좌표 출력\n");
	printf("5. 게임 종료\n");
	printf("6. 무르기\n");
	printf("7. 무르기로 저장했던 바둑 다시 두기\n");
	printf("=========================================\n");
	printf("명령어 입력 : ");

}

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

}
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
	printf("=========================================\n");

}
void CheckB(char Game[][19])
{
	printf("=========================================\n");
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
}
void CheckRTLB(char Game[][19])
{
	printf("=========================================\n");

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
	printf("=========================================\n");

}
void CheckBindex(char Game[][19])
{
	LIST list[19][19] = { 0 };
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0)
			{
				if (Game[i][k - 1] == 'B')
				{
					countB = 1;
					sumB = countB;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
				else if (Game[i][k - 1] == 'W')
				{
					countW = 1;
					sumW = countW;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
					list[i][k - 1].combo = 1;
				}
			}

			if (Game[i][k] == Game[i][k - 1])
			{
				if (Game[i][k] == 'B')
				{
					countB++;
					countW = 0;
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
					if (countW > sumW) sumW = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
			}
			else if (Game[i][k] != Game[i][k - 1])
			{
				if (Game[i][k] == 'B')
				{
					countB = 1;
					countW = 0;
					sumB = countB;

					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumB;

				}
				else if (Game[i][k] == 'W')
				{
					countW = 1;
					countB = 0;
					sumW = countW;

					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
					list[i][k].combo = sumW;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].combo > max) max = list[i][k].combo;
		}

		for (int k = 0; k < 19; k++)
		{
			if (max > 1 && list[i][k].combo == max)
			{
				printf("가로 %02d번째 연속 돌 좌표 ", i);
				if (list[i][k].state == 'B')
				{
					printf("B( Y , X ) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("( %d , %d ) ", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state == 'W')
				{
					printf("W( Y , X ) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("( %d , %d ) ", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state != 0) printf("\n");
			}
		}
	}
}

#endif