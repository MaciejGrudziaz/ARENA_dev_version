#pragma once
#include "GameObjects.h"
#include "ActionsImpl.h"

//--------------------------------------------------------------------------------------------------
//------------------------------REJESTR WSZYSTKICH OBIEKT�W �WIATA GRY------------------------------
//---------------------------------[posta� gracza, mapa, boty itp.]---------------------------------
//--------------------------------------------------------------------------------------------------

class CharacterRegister {
	CharacterRegister() {}
	CharacterRegister(const CharacterRegister& charReg) {}
	CharacterRegister& operator=(const CharacterRegister& charReg) {}

	static Map* map;																									//wka�nik na aktualn� map�
	static DynamicCharacter* player;																					//wska�nik na aktuln� posta� gracza
	static std::vector<Character*> staticCharacterVec;																	//wektor wska�nik�w na obiekty statyczne
	static std::vector<DynamicCharacter*> dynamicCharacterVec;															//wektor wska�nik�w na obiekty dynamiczne
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

	static void UnregisterMap() { map = NULL; }																			//usuni�cie mapy z rejestru
	static void UnregisterPlayer() { player = NULL; }																	//usuni�cie postaci gracza z rejestru
	static void UnregisterStaticCharacter(Character* _character);														//usuni�cie wybranego obiektu statycznego z rejestru
	static void UnregisterDynamicCharacter(DynamicCharacter* _character);												//usuni�cie wybranego obiektu dynamicznego z rejestru
	static void UnregisterBot(Bot* _bot);


	static Map* GetMap() { return map; }																				//pobranie wska�nika na aktualn� map�																	
	static DynamicCharacter* GetPlayer() { return player; }																		//pobranie wska�nika na aktualny obiekt postaci gracza
	static Actions* GetPlayerActionsModule();
	static unsigned GetStaticCharacterCount() { return staticCharacterVec.size(); }										//pobranie liczby zarejestrowanych obiekt�w statycznych
	static unsigned GetDynamicCharacterCount() { return dynamicCharacterVec.size(); }									//pobranie liczby zarejestrowanych obiekt�w dynamicznych
	static unsigned GetBotCount() { return botVec.size(); }
	static Character* GetStaticCharacter(unsigned idx);																	//pobranie wska�nika na wybrany obiekt statyczny z rejestru
	static DynamicCharacter* GetDynamicCharacter(unsigned idx);															//pobranie wska�nika na wybrany obiekt dynamiczny z rejestru
	static Actions* GetDynamicCharacterActionsModule(DynamicCharacter* character_);
	static Bot* GetBot(unsigned idx);
	static Actions* GetBotActionsModule(Bot* bot_);
};
