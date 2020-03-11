//Основная функция. Реализует переключение пинов в портах. 
#include "include.h"

//Внешние f(x)
char READ_WRITE_INI(char INI[KolPort * 8][20], char MASKA[KolPort][9], byte MaskaHex[KolPort]);
int  PrintDisplay(char INI[KolPort * 8][20], char MASKA[KolPort][9], byte SostPort[KolPort],int sost_i[KolPort * 8]);
int  PiecewiseLinearFunction(int PortPin[2], int key);
int  IMPULS_RE(int lcnt, int key, char MASKA[KolPort][9], byte MaskaHex[KolPort]);


//Глобальные переменные
int		sost_i[KolPort * 8]  = { 0 };//Состояние пина на экране
int		PortPin[2];
int		key  = 0;//Нажатая кнопка
bool     lcnt = false; //Глобальный флаг для работы потока из main ("Входной аргумент f(IMPULS_RE)").
char	INI[KolPort * 8][20] = { " " };
char	MASKA[KolPort][9]    = { " " };
byte	SostPort[KolPort]    = { 0x00 };//состояние порта
byte    MaskaHex[KolPort];//Массив масок в hex


//using
using namespace std;
using namespace Automation::BDaq;
InstantDoCtrl * instantDoCtrl = InstantDoCtrl::Create();
//
int main(int argc, char *argv[])
{
	//Локальные переменные
	int			   i;//Счётчик
	int			   sost = 0;//Переменная для PCI
	unsigned char  bit;
	
	//
	setlocale(LC_ALL, "Rus");
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);
	
	// Подключение платы и установка портов на вывод
	ICollection<PortDirection>* portDirection = instantDoCtrl->getPortDirection();
	if (portDirection != NULL)
	{
		//Set the first two port to output 
		DioPortDir dir = Output;
		for (i = 0; i < KolPort; i++)
		{
			portDirection->getItem(i).setDirection(dir);
		}
	}
	else
	{
		printf("Плата не доступна!\n");
	}

	//Обнуление портов при включении
	//for (i = 0; i < KolPort; i++)
	//{
	//	ret = instantDoCtrl->Write(i, byte(0));
	//}
	
	//while (true)
	//{
		//Считывание состояния портов
		for (i = 0; i < KolPort; i++)
		{
			ret = instantDoCtrl->Read(i, SostPort[i]);
		}

		//
		READ_WRITE_INI(INI, MASKA, MaskaHex);
		//PrintDisplay(INI, MASKA, SostPort, sost_i);

		//Switch
		//scanf("%i", &key);
		key = atoi(argv[1]);
		bit = atoi(argv[2]);
		PiecewiseLinearFunction(PortPin, key);
		if (key >= 0)
		{
			//sost = instantDoCtrl->ReadBit(PortPin[1], PortPin[0], &bit);
			if (bit == 0)
			{
				ret = instantDoCtrl->WriteBit(PortPin[1], PortPin[0], 0);
				//ret = instantDoCtrl->WriteBit(0, 0, 1);
				sost_i[key] = 1;
			}
			else if(bit == 1)
			{
				ret = instantDoCtrl->WriteBit(PortPin[1], PortPin[0], 1);
				//ret = instantDoCtrl->WriteBit(0, 0, 0);
				sost_i[key] = 0;
			}
			system("cls");
		}
		else if (key <= -10)
		{
			lcnt = !lcnt;
			thread func_thread(IMPULS_RE,lcnt, key, MASKA, MaskaHex);//Вызов функции импульса через поток.
			func_thread.detach();// Разблокировка main при работе потока.
			//IMPULS_RE(lcnt, key, MASKA, MaskaHex);
		}
		else return -1;
	//}

	//int a;
	//a = 0;
}