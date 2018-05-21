#pragma once
#include "CharacterRegister.h"
#include "WinAPIheaders.h"
#include "FONT.h"

//----------------------------------FUNKCJE KONSOLI----------------------------------
//----------definicja funkcji u�ywanych w konsoli jako sta�ych numerycznych----------

namespace {
	//const int ShowTerminal_FUNC = 0x01;
	//const int FPS_FUNC = 0x02;
	//const int CollisionBox_FUNC = 0x04;
	//const int InputProccesTime_FUNC = 0x08;
	//const int PhysicsProccesTime_FUNC = 0x10;
	//const int GraphicsProccesTime_FUNC = 0x20;
	//const int Timer_FUNC = 0x40;
	//const int PlayerPos_FUNC = 0x80;

	const unsigned fontSize = 12;
	const int ConsoleDepthVal = -1;
	const int TerminalLinesBufferCapacity = 100;
	const Vector terminalSize_garbage = { 500,264,0 };

	const Vector CONSOLE_white(1.0, 1.0, 1.0);
	const Vector CONSOLE_green(0.0, 1.0, 0.0);
	const Vector CONSOLE_red(1.0, 0.0, 0.0);
	const Vector CONSOLE_yellow(1.0, 1.0, 0.0);

	enum alignment { LEFT, RIGHT };
}
//----------------------------------------------------------------------------------------------------------------
//--------------------------------------------------KONSOLA GRY---------------------------------------------------
//----------konsola u�ywana do wprowadzania komend przez gracza oraz do wy�wietlania danych na temat gry----------
//----------------------------------------------------------------------------------------------------------------



class CONSOLE {
public:
	struct ScreenParameters {
		//punkt (0,0) dla ekranu znajduje si� na �rdoku okna
		ScreenParameters() :terminalSize(Vector()), terminalPixelSize(Vector()), textScreenWidth(0), textScreenHeight(0), textScreenRatio(0), /*textScreenAdjust(0),*/ terminalScreenFontHeight(0) {}
		Vector terminalSize;															//wielko�� terminala w OpenGL [zale�na od wsp�rz�dnej po�o�enia z oraz wielko�ci 'terminalPixelSize']
		Vector terminalPixelSize;														//wielko�� terminala w pikselach [const]
		double textScreenWidth;															//PO�OWA szeroko�ci ekranu
		double textScreenHeight;														//PO�OWA wysoko�ci ekranu
		double textScreenRatio;															//stosunek rozdzielczo�ci ekranu [szeroko��/wysoko��]
		//double textScreenAdjust;														//r�nica pomi�dzy wysoko�ci� 't�a' terminalu, a wielko�ci� tekstu
		double terminalScreenFontHeight;												//wielko�� czcionki w uk�adzie OpenGL
		unsigned terminalFontSize;														//wielko�� czcionki w pikselach
	};

	struct TerminalTextStruct {
		enum Source { USER, SYSTEM };
		std::string line;
		Source source;
		TerminalTextStruct() :source(SYSTEM), line("") {}
		TerminalTextStruct(std::string line_, Source source_) :line(line_), source(source_) {}
	};

private:
	CONSOLE() {}
	CONSOLE(const CONSOLE&) {}
	CONSOLE& operator=(const CONSOLE&) {}

	static bool status;

	static Actions actions;

	static FONT consoleFont;																//czcionka u�ywana do wypisywania danych

	//static unsigned int enabledFunc;														//zmienna okre�laj�ca kt�re funkcje konsoli s� w��czone [wart. domyslna = 0]

	//static Vector terminalSize;																//wielko�� terminala w OpenGL [zale�na od wsp�rz�dnej po�o�enia z oraz wielko�ci 'terminalPixelSize']
	//static Vector terminalPixelSize;														//wielko�� terminala w pikselach [const]

	//static std::string terminalCommand;													//komenda wpisana do terminala [tekst zatweirdzony przyciskiem enter]	
	static std::string currentTerminalText;

	static std::vector<TerminalTextStruct> terminalTextLines;

	static ScreenParameters params;

