#include "GAMElogic.h"

//funkcja inicjalizuj�ca logik� gry
void GAMElogic::InitializeGameLogic() {
	InitializeInputModule();
	GrudiEngine::Init();
	InitializeConsoleInput();

	GAMEINPUT::Init();
	WinAPImessages::SetGameLogicRefreshFun(&GAMElogic::RefreshGameLogicInitialization);
	WinAPIwindow::SetMainProcessFun(&ModulesAdmin::Process);
	InitilizeTimers();															//inicjalizacja timer�w
	InitilizeLogFiles();														//inicjalziacja plik�w log�w
	InitializeOpenGLProperties();												//inicjalziacja podstawowych w�a�ciwo�ci okna OpenGL
	GraphicsMODULE::InitializeLights();		
	GraphicsMODULE::InitializeMaterials();
	WeaponDatabase::Initialize();												//inicjalizacja bazy danych broni

	CONSOLE::Initialize();														//inicjalizacja 'konsoli' gry
	GUI::Initialize();
}

//ponowana inicjalizacja logiki gry [wykonywana w razie 'zniszczenia' okna gry]
//[u�y� w przypadku zmiany uchwytu HWND okna WinAPI]
void GAMElogic::RefreshGameLogicInitialization() {
	GAMEINPUT::Shutdown();											//zwolnienie aktualnego systemu wej�cia [zale�nego od uchwytu okna]
	GAMEINPUT::Init();											//inicjalizacja systemu wej�cia

	InitializeOpenGLProperties();												//inicjalizacja podstawowych wa��ciwo�ci okna OpenGL

	GraphicsMODULE::InitializeLights();
	GraphicsMODULE::InitializeMaterials();
												
	CONSOLE::Initialize();														//inicjalizacja 'konsoli' gry
	GUI::Initialize();
}

//inicjalizacja podstawowych w��sciwo�ci okna OpenGL
void GAMElogic::InitializeOpenGLProperties() {
	glClearColor((float)105 / 255, (float)159 / 255, (float)250 / 255, 1);		//niebieskie t�o
	glColor3f((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8);						//kolor modeli podstawowych (bez tekstur)
	glShadeModel(GL_SMOOTH);													//�agodne cieniowanie na modelach
	glEnable(GL_LIGHTING);														//w��czenie o�wietlenia sceny
	glEnable(GL_DEPTH_TEST);													//nierysowanie przes�oni�tych powierzchni
	glEnable(GL_POLYGON_SMOOTH);												//wyg�adzanie powierzchni
	glEnable(GL_CULL_FACE);														//nierysowanie 'tylnich' powierzchni
}

//inicjalizacja plik�w log�w
void GAMElogic::InitilizeLogFiles() {
	LOGFILE::CreateLogFile("FPS", "FRAME_TIME_MEASURMENT.txt");				//inicjalizacja pliku zapisuj�cego czas trwania pojdeynczej klatki gry
	LOGFILE::ClearLogFile("FPS");											//wyczyszcenie pliku
	//LOGFILE::CreateLogFile("SHOOT_TEST", "SHOOT_TEST.txt");
	//LOGFILE::ClearLogFile("SHOOT_TEST");
	//LOGFILE::CreateLogFile("SYNC_TEST", "PHYSICS_SYNC_TEST.txt");
	//LOGFILE::ClearLogFile("SYNC_TEST");
	//LOGFILE::CreateLogFile("MOUSE_TEST", "MOUSE_TEST.txt");
	//LOGFILE::ClearLogFile("MOUSE_TEST");
	//LOGFILE::CreateLogFile("BOT_HIT_TEST","BOT_HIT_TEST.txt");
	//LOGFILE::ClearLogFile("BOT_HIT_TEST");
}

//inicjalizacja timer�w
void GAMElogic::InitilizeTimers() {
	TIMER::GetFrequency();														//pobranie cz�stotliwo�ci performance countera
	TIMER::AddTimeMarker("FPS");												//dodanie zancznika timera dla pomiaru czasu trwwania jednej klatki
	TIMER::AddTimeMarker("Input");
	TIMER::AddTimeMarker("Physics");
	TIMER::AddTimeMarker("Graphics");
}

void GAMElogic::InitializeInputModule() {
	ActionsMODULE::RegisterInputModule(new ConsoleInput("Console"));
	PhysicsMODULE::RegisterAdditionalActionsModules(CONSOLE::GetActionsModule());
	ActionsMODULE::RegisterInputModule(new PlayerInput("PlayerInput"));
	ActionsMODULE::SetCurrentInputModule("PlayerInput");
}
