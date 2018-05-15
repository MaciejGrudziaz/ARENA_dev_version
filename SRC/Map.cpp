#include "Map.h"

//kontruktor - za��dowanie mapy z pliku
Map::Map(const std::string& filename, unsigned _sectorDiv, unsigned _mapDiv):Character(filename) {
	std::string name;
	name = "BASIC_MAP";
	setName(name);

	mapDiv = _mapDiv;																		//przypisaniew arto�ci dla dzielnika macierzy wsp�rz�dnych mapy
	sectorDiv = _sectorDiv;																	//przypisanie warto�ci dla dzielnika sektor�w mapy
}

//konstruktor - za�adowanie mapy z pliku i nadanie jej nazy
Map::Map(const std::string& filename, char* mapName, unsigned _sectorDiv, unsigned _mapDiv):Character(filename) {
	setName(mapName);

	mapDiv = _mapDiv;																		//przypisaniew arto�ci dla dzielnika macierzy wsp�rz�dnych mapy
	sectorDiv = _sectorDiv;																	//przypisanie warto�ci dla dzielnika sektor�w mapy
}

//dodanie postaci do wektora postaci [Character] przechowywanego w obiekcie mapy
void Map::LoadCharacter(const Character& character) {
	characters.push_back(character);
}

//inicjalizacja mapy
void Map::Initialize() {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i].name == "GROUND") {													//znalezienie indeksu obiektu tworz�cego pod�o�e mapy [p�aszczyzna (X,Z)]				
			groundIdx = i;
			break;
		}
	}
	//wyznaczenie punktu max i min dla ca�ej mapy na podstawie obiektu pod�o�a ["GROUND"]
	unsigned int n = objects[groundIdx].verticesIdx.size();
	maxPt = minPt = vertices[objects[groundIdx].verticesIdx[0]];
	for (unsigned int i = 1; i < n; i++) {
		unsigned int idx = objects[groundIdx].verticesIdx[i];
		for (unsigned int j = 0; j < 3; j++) {
			if (vertices[idx][j] < minPt[j])
				minPt[j] = vertices[idx][j];
			else if (vertices[idx][j] > maxPt[j])
				maxPt[j] = vertices[idx][j];
		}
	}
	
	sectors.Initialize(sectorDiv,minPt,maxPt);												//inicjalizacja macierzy sektor�w
	y_valMap.Initialize(mapDiv, minPt, maxPt);												//inicjalizacja macierzy wsp�rz�dnych

	LoadSectorsData();																		//za�adowanie danych do sektor�w
		
	Load_Y_valMapSectorsData();																//podzia� macierzy wsp�rz�nych na sektory i za�adwoanie podstawowych danych
	Load_Y_valMapData();																	//za��dwoanie wart. wsp. Y do macierzy wp�rz�dnych
}

//pobranie wart. wsp. Y dla danego punktu ['position'] w p�aszczy�nie (X,Z)
double Map::Get_Y_Pos(Vector position) const {
	std::pair<int, int> idx = y_valMap.GetSector(position.x, position.z);					//pobranie indeks�w sektora macierzy wsp. dla danego punktu ['position'] w p�aszczy�nie (X,Z)
	std::pair<double, unsigned int> d[4];													//tablica odleg�o�ci badanego punktu do ka�dego wierzcho�ka danego sektora
	Vector sectPt[4];																		//tablica przechowuj�ca wierzcho�ki danego sektora
	Vector midPt = y_valMap[idx.first][idx.second].midPt;									//punkt �rodkowy danego sektora	

	Get_Y_Pos_LoadDistVertTab(d, sectPt, position, idx);									//za�adowanie wart. tablicy odleg�o�ci ['d'] oraz tablicy wierzcho�k�w ['sectPt']
	
	Get_Y_Pos_SortDistTab(d);																//posortowanie tablicy odleg�o�ci ['d']

	return  Get_Y_Pos_Count_Y_val(sectPt, midPt, position, d);								//obliczenie i zwr�cenie wart. wsp. Y dla badanej pozycji na podstawie tablicy odleg�o�ci ['d']
}

//pobrnaie wektora indeks�w postaci [Character] dla danego sektora ['sectors']
std::vector<unsigned int> Map::GetSectorCharactersIdx(Vector position, double R) const{
	IdxPair idx;																			//indeksy sektora wewn�trz kt�ego znajduje sie punkt 'position'
	//obliczenie wart. indeksu w zale�no�ci od pozycji w p�aszczy�nie (X,Z)
	idx.first = static_cast<unsigned>((position.x - sectors.GetMinPoint().x) / sectors.GetXshift());				
	idx.second = static_cast<unsigned>((sectors.GetMaxPoint().z - position.z) / sectors.GetZshift());

	//je�li podano warto�� dla promienia
	if (R>0) {
		Vector shift;
		//znajd� najmniejsz� odleg�o�� punktu 'position' do wierzcho�ka oraz pobierz indeks tego wierzcho�ka
		shift = position - sectors[idx.first][idx.second][0];								
		unsigned int minIdx = 0;
		double dist = shift.MOD();
		for (unsigned i = 1; i < 4; i++) {
			shift = position - sectors[idx.first][idx.second][i];
			if (shift.MOD() < dist) {
				minIdx = i;
				dist = shift.MOD();
			}
		}
		if (dist < R * 1.41)																//je�li obliczona odleg�o�� jest mniejsza od przek�tnej kwadratu kt�ego boki okre�lone sa przez promie� 'R'
			return GetSectorsCharacters_GetIdx(idx, minIdx);								//zwr�� indeksy postaci aktualnego sektora oraz s�siednich sektor�w [w zalezno�ci od wybranego wierz.]
		else return sectors[idx.first][idx.second].charactersIdx;							//w przeciwnym wypadku zwr�c tylko indeksy postaci aktualnego sektora
	}
	else return sectors[idx.first][idx.second].charactersIdx;								//je�li nie podano wart. 'R' zwr�� tylko idneksy postaci aktualnego sektora
}

