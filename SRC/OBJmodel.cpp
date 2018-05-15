#include "OBJmodel.h"

//konstruktor domy�lny
OBJmodel::OBJmodel() {
	position = { 0,0,0 };										//ustawienie domy�lnych warto�ci p�l klasy
	orientation = { 0,0,0 };
	transform.Initilize(4, 4);
}

//funkcja �aduj�ca model z pliku
int OBJmodel::LoadModel(/*const char**/const std::string& filename) {
	std::string _filename = "MODELS/" + filename;
	char charFilename[50];
	unsigned idx = 0;
	for (idx = 0; idx < _filename.size(); idx++)
		charFilename[idx] = _filename[idx];
	charFilename[idx] = NULL;

	//unsigned int faceStartIdx;								//indeks okre�laj�cy ostatni element w wektorze 'faces' przed wczytaniem kolejengo obiektu
	bool end = false;											//znacznik pomocniczy u�ywany do wczytywania modelu
	std::fstream file;											//klasa odpowiadaj�ca za wczytywanie strumienia z pliku
	std::string objectName;
	file.open(charFilename, std::ios::in);							//otworzenie pliku [tylko do odczytu]

	if (!file.is_open())										//sprawdzenie czy plik zosta� poprawnie otworzony
		return 0;

	skipFileBegin(file);										//omini�cie znak�w na pocz�tku pliku a� do wsp�rz�dnych wierzcho�k�w

	while (!end) {
		objectName=readObjectName(file);						//wczytanie nazwy obiektu

		if (objectName.compare(0, 6, "HITBOX")==0)				//je�li nazwa obiektu zaczyna si� od s�owa "HITBOX"
			end=loadCollisionBox(file,objectName);				//wczytaj dane bry�y kolizji
		else end=loadObject(file,objectName);					//w przeciwnym wypadku wczytaj dane obiektu

	}

	file.close();												//zamkni�cie pliku

	return 1;
}

//funkcja rysuj�ca wczytany model
void OBJmodel::DrawModel() {
	Vector normal;												//aktualna normalna do rysowanej powierzchni
	Vector tmpVertices[3];										//wierzcho�ki aktualnie rysowanego tr�jk�ta

	glPushMatrix();												//umieeszczenie macierzy widoku OpenGL na stosie

	ModelTransformation();										//dokonanie odpowiedniej transformacji modelu [opisanej za pomoc� zmiennych 'position' i 'orientation'

	glBegin(GL_TRIANGLES);										//rozpocz�cie rysowania modelu

	for (unsigned int i = 0; i < objects.size(); i++) {
		for (unsigned int j = 0; j < objects[i].facesIdx.size(); j++) {
			//wczytanie danych dla powierzchni okre�lonej indeksem 'objects[i].facesIdx[j]'
			DRAW_getFaceData(tmpVertices, normal, objects[i].facesIdx[j]);
			for (int j = 0; j < 3; j++) {
				//za�adowanie normalnej do modleu widoku OpenGL
				glNormal3d(normal.x, normal.y, normal.z);		
				//za�adowanie wierzcho�k�w do modelu widoku OpenGL
				glVertex3d(tmpVertices[j].x, tmpVertices[j].y, tmpVertices[j].z);
			}
		}
	}

	glEnd();													//koniec rysowania modelu

	glPopMatrix();												//wczytanie macierzy widoku OpenGL ze stosu
}

