

#if 1

#include<iostream>
#include "Judgment.h"

#include "Omok_2020182003.h"
#include "Omok_2018180042.h"

using namespace std;

int main(void)
{
	Judgment judgment;

	judgment.SetYourFunc( 
#if 1
		// Èæµ¹ »ó´ëÆÀ, ¹éµ¹ ³»ÆÀ 
		BlackAttack_2018180042,/*¼±°ø*/
		BlackDefence_2018180042,

		WhiteAttack_2020182003,
		WhiteDefence_2020182003
#endif
// ======================================
#if 0
		// Èæµ¹ ³»ÆÀ, ¹éµ¹ »ó´ëÆÀ 
		BlackAttack_2020182003,/*¼±°ø*/
		BlackDefence_2020182003,

		WhiteAttack_2018180042,
		WhiteDefence_2018180042
#endif
	);
	judgment.GamePlay();

}

#endif


#if 0
srand((unsigned)time(NULL));

int white_x = rand() % 18;
int white_y = rand() % 18;

while (1)
{
	if (board_2020182003[white_y][white_x] == BLACK || board_2020182003[white_y][white_x] == WHITE)
	{
		white_x = rand() % 18;
		white_y = rand() % 18;
	}
	else break;
}



#endif