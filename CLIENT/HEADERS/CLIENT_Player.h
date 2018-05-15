#pragma once
#include "GrudiEngine.h"

typedef std::shared_ptr<Weapon> WeaponPtr;

class Player : public DynamicCharacter {														//klasa dziedziczy po obiekcie postaci [elementy niestatyczne w grze]
	WeaponPtr weapon;

public:
	//konstruktory
	Player(const std::string& filename);
	Player(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation);

	void AddWeapon(const std::string& weaponName);												//dodanie broni dla postaci gracza

	WeaponPtr GetWeapon() { return weapon; }

	void UpdatePosition();
	void UpdateOrientation();
	void Update();

	void DrawModel();
};
