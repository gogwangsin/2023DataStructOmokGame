#if 1

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include "AI2sup.h"
char Game[19][19];

int main(void)
{

	MakeGame(Game);

	printf("\nó�� ������ ���� �� �Դϴ�.\n");

	for (int i = 1; i <= 361; i++)
	{
		menu();
		int choice;
		if (scanf("%d", &choice) != 1)
		{
			printf("�Է� ����\n");
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
		}


		int Y, X;
		printf("\n( Y , X )�� 0���� �۰ų� 18���� ũ�ٸ� ������ �����մϴ�.\n");

		if (i % 2 == 1)
		{
			printf("\n�˵� ��ǥ�� �Է��Ͽ� �ֽʽÿ� ( Y, X ) : ");
		}
		else if (i % 2 == 0)
		{
			printf("\n�� ��ǥ�� �Է��Ͽ� �ֽʽÿ� ( Y, X ) : ");
		}


		if (scanf("%d %d", &Y, &X) != 2) {
			printf("�Է� ���� �ǹٸ��� �ʽ��ϴ�. ���α׷��� �����մϴ�.\n");
			return 0;
		} fgetc(stdin);




		if (X < 0 || Y < 0 || X > 18 || Y > 18) {
			printf("\n������ ������ϴ�. �ٽ� �Է��� �ּ���.\n");
			i--;
			continue;
		}

		if (Game[Y][X] == 'B' || Game[Y][X] == 'W') {
			printf("\n��ǥ�� �̹� ���� ���� �ֽ��ϴ�.\n");
			i--;
			continue;
		}


		if (i % 2 == 1) {
			Game[Y][X] = 'B';
			PrintGame(Game);
		}
		else if (i % 2 == 0) {
			Game[Y][X] = 'W';
			PrintGame(Game);

		}

	}



	return 0;
}




#endif