//funkcja rysuj�ca bry�y kolizji dla ca�ego modelu
void OBJmodel::DrawCollisionBox() {
	Vector normal, tmpVertices[3];														//aktualna normalna oraz wierzcho�ki powierzchni	

	glPushMatrix();																		//umieszczenie macierzy widoku OpenGL na stosie
	glBegin(GL_LINE_LOOP);																//rozpocz�cie rysowania bry� kolizji
	//rysowanie bry� kolizji dla ka�dego obiektu modelu
	for (unsigned int i = 0; i < objects.size(); i++) {
		for (unsigned int j = 0; j < objects[i].collisionBox.size(); j++) {
			for (unsigned int k = 0; k < objects[i].collisionBox[j].facesIdx.size(); k++) {
				//wczytanie danych dla powierzchni okre�lonej indeksem 'objects[i].collisionBox[j].facesIdx[k]'
				//parametr 'transformedVertices_VEC' okre�la wczytywanie wsp�rz�dnych z wektora przekszta�conych wierzcho�k�w
				DRAW_getFaceData(tmpVertices, normal, objects[i].collisionBox[j].facesIdx[k],transformedVertices_VEC);
				for (unsigned int l = 0; l < 3; l++) {									//za�adowanie normalnej do modleu widoku OpenGL
					glNormal3d(normal.x, normal.y, normal.z);
					glVertex3d(tmpVertices[l].x, tmpVertices[l].y, tmpVertices[l].z);	//za�adowanie wierzcho�k�w do modelu widoku OpenGL
				}
			}
		}
		//narysowanie g��wnej bry�y kolizji obiektu
		for (unsigned int k = 0; k < objects[i].mainColBox.facesIdx.size(); k++) {
			//wczytanie danych dla powierzchni okre�lonej indeksem 'objects[i].collisionBox[j].facesIdx[k]'
			//parametr 'transformedVertices_VEC' okre�la wczytywanie wsp�rz�dnych z wektora przekszta�conych wierzcho�k�w
			DRAW_getFaceData(tmpVertices, normal, objects[i].mainColBox.facesIdx[k], transformedVertices_VEC);
			for (unsigned int l = 0; l < 3; l++) {
				glNormal3d(normal.x, normal.y, normal.z);							//za�adowanie normalnej do modleu widoku OpenGL
				glVertex3d(tmpVertices[l].x, tmpVertices[l].y, tmpVertices[l].z);	//za�adowanie wierzcho�k�w do modelu widoku OpenGL
			}
		}
	}
	//rysowanie bry� kolizji dla ca�ego modelu
	for (unsigned int i = 0; i < collisionBox.facesIdx.size(); i++) {
		//wczytanie danych dla powierzchni okre�lonej indeksem 'objects[i].collisionBox[j].facesIdx[k]'
		//parametr 'transformedVertices_VEC' okre�la wczytywanie wsp�rz�dnych z wektora przekszta�conych wierzcho�k�w
		DRAW_getFaceData(tmpVertices, normal, collisionBox.facesIdx[i], transformedVertices_VEC);
		for (unsigned int j = 0; j < 3; j++) {
			glNormal3d(normal.x, normal.y, normal.z);							//za�adowanie normalnej do modleu widoku OpenGL
			glVertex3d(tmpVertices[j].x, tmpVertices[j].y, tmpVertices[j].z);	//za�adowanie wierzcho�k�w do modelu widoku OpenGL
		}
	}
	glEnd();																	//koniec rysowania bry� kolizji
	glPopMatrix();																//wczytanie amcierzy widoku OpenGL ze stosu
}

//transformacja macierzy przekszta�ce� modelu
void OBJmodel::ModelTransformation() {
	//przesuni�cie modelu do odpowiedniej pozycji [opisanej przy pomocy zmiennej 'position']
	glTranslated(position.x, position.y, position.z);

	//ustawienie odpowiedniej orientacji modelu [opisanej przy pomocy zmiennej 'orientation' - ka�da sk�adowa zmiennej opisuje k�t obrotu wok� odpwoiedniej osi]
	glRotated(orientation.z, 0.0, 0.0, 1.0);
	glRotated(orientation.y, 0.0, 1.0, 0.0);
	glRotated(orientation.x, 1.0, 0.0, 0.0);
}

