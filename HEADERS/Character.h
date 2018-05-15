#pragma once
#include <CommunicationManager.h>
#include "OBJmodel.h"

//---------------------------------------------------------------------------------
//------------------------------------POSTACIE-------------------------------------
//----------klasa opisuj�ca grywalne postacie [obiekty dynamiczne] w grze----------
//---------------------------------------------------------------------------------

typedef std::pair<unsigned int, unsigned int> IdxPair;

class Character:public OBJmodel {														//klasa postaci korzytsa z plik�w OBJ w celu przedstawienia postaci
protected:
	std::string name;																	//nazwa postaci

	unsigned health;

	bool enable;																		//zmienna okre�laj�ca czy posta� jest dost�pna

	Vector nextPosition;																//nast�pna pozycja postaci [w kolejnej klatce]
	Vector previousPosition;															//poprzednia pozycja postaci
	Vector previousOrientation;															//poprzednia orientacja postaci

	IdxPair sectorIdx;																	//indeks sektora w kt�rym aktualnie znajduje si� posta�

public:
	Character():enable(false) {}
	Character(const std::string& filename);													//konstruktor podstawowy [nieokreslaj�cy dok�adnej pozycji i orientacji postaci]
	Character(const std::string& filename,const std::string& Name, const Vector& Position, const Vector& Orientation);	//konstruktor wczytuj�cy od razu nazw�, pozycj� i orientacj� postaci

	void Initialize(std::string Name, Vector Position, Vector Orientation);				//funkcja inicjalizuj�ca posta� [wczytuj�ca nazw�, po�o�enie i orientacj� postaci]

	void InitilizeTransformMatrix();													//inicjalizacja macierzy przekszta�ce�
	
	void InitilizeTransformedVertices();												//inicjalizacja wektora przekszta�conych wsp�rz�dnych wierzcho�k�w modelu

	void InitilizeTransformedNormals();

	void UpdateCollisionBoxVertices();													//aktualizacja pozycji wierzcho�k�w dla bry�y kolizji
	void UpdateCollisionBoxNormals();

	//funkcje ustwiaj�ce warto�ci dla odpowiednich p�l klay
	void SetNextPosition(Vector newPosition) { nextPosition = newPosition; }
	void SetPreviousPosition(Vector newPosition) { previousPosition = newPosition; }
	void SetPreviousOrientation(Vector newOrientation) { previousOrientation = newOrientation; }

	void setName(std::string newName) { name = newName; }					
	void setPosition(Vector newPosition) { position = newPosition; }
	void setOrientation(Vector newOrientation) { orientation = newOrientation; }

	void setPositionX(double newX) { position.x = newX; }
	void setPositionY(double newY) { position.y = newY; }
	void setPositionZ(double newZ) { position.z = newZ; }

	void setOrientationX(double newX) { orientation.x = newX; }
	void setOrientationY(double newY) { orientation.y = newY; }
	void setOrientationZ(double newZ) { orientation.z = newZ; }

	void SetHealth(unsigned newHealth) { health = newHealth; }

	//funkcje zwracaj�ce warto�ci odpowiednich p�l klasy
	std::string getName() const { return name; }
	Vector getPosition() const { return position; }
	Vector getOrientation() const { return orientation; }
	CollisionBox getCollisionBox() const { return collisionBox;}
	unsigned int getObjectsCount() const { return objects.size(); }
	unsigned int getObjectCollisionBoxCount(unsigned int objIdx) const {
		return objects[objIdx].collisionBox.size();		}
	CollisionBox getObjectCollisionBox(unsigned int objIdx, unsigned int colBoxIdx) const {
		return objects[objIdx].collisionBox[colBoxIdx];	}
	CollisionBox getObjectMainCollisionBox(unsigned int objIdx) const {
		return objects[objIdx].mainColBox;	}

	//funkcje ustawiaj�ce warto�ci odpowiednich p�l klasy
	Vector getVertice(unsigned int idx) const { return vertices[idx]; }
	Vector getTransformedVertice(unsigned int idx) const { return transformedVertices[idx]; }
	Vector getNormal(unsigned int idx) const { return normals[idx]; }
	Vector getTransformedNormal(unsigned int idx) const { return transformedNormals[idx]; }
	Face getFace(unsigned int idx) const { return faces[idx]; }
	Matrix getTransformMatrix() const { return transform; }

	Vector GetNextPosition() const { return nextPosition; }
	Vector GetPreviousPosition() const { return previousPosition; }
	Vector GetPreviousOrientation() const { return previousOrientation; }
	IdxPair GetSectorIdx() const { return sectorIdx; }

	unsigned GetHealth() const { return health; }

	//w��czanie i wy��cznie postaci
	void enableCharacter() { enable = true; }
	void disableCharacter() { enable = false; }

	//sprawdzanie czy posta� jest uruchomiona
	bool IsEnabled() const { return enable; }

	//opeacje na punktach �ycia postaci
	void AddHealth(unsigned healthVal) { health += healthVal; }
	void SubstractHealth(unsigned healthVal) { 
		if (healthVal > health)
			health = 0;
		else health -= healthVal;
	}

	virtual void Update() {}
};