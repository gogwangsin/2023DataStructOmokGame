
#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AI2sup.h"


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

void PrintGame(char Game[][19])
{
	for (int i = 0; i < 19; i++) {
		for (int k = 0; k < 19; k++) {
			printf("%c", Game[i][k]);
		}
		printf("\n");
	}
	printf("\n");

}


void menu(void)
{
	printf("=========================================\n");
	printf("0. 메뉴 선택 없이 돌 두기\n");
	printf("1. 모든 가로세로 줄 돌 출력\n");
	printf("2. 각 가로 세로 연속 돌 출력\n");
	printf("3. 각 대각선 연속 돌 출력\n");
	printf("4. 각 가로 연속 돌 좌표 출력\n");
	printf("5. 게임 종료\n");
	printf("=========================================\n");
	printf("명령어 입력 : ");

}
void EveryCount(char Game[][19])
{
	printf("================== 1 =====================\n");

	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0; // 초기화 구간 

		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}
		printf("가로 %02d번째 : B : %d W : %d\n", i, countB, countW);
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
		printf("세로 %02d번째 : B : %d W : %d\n", i, countB, countW);
	}
	printf("=========================================\n");


}

void CheckA(char Game[][19])
{
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B')
			{
				countB++;
				countW = 0; // 초기화 구간 
				if (countB > sumB) sumB = countB;
			}
			else if (Game[k][i] == 'W')
			{
				countW++;
				countB = 0;
				if (countW > sumW)sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}
		}

		if (sumB > 1 || sumW > 1) // 출력구간 연속이 1보다 크면 
		{
			printf("세로 %02d번째 최대 연속 돌 : ", i); // 가로로 세는게 편함 
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumB < sumW) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
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
				if (countW > sumW)sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}
		}

		if (sumB > 1 || sumW > 1)
		{
			printf("가로 %02d번째 최대 연속 돌 : ", i);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumB < sumW) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}
	printf("=========================================\n");


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
					if (countB > sumB) sumB = countB;
				}
				else if (Game[0 + y][i + y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("우상단 %02d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}


	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;


		for (int y = 0; y < 2 * k; y++)
		{
			if (i + y < 19 && y < 19) {
				if (Game[i + y][y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[i + y][y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("좌하단 %02d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}
	printf("=========================================\n");

}
void CheckRBLT(char Game[][19])
{
	printf("=========================================\n");

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
					if (countB > sumB) sumB = countB;
				}
				else if (Game[18 - y][i + y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("우하단 %02d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
			printf("\n");
		}
	}


	for (int i = 18, k = 0; i > 0; i--, k++)
	{
		int countB = 0, countW = 0, sumB = 0, sumW = 0;


		for (int y = 0; y < 2 * k; y++)
		{
			if (k - y >= 0 && y <= 18) { // <18이 맞을것같긴해
				if (Game[k - y][y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[k - y][y] == 'W')
				{
					countW++;
					countB = 0;
					if (countW > sumW) sumW = countW;
				}
			}
		}
		if (sumB > 1 || sumW > 1) {
			printf("좌상단 %02d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB) printf("W : %d", sumW);
			if (sumB == sumW) printf("B : %d, W : %d", sumB, sumW);
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
					countB++;

					list[i][k - 1].state = 'B';
					list[i][k - 1].combo = ++sumB;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
				else if (Game[i][k - 1] == 'W')
				{
					countW++;
					list[i][k - 1].state = 'W';
					list[i][k - 1].combo = ++sumW;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}

			if (Game[i][k] == Game[i][k - 1])
			{
				if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB; // 콤보여기서 수정해서 밑에만 조심하면 될듯 
					list[i][k].state = 'B';
					list[i][k].combo = sumB;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].state = 'W';
					list[i][k].combo = sumW;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // 다를때 sum넣으면 이상해짐 -> sum은 콤보니까 되도록 같은 거 만났을때 => 
			{
				if (Game[i][k] == 'B')
				{
					countW = 0; // count가 연속일때만 sum
					countB = 1;

					list[i][k].state = 'B';
					list[i][k].combo = countB; //cb,cw,comb는 모두 정해짐 -> 여기서 콤보 안증가해도 위에서 증가함 
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'W')
				{
					countB = 0;
					countW = 1;

					list[i][k].state = 'W';
					list[i][k].combo = countW;
					list[i][k].Y = i;
					list[i][k].X = k;
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
				printf("가로 %02d번째 연속 돌 좌표 : ", i);

				if (list[i][k].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("(%d,%d) ", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++)
					{
						printf("(%d,%d) ", list[i][j].Y, list[i][j].X);
					}
				}
				if (list[i][k].state != 0) printf("\n");
			}
		}
	}
	printf("=========================================\n");


}



#endif

