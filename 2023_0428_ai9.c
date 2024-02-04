#if 1

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct LIST {

	char state;
	int Y, X;
	int combo;

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
void CheckBindex(char Game[][19]);




int main(void)
{

	STACK* top = NULL;
	STACK* back = NULL;
	STACK* temp = NULL;

	int countTop = 0;
	int countBack = 0;



	char Game[19][19];
	MakeGame(Game);

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
		case 5:
			temp = popStone(&top);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countTop--;
				countBack++;
				back = pushStone(back, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = '+';

				PrintGame(Game, top);
				PrintStack(back, countBack);
				PrintStack(top, countTop);

				i -= 2;
				if (i < 0) i = 1;
				continue;
			}

		case 6:
			temp = popStone(&back);
			if (temp == NULL)
			{
				i--; continue;
			}
			else
			{
				countTop++;
				countBack--;
				top = pushStone(top, temp->stone.y, temp->stone.x, temp->stone.team);
				Game[temp->stone.y][temp->stone.x] = temp->stone.team;

				PrintGame(Game, top);
				PrintStack(back, countBack);
				PrintStack(top, countTop);

				continue;
			}
		case 7: saveGame(top, back, countTop, countBack); i--; continue;
		case 8:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
			countBack = 0;
			countTop = 0;
			i = 1;
			loadGame(&top, &back, &countTop, &countBack, &i, Game);
			i--;
			continue;

		case 9:
		default:
			top = deleteAll(top, Game);
			back = deleteAll(back, Game);
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
			PrintStack(back, countBack);
			PrintStack(top, countTop);
		}
		else if (i % 2 == 0) {
			Game[Y][X] = 'W';
			top = pushStone(top, Y, X, 'W');
			countTop++;

			back = deleteAll(back, Game);
			countBack = 0;

			PrintGame(Game, top);
			PrintStack(back, countBack);
			PrintStack(top, countTop);

		}

	}



	return 0;
}






void menu(void)
{
	printf("=========================================\n");
	printf("0. 메뉴 선택 없이 돌 두기\n");
	printf("1 모든 가로 세로 줄 돌 출력하기\n");
	printf("2. 각 가로 세로 줄 가장 연속 돌 출력\n");
	printf("3. 각 대각선 줄 가장 연속 돌 출력\n");
	printf("4. 모든 가로줄에서 연속 돌의 좌표 출력\n");
	printf("5. 무르기\n");
	printf("6. 무르기했던 오목돌 다시 무르기\n");
	printf("7. 게임 저장하기\n");
	printf("8. 게임 불러오기\n");
	printf("9. 게임 종료\n");
	printf("=========================================\n");
	printf("명령어 입력 : ");

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
void PrintStack(STACK* stack, int count)
{
	for (STACK* i = stack; i != NULL; i = i->next) // 스택 노드 포인터로 이동하면서
	{
		printf("%c(%d,%d)->", i->stone.team, i->stone.y, i->stone.x);
	}
	printf("NULL(돌 개수: %d)\n", count);
}

STACK* pushStone(STACK* push, int y, int x, char team)
{
	STACK* new = (STACK*)malloc(sizeof(STACK));
	if (new == NULL)
	{
		printf("동적할당에 실패했습니다\n");
		return push;
	}
	new->stone.y = y;
	new->stone.x = x;
	new->stone.team = team;

	new->next = push;
	push = new;

	return push; // 메인 스택 포인터 주소 리턴
}

STACK* popStone(STACK** pop)
{
	if (*pop == NULL)
	{
		printf("스택이 비어있습니다\n");
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
	// 게임 저장하기
	FILE* fp = fopen("save.txt", "w");
	if (fp == NULL)
	{
		printf("파일 열기에 실패했습니다\n");
		return;
	}

	fprintf(fp, "%d %d\n", countTop, countBack);
	// 파일에 출력하기
	// -> 메모장 파일에 y,x,char team 한줄씩 저장되고
	// 공백이나 \n로 구분해서 저장하고 읽음

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

	printf("게임 저장에 성공했습니다!\n");
	fclose(fp);
}

void loadGame(STACK** top, STACK** back, int* countTop, int* countBack, int* i, char Game[][19])
{
	FILE* fp = fopen("save.txt", "r");
	if (fp == NULL)
	{
		printf("파일 열기에 실패했습니다\n");
		return;
	}

	if (fscanf(fp, "%d %d", countTop, countBack) != 2)
	{
		printf("입력 오류\n");
		exit(1);
	}

	// -----------------------------------------------------------

	for (int i = 0; i < *countTop; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("동적할당에 실패했습니다\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("입력 오류\n");
			exit(1);
		}
		// new로 할당한 메모리 구조체에 정보 하나씩 입력 fscanf
		new->next = *top;
		*top = new;
		Game[new->stone.y][new->stone.x] = new->stone.team;

	}

// -----------------------------------------------------------

	for (int i = 0; i < *countBack; i++)
	{
		STACK* new = (STACK*)malloc(sizeof(STACK));
		if (new == NULL)
		{
			printf("동적할당에 실패했습니다\n");
			exit(1);
		}

		if (fscanf(fp, "%d %d %c", &new->stone.y, &new->stone.x, &new->stone.team) != 3)
		{
			printf("입력 오류\n");
			exit(1);
		}

		new->next = *back;
		*back = new;
	}

	*i += *countTop;
	printf("게임 로드에 성공했습니다!\n");
	fclose(fp);

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