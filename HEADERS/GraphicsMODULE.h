#pragma once
#include "GUI.h"
#include "Camera.h"
#include "CONSOLE.h"
#include "Light.h"

//------------------------------------------------------------------------------------------
//--------------------------------PRZETWARZANIE GRAFIKI GRY---------------------------------
//------------------------------klasa obs�uguj�ca grafik� gry:------------------------------
//----------------------------------WY�WIETLANIE MODELI 3D----------------------------------
//------------------------------------USTAWIENIA KAMERY-------------------------------------
//------------------------------------------------------------------------------------------

class GraphicsMODULE {
	GraphicsMODULE(){}												//prywatny konstruktor domy�lny - singleton
	GraphicsMODULE(const GraphicsMODULE&) {}
	GraphicsMODULE& operator=(const GraphicsMODULE&) {}

	static void DrawMaps();											//rysowanie wszystkich obiekt�w klasy Map

	static void DrawCharacters();									//rysowanie wszystkich obiekt�w klasy Character

	static void DrawPlayers();										//rysowanie wszystkich obiekt�w klasy Player

	static void DrawBots();

	static void UpdateCameras();									//aktualizacja kamery

	static void SetCamera();										//ustawienie g��wnej kamery

	static void ShowConsoleOutput();								//wy�wietlenie danych wyj�ciowych z 'konsoli'

	static void ShowGUI();

	static std::vector<Light*> lights;
	static std::vector<std::pair<GLenum,GLenum> > materials;
	static std::vector<Camera*> cameras;
	static Camera* mainCamera;

	typedef std::map<Camera*, Actions*> CamerasActionsMap;
	static CamerasActionsMap camerasActions;
public:

	static void ProccessGraphics();									//przetwarzanie grafiki

	static void RegisterLight(Light& light) { lights.push_back(&light); }
	static void RegisterMaterial(GLenum face_, GLenum material_) { materials.push_back(std::pair<GLenum,GLenum>(face_,material_)); }
	static void RegisterCamera(Camera& camera_);
	static void SetMainCamera(unsigned idx);
	static Camera* GetMainCamera() { return mainCamera; }
	static Camera* GetCamera(unsigned idx);
	static Actions* GetCameraActionsModule(unsigned idx);
	static Actions* GetMainCameraActionsModule();
	static void InitializeLights();
	static void InitializeMaterials();
};