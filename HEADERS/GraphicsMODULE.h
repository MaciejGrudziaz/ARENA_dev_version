#pragma once
#include "GUI.h"
#include "Camera.h"
#include "CONSOLE.h"
#include "Light.h"

//------------------------------------------------------------------------------------------
//--------------------------------PRZETWARZANIE GRAFIKI GRY---------------------------------
//------------------------------klasa obsługująca grafikę gry:------------------------------
//----------------------------------WYŚWIETLANIE MODELI 3D----------------------------------
//------------------------------------USTAWIENIA KAMERY-------------------------------------
//------------------------------------------------------------------------------------------

class GraphicsMODULE {
	GraphicsMODULE(){}												//prywatny konstruktor domyślny - singleton
	GraphicsMODULE(const GraphicsMODULE&) {}
	GraphicsMODULE& operator=(const GraphicsMODULE&) {}

	static void DrawMaps();											//rysowanie wszystkich obiektów klasy Map

	static void DrawCharacters();									//rysowanie wszystkich obiektów klasy Character

	static void DrawPlayers();										//rysowanie wszystkich obiektów klasy Player

	static void DrawBots();

	static void UpdateCameras();									//aktualizacja kamery

	static void SetCamera();										//ustawienie głównej kamery

	static void ShowConsoleOutput();								//wyświetlenie danych wyjściowych z 'konsoli'

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
	static void RegisterCamera(Camera* camera_);
	static void SetMainCamera(unsigned idx);
	static void SetMainCamera(Camera* camera_) { mainCamera = camera_; }
	static Camera* GetMainCamera() { return mainCamera; }
	static Camera* GetCamera(unsigned idx);
	static Camera* GetCamera(std::string name);
	static Actions* GetCameraActionsModule(unsigned idx);
	static Actions* GetMainCameraActionsModule();
	static void InitializeLights();
	static void InitializeMaterials();
};