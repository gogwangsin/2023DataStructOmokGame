#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"AIsup.h"



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




void EveryCOUNT(char Game[][19])
{
	int countB = 0, countW = 0;

	printf("================ 1 ==================\n");
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}

		printf("가로 %02d번째줄 : B: %d, W : %d\n", i, countB, countW);  // 줄 한번 탐색하고 나서 초기화
		countB = 0;
		countW = 0;
	}
	printf("====================================\n");

	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B') countB++;
			if (Game[k][i] == 'W') countW++; // 세로는 i,k바꿔서
		}

		printf("세로 %02d번째줄 : B: %d, W : %d\n", i, countB, countW); // 가로로 1 아래, 2 아래..
		countB = 0;
		countW = 0;
	}
	printf("====================================\n");

}
void menu(void)
{
	printf("====================================\n");
	printf("0. 메뉴 선택 없이 돌 두기\n");
	printf("1. 가로 세로 검,흰 돌 개수\n");
	printf("2. 가로 세로 연속 돌 출력\n");
	printf("3. 대각선 연속 돌 출력\n");
	printf("4. 가장 많이 연속된 돌들의 좌표와 종류\n");
	printf("5. 게임을 종료합니다\n");
	printf("====================================\n");
	printf("명령어 입력 : ");

}



