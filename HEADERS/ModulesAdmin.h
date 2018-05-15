#pragma once
#include "ActionsMODULE.h"
#include "PhysicsMODULE.h"
#include "GraphicsMODULE.h"

class ModulesAdmin {
	ModulesAdmin() { }
	ModulesAdmin(const ModulesAdmin&) {}
	ModulesAdmin& operator=(const ModulesAdmin&) {}

	static double lastFrameTime;																		//czas wykonania ostatniej klatki gry
	static double frameResidue;

public:

	static void Process();
};