//funckaj pomocnicza dla metody opisuj�cej rysowanie modelu
void OBJmodel::DRAW_getFaceData(Vector tmpVertices[], Vector& normal,unsigned int faceIdx, int verticesVector) {
	unsigned int vertexIdx;										//zmienna pomocnicza okre�laj�ca indeks aktualnie wczytywanego wierzcho�ka
	unsigned int normalIdx;										//zmienna pomocnicza okre�laj�ca indeks aktualnie wczytywanej normalnej

	for (int j = 0; j < 3; j++) {								//wczytanie wierzcho�k�w dla aktualnej poweirzchni opisanej indeksem 'faceIdx'
		vertexIdx = faces[faceIdx].PointsIdx[j];				//pobranie indeksu wierzcho�ka

		if(verticesVector==0)	
			tmpVertices[j] = vertices[vertexIdx];					//wczytanie wsp�rz�dnych wierzcho�ka
		if (verticesVector == 1)
			tmpVertices[j] = transformedVertices[vertexIdx];
	}

	normalIdx = faces[faceIdx].NormalIdx;						//wczytanie indeksu normalnej do poweirzchni	
	if(verticesVector==0)
		normal = normals[normalIdx];								//pobranie wsp�rz�dnych normalnej
	if (verticesVector == 1)
		normal = transformedNormals[normalIdx];
}

//funkcja zamieniaj�ca ci�g znak�w 'string' o danej d�ugo�ci 'n' na liczb� ca�kowit�
int OBJmodel::char2int(char* string, int n) {
	int retVal = 0;												//warto�� zwracana
	int tmp;													//aktualnie wczytany znak z tablicy 'string'
	for (int i = 0; i < n; i++) {
		tmp = string[i] - 48;									//pobranie znaku i zmienienie go na odpowiedni� warto�� ca�kowitoliczbow�
		for (int j = 0; j < n - i - 1; j++) {
			tmp *= 10;											//okre�lenie prawid�owej 'dziesi�tnej' warto�ci danej cyfry
		}
		retVal += tmp;											//dodanie aktualnie pobranej cyfry do warto�ci zwracanej
	}

	return retVal;
}

//opuszczeni znak�w na pocz�tku pliku a� do nazwy pierwszego obiektu
void OBJmodel::skipFileBegin(std::fstream& file) {
	bool data = false;
	char tmp[1] = { NULL };

	while (!data) {
		file.read(tmp, 1);
		if (tmp[0] != 'o') {									//je�li pierwszym znakiem w nowej linii nie jest 'v'
			while (tmp[0] != '\n') {							//pobieraj kolejne znaki a� do ko�ca linii
				file.read(tmp, 1);
			}
		}
		else data = true;
	}
}

//wczytanie nazwy obiektu z pliku
std::string OBJmodel::readObjectName(std::fstream& file) {
	bool data = true;
	char tmp[1] = { NULL };
	std::string name;

	while (data) {											
		file.read(tmp, 1);
		if (tmp[0] != '\n') {									//dop�ki nie wczytano znaku ko�ca linii
			name.push_back(tmp[0]);								//wczytaj znak do stringa nazwy obiektu
		}
		else {													//w przeciwnym wypadku
			file.read(tmp, 1);									//wczytaj kolejny znak ['v']
			data = false;										//ustaw znacznik ko�ca p�tli
		}
	}

	//wyczyszczenie zawarto�ci stringa nazwy
	name.erase(0, 1);											//wykasuj pierwszy znak z nazwy [' ']
	unsigned int startIdx = 0;									//indeks startowy dla stringa nazwy
	if (name.compare(0, 6, "HITBOX")==0)						//je�li nazwa obiektu zaczyna si� od "HITBOX"
		startIdx = 7;											//startIdx=7
	else startIdx = 0;											//w przeciwnym wypadku startIdx=0
	for (unsigned int i = startIdx; i < name.size(); i++) {
		/*if (name[i] == '_')										//je�li wczytano znak '_'
			name.erase(i, std::string::npos);*/					//usu� pozosta�e znaki do ko�ca stringa
		if (name[i] == '_')										//je�li wczytano znak '_'
			if (name.compare(i + 1, 4, "MAIN")==0)				//je�li nast�pnym s�owem jest 'MAIN'
				i += 4;											//skocz iteratorem do nast�pnego s�owa
			else name.erase(i, std::string::npos);				//w przeciwnym wypadku usu� pozosta�e znaki do ko�ca stringa
	}

	return name;
}