//pobranie wektora indeks�w postaci ['Character'] dla danego sektora okre�lonego indeksem 'sectorIdx'
std::vector<unsigned> Map::GetSectorCharactersIdx(IdxPair sectorIdx) const {
	return sectors[sectorIdx.first][sectorIdx.second].charactersIdx;
}

//pobranie wektora indeks�w obiekt�w dla danego sektora ['sectors']
std::vector<unsigned int> Map::GetSectorObjectsIdx(Vector position, double R) const {
	IdxPair idx;																			//indeksy sektora wewn�trz kt�ego znajduje sie punkt 'position'
	//obliczenie wart. indeksu w zale�no�ci od pozycji w p�aszczy�nie (X,Z)
	idx.first = static_cast<unsigned>((position.x - sectors.GetMinPoint().x) / sectors.GetXshift());				
	idx.second = static_cast<unsigned>((sectors.GetMaxPoint().z - position.z) / sectors.GetZshift());

	//je�li podano warto�� dla promienia
	if (R>0) {
		Vector shift;
		//znajd� najmniejsz� odleg�o�� punktu 'position' do wierzcho�ka oraz pobierz indeks tego wierzcho�ka
		shift = position - sectors[idx.first][idx.second][0];
		unsigned int minIdx = 0;
		double dist = shift.MOD();
		for (unsigned i = 1; i < 4; i++) {
			shift = position - sectors[idx.first][idx.second][i];
			if (shift.MOD() < dist) {
				minIdx = i;
				dist = shift.MOD();
			}
		}
		if (dist < R * 1.41)																//je�li obliczona odleg�o�� jest mniejsza od przek�tnej kwadratu kt�ego boki okre�lone sa przez promie� 'R'
			return GetSectorsObjects_GetIdx(idx, minIdx);									//zwr�� indeksy obiekt�w aktualnego sektora oraz s�siednich sektor�w [w zalezno�ci od wybranego wierz.]
		else return sectors[idx.first][idx.second].objectsIdx;								//w przeciwnym wypadku zwr�c tylko indeksy obiekt�w aktualnego sektora
	}
	else return sectors[idx.first][idx.second].objectsIdx;									//je�li nie podano wart. 'R' zwr�� tylko idneksy obiekt�w aktualnego sektora
}

//pobranie wektora obiekt�w ['objects'] dla danego sektora okre�lonego indeksem 'sectorIdx'
std::vector<unsigned> Map::GetSectorObjectsIdx(IdxPair sectorIdx) const {
	return sectors[sectorIdx.first][sectorIdx.second].objectsIdx;
}

//pobranie indeks�w sektora dla danej pozycji
IdxPair Map::GetSectorIdx(const Vector& position) const {
	return sectors.GetSector(position.x, position.z);
}

//pobranie indeks�w s�siaduj�cego sektora
IdxPair Map::GetSectorNeighbourIdx(IdxPair sectorIdx, MAP::sectorNeigbours neighbour) const {
	switch (neighbour) {
		case MAP::TOP: {
			if (sectorIdx.second > 0) return IdxPair(sectorIdx.first, sectorIdx.second - 1);
			else return sectorIdx;
			break;
		}
		case MAP::BOTTOM: {
			if (sectorIdx.second < sectorDiv-1) return IdxPair(sectorIdx.first, sectorIdx.second + 1);
			else return sectorIdx;
			break;
		}
		case MAP::LEFT: {
			if (sectorIdx.first > 0) return IdxPair(sectorIdx.first - 1, sectorIdx.second);
			else return sectorIdx;
			break;
		}
		case MAP::RIGHT: {
			if (sectorIdx.first < sectorDiv-1) return IdxPair(sectorIdx.first + 1, sectorIdx.second);
			else return sectorIdx;
			break;
		}
		case MAP::TOP_RIGHT: {
			if (sectorIdx.first < sectorDiv-1 && sectorIdx.second>0) return IdxPair(sectorIdx.first + 1, sectorIdx.second - 1);
			else return sectorIdx;
			break;
		}
		case MAP::TOP_LEFT: {
			if (sectorIdx.first > 0 && sectorIdx.second > 0) return IdxPair(sectorIdx.first - 1, sectorIdx.second - 1);
			else return sectorIdx;
			break;
		}
		case MAP::BOTTOM_RIGHT: {
			if (sectorIdx.first < sectorDiv-1 && sectorIdx.second < sectorDiv-1) return IdxPair(sectorIdx.first + 1, sectorIdx.second + 1);
			else return sectorIdx;
			break;
		}
		case MAP::BOTTOM_LEFT: {
			if (sectorIdx.first > 0 && sectorIdx.second < sectorDiv-1) return IdxPair(sectorIdx.first - 1, sectorIdx.second + 1);
			else return sectorIdx;
			break;
		}
		default:
			return IdxPair(0, 0);
			break;
	}
}

//funkcja rysuj�ca map�
void Map::Draw() {
	DrawModel();																			//wywo�anie funkcji rysuj�cej dla modelu mapy

	for (unsigned int i = 0; i < characters.size(); i++) {
		if(characters[i].IsEnabled())
			characters[i].DrawModel();															//wywo�anie funkcji rysuj�cych dla ka�dego obiektu wchodz�cego w sk�ad mapy ['Character']
	}
}

