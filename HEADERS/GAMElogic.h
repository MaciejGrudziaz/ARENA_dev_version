#pragma once
#include "ModulesAdmin.h"
#include "ConsoleInput.h"
#include "ConsoleBasicFunctions.h"
#include "ActionsModuleActions.h"
#include "LOGFILE.h"

//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------G£ÓWNA LOGIKA GRY--------------------------------------------------
//--------------------------------------klasa odpowiadaj¹ca za g³ówn¹ logikê gry---------------------------------------
//-----w klasie tej definiuje siê mapy [obiekty statyczne], postacie [obiekty dynamiczne], kamerê oraz oœwietlenie-----
//---------------------------------------------------------------------------------------------------------------------

namespace GrudiEngine {
	void Init();
}

class GAMElogic {
	GAMElogic();
	GAMElogic(const GAMElogic&);
	GAMElogic& operator=(const GAMElogic&) {}

	static void InitializeOpenGLProperties();						//inicjalizacja podstawowych w³aœciwoœci okna OpenGL
	static void InitilizeLogFiles();								//inicjalizacja plików logów
	static void InitilizeTimers();									//inicjalizacja timerów

	static void InitializeInputModule();
	static void InitializeConsoleInput() { static_cast<ConsoleInput*>(ActionsMODULE::GetInputModule("Console"))->Init(); }
	static void InitializeConsoleBasicFunctions() { ConsoleBasicFunctions::Init(); }

public:
	static void InitializeGameLogic();								//inicjalziacja logiki gry

	static void RefreshGameLogicInitialization();					//ponowna inicjalizacja logiki gry [wykonywana w razie 'zniszczenia' okna gry]
};