//opuszczenie znak�w w �rodku pliku od zako�czenai wsp�rz�dnych normalnych do indeks�w wierzcho�k�w pwoeirzchni
void OBJmodel::skipMidFile(std::fstream& file) {
	char tmp[1] = { NULL };
	bool data = false;

	while (!data) {
		file.read(tmp, 1);
		if (tmp[0] != 'f') {									//je�li pierwszym znakiem w nowej linii nie jest 'f'
			while (tmp[0] != '\n') {							//pobieraj kolejne znaki a� do ko�ca linii
				file.read(tmp, 1);
			}
		}
		else data = true;
	}
}

//za�adowanie danych dla obiektu
bool OBJmodel::loadObject(std::fstream& file, std::string objectName) {
	bool endFile = false;										//znacznik ko�ca pliku
	unsigned int faceStartIdx = faces.size();

	VERTEX_LoadVertices(file);									//pobranie wsp�rz�dnych wierzcho�k�w

	NORMAL_LoadNormals(file);									//pobranie wsp�rz�dnych normalnych

	skipMidFile(file);											//omini�cie znak�w od zako�czenia wsp�rz�dnych normalnych a� do pocz�tku danych opisuj�cych powierzchnie

	if (!FACE_LoadFaces(file))									//pobranie danych poweirzchni
		endFile = true;											//je�li dotarto do ko�ca pliku zako�cz pobieranie danych
	//wczytanie danych dla obiektu
	OBJECT_LoadObject(faceStartIdx, faces.size() - 1,objectName);

	return endFile;												//zwr�cenie znacznika ko�ca pliku
}

//za�adowanie danych dla bry�y kolizji
bool OBJmodel::loadCollisionBox(std::fstream& file, std::string objectName) {
	objectName.erase(0, 7);										//usuni�cie cz�ci "HITBOX_" ze stringa nazwy obiektu [pozstawienie czystej nazwy obiektu]
	bool endFile = false;										//znacznik ko�ca pliku
	int objIdx = OBJECT_findObject(objectName);					//sprawdzenie czy dany obiekt ju� istnieje [je�li tak -> objIdx - indeks obiektu, w przeciwnym wypadku -> objIdx = -1]
	//indeksy pocz�tkowe dla wierzcho�k�w, powierzchni i normalnych wchodz�cych w sk��d bry�y kolizji
	unsigned int verticesStartIdx = vertices.size(), facesStartIdx = faces.size(), normalsStartIdx = normals.size();
	CollisionBox newCollision;								

	VERTEX_LoadVertices(file);									//pobranie wsp�rz�dnych wierzcho�k�w

	NORMAL_LoadNormals(file);									//pobranie wsp�rz�dnych normalnych

	skipMidFile(file);											//omini�cie znak�w od zako�czenia wsp�rz�dnych normalnych a� do pocz�tku danych opisuj�cych powierzchnie

	if (!FACE_LoadFaces(file))									//pobranie danych poweirzchni
		endFile = true;											//je�li dotarto do ko�ca pliku zako�cz pobieranie danych
	//wczytanie danych dla bry�y kolizji
	COLLISIONBOX_LoadData(newCollision, verticesStartIdx, facesStartIdx, normalsStartIdx);
	//za�adowanie danych obiektu bry�y kolizji do odpowiedniego obiektu
	COLLISIONBOX_LoadCollisionToObject(newCollision, objectName, objIdx);

	return endFile;												//zwr�� znacznik ko�ca pliku
}

//pobranie wsp�rz�dnych wierzcho�ka
Vector OBJmodel::VERTEX_getVertex(std::fstream& file) {
	Vector point;
	double coord;

	file >> coord;
	point.x = coord;
	file >> coord;
	point.y = coord;
	file >> coord;
	point.z = coord;

	return point;
}

