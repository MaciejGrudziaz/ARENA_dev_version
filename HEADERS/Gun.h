#pragma once
#include "Weapon.h"

//--------------------------------------------------------------------------------------
//------------------------------KLASA OPISUJ�CA BRO� PALN�------------------------------
//--------------------------------------------------------------------------------------

//struktura opisuj�ca pocisk
struct Bullet {
	std::string parentName;																							//nazwa obiektu rodzica kt�ry wystrzeli� pocisk
	bool hit;																										//zmienna sprawdzaj�ca czy pocisk uderzy� w obiekt
	double damage;																									//obra�enia zadawane przez pocisk
	double speed;																									//pr�dko�� pocisku

	Vector direction;																								//kierunek lotu pocisku
	Vector startPos;																								//pozycja startowa pocisku
	Vector hitPos;																									//pozycja dla kolizji pocisku
	Vector actualPos;																								//aktualna pozycja pocisku
	Vector previousPos;																								//poprzednia pozycja pocisku
	
	unsigned long lifetime;																							//czas �ycia pocisku

	Bullet() :parentName(""), damage(0), speed(0), direction(Vector(0, 0, 0)), startPos(Vector(0, 0, 0)), hitPos(startPos),lifetime(0),actualPos(startPos),previousPos(startPos),hit(false) {}
	Bullet(const std::string& _parentName, double _damage, double _speed, const Vector& _direction, const Vector& _startPos) :
		parentName(_parentName), damage(_damage), speed(_speed), direction(_direction), startPos(_startPos), hitPos(_startPos),lifetime(0),actualPos(startPos),previousPos(startPos),hit(false) {}
};

class Gun :public Weapon {
	std::string shotTimerName;																						//nazwa TIMERA dla odliczania czasu pomi�dzy wystrza�ami
	std::string reloadTimerName;

	unsigned ROF;																									//szybkostrzelno�� broni
	double shotTimeDif;																								//r�nica czasowa pomi�dzy strza�ami - sta�a [w mikrosekundach]
	double timeFromLastShot;																						//czas kt�ry up�yn�� od ostatniego strza�u [w mikrosekundach]
	double damage;																									//obra�enia zadawane przez bro�
	double bulletSpeed;																								//pr�dko�� pocisk�w
	unsigned magazineCapacity;																						//pojemno�� magazynka
	unsigned bulletsCount;																							//��czna liczba pocisk�w
	unsigned bulletsInMagLeft;																						//��czna liczba pocisk�w pozosta�ych w magazynku

	unsigned reloadState;
	unsigned long reloadTime;
	unsigned long actReloadTime;

	std::vector<Bullet> shotsFired;																					//wektor wystrzelonych pocik�w
	
public:

	Gun(const std::string& _name, const std::string& _parentName, const Vector& _parentMidPoint, const Vector& parentPos, const Vector& parentOrient);

	//void PerformAdditionalAction(ActionPtr Action);																	//dodatkowe akcje

	void Shoot();																									//funkcja wykonuj�ca strza� z broni

	void ClearAllBullets() { shotsFired.clear(); }																	//usuni�cie wszystkich pocisk�w z wektora 'shotsFired'

	void UpdateBullets();																							//aktualizacja stanu pocisk�w

	void DrawModel();																								//narysowanie modelu
	void DrawCrossHair();																							//narysowanie celownika

	//funkcej zwracaj�ce sk�adowe klasy
	unsigned GetShotsFiredCount() { return shotsFired.size(); }
	Bullet& GetBullet(unsigned idx) { return shotsFired[idx]; }
	unsigned GetBulletsLeftInMag() { return bulletsInMagLeft; }
	unsigned GetBulletsCount() { return bulletsCount; }
	unsigned GetReloadState() { return reloadState; }
	unsigned GetMagazineCapacity() { return magazineCapacity; }

	void SetBulletsLeftInMag(unsigned n) { bulletsInMagLeft = n; }
	void SetBulletsCount(unsigned n) { bulletsCount = n; }
	void SetReloadState(unsigned n) { 
		if (n > 100)
			reloadState = 100;
		else reloadState = n;
	}

	void AddBulletsToMag(unsigned n) { bulletsInMagLeft += n; }
	void AddBullets(unsigned n) { bulletsCount += n; }

	void Update();
};