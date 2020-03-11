#include <iostream>
#include <stdio.h>
#include "C:\Users\Пользователь\Desktop\(Управление)_(pci_1753)_ver1.2(3_потока)\DO_StaticDO\inc\compatibility.h"
#include "C:\Users\Пользователь\Desktop\(Управление)_(pci_1753)_ver1.2(3_потока)\DO_StaticDO\inc\bdaqctrl.h"
#include <sstream>
#include <cstdlib>
#include "BDaqCtrl.h"
#include <stdio.h>
#include <dos.h>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;
/////////////////////////////////////////////////////////

#define  deviceDescription  L"PCI-1753,BID#0"
using namespace Automation::BDaq;
InstantDoCtrl * instantDoCtrl = InstantDoCtrl::Create();
char lcnt; //Глобальный флаг для работы потока из main ("Входной аргумент f(IMP)").
char lcnt1; //Глобальный флаг для работы потока из main ("Входной аргумент f(IMP1)").
char lcnt2; //Глобальный флаг для работы потока из main ("Входной аргумент f(IMP2)").
int  cnt;
bool flag;

void IMP() //Функция импульса для АМ_2.
{
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);
	while (lcnt)
	{
		if (flag == true)
			ret = instantDoCtrl->WriteBit(0, 5, 0);
		else
			ret = instantDoCtrl->WriteBit(0, 5, 1);
			//Sleep(1);//30-31/10-15/1-15;
	}
	if (lcnt != 1)
		instantDoCtrl->WriteBit(0, 5, 0);
}

void IMP1() //Функция импульса для АМ_1.
{
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);
	while (lcnt1)
	{
		if (flag == true)
		ret = instantDoCtrl->WriteBit(0, 7, 0);
		else
		ret = instantDoCtrl->WriteBit(0, 7, 1);
		//Sleep(1);//30-31/10-15/1-15;
	}
	if (lcnt1 != 1)
		instantDoCtrl->WriteBit(0, 7, 0);
}