//za�adowanie wszystkich wsp�rz�dnych wierzcho�k�w
void OBJmodel::VERTEX_LoadVertices(std::fstream& file) {
	bool data = true;
	char tmp[2] = { 'v',NULL };									//ostatnio pobrane znaki
	while (data) {
		if (tmp[0] == 'v' && tmp[1] == NULL) {					//je�li w nowym wierszu pobrano znak 'v '
			vertices.push_back(VERTEX_getVertex(file));			//pobierz wsp�rz�dne wierzcho�ka

			file.read(tmp, 1);									//pobierz 2 znaki z nowej linii
			file.read(tmp, 2);
			if (tmp[1] != 'n') tmp[1] = NULL;					//je�li nie pobrano kombinacji 'vn' to usatw znak tmp[1] na NULL i pobierz nast�pne wsp�rz�dne
		}
		else
			data = false;										//je�li w nowym wierszu pobrano 'vn' zako�cz p�tl�
	}
}

//pobranie wsp�rz�dnych normalnej
Vector OBJmodel::NORMAL_getNormal(std::fstream& file) {
	Vector normal(FREE);
	double coord;

	file >> coord;
	normal.x = coord;
	file >> coord;
	normal.y = coord;
	file >> coord;
	normal.z = coord;

	return normal;
}

//pobranie wszystkich normalnych
void OBJmodel::NORMAL_LoadNormals(std::fstream& file) {
	bool data = true;
	char tmp[2] = { 'v','n' };									//ostatnio pobrane znaki

	while (data) {
		if (tmp[0] == 'v' && tmp[1] == 'n') {					//jesli w nowym wierszu pobrano 'vn'
			normals.push_back(NORMAL_getNormal(file));			//wczytaj wsp�rz�dne normalnej

			file.read(tmp, 1);									//wczytaj 2 znaki z nowej linii
			file.read(tmp, 2);
		}
		else data = false;										//je�li w nowej linii nie pobrano znak�w 'vn' zako�cz p�tl�
	}
}

//odczytywanie indeksu wierzcho�ka dla danej powierzchni [wczytuje indeks wierzcho�ka wraz ze znakiem '/' wyst�puj�cym bezpo�rednio po nim]
int OBJmodel::FACE_readPtIdx(std::fstream& file) {
	unsigned int idx = 0;										//ilo�� wczytanych znak�w
	unsigned int PtIdx;											//wczytany indeks wierzcho�ka
	char facetmp[256];											//tymczasowa tablica wczytanych znak�w
	char tmp[1];
	bool data = true;

	while (data) {
		file.read(tmp, 1);										//pobranie kolejnego znaku w linii
		if (tmp[0] == '/') data = false;						//je�li znakiem tym jest '/' zako�cz p�tl�
		else {
			facetmp[idx] = tmp[0];								//je�li pobranym znakiem nie jest '/' wczytaj go do tablicy
			idx++;												//zwi�ksz ilo�� wczytanych znak�w
		}
	}
	PtIdx = char2int(facetmp, idx);								//zmie� tablic� znak�w na liczb� int

	return PtIdx - 1;
}

//odczytywanie indeksu normalnej do poweirzchni [wczytuje indeks normalnej wraz ze znakiem ' ' wyst�puj�cym bezpo�rednio po nim]
int OBJmodel::FACE_readNormIdx(std::fstream& file) {
	unsigned int idx = 0;										//ilo�� wczytanych znak�w
	unsigned int NormIdx;										//wczytany indeks normalnej
	char facetmp[256];											//tymczasowa tablica wczytanych znak�w
	char tmp[1];
	bool data = true;

	while (data) {
		file.read(tmp, 1);										//pobranie kolejnego znaku w linii
		if (tmp[0] == ' ') data = false;						//je�li znakiem tym jest ' ' zako�cz p�tl�
		else {
			facetmp[idx] = tmp[0];								//je�li pobranym znakiem nie jest ' ' wczytaj go do tablicy
			idx++;												//zwi�ksz ilo�� wczytanych znak�w
		}
	}
	NormIdx = char2int(facetmp, idx);							//zmie� tablic� znak�w na liczb� int

	return NormIdx - 1;
}

