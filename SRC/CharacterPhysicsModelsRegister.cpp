#include "CharacterPhysicsModelsRegister.h"

std::map<DynamicCharacter*, CharacterPhysicsModels*> CharacterPhysicsModelsRegister::characterModels;

CharacterPhysicsModels* CharacterPhysicsModelsRegister::GetCharacterPhysicsModels(DynamicCharacter* character_) {
	CharacterModelsMap::iterator it = characterModels.find(character_);
	if (it != characterModels.end())
		return (*it).second;
	else return nullptr;
}

void CharacterPhysicsModelsRegister::ProcessAllCharacterModels() {
	for (CharacterModelsMap::iterator it = characterModels.begin(); it != characterModels.end(); ++it)
		(*it).second->ProcessModels();
}

void CharacterPhysicsModelsRegister::DispatchAllModelsActions() {
	for (CharacterModelsMap::iterator it = characterModels.begin(); it != characterModels.end(); ++it)
		(*it).second->DispatchActions();
}