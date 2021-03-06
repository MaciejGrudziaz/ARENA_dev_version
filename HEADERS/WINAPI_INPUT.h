#pragma once
#include "Vector.h"

//----------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------INPUT DLA WINAPI------------------------------------------------------
//------------------------------klasa interfejsu dla systemu wejścia zdefiniwoanego przez WinAPI------------------------------
//----------------------------------------------------------------------------------------------------------------------------

class WINAPI_INPUT {
protected:
	static bool keyPressed[256];										//tablica przechowująca wartości sygnałów wejściowych z klawiatury

	static POSITION mousePos;											//struktura przechowująca aktualną pozycję kursora myszy [bezwzględną]

public:
	//funkcje zwracające stan sygnałów wejściowych z klawiatury
	static bool KeyDown(int key) { return keyPressed[key]; }
	static bool KeyUp(int key) { return !(keyPressed[key]); }

	//funkcja zwracająca aktualną pozycję bezwzględną kursora myszy
	static POSITION GetMousePos() { return mousePos; }

};