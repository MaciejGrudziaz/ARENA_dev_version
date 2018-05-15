#pragma once
#include <algorithm>
#include "Character.h"

//-------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------MAPA-----------------------------------------------------------
//---------------------------------------------klasa opisuj�ca map� rozgrywki----------------------------------------------
//----------[przechowuje obiekty znajduj�ce si� na mapie, macierz punkt�w pomagaj�c� wyznaczy� warto�ci Y postaci----------
//-------------------------------oraz macierz sektor�w w celu szybszego sprawdzania kolizji]-------------------------------
//-------------------------------------------------------------------------------------------------------------------------

namespace MAP {
	const unsigned int stdSectorDiv = 20;														//standardowa liczba dzielnik�w dla sektor�w wzd�u� ka�dej kraw�dzi
	const unsigned int stdMapDiv = 200;															//standardowa liczba dzielnik�w dla macierzy punkt�w wzd�u� ka�dej kraw�dzi

	typedef std::pair<unsigned int, unsigned int> IdxPair;										//struktura opisuj�ca par� indeks�w (X,Z)
	typedef bool(*edgeCheckFun)(IdxPair idx, unsigned sectorDiv);								//wska�nik na funkcj� pomocnicz� dla funkcji 'GetSectorsCharacters_GetIdx' i 'GetSectorsObjects_GetIdx'

	enum sectorNeigbours { LEFT, RIGHT, TOP, BOTTOM, TOP_RIGHT, TOP_LEFT, BOTTOM_RIGHT, BOTTOM_LEFT };
}
//struktura opisuj�ca pojedynczy sektor mapy
struct SECTOR {
	Vector vertices[4];																		//wierzcho�ki pojedynczego sektora [CCW]					  1  _______________  0
	Vector midPt;																			//punkt �rodkowy												|				|
	double radius;																			//promie� sektora												|				|
	std::vector <unsigned int> charactersIdx;												//indeksy obiekt�w postaci w sektorze [Character]				|				|
	std::vector<unsigned int> objectsIdx;													//indeksy obiekt�w z modelu Mapy w sektorze [Objects]		  2 |_______________| 3	

	SECTOR();																				//konstruktor domy�lny

	const Vector& operator[](unsigned int i) const{													//przeci��enie operatora [] - odnoszenie si� do kolejnych wierzcho�k�w sekotra
		if (i < 4)
			return vertices[i];
		else throw std::exception();
	}
};

//klasa opisuj�ca macierz punkt�w
class SECTOR_MATRIX {
	unsigned int dimension;																	//wymiar macierzy
	SECTOR** matrix;																		//tablica przechowuj�ca wszystkie sektory macierzy
	Vector minPoint, maxPoint;																//punkt o najmniejszych i najwiekszych wsp�rz�dnych
	double xShift, zShift;																	//pojedyncze przesuni�cie wzd�u� osi X i Z - d�ugo�ci bok�w sektora

public:
	SECTOR_MATRIX();																		//konstruktor domy�lny
	void Initialize(unsigned int dimension, Vector _minPt, Vector _maxPt);					//inicjalizacja macierzy
	//funkcje zwracaj�ce kolejne warto�ci sk�adowych macierzy
	unsigned int GetDimension() const { return dimension; }
	IdxPair GetSector(double x, double z) const;
	double GetXshift() const { return xShift; }
	double GetZshift() const { return zShift; }
	Vector GetMinPoint() const { return minPoint; }
	Vector GetMaxPoint() const { return maxPoint; }

	SECTOR* operator[](unsigned int a) const;														//przeci��enie operatora [][] - odnoszenie si� do kolejnych element�w macierzy
};
//	(minX,maxZ)	 _______________________  (maxX,maxZ)
//				|						|
//				|						|
//				|						|
//				|						|
//				|_______________________|
//	(minX,minZ)							  (maxX,minZ)

//klasa Mapy
class Map:public Character {
	enum ContainerType {CharCont, ObjCont};

	unsigned sectorDiv;
	unsigned mapDiv;
	unsigned int groundIdx;																	//indeks obiektu reprezentuj�cego pod�o�e
	Vector minPt;																			//punkt o najmniejszych warto�ciach wsp�rz�dnych
	Vector maxPt;																			//punkt o najwi�kszych warto�ciach wsp�rz�dnych
	std::vector <Character> characters;														//obiekty statyczne [Character] wchodz�ce w sk�ad mapy

	//----------------------------------------------------------------------------SEKTORY MAPY-----------------------------------------------------------------------------
	//---------------'sectors' - macierz sektor�w przechowuj�ca indeksy postaci 'Character' oraz obiekt�w mapy 'objects' znajduj�cych si� w strefie sektora----------------
	//----------'y_valMap' - macierz sektor�w przechowuj�ca wart. wsp. Y dla pod�o�a mapy 'GROUND' dla danych punkt�w (X,Z) b�d�cymi wierzch. oraz p. �r. sektora----------
	//-------------------------------------------------------------------Spos�b opisu macierzy sektor�w:-------------------------------------------------------------------
	//----------------------------------------------------------------SECTOR_MATRIX[0][0] = [minPt.x, maxPt.z]-------------------------------------------------------------
	//---------------------------------------------------------SECTOR_MATRIX[maxVal][maxVal] = [maxPt.x, minPt.z]----------------------------------------------------------
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	SECTOR_MATRIX sectors;																	//sektory mapy u�ywane do detekcji kolizji obiekt�w znajduj�cych wewn�trz nich													
	SECTOR_MATRIX y_valMap;																	//macierz wsp�rz�nych okreslaj�ca warto�ci wsp. Y dla p�aszczyzny (X,Z)

