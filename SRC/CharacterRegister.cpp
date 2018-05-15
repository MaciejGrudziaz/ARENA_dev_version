#include "CharacterRegister.h"

Map* CharacterRegister::map=NULL;
DynamicCharacter* CharacterRegister::player=NULL;
std::vector<Character*> CharacterRegister::staticCharacterVec;
std::vector<DynamicCharacter*> CharacterRegister::dynamicCharacterVec;
std::vector<Bot*> CharacterRegister::botVec;

std::map<DynamicCharacter*,Actions> CharacterRegister::dynamicCharacterActions;

//rejestracja nowego obiektu statycznego
void CharacterRegister::RegisterStaticCharacter(Character* _character) {
	bool checkForChar = false;																							//zmienna sprawdzajπca czy dany obiekt zosta≥ juø dodany do rejestru

	for (Character* _char : staticCharacterVec) 
		if (_char == _character) {																						//jeúli dany obiekt juø istnieje w rejestrze
			checkForChar = true;																						//potwierdü jego znalezienie																									
			break;
		}

	if (!checkForChar)																									//jeúli nie znaleziono danego obiektu w rejestrze
		staticCharacterVec.push_back(_character);																		//dodaj jego wskaünik do rejestru
}


void CharacterRegister::RegisterDynamicCharacter(DynamicCharacter* _character) {
	bool checkForChar = false;																							//zmienna sprawdzajπca czy dany obiekt zosta≥ juø dodany do rejestru

	for (DynamicCharacter* _char : dynamicCharacterVec)
		if (_char == _character) {																						//jeúli dany obiekt juø istnieje w rejestrze
			checkForChar = true;																						//potwierdü jego znalezienie
			break;
		}

	if (!checkForChar) {																									//jeúli nie zanleziono danego obiektu w rejestrze
		dynamicCharacterVec.push_back(_character);																		//dodaj jego wskaünik do rejestru
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

//usuniÍcie wybranego obiektu statycznego z rejestru
void CharacterRegister::UnregisterStaticCharacter(Character* character) {
	for (auto it = staticCharacterVec.begin(); it != staticCharacterVec.end(); it++) {
		if (*it == character) {																							//jeúli odnaleziono dany obiekt w rejestrze
			staticCharacterVec.erase(it);																				//usuÒ go z rejestru
			break;
		}
	}
}

//usuniÍcie wybranego obiektu dynamicznego z rejestru
void CharacterRegister::UnregisterDynamicCharacter(DynamicCharacter* character) {
	for (auto it = dynamicCharacterVec.begin(); it != dynamicCharacterVec.end(); it++) {
		if (*it == character) {																							//jeúli znaleziono dany obiekt w rejestrze
			dynamicCharacterVec.erase(it);																				//usuÒ go z rejestru
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

//pobranie wskaünika na wybrany obiekt statyczny z rejestru
Character* CharacterRegister::GetStaticCharacter(unsigned idx) {
	if (idx < staticCharacterVec.size())																				//jeúli podany indeks znajduje siÍ w zakresie rejestru
		return staticCharacterVec[idx];																					//zwrÛÊ wskaünik na poszukiwany obiekt
	else return NULL;																									//w przeciwnym wypadku zwrÛc pusty wskaünik
}

//pobranie wskaünika na wybrany obiekt dynamiczny z rejestru
DynamicCharacter* CharacterRegister::GetDynamicCharacter(unsigned idx) {
	if (idx < dynamicCharacterVec.size())																				//jeúli podany indeks znajduje siÍ w zakresie rejestru
		return dynamicCharacterVec[idx];																				//zwrÛÊ wskaünik na poszukiwany obiekt
	else return NULL;																									//w przeciwnym wypadku zwrÛc pusty wskaünik
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