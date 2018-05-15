#include "TIMER.h"

LARGE_INTEGER TIMER::frequency = { 0 };									//inicjalizacja cz�stotliwo�ci performance countera

std::vector <TIME_STAMPS> TIMER::markers;								//inicjalizacja wektora zancznik�w czasowych

//pobranie cz�stotlwio�ci perfomrance countera
void TIMER::GetFrequency() {
	QueryPerformanceFrequency(&frequency);
}

//dodanie nowego znacznika czasowego
void TIMER::AddTimeMarker(std::string Name) {
	TIME_STAMPS newMarker(Name);
	markers.push_back(newMarker);
}

//usuni�cie zancznika czasowego
int TIMER::DeleteTimeMarker(std::string Name) {
	//bool search = true;
	unsigned int i = 0;

	while (i<markers.size()) {											//dop�ki nie przekoroczono zakresu wektora znacznik�w											
		if (markers[i].name == Name) {									//sprawd� zgodno�� nazwy z nazw� kolejnego znacznika
			markers.erase(markers.begin() + i);							//je�li s� zgodne - usu� znacznik
			return 1;													//pomy�lne uko�czenie usuwania
		}
		i++;															//inkrementacja indeksu wetora znacznik�w
	}

	return 0;															//usuni�cie nie powiod�o sie
}

//rozpocz�cie odmierzania czasu dla danego znacznika
int TIMER::StartTimeMeasurment(std::string Name) {
	unsigned int i = 0;

	while (i<markers.size()) {											//dop�ki nie przekroczono zakresu wektora znacznik�w
		if (markers[i].name == Name) {									//sprawd� zgodno�� nazwy z nazw� aktualnego znacznika
			QueryPerformanceCounter(&(markers[i].start));				//je�li s� zgodne - przeka� odpowiedni� warto�� do zmiennej mierz�cej pocz�tek odliczania
			return 1;													//pomy�lne uko�czenie operacji
		}
		i++;															//inkrementacja indeksu wektora znacznik�w
	}

	return 0;															//operacja nie powiod�a si�
}

//szybkie rozpocz�cie odmierzania czasu dla o danym indeksie w wekotrze znacznik�w
int TIMER::QuickStartTimeMeasurment(int idx) {
	if (idx >= 0 && idx < (int)markers.size()) {								//sprawdzenie poprawno�ci podanego indeksu [wart. domy�lna = -1]
		QueryPerformanceCounter(&(markers[idx].start));					//przekazanie odpowiedniej warto�ci do zmiennej mierz�cej pocz�tek odliczania
		return 1;														//operacja powiod�a si�
	}
	else return 0;														//operacja nie powiod�a si�
}

//zako�czenie odmierzania czasu dla danego znacznika
int TIMER::StopTimeMeasurment(std::string Name) {
	unsigned int i = 0;

	while (i<markers.size()) {											//dop�ki nie przekroczono zakresu wektora znacznik�w
		if (markers[i].name == Name) {									//sprawd� zgodno�� nazwy z nazw� aktualnego znacznika
			QueryPerformanceCounter(&(markers[i].stop));				//je�li s� zgodne - przeka� odpowiednia warto�� do zmiennej mierz�cej koniec odliczania
			//zmierz up�yw czasu przy pomocy zmiennych 'start' i 'stop'
			//r�nica mi�dzy zmiennymi 'stop' i 'start' dla danego znacznika czasowego okre�la ilo�� cykl�w performance countera
			//r�nica ta podzielona przez cz�stotliwo�� performance countera pozwala uzyska� czas w sek.
			//pomno�enie wyniku przez 1,000,000 pozwala uzyska� wynik w mikrosekundach, co przenosi si� na wi�ksz� dok�adno�� w pomiarze
			markers[i].elapsedTime = (unsigned long) ( (markers[i].stop.QuadPart - markers[i].start.QuadPart) * 1000000.0 / frequency.QuadPart );
			markers[i].allTimeMeasurments.push_back(markers[i].elapsedTime);
			return 1;													//operacja powiod�a si�
		}
		i++;															//inkrementacja indeksu wektora znacnzik�w
	}

	return 0;															//operacja nie powiod�a si�
}

//szybkie zako�czenie pomiaru czasu dla znacznika o danym indeksie w wektorze znacznik�w
int TIMER::QuickStopTimeMeasurment(int idx) {
	if (idx >= 0 && idx < (int)markers.size()) {								//sprawdzenie poprawno�ci podanego indeksu [wart. domy�lna = -1]
		QueryPerformanceCounter(&(markers[idx].stop));					//przekazanie odpoweidniej warto�ci do zmiennej mierz�cej koniec odliczania
		//zmierz up�yw czasu przy pomocy zmiennych 'start' i 'stop'
		//r�nica mi�dzy zmiennymi 'stop' i 'start' dla danego znacznika czasowego okre�la ilo�� cykl�w performance countera
		//r�nica ta podzielona przez cz�stotliwo�� performance countera pozwala uzyska� czas w sek.
		//pomno�enie wyniku przez 1,000,000 pozwala uzyska� wynik w mikrosekundach, co przenosi si� na wi�ksz� dok�adno�� w pomiarze
		markers[idx].elapsedTime = (unsigned long) ( (markers[idx].stop.QuadPart - markers[idx].start.QuadPart) * 1000000.0 / frequency.QuadPart );
		return 1;														//operacja powiod�a si�
	}
	else return 0;														//operacja nie powiod�a si�
}

//pobranie odmierzonego czasu dla danego znacznika
unsigned long TIMER::GetTime(std::string Name) {
	unsigned int i = 0;
	unsigned int retTime=0;												//warto�� zwracana odmierzonego czasu

	while (i < markers.size()) {										//dop�ki nie przekroczono zakresu wektora znacznik�w
			if (markers[i].name == Name) {								//sprawd� zgodno�� nazwy z nazw� aktualnego znacznika
				retTime = markers[i].elapsedTime;						//je�li s� zgodne - przeka� zmierzon� warto�� czasu do zwr�cenia
				break;													//zako�cz wykonywanie p�tli
			}
			i++;														//inkrementacja indeksu wektora znacznik�w
	}

	return retTime;														
}

//pobranie ca�ego wekotra pomiar�w czasu dla danego znacznika
std::vector<unsigned long> TIMER::GetAllTimeMeasurments(std::string Name) {
	unsigned int i = 0;
	std::vector<unsigned long> retTimes;								//warto�� zwracana odmierzonego czasu

	while (i < markers.size()) {										//dop�ki nie przekroczono zakresu wektora znacznik�w
		if (markers[i].name == Name) {									//sprawd� zgodno�� nazwy z nazw� aktualnego znacznika
			retTimes = markers[i].allTimeMeasurments;					//je�li s� zgodne - przeka� zmierzon� warto�� czasu do zwr�cenia
			break;														//zako�cz wykonywanie p�tli
		}
		i++;															//inkrementacja indeksu wektora znacznik�w
	}

	return retTimes;
}