//funkcja rysuj�ca bry�y kolizji
void Map::DrawCollisionBox() {
	OBJmodel::DrawCollisionBox();															//wywo�anie funkcji rysuj�cej bry�y kolizji dla modelu mapy

	for (Character i : characters)															//wywo�anie funkcji rysuj�cej bry�y kolizji dla ka�dego obiektu 'Character' wchodz�cego w sk�ad mapy
		if(i.IsEnabled())
			i.DrawCollisionBox();
}

//za�adwoanie danych do sektor�w
void Map::LoadSectorsData() {
	double xShift = sectors.GetXshift(), zShift = sectors.GetZshift();						//pobranie wart. wsp. przesuni�cia dla osi X i Z
	for (unsigned int i = 0; i < sectors.GetDimension(); i++)
		for (unsigned int j = 0; j < sectors.GetDimension(); j++) {
			SECTOR newSec; Vector midPt; Vector shift;										
			//obliczenie wart. wsp. dla pierwszego wierzcho�ka ['0']
			newSec.vertices[0].x= minPt.x + (i + 1)*xShift; newSec.vertices[0].y = 0.0; newSec.vertices[0].z = maxPt.z - j*zShift;
			midPt += newSec[0];
			//obliczenie wart. wsp. dla drugiego wierzcho�ka [1']
			newSec.vertices[1].x = minPt.x + i*xShift; newSec.vertices[1].y = 0.0; newSec.vertices[1].z = maxPt.z - j*zShift;
			midPt += newSec[1];
			//obliczenie wart. wsp. dla trzeciego wierzcho�ka ['2']
			newSec.vertices[2].x = minPt.x + i*xShift; newSec.vertices[2].y = 0.0; newSec.vertices[2].z = maxPt.z - (j + 1)*zShift;
			midPt += newSec[2];
			//obliczenie wart. wsp. dla czwartego wierzcho�ka ['3']
			newSec.vertices[3].x = minPt.x + (i + 1)*xShift; newSec.vertices[3].y = 0.0; newSec.vertices[3].z = maxPt.z - (j + 1)*zShift;
			midPt += newSec[3];
			midPt /= 4.0;																	//obliczenie wart. wsp. dla punktu �rodkowego sektora

			shift = newSec[0] - midPt;														//obliczenie przesuni�cia mi�dzy pierwszym wierzcho�kiem sektora, a jego �rodkiem
			newSec.midPt = midPt;															//wczytanie puntku �rodkowego do nowego sektora
			newSec.radius = shift.MOD();													//wczytanie warto�ci promienia okr�gu opisanego na sektorze
			sectors[i][j] = newSec;															//dodanie nowego sektora do macierzy

			LoadSectorsData_LoadCharactersAndObjects(i, j);									//za�adowanie indeks�w postaci ['Character'] dla danego sektora
		}
}

//za�adowanie indeks�w postaci ['Character'] oraz obiekt�w mapy do danego sektora
void Map::LoadSectorsData_LoadCharactersAndObjects(unsigned rowIdx, unsigned columnIdx) {
	Vector shift, charMidPt, sectorMidPt=sectors[rowIdx][columnIdx].midPt;					//wczytanie wart. wsp. punktu �rodkowego dla badanego sektora
	double charR, sectorR=sectors[rowIdx][columnIdx].radius;								//wczytanie wart. promienia dla badanego sektora
	//wczytanie indeks�w obiekt�w postaci ['Character']
	for (unsigned int i = 0; i < characters.size(); i++) {
		charMidPt = characters[i].getCollisionBox().midPoint+characters[i].getPosition();	//wczytanie wart. wsp. punktu �rodkowego dla danego obeiktu postaci
		charR = characters[i].getCollisionBox().radius;										//wczytanie wart. promienia dla danego obiektu postaci

		shift = charMidPt - sectorMidPt;													//obliczenie przesuni�cia pomi�dzy punktami �rodkowymi sektora oraz danego obektu postaci
		if (shift.MOD() <= charR + sectorR)													//je�li warto�� ta jest mniejsza/r�wna ni� suma promieni
			sectors[rowIdx][columnIdx].charactersIdx.push_back(i);							//dodaj indeks postaci do wektora dla badanego sektora
	}
	//wczytanie indeks�w obiekt� mapy
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i].name != "GROUND") {													//je�li obiektem nie jest obiekt pod�o�a
			charMidPt = objects[i].mainColBox.midPoint;										//za�adowanie wart. wsp. punktu �rodkowego dla danego obiektu
			charR = objects[i].mainColBox.radius;											//za�adowanie wart. promienia dla danego obiektu

			shift = charMidPt - sectorMidPt;												//obliczenie przesuniecia pomi�dzy �rodkiem danego obeiktu, a sektora
			if (shift.MOD() <= charR + sectorR)												//je�li wart. jest ta mniejsza/r�wna ni� suma promieni
				sectors[rowIdx][columnIdx].objectsIdx.push_back(i);							//dodaj indeks obiektu mapy do wekotra badanego sektora
		}
	}
}

