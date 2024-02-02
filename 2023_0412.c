#if 1

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include "AIsup.h"


char Game[19][19];

int main(void)
{

	MakeGame(Game);

	printf("\n처음 순서는 검은 돌 입니다.\n");

	for (int i = 1; i <= 361; i++)
	{
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
			PrintGame(Game);
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
			case 1: EveryCOUNT(Game); break;
			case 2: CheckB(Game); CheckA(Game); break;
			case 3: CheckRTLB(Game); CheckRBLT(Game); break;
			case 4: CheckBindex(Game); break;
			case 5: exit(1); break;

			}



		}
		else if (i % 2 == 0) {
			Game[Y][X] = 'W';

			PrintGame(Game);
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
			case 1: EveryCOUNT(Game); break;
			case 2: CheckB(Game); CheckA(Game); break;
			case 3: CheckRTLB(Game); CheckRBLT(Game); break;
			case 4: CheckBindex(Game); break;
			case 5: exit(1); break;

			}



		}

	}



	return 0;
}





#endif