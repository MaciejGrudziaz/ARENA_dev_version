#include "WinAPImessages.h"

RefreshGameLogicInitializationFunPtr WinAPImessages::RefreshGameLogicInitialization = nullptr;

//g�owna funkcja przetwarzania komunikat�w WinAPI
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//instrukcja switch sprawdzaj�ca dany komunikat z aplikacji

	switch (message) {
	case WM_CREATE: {
		WinAPIwindow::CreateGraphicContext(hwnd);				//stworzenie kontekst�w grafiki aplikacji WinAPI
		LOGFILE::OpenAllFiles();
		SetCursorPos(0,0);
		return 0;
	}
	case WM_DESTROY: {
		LOGFILE::CloseAllFiles();
		WinAPIwindow::ReleaseGraphicContext();					//zwolnienie kontekstu grafiki aplikacji przez WinAPI
		return 0;
	}
	//zamkni�cie okna
	case WM_CLOSE: {
		LOGFILE::CloseAllFiles();
		WinAPIwindow::ReleaseGraphicContext();					//zwolnienie kontekstu grafiki aplikacji przez WinAPI
		PostQuitMessage(0);										//wys�anie wiadomo�ci o zako�czeniu dzia�ania aplikacji
		return 0;
	}
	//zmiana rozmiaru okna
	case WM_SIZE: {
		WinAPIwindow::screenHeight = HIWORD(lParam);			//pobranie w�a�ciwych wymiar�w okna
		WinAPIwindow::screenWidth = LOWORD(lParam);
		WinAPIwindow::SetupOpenGLScreenSettings();				//ustawienie w�a�ciwo�ci okna OpenGL
		return 0;
	}
	//wci�ni�cie przycisku
	case WM_KEYDOWN: {
		//ESC
		if (wParam == VK_ESCAPE) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_ESC] = 1;
			//--------------------------------------------------------------ZAPIS WARTO�CI FPS SESJI DO PLIKU----------------------------------------
			WinAPImessages::WriteTimeMeasurmentstoFile();
			LOGFILE::CloseAllFiles();
			PostQuitMessage(0);									//wys�anie wiadomo�ci o zako�czeniu dzia�ania aplikacji
			return 0;
		}
		//TAB
		if (wParam == VK_TAB) {
			if (!WinAPImessages::keyPressed[INPUTCONST::WIN_TAB]) WinAPImessages::ChangeWindowSize();
			WinAPImessages::keyPressed[INPUTCONST::WIN_TAB] = 1;
			return 0;
		}
		//TYLDA
		if (wParam == VK_OEM_3) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_tylda] = 1;
			return 0;
		}
		// 1
		if (wParam == 0x31) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_1] = 1;
			return 0;
		}
		// 2
		if (wParam == 0x32) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_2] = 1;
			return 0;
		}
		return 0;
	}
	//puszczenie przycisku
	case WM_KEYUP: {
		//ESC
		if (wParam == VK_ESCAPE) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_ESC] = 0;
			return 0;
		}
		//TAB
		if (wParam == VK_TAB) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_TAB] = 0;
			return 0;
		}
		//TYLDA
		if (wParam == VK_OEM_3) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_tylda] = 0;
			return 0;
		}
		// 1
		if (wParam == 0x31) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_1] = 0;
			return 0;
		}
		// 2
		if (wParam == 0x32) {
			WinAPImessages::keyPressed[INPUTCONST::WIN_2] = 0;
			return 0;
		}
		return 0;
	}
	
	case WM_MOUSEMOVE:{
		WinAPImessages::mousePos.x = GET_X_LPARAM(lParam);
		WinAPImessages::mousePos.y = GET_Y_LPARAM(lParam);

		SetCursorPos(0, 0);

		return 0;
	}

	default:
		break;
	}

	return (DefWindowProc(hwnd, message, wParam, lParam));
}

//funkcja zmieniaj�ca tryb wy�wietlania okna [pe�noekranowy/okienkowy]
int WinAPImessages::ChangeWindowSize() {
	//zmiana parametr�w wielko�ci okna w zale�no�ci od obecnej warto�ci
	if (WinAPIwindow::fullscreen) {
		WinAPIwindow::fullscreen = false;
		WinAPIwindow::screenWidth = windowscreenWidth;
		WinAPIwindow::screenHeight = windowscreenHeight;

	}
	else {
		WinAPIwindow::fullscreen = true;
		WinAPIwindow::screenWidth = fullscreenWidth;
		WinAPIwindow::screenHeight = fullscreenHeight;
	}

	DestroyWindow(WinAPIwindow::hwnd);							//zniszczenie poprzedniego okna aplikacji

	if (!WinAPIwindow::CreateNewWindow())						//stworzenie okna aplikacji WinAPI
		return 0;

	WinAPIwindow::ShowWinAPIwindow();							//wy�wietlenie okna apliakcji WinAPI

	RefreshGameLogicInitialization();				//od�wie�enie inicjalizacji logiki gry

	return 1;
}

//-------------------------------------------------------------------

void WinAPImessages::WriteTimeMeasurmentstoFile() {
	std::vector<unsigned long> fps;
	fps = TIMER::GetAllTimeMeasurments("FPS");

	for (unsigned int i = 0; i < fps.size(); i++) {
		LOGFILE::WriteToLogFile("FPS", std::to_string(fps[i]));
	}
}