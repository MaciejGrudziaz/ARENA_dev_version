#include "Bot.h"

//za�adowanie nowego obiektu kolizji do wektora niezbadanych status�w kolizji

void Bot::LoadLastColStatus(GAMEPHYSICS::CollisionStatus newLastCol) {
	if (newLastCol.groundCol.collisionOccured || newLastCol.mapBoundriesCol.collisionOccured ||
		newLastCol.negativeCol.collisionOccured || newLastCol.standardCol.collisionOccured)
		lastColStatus.push_back(newLastCol);																				//je�li zasz�a jakakolwiek kolizja - dodaj j� do wektora
}

//g��wna logika bota

void Bot::MainLogic() {
	RandomMoveAction();
}

//funkcja uaktualniaj�ca stan bota

void Bot::Update() {
	DynamicCharacter::Update();

	if (health <= 0) {
		health = 0;
		disableCharacter();
	}
}

//wykonanie akcji obrotu

void Bot::MakeTurnAction(double yAngle) {
	/*double t = PHYSICSMODULE::targetFrameTime/1000000.0;																	//standardowy czas trwania jednej klatki [w sek.]

	if (yAngle >= 0) {																										//je�li wykonujemy obr�t w prawo
		double turnVal = yAngle / (static_cast<double>(t)*turnSensitivity*360.0);											//oblicz wart. dla akcji obrotu o k�t 'yAngle'
		LOOK_ACTION turn(TURN_RIGHT, turnVal);																				//stworzenie nowej akcji obrotu
		AddAction(turn);																									//dodanie jej do wektora akcji
	}
	else {
		yAngle = -yAngle;																									//je�li wykonujemy obr�t w lewo
		double turnVal = yAngle / (static_cast<double>(t)*turnSensitivity*360.0);											//oblicz wart. dla akcji obrotu o k�t 'yAngle'
		LOOK_ACTION turn(TURN_LEFT, turnVal);																				//stworzenie nowej akcji obrotu
		AddAction(turn);																									//dodanie jej do wektora akcji
	}*/
}

//wykonanie akcji zmiany widoku

void Bot::MakeLookAction(double xAngle) {

}

//wykonanie losowego ruchu

void Bot::RandomMoveAction() {
	/*double t = PHYSICSMODULE::targetFrameTime;

	MOVE_ACTION newAction(MOVE_FORWARD);
	AddAction(newAction);																									//dodanie akcji ruchu do przodu

	if (lastColStatus.size() > 0 && makeTurn == 0) {																		//je�li zasz�a kolizja  i bot nie wykonywa� �adnego obrotu
		if (lastColStatus[0].standardCol.collisionOccured || lastColStatus[0].mapBoundriesCol.collisionOccured) {			//je�li zasz�a kolizja standardowa lub z granic� mapy
			makeTurn = rand() % 180;																						//wykonaj obr�t o maks. 180 stopni
			turnOrient = rand() % 2;																						//w losowym kierunku
		}
		lastColStatus.clear();																								//wyczy�� wektor niezbadanych kolizji
	}

	if (makeTurn > 0) {																										//je�li posta� nie sko�czy�a jeszcze obrotu
		if (turnOrient == 0) {																								//je�li wykonujemy obr�t w lewo
			MakeTurnAction(-1);																								//wykonaj obr�t o 1 stopie�
			makeTurn -= 1;																									//aktualizuj warto�� pozosta�� obrotu
			if (makeTurn < 0) makeTurn = 0.0;
		}
		else {																												//je�li wykonujemy obr�t w prawo
			MakeTurnAction(1);																								//wykonaj obr�t o 1 stopie�
			makeTurn -= 1;																									//aktualizuj warto�� pozosta�� obrotu
			if (makeTurn < 0) makeTurn = 0.0;
		}
	}*/
}