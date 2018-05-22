#include "ConsoleBasicFunctions.h"

void ConsoleBasicFunctions::Init() {
	CONSOLE::RegisterConsoleFunction(new ShowFPS());
}