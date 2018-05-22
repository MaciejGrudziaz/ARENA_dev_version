#pragma once
#include "ModulesAdmin.h"
#include "ConsoleInput.h"
#include "ConsoleBasicFunctions.h"
#include "ActionsModuleActions.h"
#include "LOGFILE.h"

//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------G��WNA LOGIKA GRY--------------------------------------------------
//--------------------------------------klasa odpowiadaj�ca za g��wn� logik� gry---------------------------------------
//-----w klasie tej definiuje si� mapy [obiekty statyczne], postacie [obiekty dynamiczne], kamer� oraz o�wietlenie-----
//---------------------------------------------------------------------------------------------------------------------

namespace GrudiEngine {
	void Init();
}

class GAMElogic {
	GAMElogic();
	GAMElogic(const GAMElogic&);
	GAMElogic& operator=(const GAMElogic&) {}

	static void InitializeOpenGLProperties();						//inicjalizacja podstawowych w�a�ciwo�ci okna OpenGL
	static void InitilizeLogFiles();								//inicjalizacja plik�w log�w
	static void InitilizeTimers();									//inicjalizacja timer�w

	static void InitializeInputModule();
	static void InitializeConsoleInput() { static_cast<ConsoleInput*>(ActionsMODULE::GetInputModule("Console"))->Init(); }
	static void InitializeConsoleBasicFunctions() { ConsoleBasicFunctions::Init(); }

public:
	static void InitializeGameLogic();								//inicjalziacja logiki gry

	static void RefreshGameLogicInitialization();					//ponowna inicjalizacja logiki gry [wykonywana w razie 'zniszczenia' okna gry]
};
