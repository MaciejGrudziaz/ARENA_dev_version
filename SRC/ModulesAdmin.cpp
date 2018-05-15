#include <ModulesAdmin.h>

double ModulesAdmin::lastFrameTime = 0.0;
double ModulesAdmin::frameResidue = 0.0;

void ModulesAdmin::Process() {
	TIMER::QuickStartTimeMeasurment(0);

	lastFrameTime = TIMER::GetTime("FPS");																		//pobranie czasu trwania ostatniej klatki
	unsigned physicsIterations = static_cast<unsigned>(lastFrameTime / PHYSICSCONST::targetFrameTime);			//obliczenie ilo�ci iteracji oblicze� fizyki do wykonania w tej klatce
	frameResidue += (lastFrameTime - static_cast<double>(physicsIterations)*PHYSICSCONST::targetFrameTime);	//obliczenie 'pozosta�o�ci' z czasu po wykonaniu oblicze� fizyki
	if (frameResidue > PHYSICSCONST::targetFrameTime) {														//je�li 'pozosta�o�ci' czasu sumuj� si� do domy�. czasu trwania jednej klatki
		physicsIterations++;																					//dodaj jeszcze jedn� iteracje fizyki
		frameResidue -= PHYSICSCONST::targetFrameTime;															//aktualizuj 'pozosta�o�ci' czasu oblicze� fizycznych
	}

	for (unsigned i = 0; i < physicsIterations; i++) {															//wykonanie iteracji obliczen fizyki
		TIMER::StartTimeMeasurment("Input");
		ActionsMODULE::Process();																		//przetworzenie sygna��w wej�ciowych
		TIMER::StopTimeMeasurment("Input");

		communicationManager::Instance().DispatchPackets();

		TIMER::StartTimeMeasurment("Physics");
		PhysicsMODULE::Process();
		TIMER::StopTimeMeasurment("Physics");
	}

	TIMER::StartTimeMeasurment("Graphics");
	GraphicsMODULE::ProccessGraphics();																//przetworzenie grafiki
	TIMER::StopTimeMeasurment("Graphics");

	TIMER::QuickStopTimeMeasurment(0);
}