//przesuniecie znacznika w tek�cie [pomini�cie znak�w] dla odczytu powierzchni w zale�no�ci od obecnej pozycji w wierszu
void OBJmodel::FACE_skipSpace(std::fstream& file, int idx) {
	char tmp[1];
	bool data;

	switch (idx) {
	case 0:														//usuni�cie pojedynczej spacji po znaku 'f' oraz znaku '/' po odczytaniu pierwszego indeksu wierzcho�ka
		file.read(tmp, 1);
		break;
	case 1:														//pominiecie wszystkich znak�w pomi�dzy drugim, a trzecim indeksem wierzcho�ka
		data = false;
		file.read(tmp, 1);
		while (!data) {											//wczytuj kolejne znaki a� do momentu wczytania ' '
			file.read(tmp, 1);
			if (tmp[0] == ' ') data = true;
		}
		break;
	case 2:														//pomini�cie wszystkich znak�w po trzecim ideksie wierzcho�ka a� do ko�ca linii
		data = false;
		while (!data) {
			file.read(tmp, 1);									//wczytuj kolejne znaki a� do momentu wczytania '\n'
			if (tmp[0] == '\n') data = true;
		}
		break;
	}
}

//odczytywanie indeksu wierzcho�ka poweirzchni w zale�no�ci od jego po�o�enia w wierszu
int OBJmodel::FACE_readFaceVertexIdx(std::fstream& file, int idx) {
	unsigned int ptIdx;

	//u�ywanie funkcji pominiecia znak�w w zale�no�ci od po�o�enia indeksu w wierszu
	switch (idx) {
	case 0:
		FACE_skipSpace(file, 0);								//pomini�cie psutego znaku po pierwszym symbolu 'f' w wierszu
		break;
	case 2:
		FACE_skipSpace(file, 1);								//pomini�cie wszystkich znak�w pomi�dzy indeksem 2 i 3 wierzcho�ka
		break;
	}

	ptIdx = FACE_readPtIdx(file);								//pobranie indeksu wierzcho�ka

	return ptIdx;
}

//odczytywanie indeksu normalnej dla poweirzchni
int OBJmodel::FACE_readFaceNormalIdx(std::fstream& file) {
	unsigned int normIdx;

	FACE_skipSpace(file, 0);									//pomini�cie znaku '/' po indeksie pierwszego wierzcho�ka

	normIdx = FACE_readNormIdx(file);							//odczytanie indeksu normalnej

	return normIdx;
}

//pobranie indeks�w wierzcho�k�w oraz indeksu normalnej dla danej powierzchni
Face OBJmodel::FACE_getFace(std::fstream& file) {
	Face face;

	for (int i = 0; i < 3; i++) {
		face.PointsIdx[i] = FACE_readFaceVertexIdx(file, i);		//pobranie indeksu wierzcho�ka i
		if (i == 0) face.NormalIdx = FACE_readFaceNormalIdx(file);	//po pobraniu indeksu wierzcho�ka 0 nale�y pobra� indeks normalnej do powierzchni 
	}

	return face;
}

//pobranie wszystkich danych powierzchni
int OBJmodel::FACE_LoadFaces(std::fstream& file) {
	bool data = true;
	char tmp[1] = { 'f' };										//ostatnio pobrany znak

	while (data) {
		if (tmp[0] == 'f') {									//dop�ki pierwszym znakiem wczytanym w linii jest 'f'
			tmp[0] = NULL;

			faces.push_back(FACE_getFace(file));				//wczytaj kolejne dane powierzchni

			FACE_skipSpace(file, 2);							//pomi� wszystkie znaki po trzecim indeksie wierzcho�ka a� do ko�ca linii

			file.read(tmp, 1);									//wczytaj pierwszy znak z nowej linii
		}
		else data = false;
	}

	if (tmp[0] == '\0') return 0;								//je�li wczytano znak ko�ca pliku zwr�� 0
	else return 1;												//w przeciwnym przypadku zwr�� 1						
}

