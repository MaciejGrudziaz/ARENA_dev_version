#pragma once
#include "DynamicCharacter.h"
#include "WeaponDatabase.h"

//----------------------------------------------------------------------------------------------
//------------------------------KLASA PODSTAWOWA DLA OBIEKTU BRONI------------------------------
//--------------------------------------[klasa wirtualna]---------------------------------------
//----------------------------------------------------------------------------------------------

class Weapon:public DynamicCharacter {
protected:
	std::string parentName;																						//nazwa obiektu rodzica broni

	Vector parentMidPoint;																						//punkt �rodkowy obiektu rodzica

public:
	Weapon(const std::string name) :DynamicCharacter(WeaponDatabase::GetWeaponStats(name).filename) {}			
	Weapon(const std::string name, const std::string& _parentName, const Vector& _parentMidPoint, const Vector& parentPos, const Vector& parentOrient):
		DynamicCharacter(WeaponDatabase::GetWeaponStats(name).filename, name, parentPos, parentOrient), parentName(_parentName), parentMidPoint(_parentMidPoint) {}

	//virtual void PerformAdditionalAction(ActionPtr Action) = 0;													
};