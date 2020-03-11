//Функция чтения файла конфигурации
#include "include.h"

char READ_WRITE_INI(char INI[KolPort * 8][20], char MASKA[KolPort][9], byte MaskaHex[KolPort])
{
	int i,j;
	int ii;
	int ij;
	char str[20] = { 0 };
	char iii[9][2] = { "0", "1", "2", "3", "4", "5", "6", "7" };
	char iiii[3][2] = { "0", "1" };
	//Порты
	for (i = 0; i < KolPort; i++)
	{
		for (ii = 0; ii < 8; ii++)
		{
			GetPrivateProfileStringA((LPCSTR)&iiii[i][0], (LPCSTR)&iii[ii][0], (LPCSTR) "ERROR", (LPSTR)str, (DWORD) sizeof(str), (LPCSTR)"C:\\DATA.ini");
			for (ij = 0; ij < 20; ij++)
			{
				INI[ii + 8 * i][ij] = str[ij];
			}
		}
	}
	//Маска
	for (i = 0; i < KolPort; i++)
	{
		GetPrivateProfileStringA((LPCSTR)"MASKA", (LPCSTR)&iii[i][0], (LPCSTR) "ERROR", (LPSTR)str, (DWORD) sizeof(str), (LPCSTR)"C:\\DATA.ini");
		for (ij = 0; ij < 8; ij++)
		{
			MASKA[i][ij] = str[ij];
		}
	}

	//Перевод маски в byte
	for (j = 0; j < KolPort; j++)
	{
		for (i = 0; i < 8; i++)
		{
			if (MASKA[j][i] == '0')
				MaskaHex[j] = (MaskaHex[j] << 1);
			else
			{
				MaskaHex[j] = (MaskaHex[j] << 1);
				MaskaHex[j] = MaskaHex[j] | 0x01;
			}
		}
	}

	return INI[KolPort * 8][20], MASKA[KolPort][9], MaskaHex[KolPort];
}