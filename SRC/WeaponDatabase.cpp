#include "WeaponDatabase.h"

std::vector<WeaponDatabaseRecord> WeaponDatabase::database;

//inicjalizacja bazy danych
void WeaponDatabase::Initialize() {
	std::fstream file("RESOURCES/WeaponDatabase.txt", std::ios::in);													//otworzenie pliku opisuj�cego baz� danych broni

	WeaponDatabaseRecord newRecord;																			//nowy rekord do bazy
	char tmp='\0';
	int eof = 0;
	while (tmp != '\n')																						//pomini�cie pierwszej linii pliku
		file.read(&tmp, 1);
	while (eof!=EOF) {																						//dop�ki nie odczytano znaku ko�ca pliku
		std::string filename;
		file >> newRecord.name;																				//wczytanie nazwy broni					

		file >> filename;																					//wczytanie nazwy pliku opisuj�cego model broni
		for (unsigned i = 0; i < filename.size(); i++)
			newRecord.filename[i] = filename[i];															//przypisanie go do nazwy pliku w strukturze rekordu
		newRecord.filename[filename.size()] = NULL;
		//wczytanie statystyk broni
		file >> newRecord.ROF;
		file >> newRecord.damage;
		file >> newRecord.bulletSpeed;
		file >> newRecord.magazineCapacity;
		file >> newRecord.reloadTime;
		database.push_back(newRecord);																		//dodanie nowego rekordu do bazy danych
		eof=file.peek();																					//sprawdzenie czy nast�pnym znakiem nie jest znak ko�ca pliku
	}
}

//pobranie rekordu z bazy danych [indeksuj�c nazw� broni]
WeaponDatabaseRecord WeaponDatabase::GetWeaponStats(const std::string& weaponName) {
	for (WeaponDatabaseRecord record : database) {
		if (record.name == weaponName)																		//je�li nazwa broni rekordu zgadza si� z szukan� nazw�
			return record;																					//zwr�� dany rekord
	}
	return WeaponDatabaseRecord();																			//je�li nie znaleziono poszukiwanego rekordu zwr�� pusty rekord
}