//podzielenie macierzy wsp�rz�dnych na sektory
void Map::Load_Y_valMapSectorsData() {
	double xShift = y_valMap.GetXshift(), zShift = y_valMap.GetZshift();
	for (unsigned int i = 0; i < y_valMap.GetDimension(); i++)
		for (unsigned int j = 0; j < y_valMap.GetDimension(); j++) {
			SECTOR newSec; Vector midPt; Vector shift;
			//obliczenie wart. wsp. dla pierwszego wierzcho�ka ['0']
			newSec.vertices[0].x = minPt.x + (i + 1)*xShift; newSec.vertices[0].y = 0.0; newSec.vertices[0].z = maxPt.z - j*zShift;
			midPt += newSec[0];
			//obliczenie wart. wsp. dla drugiego wierzcho�ka ['1']
			newSec.vertices[1].x = minPt.x + i*xShift; newSec.vertices[1].y = 0.0; newSec.vertices[1].z = maxPt.z - j*zShift;
			midPt += newSec[1];
			//obliczenie wart. wsp. dla trzeciego wierzcho�ka ['2']
			newSec.vertices[2].x = minPt.x + i*xShift; newSec.vertices[2].y = 0.0; newSec.vertices[2].z = maxPt.z - (j + 1)*zShift;
			midPt += newSec[2];
			//obliczenie wart. wsp. dla czwartego wierzcho�ka ['3']
			newSec.vertices[3].x = minPt.x + (i + 1)*xShift; newSec.vertices[3].y = 0.0; newSec.vertices[3].z = maxPt.z - (j + 1)*zShift;
			midPt += newSec[3];
			midPt /= 4.0;																	//obliczenie wart. wsp. punktu �rodkowego sektora

			shift = newSec[0] - midPt;														//obliczenie wektora przesuni�cia od punktu �rodkowego do pierwszego wierzcho�ka ['0']
			newSec.midPt = midPt;															
			newSec.radius = shift.MOD();													//obliczenie wart. promienia okr�gu opisanego na sektorze
			y_valMap[i][j] = newSec;														//dodanie nowego sektora do amcierzy wsp�rz�dnych
		}
}

//za�adowanie danych dotycz�cych wsp. Y dla wczesniej stworzonych sekotr�w macierzy
void Map::Load_Y_valMapData() {
	for (unsigned int i = 0; i < objects[groundIdx].facesIdx.size(); ++i) {					//dla danej powierzchni obiektu pod�o�a ['GROUND']
		Vector minPt, maxPt;
		std::pair<Vector, Vector> minMaxPair;
		IdxPair minIdx, maxIdx;
		Vector triangle[3];
		Vector normal;
		double Surface[4];
		unsigned int fIdx = objects[groundIdx].facesIdx[i];									//pobranie indeksu dla powierzchni wchodz�cej w sk�ad obiektu pod�o�a

		for(unsigned int j=0;j<3;j++)
			triangle[j]= vertices[faces[fIdx].PointsIdx[j]];								//przypisanie wart. wsp. wierzcho�ka danej powierzchni do tablicy wierzcho�k�w
		normal = normals[faces[fIdx].NormalIdx];											//pobranie normalnej do danej powierzchni

		//obliczenie prametr�w r�wnania p�aszczyzny dla danej poweirzchni [A,B,C,D]
		for (unsigned int j = 0; j < 3; j++)
			Surface[j] = normal[j];												
		Surface[3] = -Surface[0] * triangle[0].x - Surface[1] * triangle[0].y - Surface[2] * triangle[0].z;

		minMaxPair = Load_Y_valMapData_GetMinMaxPt(fIdx);									//obliczenie najmniejszych i najwi�kszych wart. wsp. punkt�w dla powierzchni
		minPt = minMaxPair.first; maxPt = minMaxPair.second;								

		maxIdx=Load_Y_valMapData_GetMaxIdx(minPt, maxPt);									//pobranie wart. indeksu sektora najbardziej oddalonego od pocz�tku macierzy [0.0]
		minIdx = Load_Y_valMapData_GetMinIdx(minPt, maxPt);									//pobranie wart. indeksu sekotra najbli�ej pocz�tku macierzy [0,0]

		Load_Y_valMapData_LoadData(minIdx, maxIdx, Surface, triangle, normal);				//za�adowanie wart. wsp. Y do macierzy wsp�rz�dnych
	}
}

//pobranie wsp. punktu o najwi�kszych i najmniejszych warto�ciach dla aktualnie rozwa�anej powierzchni	
std::pair<Vector, Vector> Map::Load_Y_valMapData_GetMinMaxPt(unsigned int faceIdx) {		
	Vector minPt, maxPt;																	//wsp. punkt�w min i max
	minPt = maxPt = vertices[faces[faceIdx].PointsIdx[0]];									
	for (unsigned int j = 1; j < 3; j++) {													//wyszukanie najmniejszych i najwi�kszych wart. wsp�r��dnych dla punkt�w danej powierzchni
		for (unsigned int k = 0; k < 3; k++) {
			if (vertices[faces[faceIdx].PointsIdx[j]][k] < minPt[k])
				minPt[k] = vertices[faces[faceIdx].PointsIdx[j]][k];
			else if (vertices[faces[faceIdx].PointsIdx[j]][k] > maxPt[k])
				maxPt[k] = vertices[faces[faceIdx].PointsIdx[j]][k];
		}
	}

	std::pair<Vector, Vector> retVal;														//utworzenie pary zwrotnej punkt�w min i max
	retVal.first = minPt;
	retVal.second = maxPt;

	return retVal;
}

//pobranie indeks�w sektora macierzy dla punku o najwi�kszych wart. wsp.
IdxPair Map::Load_Y_valMapData_GetMaxIdx(Vector minPt, Vector maxPt) {
	IdxPair maxIdx;																			//maks. wart. indeks�w dla macierzy wsp�rz�dnych dla danych punkt�w 'minPt' i 'maxPt' 
	maxIdx = y_valMap.GetSector(maxPt.x, minPt.z);											//pobranie indeks�w sektora dla danego punktu
	if (maxIdx.first < y_valMap.GetDimension() - 2) maxIdx.first += 2;						//je�li to mo�liwe pobierz indeks sektor�w o 2 wi�kszych [zwi�ksza obszar przeszukwianych sektor�w]
	else if (maxIdx.first < y_valMap.GetDimension() - 1) maxIdx.first++;					//je�li nie, to zwi�ksz o 2
	if (maxIdx.second < y_valMap.GetDimension() - 2) maxIdx.second += 2;
	else if (maxIdx.second < y_valMap.GetDimension() - 1) maxIdx.second++;

	return maxIdx;
}

