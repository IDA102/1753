#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <dos.h>
#include <chrono>
#include "windows.h"
#include "BDaqCtrl.h"

//Внешние библиотеки
#include "compatibility.h"
#include "bdaqctrl.h"

//
# define KolPort 2 //Количество считываемых портов
# define deviceDescription  L"PCI-1751,BID#0"
# define k 7 //Константа для расчёта порта и пина
#define  clc 32

//
using namespace std;
using namespace Automation::BDaq;