void CheckA(char Game[][19])
{
	LIST list[19][19] = { 0 };

	printf("============ 2. 세로 연속 ==================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0) // 0일때 위치저장 
			{
				if (Game[k - 1][i] == 'W')
				{

					countW++;
					list[k - 1][i].combo = ++sumW;
					list[k - 1][i].state = 'W';
					list[k - 1][i].Y = k - 1;
					list[k - 1][i].X = i;

				}
				else if (Game[k - 1][i] == 'B')
				{
					countB++;
					list[k - 1][i].combo = ++sumB;
					list[k - 1][i].state = 'B';
					list[k - 1][i].Y = k - 1;
					list[k - 1][i].X = i;

				}

			}
			if (Game[k][i] == Game[k - 1][i]) // 1부터 그전 까지 쭉 비교 
			{
				if (Game[k][i] == 'W')
				{
					countW++;
					sumW = countW;
					list[k][i].combo = sumW;
					list[k][i].state = 'W';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
				else if (Game[k][i] == 'B') // else 안하면 0,0되서 콤보가 안됨 
				{
					countB++;
					sumB = countB;
					list[k][i].combo = sumB;
					list[k][i].state = 'B';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
			}
			else if (Game[k][i] != Game[k - 1][i]) // 1부터 그전 까지 쭉 비교 
			{
				if (Game[k][i] == 'W')
				{
					countW = 1;
					countB = 0;

					list[k][i].combo = countW;
					list[k][i].state = 'W';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
				else if (Game[k][i] == 'B')
				{
					countB = 1;
					countW = 0;

					list[k][i].combo = countB;
					list[k][i].state = 'B';
					list[k][i].Y = k;
					list[k][i].X = i;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[k][i].combo > max) max = list[k][i].combo;
		}

		for (int k = 0; k < 19; k++)
		{
			if (max != 0 && list[k][i].combo == max)
			{
				printf("%d번줄 : ", i); //%02d, i까지
				if (list[k][i].state == 'B')
				{
					printf("%c %d", list[k][i].state, list[k][i].combo);
				}

				if (list[k][i].state == 'W')
				{
					printf("%c %d", list[k][i].state, list[k][i].combo);
				}
				if (list[k][i].state != 0)
				{
					printf("\n");
				}
			}
		}

	}
	printf("=========================================\n");

}
void CheckB(char Game[][19]) // 가로 [기준][여기] 
{
	LIST list[19][19] = { 0 };

	printf("============ 2. 가로 연속 ==================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0) // 0일때 위치저장 
			{
				if (Game[i][k - 1] == 'W')
				{

					countW++;
					list[i][k - 1].combo = ++sumW;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}
				else if (Game[i][k - 1] == 'B')
				{
					countB++;
					list[i][k - 1].combo = ++sumB;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}

			}
			if (Game[i][k] == Game[i][k - 1]) // 1부터 그전 까지 쭉 비교 
			{
				if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].combo = sumW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB;
					list[i][k].combo = sumB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // 1부터 그전 까지 쭉 비교 
			{
				if (Game[i][k] == 'W')
				{
					countW = 1;
					countB = 0;

					list[i][k].combo = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB = 1;
					countW = 0;

					list[i][k].combo = countB;
					list[i][k].state = 'B';
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
			if (max != 0 && list[i][k].combo == max)
			{
				printf("%d번줄 : ", i);
				if (list[i][k].state == 'B')
				{
					printf("%c %d", list[i][k].state, list[i][k].combo);
				}

				if (list[i][k].state == 'W')
				{
					printf("%c %d", list[i][k].state, list[i][k].combo);
				}
				if (list[i][k].state != 0)
				{
					printf("\n");
				}
			}
		}

	}
	printf("=========================================\n");

}

void CheckRTLB(char Game[][19])
{
	printf("======= 대각 가로 연속 ==============\n");

	for (int i = 18, k = 0; i >= 0; i--, k++) // 18 17 16.... 1  시작점 y=0, x 18--, 확인점 +,+, 끝점 x=18, y-- => 2개씩 확인수 늘어남 
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // ++ 증가를 y로 표현하고 [0++][18-- 0++] 시작점이 --되고 확인점은 ++, 최대확인 +2씩
		{

			if (y < 19 && i + y < 19) {// 여기서 2*k 36되서 인덱스가 침범하니까 y는 증가되니까 막아야함 y가 가는 방향을 인터셑트

				if (Game[0 + y][i + y] == 'B') // y 0에서 탐색, 시작점은 18--
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

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

		if (sumB > 0 || sumW > 0)
		{
			printf("우상단 %d번째 대각선 : ", k);// k번째라는것도 잊지마 
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}

	// 0안겹치게
	for (int i = 18, k = 0; i > 0; i--, k++) // 18,0 17,0, 16,0 -> ++. 18 1 18 2 18 3 ..
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (y < 19 && i + y < 19) {

				if (Game[i + y][y + 0] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

				}
				else if (Game[i + y][y + 0] == 'W')
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

		if (sumB > 0 || sumW > 0)
		{
			printf("좌하단 %d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}
	printf("=========================================\n");

}
void CheckRBLT(char Game[][19])
{

	for (int i = 18, k = 0; i > 0; i--, k++) // 18 17 16.... 1  시작점 y=0, x 18--, 확인점 +,+, 끝점 x=18, y-- => 2개씩 확인수 늘어남 
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // ++ 증가를 y로 표현하고 [0++][18-- 0++] 시작점이 --되고 확인점은 ++, 최대확인 +2씩
		{
			if (y < 19 && k - y >= 0) {
				if (Game[k - y][0 + y] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

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

		if (sumB > 0 || sumW > 0)
		{
			printf("좌상단 %d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}


	for (int i = 18, k = 0; i >= 0; i--, k++) // 18,0 17,0, 16,0 -> ++. 18 1 18 2 18 3 ..
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) {

				if (Game[18 - y][i + y] == 'B')
				{
					countW = 0;
					countB++;
					if (countB > sumB) sumB = countB;

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

		if (sumB > 0 || sumW > 0)
		{
			printf("우하단 %d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			else if (sumB < sumW) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}

	}
	printf("=========================================\n");


}

void CheckBindex(char Game[][19])
{
	LIST list[19][19] = { 0 };

	printf("============ 4. 가로 좌표 ==================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0;
		int countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{
			if (k - 1 == 0) // 0일때 좌표 기억 -> 2개씩 비교하면 1개만 저장하고 끝에 가면 공백이 생겨서 채워야함 
			{
				if (Game[i][k - 1] == 'W')
				{

					countW++;
					list[i][k - 1].combo = ++sumW;
					list[i][k - 1].state = 'W';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}
				else if (Game[i][k - 1] == 'B')
				{
					countB++;
					list[i][k - 1].combo = ++sumB;
					list[i][k - 1].state = 'B';
					list[i][k - 1].Y = i;
					list[i][k - 1].X = k - 1;

				}

			}
			if (Game[i][k] == Game[i][k - 1]) // 1부터 그전 까지 쭉 비교 
			{
				if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].combo = sumW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB;
					list[i][k].combo = sumB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}
			else if (Game[i][k] != Game[i][k - 1]) // 1부터 그전 까지 쭉 비교 
			{ // 콤보 초기화 -> list에 공백없이 돌이 있을때만 저장해서 초기화도 이때 해야함 -> 가장 많이 실행되는구간 
				if (Game[i][k] == 'W')
				{
					countW = 1;
					countB = 0;

					list[i][k].combo = countW;
					list[i][k].state = 'W';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB = 1;
					countW = 0;

					list[i][k].combo = countB;
					list[i][k].state = 'B';
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].combo > max) max = list[i][k].combo;//list combo젤 큰거 저장 
		}

		for (int k = 0; k < 19; k++)
		{
			if (max != 0 && list[i][k].combo == max) //// 최대가 >1로 바꾸자 
			{
				printf("%d번줄 : ", i);
				if (list[i][k].state == 'B')
				{
					printf("B(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++) // 콤보 3이라할때 3, 2, 1,
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);

					}
				}
				// else 안붙는거 -> B, W순서대로 출력하고 
				if (list[i][k].state == 'W')
				{
					printf("W(Y,X) : ");
					for (int j = k + 1 - list[i][k].combo; j <= k; j++) // 콤보 3이라할때 3, 2, 1,
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);

					}// 인덱스 +1 해서 그 위치부터 콤보만큼 +1하는게 0번째 칸 지나야함 j<=k는 k일때 combo최대치라
				}
				if (list[i][k].state != 0)
				{
					printf("\n"); // 상태 0아닌 -> b,w가 잇을때 줄 내리기 
				}
			}
		}

	}
	printf("=========================================\n");

}


/*

항상 시작점 안변하는가 0 or 18 or i or k
어디로 증가하는가 y
i = 18, i++, k-- y++ y<2*k ( 0일땐x)
RTLB
[0+y][i+y]
[i+y][y+0]

RBLT
[18-y][i+y]
[k-y][y]*/






#endif
