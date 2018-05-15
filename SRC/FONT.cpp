#include "FONT.h"

//inicjalizacja wybranej czcionki
void FONT::Initilize(char* fontName, unsigned int FontSize, HDC _hDC) {
	fontSize = FontSize;
	hDC = _hDC;

	if (listBase == 0)																	//je�li nie zosta�a zainicjalizowana �adna lista czcionek
		listBase = CreateBitmapFont(fontName, FontSize);								//stw�rz czcionk� o danej nazwie i rozmiarze
	else {
		glDeleteLists(listBase, 96);													//w przeciwnym wypadku - usu� istniej�ce listy

		listBase = CreateBitmapFont(fontName, FontSize);								//i stw�rz nowe
	}
}

//wypisanie stringa na ekranie
void FONT::PrintString(char* str) {
	if ((listBase == 0) || (str == NULL))												//sprawdzenie czy czionka istnieje i czy podany string istnieje
		return;

	glPushAttrib(GL_LIST_BIT);															//zachowanie atrybutu GL_LIST_BIT na stosie											
	glListBase(listBase - 32);															//wyznacza offset dla funkcji glCallLists do wygenerowania listy
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);									//wywo�anie list [ 'strlen(str)' - ilo�� list do wygenerowania, 'GL_UNSIGNED_BYTE' - rodzaj danych reprezontowanych 
																						//przez list�, 'str' - adres tablicy offset�w dla list do wygenerowania]
	glPopAttrib();																		//przywr�cenie atrybut�w zachowanych na stosie
}

//stworzenie i zarejestrowanie w systemie czcionki o danej nazwie i rozmiarze
unsigned int FONT::CreateBitmapFont(char* fontName, int fontSize) {
	HFONT hFont;																		//uchwyt dla czionki
	unsigned int base;																	//identyfiaktor listy bazowej dla czionki

	base = glGenLists(96);																//wygenerowanie 96 list wy�wietlania

	if (_stricmp(fontName, "symbol") == 0) {											//je�li jako nazw� czcionki podano nazw� 'symbol'
		hFont = CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,				//wczytaj zestaw znak�w SYMBOL_CHARSET
			SYMBOL_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			fontName);
	}
	else {
		hFont = CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,				//w przeciwnym wypadku wczytaj zestaw znak�w ANSI_CHARSET
			ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
			fontName);
	}

	if (!hFont)																			//je�li nie udao si� zarejestrowa� czcionki zwr�c warto�� identyfiakotra listy bazowej = 0
		return 0;
																						//je�li czcionka zosta�a zarejestrowana
	SelectObject(hDC, hFont);												//wybranie kontekstu urz�dzenia	
	wglUseFontBitmaps(hDC, 32, 96, base);									//przygotowanie czcionki do u�ycia w OpenGL

	return base;																		//zwr�cenie warto�ci identyfikatora listy bazowej dla stworzonej czcionki
}