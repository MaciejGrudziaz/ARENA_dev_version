#include "PhysicsMODULE.h"

double PhysicsMODULE::lastFrameTime = 0.0;
double PhysicsMODULE::frameResidue = 0.0;
std::vector<Actions*> PhysicsMODULE::additionalActionsModules;

void PhysicsMODULE::Process() {
	PerformActions();

	CharacterPhysicsModelsRegister::ProcessAllCharacterModels();

	CharacterPhysicsModelsRegister::DispatchAllModelsActions();

	PerformActions();

	UpdateCharacters();
}

//aktualizacja stanu postaci úwiata gry
void PhysicsMODULE::UpdateCharacters() {	
	Map* map = CharacterRegister::GetMap();																		//wskaünik na aktualny obiekt mapy
	
	//wywo≥anie metody Update [oraz 'SetSectorIdx' dla postaci dynamicznych] dla kaødej zarejestrowanej postaci
	for (unsigned i = 0; i < CharacterRegister::GetStaticCharacterCount(); i++)									
		if (CharacterRegister::GetStaticCharacter(i)->IsEnabled())
			CharacterRegister::GetStaticCharacter(i)->Update();

	for (unsigned i = 0; i < CharacterRegister::GetDynamicCharacterCount(); i++)
		if (CharacterRegister::GetDynamicCharacter(i)->IsEnabled()) {
			DynamicCharacter* charPtr = CharacterRegister::GetDynamicCharacter(i);
			charPtr->Update();
			charPtr->SetSectorIdx(map->GetSectorIdx(charPtr->getPosition()));
		}

	for (unsigned i = 0; i < CharacterRegister::GetBotCount(); i++)
		if (CharacterRegister::GetBot(i)->IsEnabled()) {
			Bot* botPtr = CharacterRegister::GetBot(i);
			botPtr->Update();
			botPtr->SetSectorIdx(map->GetSectorIdx(botPtr->getPosition()));
		}

	if (CharacterRegister::GetPlayer()->IsEnabled()) {
		DynamicCharacter* playerPtr = CharacterRegister::GetPlayer();
		playerPtr->Update();
		playerPtr->SetSectorIdx(map->GetSectorIdx(playerPtr->getPosition()));
	}
}

void PhysicsMODULE::PerformActions() {
	CharacterRegister::GetPlayerActionsModule()->PerformAllActions();

	for (unsigned i = 0; i < CharacterRegister::GetBotCount(); ++i)
		CharacterRegister::GetBotActionsModule(CharacterRegister::GetBot(i))->PerformAllActions();

	for (unsigned i = 0; i < CharacterRegister::GetDynamicCharacterCount(); ++i)
		CharacterRegister::GetDynamicCharacterActionsModule(CharacterRegister::GetDynamicCharacter(i))->PerformAllActions();

	for (Actions* module_ : additionalActionsModules) {
		module_->PerformAllActions();
	}
	
}