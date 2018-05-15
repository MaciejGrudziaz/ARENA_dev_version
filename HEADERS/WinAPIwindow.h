#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//definicja rozmiar�w okna dla wybranych tryb�w wy�wietlania
const unsigned int fullscreenWidth = 1920;
const unsigned int fullscreenHeight = 1080;
const unsigned int windowscreenWidth = 1280;
const unsigned int windowscreenHeight = 720;

//-------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------OKNO APLIKACJI WINAPI-----------------------------------------------                                                                                              
//-----[klasa przechowuj�ca struktury okre�laj�ce dan� instancj� okna oraz metody umo�liwij�ce jego stworzenie]------
//-------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

typedef void (*ModulesAdminProcessFunPtr)();

class WinAPIwindow {
	WinAPIwindow() {}
	WinAPIwindow(const WinAPIwindow&) {}
	WinAPIwindow& operator= (const WinAPIwindow&) {}

	static void initializeWindowClassEx();							//iniclaizacja klasy okna WinAPI
	static DWORD getWindowStyle();									//okre�lenie podstawowych sty��w okna WinAPI w zale�no�ci od trybu wy�wietlania [pe�noekranowy/okienkowy]
	static DWORD getWindowExStyle();								//okre�lenie dodatkowych styl�w okna WinAPI w zale�no�ci od trybu wy�wietlania [pe�noekranowy/okienkowy]
	static int createWindowEx();									//stworzenie okna WinAPI w zale�no�ci od trybu wy�wietlania [pe�noekranowy/okienkowy]
	static void SetupFullscreenSettings();							//ustawianie w�a�ciwo�ci okna dla trybu pe�noekranowego
	static void SetupPixelFormat();									//funkcja okre�laj�ca foramt pikseli dla OpenGL

	static ModulesAdminProcessFunPtr Process;

public:
	static WNDCLASSEX windowClass;									//klasa okna Windows
	static HWND hwnd;												//uchwyt okna WinAPI
	static MSG msg;													//komunikat pochodz�cy z aplikacji WinAPI
	static HDC hDC;													//kontekst urz�dzenia [u�ywany do tworzenia grafiki w oknie]
	static HGLRC hRC;												//kontekst grafiki OpenGL
	static HINSTANCE hInstance;										//obecna instancja okna aplikacji
	static double FOV;												//obecna warto�� FOV

	static bool fullscreen;											//tryb pe�noekranowy
	static int screenWidth;											//szeroko�� i wysoko�� ekranu
	static int screenHeight;

	static int SetupWindowSettings(HINSTANCE hInstance);			//stworzenie ca�ego okna WinAPI [klasa okna, uchwyt, kontekst urz�dzenia]
	static int CreateNewWindow();									//stworzenie nowego okna [stworzenie samego nowego uchwytu i kontekstu urz�dzenia bez nowej klasy]
	static int CreateGraphicContext(HWND hwnd);						//utworzenie kontekst�w grafiki dla okna WinAPI
	static void ReleaseGraphicContext();							//funkcja s�u��ca do zwolnienia kontekstu grafiki OpenGL dla kontekstu urz�dzenia WinAPI
	static void ShowWinAPIwindow();									//funkcja wy�witalj�ca okno apliakcji WinAPI
	static void MessageProcessing();								//przetwarzanie komunikat�w okna WinAPI
	static int SetupOpenGLScreenSettings();							//funkcja ustawiaj�ca dane opcje dla ekranu apliakcji OpenGL
	
	static void SetMainProcessFun(ModulesAdminProcessFunPtr funPtr) { Process = funPtr; }

	static void WinAPImainLoop();									//g��wna p�tla aplikacji okna WinAPI
};