	void LoadSectorsData();																	//za�adowanie danych do macierzy sektor�w [sectors]
	void LoadSectorsData_LoadCharactersAndObjects(unsigned rowIdx,unsigned columnIdx);		//przypisanie obiekt�w Character i obeikt�w mapy do danego sektora

	void Load_Y_valMapSectorsData();														//podzielenie macierzy wsp�rz�dnych na sektory

	void Load_Y_valMapData();																//za�adowanie danych dotycz�cych wsp. Y dla wczesniej stworzonych sekotr�w macierzy

	//funkcje pomocnicze dla 'Load_Y_valMapData()'
	std::pair<Vector,Vector> Load_Y_valMapData_GetMinMaxPt(unsigned int faceIdx);			//pobranie wsp. punktu o najwi�kszych i najmniejszych warto�ciach dla aktualnie rozwa�anej powierzchni
	IdxPair Load_Y_valMapData_GetMaxIdx(Vector minPt, Vector maxPt);						//pobranie indeks�w sektora macierzy dla punku o najwi�kszych wart. wsp.
	IdxPair Load_Y_valMapData_GetMinIdx(Vector minPt, Vector maxPt);						//pobranie indeks�w sekotra macierzy dla punktu o najmniejszych wart. wsp.
	void Load_Y_valMapData_LoadData(IdxPair minIdx, IdxPair maxIdx,							
		double Surface[], Vector triangle[], Vector normal);								//za�adowanie wart. wsp. Y dla danych sektor�w

	//funkcje pomocnicze dla 'Get_Y_Pos(..)'
	void Get_Y_Pos_LoadDistVertTab(std::pair<double, unsigned int> distTab[],				//obliczenie wart. dla tablicy dystans�w [odl. badanego punktu do ka�dego wierzcho�ka sektora]	
		Vector sectPt[], const Vector mainPt, IdxPair idx) const;									//oraz wczytanie wart. wsp. wierzcho�k�w dla sektora
	void Get_Y_Pos_SortDistTab(std::pair<double, unsigned int> distTab[]) const;					//posortowanie tablicy dystans�w
	double Get_Y_Pos_Count_Y_val(Vector sectPt[], Vector midPt, Vector mainPt,				
		std::pair<double, unsigned int> distTab[]) const;											//obliczenie wart. wsp. Y dla badanego punktu w p��szczy�nie (X,Z)

	std::vector<unsigned> GetSectorsCharacters_GetIdx(IdxPair mainIdx, unsigned vertexIdx) const;	//pobranie indeks�w postaci 'Character' znajduj�cych si� w danym sektorze
	std::vector<unsigned> GetSectorsObjects_GetIdx(IdxPair mainIdx, unsigned vertexIdx) const;	//pobranie indeks�w obiekt� 'objects' znajduj�cych si� w danym sektorze
	void GetSectorsCharacters_Objects_LoadNeighboursIdx(IdxPair neighbours[],	
		IdxPair mainIdx, unsigned vertexIdx) const;												//za�adowanie wart. indeks�w s�siad�w sektora ['neighbours'] w zalezno�ci od wybranego wierzcho�ka
	void GetSectorsCharacters_Objects_LoadEdgeCheckFun(MAP::edgeCheckFun fun[], 
		IdxPair mainIdx, unsigned vertexIdx) const;												//za�adowanie funkcji pomocniczych  ['fun'] w zale�no�ci od wybranego wierzcho�ka

	static bool CheckPointInTriangle(Vector point, Vector triangle[], Vector normal);		//funkcja sprawdzaj�ca czy dany punkt znajduje si� wewn�trz tr�jk�ta (w rzucie X,Z)

public:
	//konstruktory
	Map(const std::string& filename,unsigned _sectorDiv=MAP::stdSectorDiv,unsigned _mapDiv=MAP::stdMapDiv);
	Map(const std::string& filename, char* mapName, unsigned _sectorDiv = MAP::stdSectorDiv,
		unsigned _mapDiv = MAP::stdMapDiv);

	void LoadCharacter(const Character& character);											//za�adowanie obiektu Character do mapy
	void Initialize();																		//inicjalizacha mapy

	double Get_Y_Pos(Vector position) const;														//pobranie pozycji Y dla danego punktu ['position']  w p�aszczyxnie (X,Z)

	std::vector<unsigned> GetSectorCharactersIdx(Vector position, double R = 0.0)const;		//pobrnaie wektora indeks�w postaci [Character] dla danego sektora ['sectors']
	std::vector<unsigned> GetSectorCharactersIdx(IdxPair sectorIdx)const;
	std::vector<unsigned> GetSectorObjectsIdx(Vector position,double R=0.0)const;			//pobranie wektora indeks�w obiekt�w dla danego sektora ['sectors']
	std::vector<unsigned> GetSectorObjectsIdx(IdxPair sectorIdx)const;

	const Character& GetCharacter(unsigned int idx) const { return characters[idx]; }					//pobranie postaci o danym indeksie

	Vector GetMaxPoint() const { return maxPt; }
	Vector GetMinPoint() const { return minPt; }

	IdxPair GetSectorIdx(const Vector& position) const;											//pobranie indeks�w sektora dla danej pozycji
	IdxPair GetSectorNeighbourIdx(IdxPair sectorIdx, MAP::sectorNeigbours neighbour) const;
	std::pair<double, double> GetSectorShift() const {
		return std::pair<double, double>(sectors.GetXshift(), sectors.GetZshift());
	}

	void Draw();																			//funkcja rysuj�ca map�
	void DrawCollisionBox();																//funkcja rysuj�ca bry�y kolizji
};