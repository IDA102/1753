//Функция вывода на экран информации о пинах и портах
#include "include.h"
int  PrintDisplay(char INI[KolPort * 8][20], char MASKA[KolPort][9], byte SostPort[KolPort], int sost_i[KolPort * 8])

{
	//
	int i,j;
	char state_key[2][4] = { "OFF", "ON" };

	//
	for (j = 0; j < KolPort; j++)
	{
		printf("%35s%i\n","Port = ",j);
		printf("%35s%x\n", "SostPort = ",SostPort[j]);
		printf("%35s%s\n", "MASCA = ", MASKA[j]);
		for (i = 0 + j * 8; i < 8 + j * 8; i++)
		{
			printf("%20s -%2i %20s-%s \n", INI[i], i, INI[i], state_key[sost_i[i]]);
		}
	}
	printf("%37s\n", "exit - -1 ");
	return 0;
}
