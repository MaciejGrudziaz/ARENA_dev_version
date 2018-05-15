#pragma once
#include <windowsx.h>
#include "WinAPIwindow.h"
#include "LOGFILE.h"
#include "WINAPI_INPUT.h"
#include "GAMEINPUT_CONSTANTS.h"
#include "TIMER.h"

//------------------------------------------------------------------
//--------------------OBS£UGA KOMUNIKATÓW WINAPI--------------------
//----klasa obs³uguj¹ca komunikaty pochodz¹ce z aplikacji WinAPI----
//----------------[mo¿e byæ u¿yta do obs³ugi wejœcia]---------------
//------------------------------------------------------------------



typedef void(*RefreshGameLogicInitializationFunPtr)();
class WinAPImessages :public WINAPI_INPUT {
	WinAPImessages() {}

	static RefreshGameLogicInitializationFunPtr RefreshGameLogicInitialization;

	static int ChangeWindowSize();									//funkcja pomocnicza u¿ywana przy zmianie trybu wyœwietlania [pe³noekranowy/okienkowy]

	static void WriteTimeMeasurmentstoFile();

	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	//g³owna funkcja przetwarzaj¹ca komunikaty WinAPI
	//static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void SetGameLogicRefreshFun(RefreshGameLogicInitializationFunPtr fun) { RefreshGameLogicInitialization = fun; }
};