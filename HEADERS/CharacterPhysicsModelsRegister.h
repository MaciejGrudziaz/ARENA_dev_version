#pragma once
#include "CharacterPhysicsModels.h"
#include "PhysicsModels.h"

class CharacterPhysicsModelsRegister {
	CharacterPhysicsModelsRegister() {}
	CharacterPhysicsModelsRegister(const CharacterPhysicsModelsRegister&) {}
	CharacterPhysicsModelsRegister& operator=(const CharacterPhysicsModelsRegister&) {}

	typedef std::map<DynamicCharacter*, CharacterPhysicsModels*> CharacterModelsMap;
	static CharacterModelsMap characterModels;

public:
	
	static void Register(DynamicCharacter* character_) {
		characterModels.insert(CharacterModelsMap::value_type(character_, new CharacterPhysicsModels(character_)));
	}

	static CharacterPhysicsModels* GetCharacterPhysicsModels(DynamicCharacter* character_);

	static void ProcessAllCharacterModels();

	static void DispatchAllModelsActions();

};