	//parametry opisuj�ce wymiary ekranu w OpenGL
	//static double textScreenWidth;															//PO�OWA szeroko�ci ekranu
	//static double textScreenHeight;															//PO�OWA wysoko�ci ekranu
	//static double textScreenRatio;															//stosunek rozdzielczo�ci ekranu [szeroko��/wysoko��]
	//static double textScreenAdjust;															//r�nica pomi�dzy wysoko�ci� 't�a' terminalu, a wielko�ci� tekstu
	//static double screenFontHeight;
	
	static unsigned maxTerminaTextSize;
	static unsigned maxTerminalLinesCount;

	//static unsigned long timer;																//mierzona warto�� czasu przez funkcj� 'ShowTimer'

	//static std::vector<unsigned> FPSval;

	//static void CheckCommand();																//sprawdzenie wprowadzonej komendy do terminala

	static void ShowConsoleTerminal();														//wy�wietlenie terminalu konsoli
	static void DrawTerminalBackground();													//narysowanie 't�a' terminalu konsoli
	static Vector GetTerminalBackgroundPosition();											//pobranie pozycji 't�a' terminalu konsoli
	static void TerminalText();																//wy�wietlenie tekstu w terminalu
	static Vector GetTerminalTextPosition(unsigned line);												//pobranie pozycji tekstu w terminalu

	//static void ShowFPS();																	//wy�wietlenie aktualnej liczby FPS
	//static unsigned int GetFPS();															//pobranie aktulanej warto�ci FPS

	//static void DrawCollisionBoxes();														//wy�wietalnie bry� kolizji postaci [klasy 'Character' i 'Player']

	//static void ShowInputProccessTime();													//wy�wietlenie czasu wykonywania operacji pobrania sygna��w wej�ciwoych
	//static void ShowPhysicsProcessTime();													//wy�wietlenie czasu wykonania operacji obliczenia 'fizyki' gry
	//static void ShowGraphicsProccessTime();													//wy�wietlenie czasu wykonania operacji wy�wietlenia grafiki

	//static void ShowTimer();																//wy�wietlanie pomiaru czasu
	//static void GetTimerVal(char* buffer);													//zapis warto�ci zmierzonego czasu do bufora
	//static void ResetTimer();																//zresetowanie timera

	//static void ShowPlayerPos();

	//static bool IsFuncEnabled(int func) { return (enabledFunc & func); }					//sprawdzenie czy dana funkcja jest 'w��czona'
	//static void EnableFunc(int func) { enabledFunc |= func; }								//w��czenie funkcji
	//static void DisableFunc(int func) { enabledFunc &= ~func; }								//wy��czenie funkcji

	static void CountTextScreenParams();											//obliczenie parametr�w opisuj�cych wymiary okna OpenGL

	//static Vector GetTextScreenPosition(alignment alin, unsigned int line);
	//static void WriteTextOnScreen(Vector position, std::string buffer, Vector color, const FONT& font_=consoleFont);

public:
	static void Initialize();																//inicjalizacja konsoli

	static void ShowConsoleOutput();														//wy�wietlenie aktywnych 'funkcji' konsoli

	static Actions* GetActionsModule() { return &actions; }

	static void ShowTerminal() { status = true; }						//w��czenie terminala

	static void HideTerminal() { status = false; }						//wy��czenie terminala

	static unsigned int GetTerminalStatus() { return status; }	//sprawdzenie stanu terminala

	static void Insert(char a);													//wczytanie znaku do terminala

	ScreenParameters GetScreenParameters() { return params; }

	static void AddTerminalTextLine(std::string line, TerminalTextStruct::Source source_);

	static void WriteTextOnScreen(Vector position, std::string buffer, Vector color, const FONT& font_ = consoleFont);

	static double GetScreenFontHeight(unsigned fontSize);

	static void SetCurrentTerminalText(std::string line) { currentTerminalText = line; }

	static unsigned GetTerminalTextLinesSize() { return terminalTextLines.size(); }

	static TerminalTextStruct GetTerminalText(unsigned idx) {
		if (idx >= terminalTextLines.size()) {
			if (terminalTextLines.size() > 0) idx = terminalTextLines.size() - 1;
			else return TerminalTextStruct("", TerminalTextStruct::USER);
		}
		return terminalTextLines[idx];
	}
};