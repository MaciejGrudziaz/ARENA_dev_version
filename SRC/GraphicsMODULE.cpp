#include "GraphicsMODULE.h"

std::vector<Light*> GraphicsMODULE::lights;
std::vector<std::pair<GLenum, GLenum> > GraphicsMODULE::materials;
std::vector<Camera*> GraphicsMODULE::cameras;
Camera* GraphicsMODULE::mainCamera = nullptr;
std::map<Camera*, Actions*> GraphicsMODULE::camerasActions;

//przetwarzanie grafiki
void GraphicsMODULE::ProccessGraphics() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//wyczyszcenie buforów koloru i g³êbi
	glLoadIdentity();															//zresetowanie macierzy widoku modelu

	UpdateCameras();
	SetCamera();																//ustawienie pozycji i oreintacji kamery

	DrawMaps();																	//narysowanie map [klasa Map]

	DrawCharacters();															//narysowanie postaci statycznych [klasa Character]

	DrawBots();

	DrawPlayers();																//narysowanie postaci sterowanych przez gracza [klasa Player]

	ShowGUI();

	ShowConsoleOutput();														//wyœwietlenie danych wyjœciowych z 'konsoli'

	glFlush();																	//opró¿nienie buforów grafiki OpenGL

	SwapBuffers(WinAPIwindow::hDC);												//zamiana buforów [p³ynniejsze wykonywanie grafiki]
}

void GraphicsMODULE::RegisterCamera(Camera* camera_) {
	cameras.push_back(camera_);
	camerasActions.insert(CamerasActionsMap::value_type(camera_, new Actions()));
}

void GraphicsMODULE::SetMainCamera(unsigned idx) {
	assert(idx < cameras.size());
	mainCamera = cameras[idx];
}

Camera* GraphicsMODULE::GetCamera(unsigned idx) {
	assert(idx < cameras.size());
	return cameras[idx];
}

Camera* GraphicsMODULE::GetCamera(std::string name) {
	for (Camera* camera : cameras) {
		if (strcmp(name.c_str(), camera->GetName().c_str()) == 0)
			return camera;
	}

	return nullptr;
}

Actions* GraphicsMODULE::GetCameraActionsModule(unsigned idx) {
	assert(idx < cameras.size());
	CamerasActionsMap::iterator it = camerasActions.find(cameras[idx]);
	assert(it != camerasActions.end());
	return (*it).second;
}

Actions* GraphicsMODULE::GetMainCameraActionsModule() {
	assert(mainCamera != nullptr);
	CamerasActionsMap::iterator it = camerasActions.find(mainCamera);
	assert(it != camerasActions.end());
	return (*it).second;
}

void GraphicsMODULE::InitializeLights() {
	for (unsigned i = 0; i < lights.size(); ++i) {
		lights[i]->Initialize();
		lights[i]->EnableLight();
	}
}

void GraphicsMODULE::InitializeMaterials() {
	glEnable(GL_COLOR_MATERIAL);

	for (std::pair<GLenum, GLenum>& materialPair : materials) 
		glColorMaterial(materialPair.first, materialPair.second);
	
}

//rysowanie wszystkich obiektów klasy Map
void GraphicsMODULE::DrawMaps() {
	if (CharacterRegister::GetMap()->IsEnabled())
		CharacterRegister::GetMap()->Draw();
}

//rysowanie wszystkich obiektów klasy Character
void GraphicsMODULE::DrawCharacters() {
	for (unsigned i = 0; i < CharacterRegister::GetStaticCharacterCount(); ++i)
		if (CharacterRegister::GetStaticCharacter(i)->IsEnabled())
			CharacterRegister::GetStaticCharacter(i)->DrawModel();

	for (unsigned i = 0; i < CharacterRegister::GetDynamicCharacterCount(); ++i)
		if (CharacterRegister::GetDynamicCharacter(i)->IsEnabled())
			CharacterRegister::GetDynamicCharacter(i)->DrawModel();
}

void GraphicsMODULE::DrawBots() {
	for (unsigned i = 0; i < CharacterRegister::GetBotCount(); ++i)
		if (CharacterRegister::GetBot(i)->IsEnabled())
			CharacterRegister::GetBot(i)->DrawModel();
}

//rysowanie wszystkich obiektów klasy Player
void GraphicsMODULE::DrawPlayers() {
	if (CharacterRegister::GetPlayer()->IsEnabled())
		CharacterRegister::GetPlayer()->DrawModel();
}

void GraphicsMODULE::UpdateCameras() {
	assert(cameras.size() != 0);
	if (mainCamera == nullptr)
		mainCamera = cameras[0];

	for (Camera* camera : cameras)
		camera->Update();
}

//wszystkie ustawienia kamery
void GraphicsMODULE::SetCamera() {
	mainCamera->SetCamera();
}

//wyœwietlenie danych wyjœciowych z 'konsoli'
void GraphicsMODULE::ShowConsoleOutput() {
	CONSOLE::ShowConsoleOutput();
}

void GraphicsMODULE::ShowGUI() {
	GUI::Show();
}