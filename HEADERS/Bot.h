#pragma once
#include "DynamicCharacter.h"

//--------------------------------------------------------------------------------------------
//-----------------------------------KLASA PROTOTYPOWA BOTA-----------------------------------
//--------------------------------------------------------------------------------------------


class Bot :public DynamicCharacter{
	std::vector<GAMEPHYSICS::CollisionStatus> lastColStatus;														//wektor ostatnich, niezbadanych status�w kolizji

	double makeTurn;																								//warto�� k�ta obrotu [makeTurn > 0 - pozosta�a warto�� obrotu do wykonania]
	unsigned turnOrient;																							//orientacja obrotu [LEWO, PRAWO]

	void MakeTurnAction(double yAngle);																				//wykonanie akcji obrotu
	void MakeLookAction(double xAngle);																				//wykonanie akcji zmainy widoku

	void RandomMoveAction();																						//wykonanie losowego ruchu

	CommunicationManager manager;

public:
	Bot(const std::string& filename) : DynamicCharacter(filename),makeTurn(0) {}
	Bot(const std::string& filename, const std::string& name, const Vector& position, const Vector& orientation) :
		DynamicCharacter(filename, name, position, orientation),makeTurn(0) {}

	//void PerformAdditionalAction(ActionPtr Action) {}																//dodatkowe akcje bota do wykonania [brak]

	void LoadLastColStatus(GAMEPHYSICS::CollisionStatus newLastCol);												//za�adowanie nowego obiektu kolizji do wektora niezbadanych status�w kolizji

	void MainLogic();																								//g��wna logika bota

	void Update();																									//funkcja uaktualniaj�ca stan bota
};
