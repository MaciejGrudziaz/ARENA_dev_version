#pragma once
#include <windows.h>
#include <vector>

//-------------------------------------------------------------------------
//----------------------------------TIMER----------------------------------
//-------------------klasa używana do odmierzania czasu--------------------
//----------może odmierzać czas dla wielu znaczników jednocześnie----------
//-------------------------------------------------------------------------

//struktura używana do inicjalizowania znaczników czasowych
struct TIME_STAMPS {
	std::string name;															//nazwa znacznika
	LARGE_INTEGER start, stop;													//zmienne określające początek i koniec odliczania czasu
	unsigned long elapsedTime;													//zmierzony czas [w mikrosekundach]
	std::vector<unsigned long> allTimeMeasurments;								//wszystkie pomiary czasowe

	//konstruktor
	TIME_STAMPS(std::string Name) {									
		name = Name; start = { 0 }; stop = { 0 }; elapsedTime = 0;				//pobiera nazwę znacznika, a dla pozostałych pól struktury ustawia wartości domyślneS
	}
};

class TIMER {
	TIMER();																	//zablokowany [prywatny] konstruktor domyślny - klasa singletonowa

	static LARGE_INTEGER frequency;												//częstotliwość performance countera

	static std::vector <TIME_STAMPS> markers;									//wektor znaczników czasowych

public:
	static void GetFrequency();													//pobranie częstotliwości performance countera
	static void AddTimeMarker(std::string Name);								//dodanie nowego znacznika czasowego
	static int DeleteTimeMarker(std::string Name);								//usunięcie znacznika czasowego
	static int StartTimeMeasurment(std::string Name);							//rozpoczęcie odmierzania czasu dla znacznika o danej nazwie
	static int QuickStartTimeMeasurment(int idx = -1);							//szybkie rozpoczęcie odmierzania czasu dla znacznika o danym indeksie
	static int StopTimeMeasurment(std::string Name);							//zakończenie odmierzania czasu dla znacznika o danej nazwie
	static int QuickStopTimeMeasurment(int idx = -1);							//szybkie zakończenie odmierzania czasu dla znacznika o danym indeksie
	static unsigned long GetTime(std::string Name);								//pobranie zmierzonego czasu dla danego znacznika
	static std::vector<unsigned long> GetAllTimeMeasurments(std::string Name);	//pobranie wszystkich zmierzonych i zapisanych wartości czasu dla danego znacznika
};