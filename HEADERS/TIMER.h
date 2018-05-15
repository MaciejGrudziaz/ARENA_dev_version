#pragma once
#include <windows.h>
#include <vector>

//-------------------------------------------------------------------------
//----------------------------------TIMER----------------------------------
//-------------------klasa u�ywana do odmierzania czasu--------------------
//----------mo�e odmierza� czas dla wielu znacznik�w jednocze�nie----------
//-------------------------------------------------------------------------

//struktura u�ywana do inicjalizowania znacznik�w czasowych
struct TIME_STAMPS {
	std::string name;															//nazwa znacznika
	LARGE_INTEGER start, stop;													//zmienne okre�laj�ce pocz�tek i koniec odliczania czasu
	unsigned long elapsedTime;													//zmierzony czas [w mikrosekundach]
	std::vector<unsigned long> allTimeMeasurments;								//wszystkie pomiary czasowe

	//konstruktor
	TIME_STAMPS(std::string Name) {									
		name = Name; start = { 0 }; stop = { 0 }; elapsedTime = 0;				//pobiera nazw� znacznika, a dla pozosta�ych p�l struktury ustawia warto�ci domy�lneS
	}
};

class TIMER {
	TIMER();																	//zablokowany [prywatny] konstruktor domy�lny - klasa singletonowa

	static LARGE_INTEGER frequency;												//cz�stotliwo�� performance countera

	static std::vector <TIME_STAMPS> markers;									//wektor znacznik�w czasowych

public:
	static void GetFrequency();													//pobranie cz�stotliwo�ci performance countera
	static void AddTimeMarker(std::string Name);								//dodanie nowego znacznika czasowego
	static int DeleteTimeMarker(std::string Name);								//usuni�cie znacznika czasowego
	static int StartTimeMeasurment(std::string Name);							//rozpocz�cie odmierzania czasu dla znacznika o danej nazwie
	static int QuickStartTimeMeasurment(int idx = -1);							//szybkie rozpocz�cie odmierzania czasu dla znacznika o danym indeksie
	static int StopTimeMeasurment(std::string Name);							//zako�czenie odmierzania czasu dla znacznika o danej nazwie
	static int QuickStopTimeMeasurment(int idx = -1);							//szybkie zako�czenie odmierzania czasu dla znacznika o danym indeksie
	static unsigned long GetTime(std::string Name);								//pobranie zmierzonego czasu dla danego znacznika
	static std::vector<unsigned long> GetAllTimeMeasurments(std::string Name);	//pobranie wszystkich zmierzonych i zapisanych warto�ci czasu dla danego znacznika
};