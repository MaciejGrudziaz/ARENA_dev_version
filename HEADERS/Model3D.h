#pragma once
#include <vector>
#include "Quaternion.h"

//------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------MODEL 3D--------------------------------------------------------------
//-----------------------------------------------klasa s�u��ca za interfejs model�w 3D------------------------------------------------
//-----ka�da klasa odpowiadaj�ca za wczytywanie plik�w 3D w danym formacie musi zdefiniowa� funkcje LoadModel(..) i DrawModel(..)-----
//------------------------------------------------------------------------------------------------------------------------------------

//struktura opisuj�ca powierzchni� (tr�jk�t)
struct Face{
	unsigned int PointsIdx[3];							//indeksy wierzcho�k�w wchodz�cych w sk�ad powierzchni [tr�jk�ta]
	unsigned int NormalIdx;								//indeks normalnej dla danej poweirzchni
};

//struktura opisuj�ca bry�� kolizji
struct CollisionBox {
	std::vector<unsigned int> verticesIdx;				//wektor punkt�w opisuj�cych model
	std::vector<unsigned int> facesIdx;					//wektor powierzchni wchdz�cych w sk�ad modelu
	std::vector<unsigned int> normalsIdx;				//wektor normalnych do danych powierzchni

	Vector midPoint;									//punkt wyznaczaj�cy geometryczny �rodek bry�y kolizji
	Vector maxPoint;									//punkt o maksymalnych warto�ciach wsp�r�ednych dla ca�ej bry�y kolizji
	Vector minPoint;

	double radius;										//promie� kore�laj�cy sfer� kolizji [midPoint - �rodek sfery]

	Vector size;
};

//struktura opisuj�ca obiekt
struct Object {
	std::string name;
	std::vector<unsigned int> facesIdx;					//indeksy powierzchni wchodz�cych w sk�ad obiektu
	std::vector<unsigned int> verticesIdx;				//indeksy wierzcho�k�w wchodz�cych w sk�ad obiektu
	std::vector<CollisionBox> collisionBox;				//bry�y kolizji dla obiektu
	CollisionBox mainColBox;
};

//podstawowa klasa modelu 3D
class Model3D {
protected:
	std::vector<Vector> vertices;						//wektor punkt�w opisuj�cych model
	std::vector<Face> faces;							//wektor powierzchni wchdz�cych w sk�ad modelu
	std::vector<Vector> normals;						//wektor normalnych do danych powierzchni
	std::vector<Object> objects;						//wektor obiekt�w wchodz�cych w sk�ad modelu

	std::vector<Vector> transformedVertices;			//wektor przekszta�conych wierzcho�k�w modelu
	std::vector<Vector> transformedNormals;

	CollisionBox collisionBox;							//bry�a kolizji dla ca�ego modelu

	Vector position;									//obecna pozycja modelu
	Vector orientation;									//obecna orientacja modelu [przechowuje k�t obrotu wok� osi x, y i z w STOPNIACH]

	Matrix transform;									//macierz przekszta�cenia jednorodnego opisuj�ca przekszta�cenia wierzcho�k�w modelu

public:
	virtual int LoadModel(const std::string& filename) = 0;			//funkcja ��duj�ca model [funkcja wirtualna definiowana dla klasy danego typu plik�w]
	virtual void DrawModel() = 0;						//funkcja rysuj�ca model [funkcja wirtualna definiowana dla klasy danego typu plik�w]

};