#define WIN32_LEAN_AND_MEAN		//'odchudzanie' aplikacji Windows
#include "Gamelogic.h"

//-----------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------FUNKCJA MAIN APLIKACJI WINAPI------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInsatnce, LPSTR lpCmdLine, int nShowCmd) {
	if (!WinAPIwindow::SetupWindowSettings(hInstance))		//stworzenie okna aplikacji WinAPI
		return 0;

	WinAPIwindow::ShowWinAPIwindow();						//wy�wietlenie okna apliakcji WinAPI

	GAMElogic::InitializeGameLogic();						//inicjalizacja logiki gry

	WinAPIwindow::WinAPImainLoop();							//g��wna p�tla aplikacji WinAPI

	return (WinAPIwindow::msg).wParam;
}