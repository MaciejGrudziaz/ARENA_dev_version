#pragma once
#include <vector>
#include "CLIENT_Player.h"

//--------------------------------------------------------------------------------------------------
//----------------------------------------OBIEKTY �WIATA GRY----------------------------------------
//----------klasa przechowuj�ca obiekty znajduj�ce si� w �wiecie gry (postacie, mapy itp.)----------
//--------------------------------------------------------------------------------------------------

class Map;

class GameObjects {
	GameObjects();											//klasa singletonowa [zablokowany konstruktor domy�lny]

public:
	static std::vector <Player*> players;					//wekotr przechowuj�cy wszytkie obiekty postaci sterowanych przez gracza

	static std::vector <Character> characters;				//wektor przechowuj�cy wszystkie pozosta�� obiekty �wiata gry

	static std::vector <Light> lights;						//wektor przechowuj�cy wszystkie �r�d�a �wiat�a w �wiecie gry

	static std::vector <Map> maps;

	static std::vector<Bot> bots;
};