//pobranie indeks�w sekotra macierzy dla punktu o najmniejszych wart. wsp.
IdxPair Map::Load_Y_valMapData_GetMinIdx(Vector minPt,Vector maxPt) {
	IdxPair minIdx;																			//min. wart. indeks�w macierzy wsp�rz�dnych dla danych punkt�w 'minPt' i 'maxPt'
	minIdx = y_valMap.GetSector(minPt.x, maxPt.z);											//pobranie indeks�w sektora dla danego punktu
	if (minIdx.first > 1) minIdx.first -= 2;												//je�li to mo�liwe pobierz indeks sektor�w o 2 mniejszych [zwi�ksza obszar przesukwianych sektor�w]
	else if (minIdx.first > 0) minIdx.first--;												//je�li nie to zmniejsz o 1
	if (minIdx.second > 1) minIdx.second -= 2;
	else if (minIdx.second > 0) minIdx.second--;

	return minIdx;
}

//za�adowanie wart. wsp. Y dla danych sektor�w
//'minIdx', 'maxIdx' - min. i maks. badanych indeksy sektor�w
//'Surface' - wsp. r�wnania dla badanej powierzchni [A,B,C,D], 'traingle' - wierzcho�ki powierzchni, 'normal' - normalna do powierzchni 
void Map::Load_Y_valMapData_LoadData(IdxPair minIdx, IdxPair maxIdx,double Surface[],Vector triangle[],Vector normal) {
	Vector y_norm(0, 1, 0);																	//wektor normalny skierowany wzd�u� osi Y
	for (unsigned int j = minIdx.first; j < maxIdx.first; j++)								
		for (unsigned int k = minIdx.second; k < maxIdx.second; k++) {						//dla wszystkich sektor�w ograniczonych przez indeksy 'minIdx' i 'maxIdx'
			double t;																		//parametr 't' dla parametrycznego r�wnania prostej
			Vector mid = y_valMap[j][k].midPt;												//punkt �rodkowy danego sektora
			//obliczenie licznika i mianownika dla parametru 't' [rzutowanie punktu 'mid' wzd�u� wektora 'y_norm' na badan� powierzchni�]
			double licz = -Surface[3] - Surface[0] * mid.x - Surface[1] * mid.y - Surface[2] * mid.z;														
			double mian = Surface[0] * y_norm.x + Surface[1] * y_norm.y + Surface[2] * y_norm.z;
			if (mian == 0.0) t = 0.0;														//je�li mianownik nie jest r�wny 0 - oblicz wart. 't'
			else t = licz / mian;

			mid = y_norm*t + mid;															//oblicz wart. punktu mid po zrzutowaniu na powierzchni�

			if (CheckPointInTriangle(mid, triangle, normal))								//je�li punkt ten znajduje si� wewn�trz badanej powierzchni
				y_valMap[j][k].midPt = mid;													//przypisz go do sektora

			for (unsigned int l = 0; l < 4; l++) {											//dla ka�dego wierzcho�ka sektora
				Vector point = y_valMap[j][k][l];											//pobierz wart. wsp. wierzcho�ka 
				//obliczenie licznika dla parametru 't' [rzutowanie wierzcho�ka wzd�u� wektora 'y_norm' na badan� powierzchni�], mianownik niezale�ny od badanego punktu
				licz = -Surface[3] - Surface[0] * point.x - Surface[1] * point.y -
					Surface[2] * point.z;
				if (mian == 0.0) t = 0.0;													//je�li mianownik nie jest r�wny 0 - oblicz wart. 't'
				else t = licz / mian;

				point = y_norm*t + point;													//oblicz wart. wierzcho�ka po zrzutowaniu na poweirzchni�

				if (CheckPointInTriangle(point, triangle, normal))							//je�li punkt ten znajduje si� wewn�trz badanej powierzchni
					y_valMap[j][k].vertices[l] = point;
			}
		}
}

//obliczenie wart. dla tablicy dystans�w [odl. badanego punktu do ka�dego wierzcho�ka sektora]
//'distTab' - �adowana tablica dystans�w, 'sectPt' - �adowana tablica wierzcho�k�w sektora, 'mainPt' - badany punkt, 'idx' - indeksy sektora 
void Map::Get_Y_Pos_LoadDistVertTab(std::pair<double,unsigned int> distTab[],Vector sectPt[],Vector mainPt,IdxPair idx) const {
	Vector tmp1;
	for (unsigned int i = 0; i < 4; i++) {													//dla ka�dego wierzcho�ka sektora
		sectPt[i] = y_valMap[idx.first][idx.second][i];										//wczytaj wart. wierzcho�k�w sektora		
		tmp1 = Vector(mainPt - sectPt[i]);													//pomocniczy wektor przesuni�cia pomi�dzy danym wierzcho�kiem, a badanym punktem
		distTab[i].first = tmp1.MOD();														//obliczenie dystansu pomi�dzy danym wierzcho�kiem, a badanym punktem
		distTab[i].second = i;																//przypisanie indeksu wierzcho�ka do danego dystansu
	}
}

