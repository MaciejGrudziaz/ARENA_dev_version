#pragma once
#include "GUI.h"
#include "Camera.h"
#include "CONSOLE.h"
#include "Light.h"

//------------------------------------------------------------------------------------------
//--------------------------------PRZETWARZANIE GRAFIKI GRY---------------------------------
//------------------------------klasa obs³uguj¹ca grafikê gry:------------------------------
//----------------------------------WYŒWIETLANIE MODELI 3D----------------------------------
//------------------------------------USTAWIENIA KAMERY-------------------------------------
//------------------------------------------------------------------------------------------

class GraphicsMODULE {
	GraphicsMODULE(){}												//prywatny konstruktor domyœlny - singleton
	GraphicsMODULE(const GraphicsMODULE&) {}
	GraphicsMODULE& operator=(const GraphicsMODULE&) {}

	static void DrawMaps();											//rysowanie wszystkich obiektów klasy Map

	static void DrawCharacters();									//rysowanie wszystkich obiektów klasy Character

	static void DrawPlayers();										//rysowanie wszystkich obiektów klasy Player

	static void DrawBots();

	static void SetCameraPosition();								//ustalenie odpowiedniej pozycji

	static void SetCameraOrientation();								//ustalenie odpowiedniej orientacji kamery

	static void SetCamera();										//wszystkie ustawienia kamery

	static void ShowConsoleOutput();								//wyœwietlenie danych wyjœciowych z 'konsoli'

	static void ShowGUI();

	static std::vector<Light*> lights;
	static std::vector<std::pair<GLenum,GLenum> > materials;
public:

	static void ProccessGraphics();									//przetwarzanie grafiki

	static void RegisterLight(Light& light) { lights.push_back(&light); }
	static void RegisterMatrial(GLenum face_, GLenum material_) { materials.push_back(std::pair<GLenum,GLenum>(face_,material_)); }
	static void InitializeLights();
	static void InitializeMaterials();
};