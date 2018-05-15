#pragma once
#include "Vector.h"

//----------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------INPUT DLA WINAPI------------------------------------------------------
//------------------------------klasa interfejsu dla systemu wej�cia zdefiniwoanego przez WinAPI------------------------------
//----------------------------------------------------------------------------------------------------------------------------

class WINAPI_INPUT {
protected:
	static bool keyPressed[256];										//tablica przechowuj�ca warto�ci sygna��w wej�ciowych z klawiatury

	static POSITION mousePos;											//struktura przechowuj�ca aktualn� pozycj� kursora myszy [bezwzgl�dn�]

public:
	//funkcje zwracaj�ce stan sygna��w wej�ciowych z klawiatury
	static bool KeyDown(int key) { return keyPressed[key]; }
	static bool KeyUp(int key) { return !(keyPressed[key]); }

	//funkcja zwracaj�ca aktualn� pozycj� bezwzgl�dn� kursora myszy
	static POSITION GetMousePos() { return mousePos; }

};