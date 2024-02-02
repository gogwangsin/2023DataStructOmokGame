

#if 1
typedef struct LIST {

	char state;
	int Y, X;
	int combo;

}LIST;



void menu(void);
void MakeGame(char Game[][19]);
void PrintGame(char Game[][19]);
void EveryCOUNT(char Game[][19]);

void CheckA(char Game[][19]);
void CheckB(char Game[][19]);
void CheckRTLB(char Game[][19]);
void CheckRBLT(char Game[][19]);

void CheckBindex(char Game[][19]);
#endif