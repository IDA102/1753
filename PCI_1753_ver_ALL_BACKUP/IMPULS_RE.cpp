// Функция импульсного режима в отдельном потоке
#include "include.h"

int IMPULS_RE(int lcnt, int key, char MASKA[KolPort][9], byte MaskaHex[KolPort]) //Функция импульса.
{
	//
	ErrorCode ret = Success;
	InstantDoCtrl * instantDoCtrl = AdxInstantDoCtrlCreate();
	DeviceInformation devInfo(deviceDescription);
	ret = instantDoCtrl->setSelectedDevice(devInfo);
	int  i;
	int  w = 0;//Порт после смещения
	int  cnt  = 0;
	byte bits = 0x00;
	w = abs(key) - 10;//Смещение порта
	while (lcnt)
	{
		ret = instantDoCtrl->Read(w, bits);
		//bits ^= (1 << 6);
		//if ((cnt == 0) | (cnt == 32)) 		bits ^= (1 << 5) | (1 << 7);
		if ((cnt == 0) | (cnt == clc)) 		bits ^= MaskaHex[w];
		ret = instantDoCtrl->Write(w, bits);
		cnt++;
	}
	ret = instantDoCtrl->Write(w, byte(0));//Обнудение порта при выключении режима
	return - 1;
}