//wczytanie indeks�w powierzchni oraz wierzcho�k� dla danego obiektu
void OBJmodel::OBJECT_LoadObject(unsigned int startIdx, unsigned int endIdx,std::string objectName) {
	//Object newObj;											//obiekt do wczytania
	int objIdx = OBJECT_findObject(objectName);

	Object* obj;
	if (objIdx != -1) obj = &objects[objIdx];
	else obj = new Object;

	obj->name = objectName;

	for (unsigned int i = startIdx; i <= endIdx; i++) {
		obj->facesIdx.push_back(i);								//wczytanie do wektora indeks�w powierzchni kolejnych powierzchni wchodz�cych w jego sk�ad

		for (unsigned int j = 0; j < 3; j++) {
			unsigned int idx = faces[i].PointsIdx[j];
			if (!OBJECT_CheckVertexInVector(*obj, idx))			//je�li dany wierzcho�ek nie zosta� jeszcze wczytany do obiektu
				obj->verticesIdx.push_back(idx);				//dodaj go do wekotra wierzcho�k�w obiektu
		}
	}

	if (objIdx == -1) {
		objects.push_back(*obj);								//wczytanie obiektu do wektora obiekt�w
		delete obj;
	}
}

//sprawdzenie czy dany wierzcho�ek znajduje si� w wekotrze wierzcho�k�w danego obiektu
bool OBJmodel::OBJECT_CheckVertexInVector(Object obj,unsigned int vertexIdx) {
	unsigned int n = obj.verticesIdx.size();
	for (unsigned int i = 0; i < n; i++) {
		unsigned int idx = obj.verticesIdx[i];
		if (idx == vertexIdx) return true;						//je�li tak zwr�� TRUE
	}

	return false;												//w przeciwnym wypadku zwr�� FALSE
}

//funkcja zwracaj�ca indeks obiektu o danej nazwie w wektorze obiekt�w modelu ['objects']
//je�li dany obiekt nie istnieje - funkcja zwraca warto�� -1
int OBJmodel::OBJECT_findObject(std::string objectName) {
	unsigned int n = objects.size();

	for (unsigned int i = 0; i < n; i++)
		if (objects[i].name.compare(objectName)==0)				//je�li nazwa obiektu zgadza si� z dan� nazw� 'objectName'
			return i;											//zwr�� indeks obiektu

	return -1;													//je�li nie znaleziono obiektu o danej nazwie zwr�� -1
}

//za�adowanie danych do obiektu bry�y kolizji
void OBJmodel::COLLISIONBOX_LoadData(CollisionBox &colBox, unsigned int verticesStartIdx, unsigned int facesStartIdx, unsigned int normalsStartIdx){
	Vector midPt(0,0,0), maxPt(vertices[verticesStartIdx]),minPt(vertices[verticesStartIdx]);		//inicajlizacja zmiennych opisuj�cych �rodek bry�y kolizji [midPt] i punktu o maksymalnych wsp�rz�dnych dla ka�dej osi [maxPt]

	for (unsigned int i = verticesStartIdx; i < vertices.size(); i++) {
		colBox.verticesIdx.push_back(i);						//wczytanie indeksu wierzcho�ka do wektora indeks�w bry�y kolizji
		/*if (vertices[i].x > maxPt.x) maxPt.x = vertices[i].x;	//sprawdzenie czy dany punkt nie ma wsp�rz�dnych wi�kszych ni� odpowiednie wsp�rz�dne 'maxPt'
		if (vertices[i].y > maxPt.y) maxPt.y = vertices[i].y;
		if (vertices[i].z > maxPt.z) maxPt.z = vertices[i].z;*/
		for (unsigned j = 0; j < 3; j++) {
			if (vertices[i][j] > maxPt[j]) maxPt[j] = vertices[i][j];
			if (vertices[i][j] < minPt[j]) minPt[j] = vertices[i][j];
		}

		//midPt += vertices[i];									//dodanie danego wierzcho�ka do sumy wsp�rzednych w celu obliczenia punktu 'midPt'
	}
	for (unsigned int i = facesStartIdx; i < faces.size(); i++)	
		colBox.facesIdx.push_back(i);							//wczytanie indeks�w powierzchni do wekotra indeks�w bry�y kolizji
	for (unsigned int i = normalsStartIdx; i < normals.size(); i++)
		colBox.normalsIdx.push_back(i);							//wczytanie indesk�w normalnych do wektora indeks�w bry�y kolizji

	//midPt /= (vertices.size() - verticesStartIdx);				//podzielenie sumy wszystkich wierzcho�k�w bry�y kolizji przez ich liczb�
	midPt = (maxPt + minPt) / 2.0;
	colBox.midPoint = midPt;									//dodanie punktu �rodkowego do bry�y kolizji

	Vector shift(maxPt - midPt);								//obliczenie wektora przesuniecia od punktu �rodkowego do punktu o maksymlanych wsp�lrz�dnych ['maxPt']
	colBox.radius = shift.MOD();								//wczytanie promienia bry�y kolizji jako d�ugo�ci wektora przesuni�cia

	colBox.maxPoint = maxPt;									//dodanie wsp�rz�dnych punktu najbardziej wysuni�tego do bry�y kolizji
	colBox.minPoint = minPt;

	colBox.size = (maxPt - midPt) * 2.0;
}

