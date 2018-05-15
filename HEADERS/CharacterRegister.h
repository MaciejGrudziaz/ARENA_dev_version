#pragma once
#include "GameObjects.h"
#include "ActionsImpl.h"

//--------------------------------------------------------------------------------------------------
//------------------------------REJESTR WSZYSTKICH OBIEKTÓW ŒWIATA GRY------------------------------
//---------------------------------[postaæ gracza, mapa, boty itp.]---------------------------------
//--------------------------------------------------------------------------------------------------

class CharacterRegister {
	CharacterRegister() {}
	CharacterRegister(const CharacterRegister& charReg) {}
	CharacterRegister& operator=(const CharacterRegister& charReg) {}

	static Map* map;																									//wkaŸnik na aktualn¹ mapê
	static DynamicCharacter* player;																					//wskaŸnik na aktuln¹ postaæ gracza
	static std::vector<Character*> staticCharacterVec;																	//wektor wskaŸników na obiekty statyczne
	static std::vector<DynamicCharacter*> dynamicCharacterVec;															//wektor wskaŸników na obiekty dynamiczne
	static std::vector<Bot*> botVec;

	typedef std::map<DynamicCharacter*, Actions> DynamiCharacterActionsMap;

	static DynamiCharacterActionsMap dynamicCharacterActions;

public:
	static void RegisterMap(Map* _map) { map = _map; }																	//rejestracja nowej mapy
	static void RegisterPlayer(DynamicCharacter* _player) { player = _player; 
		dynamicCharacterActions.insert(DynamiCharacterActionsMap::value_type(_player, Actions())); }					//rejestracja nowego obiektu postaci gracza
	static void RegisterStaticCharacter(Character* _character);															//rejestracja nowego obiektu statycznego
	static void RegisterDynamicCharacter(DynamicCharacter* _character);													//rejestracja nowego obiektu dynamicznego
	static void RegisterBot(Bot* _bot);

	static void UnregisterMap() { map = NULL; }																			//usuniêcie mapy z rejestru
	static void UnregisterPlayer() { player = NULL; }																	//usuniêcie postaci gracza z rejestru
	static void UnregisterStaticCharacter(Character* _character);														//usuniêcie wybranego obiektu statycznego z rejestru
	static void UnregisterDynamicCharacter(DynamicCharacter* _character);												//usuniêcie wybranego obiektu dynamicznego z rejestru
	static void UnregisterBot(Bot* _bot);


	static Map* GetMap() { return map; }																				//pobranie wskaŸnika na aktualn¹ mapê																	
	static DynamicCharacter* GetPlayer() { return player; }																		//pobranie wskaŸnika na aktualny obiekt postaci gracza
	static Actions* GetPlayerActionsModule();
	static unsigned GetStaticCharacterCount() { return staticCharacterVec.size(); }										//pobranie liczby zarejestrowanych obiektów statycznych
	static unsigned GetDynamicCharacterCount() { return dynamicCharacterVec.size(); }									//pobranie liczby zarejestrowanych obiektów dynamicznych
	static unsigned GetBotCount() { return botVec.size(); }
	static Character* GetStaticCharacter(unsigned idx);																	//pobranie wskaŸnika na wybrany obiekt statyczny z rejestru
	static DynamicCharacter* GetDynamicCharacter(unsigned idx);															//pobranie wskaŸnika na wybrany obiekt dynamiczny z rejestru
	static Actions* GetDynamicCharacterActionsModule(DynamicCharacter* character_);
	static Bot* GetBot(unsigned idx);
	static Actions* GetBotActionsModule(Bot* bot_);
};