void IMP2() //Функция импульса для ФМ.
{
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);
	while (lcnt2)
	{
		if (cnt <= 10)
		{
			cnt = cnt + 1;
			ret = instantDoCtrl->WriteBit(0, 6, 0);
			ret = instantDoCtrl->WriteBit(0, 6, 1);
			//Sleep(1);//30-31/10-15/1-15;
		}
		else
		{
			flag = !flag;
			cnt = 0;
		}
	}
	if (lcnt2 != 1)
		instantDoCtrl->WriteBit(0, 6, 0);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);

	// Read profile to configure device
	//ret = instantDoCtrl->LoadProfile(filePath);

	ICollection<PortDirection>* portDirection = instantDoCtrl->getPortDirection();
	if (portDirection != NULL)
	{
		//Set the first two port to output 
		DioPortDir dir =Output;
		portDirection->getItem(0).setDirection(dir);
		portDirection->getItem(1).setDirection(dir);
	}
	else
	{
		printf("There is no DIO port of the selected device can set direction!\n");
	}

	ret = instantDoCtrl->Write(0, byte(0));
	ret = instantDoCtrl->Write(1, byte(0));

	int8 state;
	int8 portData;
	int  a    = 0;
	int  key  = 0;
	int  sost = 0;
	int  i[14][1] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	unsigned char  bit[1];
	char           state_key [2][4]	 = { "ON", "OFF"};
	byte bufferForReading[1] = { 0 };
	while (true)
	{
		sost = instantDoCtrl->Read(0, 1, bufferForReading);

		printf("Режим импульса_1 - 10	IMP_1   - %s \n\n"			, state_key[*i[10]]);	
		printf("Режим импульса_2 - 11	IMP_2   - %s \n\n"			, state_key[*i[11]]);
		printf("Режим импульса_3 - 12	IMP_3   - %s \n\n"			, state_key[*i[12]]);

		printf("name1  - 1		name10 - %s \n"				, state_key[*i[0]]);
		printf("name2  - 2		name11 - %s \n"				, state_key[*i[1]]);
		printf("name3  - 3		name12 - %s \n"				, state_key[*i[2]]);
		printf("name4  - 4		name13 - %s \n"				, state_key[*i[3]]);
		printf("name5  - 5		name14 - %s \n"			    , state_key[*i[4]]);
		printf("name6  - 6		name15 - %s \n"				, state_key[*i[5]]);
		printf("name7  - 7		name16 - %s		Sost = %x\n", state_key[*i[6]], bufferForReading[0]);
		printf("name8  - 8		name17 - %s \n"				, state_key[*i[7]]);
		printf("name9  - 9		name18 - %s \n"				, state_key[*i[8]]);
		printf("exit   - 0			          \n");

		scanf("%i", &key);
		switch (key)
		{
		case 1:
			//----------------------1
			sost = instantDoCtrl->ReadBit(0, 0, &bit[0]);
			if (bit[0] == 0)
			{
				ret = instantDoCtrl->WriteBit(0, 0, 1);
				i[0][0] = 0;
			}
			else
			{
				ret = instantDoCtrl->WriteBit(0, 0, 0);
				i[0][0] = 1;
			}
			system("cls");
			break;
		case 2:
			//----------------------2
			sost = instantDoCtrl->ReadBit(0, 1, &bit[0]);
			if (bit[0] == 0)
			{
				ret = instantDoCtrl->WriteBit(0, 1, 1);
				i[1][0] = 0;
			}
			else
			{
				ret = instantDoCtrl->WriteBit(0, 1, 0);
				i[1][0] = 1;
			}
			system("cls");
			break;
		case 3:
			//----------------------3
			sost = instantDoCtrl->ReadBit(0, 2, &bit[0]);
			if (bit[0] == 0)
			{
				ret = instantDoCtrl->WriteBit(0, 2, 1);
				i[2][0] = 0;
			}
			else
			{
				ret = instantDoCtrl->WriteBit(0, 2, 0);
				i[2][0] = 1;
			}
			system("cls");
			break;
		case 4:
			//----------------------4
			sost = instantDoCtrl->ReadBit(0, 3, &bit[0]);
			if (bit[0] == 0)
			{
				ret = instantDoCtrl->WriteBit(0, 3, 1);
				i[3][0] = 0;
			}
			else
			{
				ret = instantDoCtrl->WriteBit(0, 3, 0);
				i[3][0] = 1;
			}
			system("cls");
			break;
		case 5:
			//----------------------5
			sost = instantDoCtrl->ReadBit(0, 4, &bit[0]);
			if (bit[0] == 0)
			{
				ret = instantDoCtrl->WriteBit(0, 4, 1);
				i[4][0] = 0;
			}
			else
			{
				ret = instantDoCtrl->WriteBit(0, 4, 0);
				i[4][0] = 1;
			}
			system("cls");
			break;
		case 6:
			//----------------------6
			if (lcnt == 0) //Проверка на режим работы импульсного режима(при включ.имп.реж. ручной режим АМ не работает!).
			{
				sost = instantDoCtrl->ReadBit(0, 5, &bit[0]);
				if (bit[0] == 0)
				{
					ret = instantDoCtrl->WriteBit(0, 5, 1);
					i[5][0] = 0;
				}
				else
				{
					ret = instantDoCtrl->WriteBit(0, 5, 0);
					i[5][0] = 1;
				}
			}
			else
			{
				system("cls");
				break;
				
			} 
			system("cls");
			break;
		case 7:
			//----------------------7
			if (lcnt1 == 0)
			{
				sost = instantDoCtrl->ReadBit(0, 6, &bit[0]);
				if (bit[0] == 0)
				{
					ret = instantDoCtrl->WriteBit(0, 6, 1);
					i[6][0] = 0;
				}
				else
				{
					ret = instantDoCtrl->WriteBit(0, 6, 0);
					i[6][0] = 1;
				}
			}
			else
			{
				system("cls");
				break;
			}
			system("cls");
			break;
		case 8:
			//----------------------8
			if (lcnt2 == 0)
			{
				sost = instantDoCtrl->ReadBit(0, 7, &bit[0]);
				if (bit[0] == 0)
				{
					ret = instantDoCtrl->WriteBit(0, 7, 1);
					i[7][0] = 0;
				}
				else
				{
					ret = instantDoCtrl->WriteBit(0, 7, 0);
					i[7][0] = 1;
				}
			}
			else
			{
				system("cls");
				break;
			}
			system("cls");
			break;
		case 9:
			//----------------------9
			sost = instantDoCtrl->ReadBit(1, 0, &bit[0]);
			if (bit[0] == 0)
			{
				ret = instantDoCtrl->WriteBit(1, 0, 1);
				i[8][0] = 0;
			}
			else
			{
				ret = instantDoCtrl->WriteBit(1, 0 , 0);
				i[8][0] = 1;
			}
			system("cls");
			break;
			
		case 10: // Вкл/Выкл имплуьсного режима.
			//----------------------10
			if (i[10][0] == 1)
			{
			i[10][0] = 0;
			thread func_thread(IMP);//Вызов функции импульса через поток.
			func_thread.detach();// Разблокировка main при работе потока.
			lcnt = 1;

			}
			else
			{
				i[10][0] = 1;
				lcnt = 0;
			}
			system("cls");
			break;

		case 11: // Вкл/Выкл имплуьсного режима.
			//----------------------10
			if (i[11][0] == 1)
			{
				i[11][0] = 0;
				thread func_thread(IMP1);//Вызов функции импульса через поток.
				func_thread.detach();// Разблокировка main при работе потока.
				lcnt1 = 1;

			}
			else
			{
				i[11][0] = 1;
				lcnt1 = 0;
			}
			system("cls");
			break;

		case 12: // Вкл/Выкл имплуьсного режима.
			//----------------------10
			if (i[12][0] == 1)
			{
				i[12][0] = 0;
				thread func_thread(IMP2);//Вызов функции импульса через поток.
				func_thread.detach();// Разблокировка main при работе потока.
				lcnt2 = 1;

			}
			else
			{
				i[12][0] = 1;
				lcnt2 = 0;
			}
			system("cls");
			break;

		case 0:
			//----------------------0
			return -1;
		}
	}
}
//ret = instantDoCtrl->Read(portNum, &portData);
