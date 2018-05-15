#pragma once
#include "CharacterRegister.h"
#include "PhysicsModelImpl.h"

class CharacterPhysicsModels {
	DynamicCharacter* character;
	Actions* actionsModule;
	std::vector<PhysicsModelImpl*> physicsModels;

	CommunicationManager commManager;

	void UpdateCollisionBox();
public:

	CharacterPhysicsModels() :character(nullptr),actionsModule(nullptr) {}
	CharacterPhysicsModels(DynamicCharacter* character_) :character(character_){
		actionsModule = CharacterRegister::GetDynamicCharacterActionsModule(character_);
	}
	void RegisterCharacter(DynamicCharacter* character_) { 
		character = character_; 
		actionsModule = CharacterRegister::GetDynamicCharacterActionsModule(character_);
	}

	void RegisterModel(PhysicsModelImpl* model) { 
			model->RegisterCharacter(character);
			model->RegisterCommManager(&commManager);
			model->RegisterActionsModule(actionsModule);
			physicsModels.push_back(model);
	}

	void ProcessModels();

	void DispatchActions() { commManager.DispatchPackets(); }

	~CharacterPhysicsModels();
};