//posortowanie tablicy dystans�w
void Map::Get_Y_Pos_SortDistTab(std::pair<double,unsigned int> distTab[]) const {
	for (unsigned int i = 0; i<3; ++i)
		for (unsigned int j = i + 1; j < 4; ++j)											//posortowanie tablicy dystans�w [od najmniejszego dystansu do najwi�kszego]
		{
			if (distTab[i] > distTab[j]) {
				std::pair<double, unsigned int> tmpD = distTab[i];
				distTab[i] = distTab[j];
				distTab[j] = tmpD;
			}
		}
	//usuni�cie artefakt�w z posortowanej tablicy dystans�w
	switch (distTab[0].second) {															
	case 0:																					//je�li pierwszym indeksem jest 0 - to drugim indeksem powinien by� albo 1 albo 3
		if (distTab[1].second != 1 && distTab[1].second != 3)
			if (distTab[2].second == 1) distTab[1].second = 1;								//je�li wierzcho�ek '1' znajduje si� bli�ej to drugim indeksem jest 1
			else distTab[1].second = 3;														//w przeciwnym wypadku 3
			break;
	case 1:																					//je�li pierwszym indeksem jest 1 - to drugim indeksem powinien by� albo 0 albo 2
		if (distTab[1].second != 0 && distTab[1].second != 2)
			if (distTab[2].second == 0) distTab[1].second = 0;								//je�li wierzcho�ek '0' znajduje si� bli�ej to drugim indeksem jest 0	
			else distTab[1].second = 2;														//w przeciwnym wypadku 2
			break;
	case 2:																					//je�li pierwszym indeksem jest 2 - to drugim indeksem powinien by� albo 1 albo 3
		if (distTab[1].second != 1 && distTab[1].second != 3)								
			if (distTab[2].second == 1) distTab[1].second = 1;								//je�li wierzcho�ek '1' znajduje si� bli�ej to drugim indeksem jest 1
			else distTab[1].second = 3;														//w przeciwnym wypadku 3
			break;
	case 3:																					//je�li pierwszym indeksem jest 3 - to drugim indeksem powinien by� albo 2 albo 0
		if (distTab[1].second != 2 && distTab[1].second != 0)
			if (distTab[2].second == 2) distTab[1].second = 2;								//je�li wierzcho�ek '2' znajduje si� bli�ej to drugim indeksem jest 2
			else distTab[1].second = 0;														//w preciwnym wypadku 0
			break;
	}
}

//obliczenie wart. wsp. Y dla badanego punktu w p��szczy�nie (X,Z)
//'sectPt' - wierzcho�ki sektor�w, 'mainPt' - badany punkt, 'distTab' - tablica dystans�w
double Map::Get_Y_Pos_Count_Y_val(Vector sectPt[],Vector midPt,Vector mainPt,std::pair<double,unsigned int> distTab[]) const {
	Vector normal,tmp1,tmp2;																//normal - normalna tr�jk�ta wyznaczonego przez punkt �rodkowy sektora oraz dwa jego wierzcho�ki
	Vector yNorm(0, 1, 0);																	//wektor jednostkowy wzd�u� osi Y
	double Surface[4];																		//parametry r�wnania powierzchni 
	double t, t_licz, t_mian;																//parametr 't' parametrycznego r�wnania prostej

	tmp1 = Vector(sectPt[distTab[0].second] - midPt);										//wektor przesuni�cia pomi�dzy pierwszym wierz. z tablicy dyst. a punktem �r. sektora
	tmp2 = Vector(sectPt[distTab[1].second] - midPt);										//wektor przesuni�cia pomi�dzy drugim wierz. z tablicy dyst. a punktem �r. sektora
	normal = tmp1.CrossProduct(tmp2);														//obliczenie normalnej
	//za�adowanie wart. param. r�wnania powierzchni
	for (unsigned int i = 0; i < 3; i++)
		Surface[i] = normal[i];
	Surface[3] = -Surface[0] * sectPt[1].x - Surface[1] * sectPt[1].y - Surface[2] * sectPt[1].z;
	//obliczenie licznika i minaownika param. 't' [rzut punktu 'mainPt' na poweirzchni� okreslon� przez wktor 'normal']
	t_licz = -Surface[3] - Surface[0] * mainPt.x - Surface[1] * mainPt.y - Surface[2] * mainPt.z;
	t_mian = Surface[0] * yNorm.x + Surface[1] * yNorm.y + Surface[2] * yNorm.z;

	if (t_mian != 0.0) t = t_licz / t_mian;													//je�li mianownik nie jest r�wny 0 - oblicz wart. param. 't'
	else return mainPt.y;

	tmp1 = (yNorm*t) + mainPt;																//obliczenie wart. wsp. rzutowanego punktu 'mainPt' na badan� powierzchni� 

	return tmp1.y;																			//zwr�cenie wsp. Y rzutowanego punktu
}

