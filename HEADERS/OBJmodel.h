#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Model3D.h"

#define vertices_VEC 0
#define transformedVertices_VEC 1

//------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------TYP PLIK�W OBJ-----------------------------------------------------
//------------------------------klasa odpowiadaj�ca za wczytywanie plik�w 3D w formacie OBJ-------------------------------
//------------------------------[musi mie� zdefiniowane funkcje LoadModel(..) i DrawModel()]------------------------------
//------------------------------------------------------------------------------------------------------------------------

class OBJmodel: public Model3D {
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------FUNKCJE POMOCNICZA DLA WCZYTYWANIA DANYCH MODELU------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//funkcje charakterystyczne dla formatu plik�w OBJ
	int char2int(char* string, int n);									//zamiana tablicy znak�w char na liczb� ca�kowit� int

	//funkcje przemieszczaj�ce znacznik w tek�cie do docelowej pozycji [opuszcanie znak�w]
	void skipFileBegin(std::fstream& file);								//pomini�cie znak�w na pocz�tku pliku a� do pocz�tku wsp�rz�dnych wierzcho�k�w
	std::string readObjectName(std::fstream& file);
	void skipMidFile(std::fstream& file);								//pomini�cie znak�w w �rodku pliku od ko�ca wsp�rzednych normalnych do pocz�tku danych dla powierzchni

	bool loadObject(std::fstream& file,std::string objectName);			//za�adowanie danych obiektu
	bool loadCollisionBox(std::fstream& file, std::string objectName);	//za�adowanie danych bry�y kolizji

	//funkcje odpowiadaj�ce za wczytywanie wsp�rz�dnych wierzcho�k�w
	Vector VERTEX_getVertex(std::fstream& file);						//pobranie wsp�rz�dnych wierzcho�ka
	void VERTEX_LoadVertices(std::fstream& file);						//za�adowanie danych dla wszystkich wierzcho�k�w

	//funkcje odpowiadaj�ce za wczytywanie wsp�rz�dnych normalnych
	Vector NORMAL_getNormal(std::fstream& file);						//pobranie wsp�rz�dnych normalnej
	void NORMAL_LoadNormals(std::fstream& file);						//za�adowanie danych dla wszystkich normalnych

	//funkcje odpowiadj�ce za wczytywanie danych dla powierzchni
	int FACE_readPtIdx(std::fstream& file);								//wczytanie indeksu wierzcho�ka [niskopoziomowo]
	int FACE_readNormIdx(std::fstream& file);							//wczytanie indeksu normalnej dla powierzchni	[niskopoziomowo]
	void FACE_skipSpace(std::fstream& file, int idx);					//opuszcanie znak�w w wierszu w zalezno�ci od obecnego po�o�enia znacznika w tek�cie
	int FACE_readFaceVertexIdx(std::fstream& file, int idx);			//wczytanie indeksu wierzcho�ka [wysokopoziomowo]
	int FACE_readFaceNormalIdx(std::fstream& file);						//wczytanie indeksu normalnej [wysokopoziomowo]
	Face FACE_getFace(std::fstream& file);								//wczytanie danych dla danej powierzchni
	int FACE_LoadFaces(std::fstream& file);								//wczytanie danych dla wszystkich powierzchni

	//funkcje odpwoiadajce za wczytywanie danych dla obiektu
	void OBJECT_LoadObject(unsigned int startIdx, 
		unsigned int endIdx,std::string objectName);					//wczytanie indeks�w powierzchni dla danego obiektu
	bool OBJECT_CheckVertexInVector(Object obj,unsigned int vertexIdx);	//sprawdzenie czy wierzcho�ek o danym indeksie znajduje si� w wekotrze wirzcho�k�w obiektu
	int OBJECT_findObject(std::string objectName);						//sprawdzenie czy dany obiekt ju� istnieje

	//funkcje odpowiadaj�ce za wczytywanie danych dla bry�y kolizji
	void COLLISIONBOX_LoadData(CollisionBox &colBox,
		unsigned int verticesStartIdx, unsigned int facesStartIdx, unsigned int normalsStartIdx);
	void COLLISIONBOX_LoadCollisionToObject(CollisionBox& newCollision, std::string objectName, unsigned int objIdx);
	bool COLLISIONBOX_LoadCollisionToObject_CheckIfMainHitbox(std::string& objectName);
	void COLLISIONBOX_LoadCollisionToObject_LoadObjectMainHitbox(std::string objectName, CollisionBox& newCollision);


	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------FUNKCJE POMOCNICZE DLA RYSOWANIA MODELU-----------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//pobranie wp�rz�dnych wszystkich wierzcho�k�w oraz wchodz�cych w sk�ad powierzchni oraz normalnej do tej powierzchni
	//powierzchnia dana jest indeksem 'faceIdx'
	void DRAW_getFaceData(Vector tmpVertices[], Vector& normal, unsigned int faceIdx, int verticesVector=0);
	void ModelTransformation();											//przekszta�cenie macierzy widoku modelu

public:
	OBJmodel();															//konstruktor inicjalizuj�ce zmienne
	int LoadModel(const std::string& filename);										//�adowanie danych modelu z pliku
	void DrawModel();													//funkcja rysuj�ca model
	void DrawCollisionBox();
};