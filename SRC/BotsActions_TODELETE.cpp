//#include "BotsActions.h"

/*//obliczenie nowych zachowa� bot�w ['MainLogic()']
void BotsActions::CalculateNewMoves() {
	for (unsigned i = 0; i < CharacterRegister::GetBotCount(); i++) {													//dla wszystkich zarejestrowanych bot�w
		Bot* bot = CharacterRegister::GetBot(i);																		//pobranie wska�nika na obiekt bota
		if (bot->IsEnabled())																							//je�li jest odblokowany
			bot->MainLogic();																							//wykonaj g��wn� logik� bota
	}
}

//wykonanie wszystkich oczekuj�cych akcji bot�w
void BotsActions::PerformAllActions() {
	for(unsigned i=0;i<CharacterRegister::GetBotCount();i++){															//dla wszystkich zarejestroanych bot�w
		Bot* bot = CharacterRegister::GetBot(i);																		//pobranie wska�nika na obiekt bota
		if (bot->IsEnabled())																							//je�li jest odblokowany
			bot->PerformAllActions();																					//wykonaj wszystkie oczekuj�ce akcje bota
	}
}

//aktualizacja bry� kolizji bot�w
void BotsActions::UpdateCollisionBox() {
	for(unsigned i=0;i<CharacterRegister::GetBotCount();i++){															//dla wszystkich zarejestrowanych bot�w
		Bot* bot = CharacterRegister::GetBot(i);																		//pobranie wska�nika na obiekt bota

		Vector pos, prevPos, orient, prevOrient;
		pos = bot->getPosition();																						//wczytanie obecnej pozycji bota
		prevPos = bot->GetPreviousPosition();																			//wczytanie poprzedniej pozycji bota
		orient = bot->getOrientation();																					//wczytanie orientacji bota
		prevOrient = bot->GetPreviousOrientation();																		//wczytanie poprzedniej orientacji bota

		if (pos != prevPos || orient != prevOrient) {																	//je�li poz. lub orient. bota nie zgadzaj� si� z poprzedni� poz. lub orient.
			bot->UpdateTransformMatrix();																				//aktualizuj macierz przekszta�cenia bota
			bot->UpdateCollisionBoxVertices();																			//aktualizuj wsp�rz�dne wierzcho�k�w bry� kolizji bota
			bot->UpdateCollisionBoxNormals();																			//aktualizuj normalne bry� kolizji bota
		}
	}
}

//wykonanie ca�ej logiki bot�w
void BotsActions::PerformBotLogic() {
	CalculateNewMoves();																								//obliczenie nowych zachowa� bot�w
	PerformAllActions();																								//wykonanie wszystkich oczekuj�cych akcji
	UpdateCollisionBox();																								//aktulizacja bry� kolizji
}*/