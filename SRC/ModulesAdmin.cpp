#include <ModulesAdmin.h>

double ModulesAdmin::lastFrameTime = 0.0;
double ModulesAdmin::frameResidue = 0.0;

void ModulesAdmin::Process() {
	TIMER::QuickStartTimeMeasurment(0);

	lastFrameTime = TIMER::GetTime("FPS");																		//pobranie czasu trwania ostatniej klatki
	unsigned physicsIterations = static_cast<unsigned>(lastFrameTime / PHYSICSCONST::targetFrameTime);			//obliczenie iloœci iteracji obliczeñ fizyki do wykonania w tej klatce
	frameResidue += (lastFrameTime - static_cast<double>(physicsIterations)*PHYSICSCONST::targetFrameTime);	//obliczenie 'pozosta³oœci' z czasu po wykonaniu obliczeñ fizyki
	if (frameResidue > PHYSICSCONST::targetFrameTime) {														//jeœli 'pozosta³oœci' czasu sumuj¹ siê do domyœ. czasu trwania jednej klatki
		physicsIterations++;																					//dodaj jeszcze jedn¹ iteracje fizyki
		frameResidue -= PHYSICSCONST::targetFrameTime;															//aktualizuj 'pozosta³oœci' czasu obliczeñ fizycznych
	}

	for (unsigned i = 0; i < physicsIterations; i++) {															//wykonanie iteracji obliczen fizyki
		TIMER::StartTimeMeasurment("Input");
		ActionsMODULE::Process();																		//przetworzenie sygna³ów wejœciowych
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