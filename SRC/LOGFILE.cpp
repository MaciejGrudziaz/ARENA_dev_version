#include "LOGFILE.h"

std::vector<FileHeader> LOGFILE::logs;														//inicjalizacja wektora przechowuj�cego nag��wki log�w

//stworzenie nowego pliku log�w
void LOGFILE::CreateLogFile(std::string Name, std::string FileName) {
	FileHeader newHeader(Name, FileName);													//stworzenie nowego nag��wka [jest jednoznaczne z otworzeniem pliku]
	logs.push_back(newHeader);																//dodanie nowego nag��wka do wektora
}

//zapis wiadomo�ci do danego pliku log�w
int LOGFILE::WriteToLogFile(std::string Name, std::string message) {
	for (FileHeader& header : logs) {
		if (header.name == Name) {															//sprawd� czy nazwa jest zgodna z nazw� danego logu
			header.fileHandler << message << "\n";											//wpisanie nowej wiadomo�ci do logu
			return 0;																		//operacja powiod�a si�
		}
	}

	return 1;																				//operacja nie powiod�a si�										
}

//wyczyszczenie pliku log�w
int LOGFILE::ClearLogFile(std::string Name) {
	for (FileHeader& header : logs) {
		if (header.name == Name) {															//sprawd� czy nazwa jest zgodna z nazw� danego logu
			if (header.fileHandler.is_open()) header.fileHandler.close();					//je�li dany plik jest otwarty, zamknij go najpierw
			header.fileHandler.open(header.filename, std::ios::out | std::ios::trunc);		//otw�rz dany plik czyszcz�c jego zawarto��
			return 0;																		//operacja powiod�a si�
		}
	}

	return 1;																				//operacja nie powiod�a si�
}

void LOGFILE::OpenAllFiles() {
	for (FileHeader& header : logs)
		header.fileHandler.open(header.filename,std::ios::in | std::ios::app);
}

//zamkni�cie wszystkich plik�w log�w przed zako�czeniem pracy programu
void LOGFILE::CloseAllFiles() {
	for (FileHeader& header : logs) {
		header.fileHandler.close();															//zamkni�cie danego logu
	}
}