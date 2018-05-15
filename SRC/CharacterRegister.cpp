#include "CharacterRegister.h"

Map* CharacterRegister::map=NULL;
DynamicCharacter* CharacterRegister::player=NULL;
std::vector<Character*> CharacterRegister::staticCharacterVec;
std::vector<DynamicCharacter*> CharacterRegister::dynamicCharacterVec;
std::vector<Bot*> CharacterRegister::botVec;

std::map<DynamicCharacter*,Actions> CharacterRegister::dynamicCharacterActions;

//rejestracja nowego obiektu statycznego
void CharacterRegister::RegisterStaticCharacter(Character* _character) {
	bool checkForChar = false;																							//zmienna sprawdzaj�ca czy dany obiekt zosta� ju� dodany do rejestru

	for (Character* _char : staticCharacterVec) 
		if (_char == _character) {																						//je�li dany obiekt ju� istnieje w rejestrze
			checkForChar = true;																						//potwierd� jego znalezienie																									
			break;
		}

	if (!checkForChar)																									//je�li nie znaleziono danego obiektu w rejestrze
		staticCharacterVec.push_back(_character);																		//dodaj jego wska�nik do rejestru
}


void CharacterRegister::RegisterDynamicCharacter(DynamicCharacter* _character) {
	bool checkForChar = false;																							//zmienna sprawdzaj�ca czy dany obiekt zosta� ju� dodany do rejestru

	for (DynamicCharacter* _char : dynamicCharacterVec)
		if (_char == _character) {																						//je�li dany obiekt ju� istnieje w rejestrze
			checkForChar = true;																						//potwierd� jego znalezienie
			break;
		}

	if (!checkForChar) {																									//je�li nie zanleziono danego obiektu w rejestrze
		dynamicCharacterVec.push_back(_character);																		//dodaj jego wska�nik do rejestru
		dynamicCharacterActions.insert(DynamiCharacterActionsMap::value_type(_character, Actions()));
	}
}

void CharacterRegister::RegisterBot(Bot* _bot) {
	bool checkForBot = false;

	for (Bot* bot : botVec)
		if (bot == _bot) {
			checkForBot = true;
			break;
		}

	if (!checkForBot) {
		botVec.push_back(_bot);
		dynamicCharacterActions.insert(DynamiCharacterActionsMap::value_type(_bot, Actions()));
	}
}

//usuni�cie wybranego obiektu statycznego z rejestru
void CharacterRegister::UnregisterStaticCharacter(Character* character) {
	for (auto it = staticCharacterVec.begin(); it != staticCharacterVec.end(); it++) {
		if (*it == character) {																							//je�li odnaleziono dany obiekt w rejestrze
			staticCharacterVec.erase(it);																				//usu� go z rejestru
			break;
		}
	}
}

//usuni�cie wybranego obiektu dynamicznego z rejestru
void CharacterRegister::UnregisterDynamicCharacter(DynamicCharacter* character) {
	for (auto it = dynamicCharacterVec.begin(); it != dynamicCharacterVec.end(); it++) {
		if (*it == character) {																							//je�li znaleziono dany obiekt w rejestrze
			dynamicCharacterVec.erase(it);																				//usu� go z rejestru
			break;
		}
	}
}

void CharacterRegister::UnregisterBot(Bot* _bot) {
	for (auto it = botVec.begin(); it != botVec.end(); it++) {
		if (*it == _bot) {
			botVec.erase(it);
			break;
		}
	}
}

Actions* CharacterRegister::GetPlayerActionsModule() {
	DynamiCharacterActionsMap::iterator it = dynamicCharacterActions.find(player);
	if (it != dynamicCharacterActions.end())
		return &(*it).second;
	else return nullptr;
}

//pobranie wska�nika na wybrany obiekt statyczny z rejestru
Character* CharacterRegister::GetStaticCharacter(unsigned idx) {
	if (idx < staticCharacterVec.size())																				//je�li podany indeks znajduje si� w zakresie rejestru
		return staticCharacterVec[idx];																					//zwr�� wska�nik na poszukiwany obiekt
	else return NULL;																									//w przeciwnym wypadku zwr�c pusty wska�nik
}

//pobranie wska�nika na wybrany obiekt dynamiczny z rejestru
DynamicCharacter* CharacterRegister::GetDynamicCharacter(unsigned idx) {
	if (idx < dynamicCharacterVec.size())																				//je�li podany indeks znajduje si� w zakresie rejestru
		return dynamicCharacterVec[idx];																				//zwr�� wska�nik na poszukiwany obiekt
	else return NULL;																									//w przeciwnym wypadku zwr�c pusty wska�nik
}

Actions* CharacterRegister::GetDynamicCharacterActionsModule(DynamicCharacter* character_) {
	DynamiCharacterActionsMap::iterator it = dynamicCharacterActions.find(character_);
	if (it != dynamicCharacterActions.end())
		return &(*it).second;
	else return nullptr;
}

Bot* CharacterRegister::GetBot(unsigned idx) {
	if (idx < botVec.size())
		return botVec[idx];
	else return NULL;
}

Actions* CharacterRegister::GetBotActionsModule(Bot* bot_) {
	DynamiCharacterActionsMap::iterator it = dynamicCharacterActions.find(bot_);
	if (it != dynamicCharacterActions.end())
		return &(*it).second;
	else return nullptr;
}