#pragma once
#include "CharacterPhysicsModelsRegister.h"
#include "PhysicsModuleConst.h"
#include "TIMER.h"

//------------------------------------------------------------------------------------------------------
//------------------------------KLASA ODPOWIDAJ¥CA ZA WYKONANIE FIZYKI GRY------------------------------
//------------------------------------------------------------------------------------------------------

class PhysicsMODULE {
	PhysicsMODULE() {}
	PhysicsMODULE(const PhysicsMODULE& module) {}
	PhysicsMODULE& operator=(const PhysicsMODULE& module) {}

	static double lastFrameTime;																		//czas wykonania ostatniej klatki gry
	static double frameResidue;																			//'pozosta³oœæ' z ostatniej klatki gry

	static void UpdateCharacters();																		//aktualizacja stanu postaci œwiata gry

	static void PerformActions();

	static std::vector<Actions*> additionalActionsModules;

public:
	static void Process();

	static void RegisterAdditionalActionsModules(Actions* module_) { additionalActionsModules.push_back(module_); }
};