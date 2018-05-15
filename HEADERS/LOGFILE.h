#pragma once
#include <vector>
#include <string>
#include <fstream>

//------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------LOGFILES-----------------------------------------------------
//--------------------klasa u�ywana do tworzenia plik�w komunikat�w [log�w] wysy�anych przez gr�--------------------
//-----------------------------------mo�e tworzy� i pisa� do wielu plik�w na raz------------------------------------
//------------------------------------------------------------------------------------------------------------------

//struktura u�ywana do przechowywania nazwy logu [nazwa poprzez kt� u�ytkownik odnosi si� do konkrentego pliku]
//oraz nazwy pliku przechowuj�cego dane komuniaktu
struct FileHeader {
	std::string name;																//nazwa logu
	std::string filename;															//nazwa pliku
	std::fstream fileHandler;

	//konstruktor wczytuj�cy nazw� logu i nazw� pliku
	FileHeader(std::string Name, std::string FileName) { 
		name = Name; filename = "LOGS/"+FileName;
		fileHandler.open(filename);
		if (!fileHandler.is_open())														//sprawdzenie czy  plik o danej nazwie ju� istnieje
			fileHandler.open(filename, std::ios::out);
	}

	FileHeader(const FileHeader& header) {
		name = header.name;
		filename = header.filename;
		fileHandler.open(filename);
		if (!fileHandler.is_open())														//sprawdzenie czy  plik o danej nazwie ju� istnieje
			fileHandler.open(filename, std::ios::out);
	}
};

class LOGFILE {
	LOGFILE();																		

	static std::vector<FileHeader> logs;											//wektor przechowuj�cy adresy nag��wki log�w [nazwy log�w oraz zwi�zane z nimi nazwy plik�w]

public:
	static void CreateLogFile(std::string Name, std::string FileName);				//stworzenie pliku log�w
	static int ClearLogFile(std::string Name);										//wyczyszczenie istniej�cego pliku log�w
	static int WriteToLogFile(std::string Name, std::string message);				//zapis wiadomo�ci do pliku
	static void OpenAllFiles();
	static void CloseAllFiles();													//zamkni�cie wszystkich plik�w log�w przed zako�czeniem pracy programu
};