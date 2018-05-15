#pragma once
//#include "WinAPIwindow.h"
#include<Windows.h>
#include<gl\GL.h>

//-------------------------------------------------------------------------------------------------------------------
//----------------------------------------CZCIONKI WY�WIETLANE NA EKRANIE GRY----------------------------------------
//--------------------klasa odpowiadaj�ca za definicj� czcionki rastrowej wy�wietlanej na ekranie--------------------
//-------------------------------------------------------------------------------------------------------------------

class FONT {
	HDC hDC;																		//uchwyt aktualnego okna dla czcionki

	unsigned int fontSize;															//rozmiar czcionki

	unsigned int listBase;															//identyfikator listy bazowej dla czcionki

	unsigned int CreateBitmapFont(char* fontName, int fontSize);					//stworzenie i zarejestrowanie w systemie czcionki o danej nazwie i rozmiarze

public:
	FONT() { listBase = 0; fontSize = 0; }														//kosntruktor domy�lny [domy�lna warto�� listBase=0 - lista nie zosta�a stworzona]
	FONT(char* fontName, unsigned int FontSize):fontSize(FontSize) {									//konstruktor tworz�cy czcionk� o danej nazwie i rozmiarze
		listBase = CreateBitmapFont(fontName, FontSize);
	}
	~FONT() {																		//destruktor [usuwa wszystkie listy przechowuj�ce czcionki]
		if (listBase != 0)
			glDeleteLists(listBase, 96);											//zwolnienie wszystkich list wy�wietlania
	}

	void Initilize(char* fontName, unsigned int fontSize, HDC _hDC);				//inicjalizacja wybranej czcionki

	void PrintString(char* str);													//wypisanie stringa na ekranie

	unsigned int GetFontSize() { return fontSize; }
};