#include "Character.h"

//podstawowy konstruktor postaci okre�laj�cy tylko model tworzonego obiektu
Character::Character(const std::string& filename) {
	LoadModel(filename);																	//wczytanie modelu

	name = "";																				//ustawienie domy�lnych warto�ci dla odpowiednich p�l klasy
	position = { 0,0,0 };
	orientation = { 0,0,0 };
	sectorIdx = IdxPair(0, 0);
	enable = false;
	health = 100;

	InitilizeTransformMatrix();
	InitilizeTransformedVertices();
	InitilizeTransformedNormals();
	UpdateCollisionBoxVertices();
}

//konstruktur okre�laj�cy od razu nazw�, po�o�enie i oreintacj� postaci
Character::Character(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation) {
	LoadModel(filename);																	//wczytanie modelu

	name = Name;																			//ustwienie warto�ci dla odpowiednich p�l klasy

	position = Position;
	orientation = Orientation;
	sectorIdx = IdxPair(0, 0);
	enable = false;
	health = 100;

	InitilizeTransformMatrix();
	InitilizeTransformedVertices();
	InitilizeTransformedNormals();
	UpdateCollisionBoxVertices();
}

//inicjalizacja postaci
void Character::Initialize(std::string Name, Vector Position, Vector Orientation) {
	name = Name;																			//ustwienie warto�ci dla odpowiednich p�l klasy
	position = Position;
	orientation = Orientation;
	sectorIdx = IdxPair(0, 0);

	InitilizeTransformMatrix();
	InitilizeTransformedVertices();
	InitilizeTransformedNormals();
	UpdateCollisionBoxVertices();
}

//inicjalizacja macierzy przekszta�ce� [macierz przekszta�cenia jednorodnego]
//w celu wygenerowania macierzy przekszta�ce� wykorzystywana jest pozycja postaci oraz jej orientacja
void Character::InitilizeTransformMatrix() {
	Vector angle(orientation); angle = angle / 360.0 * 2.0 * 3.1415;						//warto�ci k�t�w orientacji postaci w radianach
	//wpisanie odpowiednich warto�ci do macierzy przekszat�ce�
	transform[0][0] = cos(angle.y)*cos(angle.z); transform[0][1] = cos(angle.z)*sin(angle.x)*sin(angle.y) - cos(angle.x)*sin(angle.z);
	transform[0][2] = sin(angle.x)*sin(angle.z) + cos(angle.x)*cos(angle.z)*sin(angle.y); transform[0][3] = position.x;

	transform[1][0] = cos(angle.y)*sin(angle.z); transform[1][1] = cos(angle.x)*cos(angle.z) + sin(angle.x)*sin(angle.y)*sin(angle.z);
	transform[1][2] = cos(angle.x)*sin(angle.y)*sin(angle.z) - cos(angle.z)*sin(angle.x); transform[1][3] = position.y;

	transform[2][0] = -sin(angle.y); transform[2][1] = cos(angle.y)*sin(angle.x); transform[2][2] = cos(angle.x)*cos(angle.y); transform[2][3] = position.z;

	transform[3][0] = transform[3][1] = transform[3][2] = 0.0; transform[3][3] = 1.0;
}

//inicjalizacja wekotra przekszta�conych wsp�rz�dnych wierzcho�k�w modelu
void Character::InitilizeTransformedVertices() {
	for (unsigned int i = 0; i < vertices.size(); i++)
		transformedVertices.push_back(transform*vertices[i]);
}

void Character::InitilizeTransformedNormals() {
	for (unsigned int i = 0; i < normals.size(); i++)
		transformedNormals.push_back(transform*normals[i]);
}

//aktualizacja wierzcho�k�w bry�y kolizji [dla wszystkich bry� kolizji wchodz�cych w sk�ad postaci]
void Character::UpdateCollisionBoxVertices() {
	for (unsigned int i = 0; i < objects.size(); i++) {										//sprawdzenie wszystkich obiekt�w wchodz�cych w sk�ad modelu
		unsigned int colBoxSize = objects[i].collisionBox.size();
		for (unsigned int j = 0; j < colBoxSize; j++) {										//sprawdzenie wszystkich bry� kolizji dla ka�dego obiektu
			unsigned int vertSize = objects[i].collisionBox[j].verticesIdx.size();
			for (unsigned int k = 0; k < vertSize; k++) {
				unsigned int idx = objects[i].collisionBox[j].verticesIdx[k];				//wczytanie indeksu wierzcho�ka bry�y kolizji
				transformedVertices[idx] = transform*vertices[idx];							//aktualizacja wsp�rz�dnych wierzcho�ka bry�y kolizji dla pojedynczych obiekt�w modelu
			}
		}
	}

	//aktualizacja wierzcho�k�w dla bry�y kolizji ca�ego modelu							
	for (unsigned int i = 0; i < collisionBox.verticesIdx.size(); i++) {					//sprawdzenie wszystkich wierzcho�k�w z bry�y kolizji
		unsigned int idx = collisionBox.verticesIdx[i];										//wczytanie indeksu wierzcho�ka bry�y kolizji
		transformedVertices[idx] = transform*vertices[idx];									//aktualizacja wsp�rz�dnych bry�y kolizji dla ca�ego modelu
	}
}

void Character::UpdateCollisionBoxNormals() {
	for (unsigned int i = 0; i < objects.size(); i++) {										//sprawdzenie wszystkich obiekt�w wchodz�cych w sk�ad modelu
		unsigned int colBoxSize = objects[i].collisionBox.size();
		for (unsigned int j = 0; j < colBoxSize; j++) {										//sprawdzenie wszystkich bry� kolizji dla ka�dego obiektu
			unsigned int faceSize = objects[i].collisionBox[j].normalsIdx.size();
			for (unsigned int k = 0; k < faceSize; k++) {
				unsigned int idx = objects[i].collisionBox[j].normalsIdx[k];				//wczytanie indeksu wierzcho�ka bry�y kolizji
				transformedNormals[idx] = transform*normals[idx];						//aktualizacja wsp�rz�dnych wierzcho�ka bry�y kolizji dla pojedynczych obiekt�w modelu
			}
		}
	}

	//aktualizacja wierzcho�k�w dla bry�y kolizji ca�ego modelu							
	for (unsigned int i = 0; i < collisionBox.normalsIdx.size(); i++) {					//sprawdzenie wszystkich wierzcho�k�w z bry�y kolizji
		unsigned int idx = collisionBox.normalsIdx[i];										//wczytanie indeksu wierzcho�ka bry�y kolizji
		transformedNormals[idx] = transform*normals[idx];									//aktualizacja wsp�rz�dnych bry�y kolizji dla ca�ego modelu
	}
}