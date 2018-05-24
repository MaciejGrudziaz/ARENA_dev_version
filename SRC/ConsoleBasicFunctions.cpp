#include "ConsoleBasicFunctions.h"

void ConsoleBasicFunctions::Init() {
	CONSOLE::RegisterConsoleFunction(new ShowFPS());
	CONSOLE::RegisterConsoleFunction(new CameraMode(GraphicsMODULE::GetMainCamera(),"Camera"));
}