//za��dowanie danej bry�y kolizji 'newCollision' do obiektu o danym indeksie 'objIdx'
void OBJmodel::COLLISIONBOX_LoadCollisionToObject(CollisionBox& newCollision,std::string objectName,unsigned int objIdx) {
	bool mainColBox = false;
	if (objIdx == -1) {											//je�li obiekt o danej anzwie nie istnieje
		if (objectName == "MODEL")								//je�li nazwa obiektu == 'MODEL"
			collisionBox = newCollision;						//oznacza to �e wczytana bry�a kolizji jest bry�� kolizji dla ca�ego modelu
		else {
																//je�li nie jest to g��wna bry�a kolizji obiektu
			if (!COLLISIONBOX_LoadCollisionToObject_CheckIfMainHitbox(objectName)) {										
				Object obj;										//stw�rz nowy obiekt
				obj.name = objectName;							//wczytaj jego nazw�
				obj.collisionBox.push_back(newCollision);		//dodaj dla niego wczytan� bry�� kolizji
				objects.push_back(obj);							//dodaj obiekt do wekotra obiket�w modelu
			}
																//w przeciwnym wypadku za�aduj do obiektu g��wn� bry�e kolizji
			else COLLISIONBOX_LoadCollisionToObject_LoadObjectMainHitbox(objectName, newCollision);
		}

	}
	else objects[objIdx].collisionBox.push_back(newCollision);		//je�li istnieje - dodaj bry�e kolizji do odpowiedniego wektora obiektu danego indeksem objIdx
}

bool OBJmodel::COLLISIONBOX_LoadCollisionToObject_CheckIfMainHitbox(std::string& objectName) {
	for (unsigned int i = 0; i < objectName.size(); i++) {			//sprawdzenie nazwy obiektu
		if (objectName[i] == '_') {
			if (objectName.compare(i + 1, 4, "MAIN") == 0) {		//je�li nazwa zako�czona jest na "MAIN"
				objectName.erase(i, std::string::npos);				//usuni�cie s�owa "MAIN" z nazwy
				return true;
			}
		}
	}

	return false;
}

void OBJmodel::COLLISIONBOX_LoadCollisionToObject_LoadObjectMainHitbox(std::string objectName, CollisionBox& newCollision) {
	unsigned int objIdx = OBJECT_findObject(objectName);			//sprawd� czy istnieje obiekt o danej nazwie
	if (objIdx == -1) {												//je�li nie
		Object obj;													//stw�rz go
		obj.name = objectName;
		obj.mainColBox = newCollision;								//za�aduj g��wn� bry�� kolizji obiektu
		objects.push_back(obj);										//dodaj obiekt do wektora wszystkich obiekt�w dla modelu
	}
	else objects[objIdx].mainColBox = newCollision;					//je�li istnieje to dodaj do za�aduj do niego g��wn� bry�� kolizji
}