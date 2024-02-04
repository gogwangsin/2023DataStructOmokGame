
#if 1

typedef struct LIST {

	char state;
	int Y, X;
	int combo;

}LIST;


void MakeGame(char Game[][19]);
void PrintGame(char Game[][19]);

void menu(void);
void EveryCount(char Game[][19]);

void CheckA(char Game[][19]);
void CheckB(char Game[][19]);

void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);

void CheckBindex(char Game[][19]);


#endif

/*


/*


void menu(void)
{
	printf("=========================================\n");
	printf("0. 메뉴 선택 없이 돌 두기\n");
	printf("1. 가로 세로 검,흰 돌 개수\n");
	printf("2. 가로 세로 연속 돌 개수\n");
	printf("3. 대각선 연속 돌 출력\n");
	printf("4. 모든 가로줄 연속 돌 좌표\n");
	printf("5. 게임 종료\n");
	printf("=========================================\n");
	printf("명령어 입력 : ");
}



void EveryCount(char Game[][19])
{
	int countB = 0, countW = 0;

	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[i][k] == 'B') countB++;
			if (Game[i][k] == 'W') countW++;
		}
		printf("가로 %02d번째줄 : B %d, W : %d\n", i, countB, countW); // 줄 한번 탐색하고 나서 초기화
		countB = 0;
		countW = 0;
	}
	printf("=========================================\n");
	for (int i = 0; i < 19; i++)
	{
		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B') countB++;
			if (Game[k][i] == 'W') countW++;
		}
		printf("세로 %02d번째줄 : B %d, W : %d\n", i, countB, countW); // 세로는 i,k바꿔서
		countB = 0;
		countW = 0;
	}
	printf("=========================================\n");


}

void CheckA(char Game[][19])
{
	printf("=========================================\n");

	for (int i = 0; i < 19; i++)
	{
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int k = 0; k < 19; k++)
		{
			if (Game[k][i] == 'B')
			{
				countB++;
				countW = 0;
				if (countB > sumB) sumB = countB;
			}
			else if (Game[k][i] == 'W') // else 안하면 0,0되서 콤보가 안됨
			{
				countW++;
				countB = 0;
				if (countW > sumW) sumW = countW;
			}
			else
			{
				countW = 0, countB = 0;
			}

		}

		if (sumB > 0 || sumW > 0) // 시험때는 >1이 나을듯
		{
			printf("세로 %02d번째 최대 연속 돌 : ", i);
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB)printf("W : %d", sumW);
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
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

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
				countW = 0, countB = 0;
			}

		}

		if (sumB > 0 || sumW > 0)
		{
			printf("가로 %02d번째 최대 연속 돌 : ",i); //%02d, i까지
			if (sumB > sumW) printf("B : %d", sumB);
			if (sumW > sumB)printf("W : %d", sumW);
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
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // 여기서 2*k 36되서 인덱스가 침범하니까 y는 증가되니까 막아야함 y가 가는 방향을 인터셑트
		{
			if (y < 19 && i + y < 19) {

				if (Game[0 + y][i + y] == 'B')
				{
					countW = 0;
					countB++;
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
		if (sumB > 0 || sumW > 0)
		{
			printf("우상단 %02d번째 대각선 : ",k); // k번째라는것도 잊지마
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}
	}

	for (int i = 18, k = 0; i > 0; i--, k++) // 0안겹치게
	{
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int y = 0; y < 2 * k; y++) // 여기서 2*k 36되서 인덱스가 침범하니까 y는 증가되니까 막아야함 y가 가는 방향을 인터셑트
		{
			if (y < 19 && i + y < 19) {

				if (Game[i + y][0 + y] == 'B')
				{
					countW = 0;
					countB++;
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
		if (sumB > 0 || sumW > 0)
		{
			printf("좌하단 %02d번째 대각선 : ", k); // k번째라는것도 잊지마
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}
	}
	printf("=========================================\n");



}
void CheckRBLT(char Game[][19])
{
	printf("=========================================\n");

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumW = 0, sumB = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (k-y >= 0 &&  y < 19) {

				if (Game[k-y][y] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[k-y][y] == 'W')
				{
					countW++;
					countB = 0;
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
			printf("우하단 %02%d번째 대각선 : ", k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
		}
	}

	for (int i = 18, k = 0; i >= 0; i--, k++)
	{
		int countB = 0, countW = 0, sumW = 0, sumB = 0;

		for (int y = 0; y < 2 * k; y++)
		{
			if (18 - y >= 0 && i + y < 19) {

				if (Game[18 - y][y + i] == 'B')
				{
					countB++;
					countW = 0;
					if (countB > sumB) sumB = countB;
				}
				else if (Game[18 - y][y + i] == 'W')
				{
					countW++;
					countB = 0;
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
			printf("우하단 %02%d번째 대각선 : ",k);
			if (sumB > sumW) printf("B : %d\n", sumB);
			if (sumW > sumB) printf("W : %d\n", sumW);
			else printf("B : %d, W : %d\n", sumB, sumW);
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
		int sumB = 0, sumW = 0, countB = 0, countW = 0;

		for (int k = 1; k < 19; k++)
		{

			if (k - 1 == 0) // 0일때 좌표 기억 -> 2개씩 비교하면 1개만 저장하고 끝에 가면 공백이 생겨서 채워야함
			{
				if (Game[i][k - 1] == 'W')
				{
					countW++;
					list[i][k - 1].state = 'W';
					list[i][k - 1].combo = 1; // 콤보 1
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
				else if (Game[i][k - 1] == 'B')
				{
					countB++;
					list[i][k - 1].state = 'B';
					list[i][k - 1].combo = 1;
					list[i][k - 1].Y = i;
					list[i][k - 1].X = 0;
				}
			}

			if (Game[i][k] == Game[i][k - 1])
			{
				if (Game[i][k] == 'W')
				{
					countW++;
					sumW = countW;
					list[i][k].state = 'W';
					list[i][k].combo = sumW; // 콤보
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countB++;
					sumB = countB;
					list[i][k].state = 'B';
					list[i][k].combo = sumB;
					list[i][k].Y = i;
					list[i][k].X = k;
				}

			}
			else if (Game[i][k] != Game[i][k - 1])
			{
				if (Game[i][k] == 'W')
				{
					countW = 1; // 콤보 초기화 -> list에 공백없이 돌이 있을때만 저장해서 초기화도 이때 해야함 -> 가장 많이 실행되는구간
					countB = 0;
					list[i][k].state = 'W';
					list[i][k].combo = countW;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
				else if (Game[i][k] == 'B')
				{
					countW = 0;
					countB = 1;
					list[i][k].state = 'B';
					list[i][k].combo = countB;
					list[i][k].Y = i;
					list[i][k].X = k;
				}
			}

		}

		int max = 0;
		for (int k = 0; k < 19; k++)
		{
			if (list[i][k].combo > max) max = list[i][k].combo; //list combo젤 큰거 저장
		}

		for (int k = 0; k < 19; k++)
		{
			if (max != 0 && list[i][k].combo == max) // 최대가 >1로 바꾸자
			{
				printf("%02d번줄 : ", i);
				if (list[i][k].state == 'B')
				{
					printf("B(X,Y) : ");
					for (int j = k - list[i][k].combo + 1; j <= k; j++)
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state == 'W') // else 안붙는거 -> B, W순서대로 출력하고
				{
					printf("W(X,Y) : ");
					for (int j = k - list[i][k].combo + 1; j <= k; j++) // 인덱스 +1 해서 그 위치부터 콤보만큼 +1하는게 0번째 칸 지나야함 j<=k는 k일때 combo최대치라
					{
						printf("(%d,%d)", list[i][j].Y, list[i][j].X);
					}
				}

				if (list[i][k].state != 0) printf("\n"); // 상태 0아닌 -> b,w가 잇을때 줄 내리기
			}
		}

	}
	printf("=========================================\n");


}


*/