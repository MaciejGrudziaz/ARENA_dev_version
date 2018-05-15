#include "GraphicsMODULE.h"

std::vector<Light*> GraphicsMODULE::lights;
std::vector<std::pair<GLenum, GLenum> > GraphicsMODULE::materials;

//przetwarzanie grafiki
void GraphicsMODULE::ProccessGraphics() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);							//wyczyszcenie buforów koloru i g³êbi
	glLoadIdentity();															//zresetowanie macierzy widoku modelu

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

//ustalenie odpowiedniej pozycji
void GraphicsMODULE::SetCameraPosition() {
	if (CharacterRegister::GetPlayer()->IsEnabled()){
		Vector position = CharacterRegister::GetPlayer()->getPosition();			//pobranie pozycji postaci
		Vector orientation = CharacterRegister::GetPlayer()->getOrientation();		//pobranie orienatcji postaci
		Vector relativePos = Camera::GetRelativePosition();					//pobranie pozycji kamery relatywnej do postaci

		double angle = orientation.y / 360.0 * 2.0 * 3.1415;				//k¹t obrotu postaci wokó³ osi y [w radianach; 2.0 * 3.1415 -> 2 * PI]
		position.x -= relativePos.z*sin(-angle);							//wartoœæ pozycji kamery w osi x w stosunku do pozycji postaci
		position.y += relativePos.y;										//wartoœæ pozycji kamery w osi y w stosunku do pozycji postaci
		position.z += relativePos.z*cos(-angle);							//wartoœæ pozycji kamery w osi z w stosunku do pozycji postaci

		Camera::SetPosition(position.x, position.y, position.z);			//ustawienie nowej pozycji kamery
	}
}

//ustalenie odpowiedniej orientacji kamery
void GraphicsMODULE::SetCameraOrientation() {
		Vector camCenter;														//pozycja punktu 'wycentrowania' kamery
		Vector camPos = Camera::GetPosition();									//pozycja kamery
		Vector relativePos = Camera::GetRelativePosition();						//pozycja 'wzglêdna' kamery
		Vector relativeCenter = Camera::GetRelativeCenter();					//relatywna pozycja punktu 'wycentrowania' kamery
		Vector camOrientation = Camera::GetOrientation();						//orientacja kamery

		if (CharacterRegister::GetPlayer()->IsEnabled()) {
			Vector playerOrient = CharacterRegister::GetPlayer()->getOrientation();
			camOrientation.y = playerOrient.y;
			camOrientation.x = CharacterRegister::GetPlayer()->GetLookAngle();
		}

		//przeliczenie orientacji kamery na radiany
		camOrientation.x = camOrientation.x / 360.0 * 2.0 *3.1415;
		camOrientation.y = camOrientation.y / 360.0 * 2.0 *3.1415;
		camOrientation.z = camOrientation.z / 360.0 * 2.0 *3.1415;
		
		//wyliczenie wspó³rzêdnych punktu 'wycentrowania' kamery ze wzoru:
		//y = R * sin( -camOrientation.x ), x = r * sin( camOrientation.y ), z = r * cos( camOrientation.y )
		//gdzie: R - odleg³oœæ od œrodka kamery do punktu 'wycentrowania', r - rzutowanie odleg³oœci R na p³aszczyznê (X,Z), obliczona zgodnie ze wzorem: r = sqrt( R^2 + y^2 )
		double R = sqrt((-relativePos.z + relativeCenter.z)*(-relativePos.z + relativeCenter.z) + relativePos.y*relativePos.y);

		camCenter.y = R*sin(-camOrientation.x);
			
		double r = sqrt(R*R + camCenter.y*camCenter.y);

		camCenter.x = camPos.x+r*sin(camOrientation.y);
		camCenter.y = camPos.y - camCenter.y;
		camCenter.z = camPos.z+r*cos(camOrientation.y);

		Camera::SetCenter(camCenter.x, camCenter.y, camCenter.z);				//ustawienie punktu 'wycentrowania' kamery
}

//wszystkie ustawienia kamery
void GraphicsMODULE::SetCamera() {
	SetCameraPosition();														//ustawienie odpwoiedniej pozycji kamery
	SetCameraOrientation();														//ustawienie odpwoiedniej orientacji kamery
	Camera::SetCamera();														//wprowadzenie nowych ustawieñ kamery do maszyny stanów OpenGL
}

//wyœwietlenie danych wyjœciowych z 'konsoli'
void GraphicsMODULE::ShowConsoleOutput() {
	CONSOLE::ShowConsoleOutput();
}

void GraphicsMODULE::ShowGUI() {
	GUI::Show();
}