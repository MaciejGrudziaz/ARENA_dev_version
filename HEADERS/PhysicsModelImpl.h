#pragma once
#include "GameObjects.h"
#include "ActionsImpl.h"

//--------------------------------------------------------------------------------------------
//------------------------------KLASA WZORCOWA DLA MODELU FIZYKI------------------------------
//-------------------------------------[klasa wirtualna]--------------------------------------
//--------------------------------------------------------------------------------------------

class PhysicsModelImpl {
protected:
	DynamicCharacter* character;
	CommunicationManager* commManager;
	Actions* actions;

public:
	PhysicsModelImpl() :character(nullptr) {}

	virtual void Process() = 0;													//funkcja przetwarzaj¹ca model [czysto wirtualna - musi byæ zdefiniowana w ka¿dym modelu]

	void RegisterCharacter(DynamicCharacter* character_) { character = character_; }
	void RegisterCommManager(CommunicationManager* commManager_) { commManager = commManager_; }
	void RegisterActionsModule(Actions* actionsModule) { actions = actionsModule; }

	virtual ~PhysicsModelImpl() {}
};