//pobranie indeks�w postaci 'Character' znajduj�cych si� w danym sektorze
//'mainIdx' - indeksy podstawowego sektora, 'vertexIdx' - indeks wybranego wierzcho�ka sektora [przy jego pomocy ustalani s� s�siedzi sektora]
std::vector<unsigned> Map::GetSectorsCharacters_GetIdx(IdxPair mainIdx, unsigned vertexIdx) const {
	std::vector<unsigned> retVec;															//zwracany wektor indeks�w
	IdxPair neighbours[3];																	//indeksy sektor�w s�siad�w sektora podstawowego
	MAP::edgeCheckFun edgeVal[2];

	GetSectorsCharacters_Objects_LoadNeighboursIdx(neighbours, mainIdx, vertexIdx);			//pobranie indeks�w dla s�siad�w aktualnego sektora

	GetSectorsCharacters_Objects_LoadEdgeCheckFun(edgeVal, mainIdx, vertexIdx);				//pobranie funkcji testuj�cych czy aktualny sektor znajduje si� na granicy macierzy

	retVec.insert(retVec.end(), sectors[mainIdx.first][mainIdx.second].charactersIdx.begin(),
		sectors[mainIdx.first][mainIdx.second].charactersIdx.end());						//dodanie indeks�w z podstawowego sektora

	if (edgeVal[0](mainIdx, sectorDiv)) {													//je�li aktualny sektor nie jest na granicy macierzy w osi X
		retVec.insert(retVec.end(), sectors[neighbours[0].first][neighbours[0].second].charactersIdx.begin(),
			sectors[neighbours[0].first][neighbours[0].second].charactersIdx.end());		//dodaj indeksy z s�siedniego sektora

		if (edgeVal[1](mainIdx, sectorDiv))													//je�li aktualny sektor nie jest na granicy macierzy w osi Z
			retVec.insert(retVec.end(), sectors[neighbours[1].first][neighbours[1].second].charactersIdx.begin(),
				sectors[neighbours[1].first][neighbours[1].second].charactersIdx.end());	//dodaj indeksy z s�siedniego sektora
	}
	if (edgeVal[1](mainIdx, sectorDiv))														//je�li aktualny sektor nie jest na granicy macierzy w osi Z
		retVec.insert(retVec.end(), sectors[neighbours[2].first][neighbours[2].second].charactersIdx.begin(),
			sectors[neighbours[2].first][neighbours[2].second].charactersIdx.end());		//dodaj indeksy z s�siedniego sektora

	std::sort(retVec.begin(), retVec.end());												//posortowanie pobranych indeks�w [dla funkcji 'erase']
	retVec.erase(std::unique(retVec.begin(), retVec.end()), retVec.end());					//usuni�cie powt�rze� indeks�w

	return retVec;
}

//pobranie indeks�w obiekt� 'objects' zmajduj�cych si� w danym sektorze
//'mainIdx' - indeksy podstawowego sektora, 'vertexIdx' - indeks wybranego wierzcho�ka sektora [przy jego pomocy ustalani s� s�siedzi sektora]
std::vector<unsigned> Map::GetSectorsObjects_GetIdx(IdxPair mainIdx, unsigned vertexIdx) const {
	std::vector<unsigned> retVec;															//zwracany wektor indeks�w
	IdxPair neighbours[3];																	//indeksy sektor�w s�siad� sektora podstawowego
	MAP::edgeCheckFun edgeVal[2];

	GetSectorsCharacters_Objects_LoadNeighboursIdx(neighbours, mainIdx, vertexIdx);			//pobranie indeks�w dla s�siad�w aktualnego sektora

	GetSectorsCharacters_Objects_LoadEdgeCheckFun(edgeVal,mainIdx, vertexIdx);				//pobranie funkcji testuj�cych czy aktualny sektor znajduje si� na granicy macierzy

	retVec.insert(retVec.end(), sectors[mainIdx.first][mainIdx.second].objectsIdx.begin(),
		sectors[mainIdx.first][mainIdx.second].objectsIdx.end());							//dodanie indeks�w z podstawowego sektora

	if (edgeVal[0](mainIdx,sectorDiv)) {													//je�li aktualny sektor nie jest na granicy macierzy w osi X
		retVec.insert(retVec.end(), sectors[neighbours[0].first][neighbours[0].second].objectsIdx.begin(),
			sectors[neighbours[0].first][neighbours[0].second].objectsIdx.end());			//dodaj indeksy z s�siedniego sektora

		if (edgeVal[1](mainIdx,sectorDiv))													//je�li aktualny sektor nie jest na granicy macierzy w osi Z
			retVec.insert(retVec.end(), sectors[neighbours[1].first][neighbours[1].second].objectsIdx.begin(),
				sectors[neighbours[1].first][neighbours[1].second].objectsIdx.end());		//dodaj indeksy z s�siedneigo sektora
	}
	if (edgeVal[1](mainIdx,sectorDiv))														//je�li aktualny sektor nie jest na granicy macierzy w osi Z
		retVec.insert(retVec.end(), sectors[neighbours[2].first][neighbours[2].second].objectsIdx.begin(),
			sectors[neighbours[2].first][neighbours[2].second].objectsIdx.end());			//dodaj indeksy z s�siedniego sektora

	std::sort(retVec.begin(), retVec.end());												//posortowanie pobranych indeks�w [dla funkcji 'erase']
	retVec.erase(std::unique(retVec.begin(), retVec.end()), retVec.end());					//usuni�cie powt�rze� indeks�w

	return retVec;
}

//za�adowanie wart. indeks�w s�siad�w sektora ['neighbours'] w zalezno�ci od wybranego wierzcho�ka
void Map::GetSectorsCharacters_Objects_LoadNeighboursIdx(IdxPair neighbours[], IdxPair mainIdx, unsigned vertexIdx) const {
	switch (vertexIdx) {																	//w zale�no�ci od wybranego wierzcho�ka sektora
		//za�aduj warto�ci indeks�w dla s�siad�w aktualnego sektora w okolicy danego wierzcho�ka
	case 0:
		neighbours[0].first = mainIdx.first + 1;  neighbours[0].second = mainIdx.second;
		neighbours[1].first = mainIdx.first + 1; neighbours[1].second = mainIdx.second - 1;
		neighbours[2].first = mainIdx.first; neighbours[2].second = mainIdx.second - 1;
		break;
	case 1:
		neighbours[0].first = mainIdx.first - 1;  neighbours[0].second = mainIdx.second;
		neighbours[1].first = mainIdx.first - 1; neighbours[1].second = mainIdx.second - 1;
		neighbours[2].first = mainIdx.first; neighbours[2].second = mainIdx.second - 1;
		break;
	case 2:
		neighbours[0].first = mainIdx.first - 1;  neighbours[0].second = mainIdx.second;
		neighbours[1].first = mainIdx.first - 1; neighbours[1].second = mainIdx.second + 1;
		neighbours[2].first = mainIdx.first; neighbours[2].second = mainIdx.second + 1;
		break;
	case 3:
		neighbours[0].first = mainIdx.first + 1;  neighbours[0].second = mainIdx.second;
		neighbours[1].first = mainIdx.first + 1; neighbours[1].second = mainIdx.second + 1;
		neighbours[2].first = mainIdx.first; neighbours[2].second = mainIdx.second + 1;
		break;
	}
}

