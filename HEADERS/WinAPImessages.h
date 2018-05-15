#pragma once
#include <windowsx.h>
#include "WinAPIwindow.h"
#include "LOGFILE.h"
#include "WINAPI_INPUT.h"
#include "GAMEINPUT_CONSTANTS.h"
#include "TIMER.h"

//------------------------------------------------------------------
//--------------------OBS�UGA KOMUNIKAT�W WINAPI--------------------
//----klasa obs�uguj�ca komunikaty pochodz�ce z aplikacji WinAPI----
//----------------[mo�e by� u�yta do obs�ugi wej�cia]---------------
//------------------------------------------------------------------



typedef void(*RefreshGameLogicInitializationFunPtr)();
class WinAPImessages :public WINAPI_INPUT {
	WinAPImessages() {}

	static RefreshGameLogicInitializationFunPtr RefreshGameLogicInitialization;

	static int ChangeWindowSize();									//funkcja pomocnicza u�ywana przy zmianie trybu wy�wietlania [pe�noekranowy/okienkowy]

	static void WriteTimeMeasurmentstoFile();

	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	//g�owna funkcja przetwarzaj�ca komunikaty WinAPI
	//static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void SetGameLogicRefreshFun(RefreshGameLogicInitializationFunPtr fun) { RefreshGameLogicInitialization = fun; }
};