//za�adowanie funkcji pomocniczych  ['fun'] w zale�no�ci od wybranego wierzcho�ka
void Map::GetSectorsCharacters_Objects_LoadEdgeCheckFun(MAP::edgeCheckFun fun[],IdxPair mainIdx,unsigned vertexIdx) const {
	switch (vertexIdx) {																	//w zalezno�ci od wybranego wierzcho�ka sektora
		//utw�rz odpowiednie funkcje sprawdzaj�ce czy dany sektor jest na granicy macierzy
		//sprawdzenie to s�u�y podj�ciu decyzji czy mozna wczyta� indeksy s�siad�w dla aktualnego sektora
	case 0:
		fun[0] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.first < sectorDiv - 1) return true; else return false; };
		fun[1] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.second > 0)return true; else return false; };
		break;
	case 1:
		fun[0] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.first > 0) return true; else return false; };
		fun[1] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.second > 0) return true; else return false; };
		break;
	case 2:
		fun[0] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.first > 0) return true; else return false; };
		fun[1] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.second < sectorDiv - 1) return true; else return false; };
		break;
	case 3:
		fun[0] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.first < sectorDiv - 1) return true; else return false; };
		fun[1] = [](IdxPair idx, unsigned sectorDiv)->bool {if (idx.second < sectorDiv - 1) return true; else return false; };
		break;
	}
}

//funkcja sprawdzaj�ca czy dany punkt znajduje si� wewn�trz tr�jk�ta (w rzucie X,Z)
bool Map::CheckPointInTriangle(Vector point, Vector triangle[], Vector normal) {			//tr�jk�t opisany jest przy pomocy 3 kolejno podanych punkt�w ['triangle'] oraz normalnej
	Vector n[3], AB, BC, CA;
	AB = triangle[1] - triangle[0]; BC = triangle[2] - triangle[1];
	CA = triangle[0] - triangle[2];															//inicjalizacja wektor�w opisuj�cych kolejne ramiona tr�jk�ta
	n[0] = AB.CrossProduct(normal);															//obliczenie normalnych do ka�dego boku tr�jk�ta (wskazuj� one na zewn�trz tr�jk�ta)
	n[1] = BC.CrossProduct(normal);
	n[2] = CA.CrossProduct(normal);

	for (unsigned int i = 0; i < 3; i++) {													//dla ka�dego boku
		double A, B, C, D;
		A = n[i].x; B = n[i].y; C = n[i].z;													//wyzanczamy parametry powierzchni opisuj�cej dany bok	
		D = -A*triangle[i].x - B*triangle[i].y - C*triangle[i].z;							//[przy pomocy normalnej do danego boku oraz punkt�w wchodz�cych w jego sk�ad]

		double t = -D - A*point.x - B*point.y - C*point.z;									//obliczenie parametru 't' dla parametrycznego r�wnania prostej	
		t /= A*n[i].x + B*n[i].y + C*n[i].z;												//zaczynaj�cej si� w punkcie 'point' i skierowanej zgodnie z wektorem normalnym

		if (t < 0) return false;															//je�li warto�c ta jest ujemna - punkt nie zanjduje si� wewn�trz tr�jk�ta - zwr�� FALSE
	}

	return true;																			//je�li wszystkie warto�ci parametru 't' by�y dodatnie - punkt znajduje si� wewn�trz tr�jk�ta
}

//konstruktor sektora
SECTOR::SECTOR() {
	for (unsigned int i = 0; i < 4; i++)
		vertices[i] = Vector();																//za�aduj wierzcho�ki warto�ciami domy�lnymi
}

//konstruktor macierzy sektor�w
SECTOR_MATRIX::SECTOR_MATRIX() {

}

//inicjalizacja macierzy sektor�w
void SECTOR_MATRIX::Initialize(unsigned int _dimension,Vector _minPt, Vector _maxPt) {
	dimension = _dimension;																	//wczytanie wymiaru macierzy
	matrix = new SECTOR*[dimension];														//stworzenie macierzy sektor�w o podanym wymiarze
	for (unsigned int i = 0; i < dimension; i++)
		matrix[i] = new SECTOR[dimension];

	minPoint = _minPt;																		//wczytanie wart. punktu min.
	maxPoint = _maxPt;																		//wczytanie wart. punktu max.

	xShift= (maxPoint.x - minPoint.x) / dimension;											//obliczenie d�ugo�ci pojedynczego sektora w osi X 
	zShift = (maxPoint.z - minPoint.z) / dimension;											//obliczenie d�ugo�ci pojedynczego sektora w osi Z
}

//pobranie indeks�w sektora dla danego punktu w p�aszczy�nie (X,Z)
IdxPair SECTOR_MATRIX::GetSector(double x, double z) const {
	IdxPair idx;

	idx.first = static_cast<unsigned>((x - minPoint.x) / xShift);
	idx.second = static_cast<unsigned>((maxPoint.z - z) / zShift);

	return idx;
}

//przeci��enie operatora '[]' [umo�liwia to odwo�ywanie si� do konkretnrych sektor�w przy u�yciu sk�adni: MATRIX_SECTOR[0][0] ] 
SECTOR* SECTOR_MATRIX::operator[](unsigned int a) const{
	if (a < dimension)
		return matrix[a];
	else return NULL;
}
