#pragma once
#include "CharacterRegister.h"
#include "WinAPIheaders.h"
#include "FONT.h"

//----------------------------------FUNKCJE KONSOLI----------------------------------
//----------definicja funkcji u¿ywanych w konsoli jako sta³ych numerycznych----------

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
//----------konsola u¿ywana do wprowadzania komend przez gracza oraz do wyœwietlania danych na temat gry----------
//----------------------------------------------------------------------------------------------------------------



class CONSOLE {
public:
	struct ScreenParameters {
		//punkt (0,0) dla ekranu znajduje siê na œrdoku okna
		ScreenParameters() :terminalSize(Vector()), terminalPixelSize(Vector()), textScreenWidth(0), textScreenHeight(0), textScreenRatio(0), /*textScreenAdjust(0),*/ terminalScreenFontHeight(0) {}
		Vector terminalSize;															//wielkoœæ terminala w OpenGL [zale¿na od wspó³rzêdnej po³o¿enia z oraz wielkoœci 'terminalPixelSize']
		Vector terminalPixelSize;														//wielkoœæ terminala w pikselach [const]
		double textScreenWidth;															//PO£OWA szerokoœci ekranu
		double textScreenHeight;														//PO£OWA wysokoœci ekranu
		double textScreenRatio;															//stosunek rozdzielczoœci ekranu [szerokoœæ/wysokoœæ]
		//double textScreenAdjust;														//ró¿nica pomiêdzy wysokoœci¹ 't³a' terminalu, a wielkoœci¹ tekstu
		double terminalScreenFontHeight;												//wielkoœæ czcionki w uk³adzie OpenGL
		unsigned terminalFontSize;														//wielkoœæ czcionki w pikselach
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

	static FONT consoleFont;																//czcionka u¿ywana do wypisywania danych

	//static unsigned int enabledFunc;														//zmienna okreœlaj¹ca które funkcje konsoli s¹ w³¹czone [wart. domyslna = 0]

	//static Vector terminalSize;																//wielkoœæ terminala w OpenGL [zale¿na od wspó³rzêdnej po³o¿enia z oraz wielkoœci 'terminalPixelSize']
	//static Vector terminalPixelSize;														//wielkoœæ terminala w pikselach [const]

	//static std::string terminalCommand;													//komenda wpisana do terminala [tekst zatweirdzony przyciskiem enter]	
	static std::string currentTerminalText;

	static std::vector<TerminalTextStruct> terminalTextLines;

	static ScreenParameters params;

	//parametry opisuj¹ce wymiary ekranu w OpenGL
	//static double textScreenWidth;															//PO£OWA szerokoœci ekranu
	//static double textScreenHeight;															//PO£OWA wysokoœci ekranu
	//static double textScreenRatio;															//stosunek rozdzielczoœci ekranu [szerokoœæ/wysokoœæ]
	//static double textScreenAdjust;															//ró¿nica pomiêdzy wysokoœci¹ 't³a' terminalu, a wielkoœci¹ tekstu
	//static double screenFontHeight;
	
	static unsigned maxTerminaTextSize;
	static unsigned maxTerminalLinesCount;

	//static unsigned long timer;																//mierzona wartoœæ czasu przez funkcjê 'ShowTimer'

	//static std::vector<unsigned> FPSval;

	//static void CheckCommand();																//sprawdzenie wprowadzonej komendy do terminala

	static void ShowConsoleTerminal();														//wyœwietlenie terminalu konsoli
	static void DrawTerminalBackground();													//narysowanie 't³a' terminalu konsoli
	static Vector GetTerminalBackgroundPosition();											//pobranie pozycji 't³a' terminalu konsoli
	static void TerminalText();																//wyœwietlenie tekstu w terminalu
	static Vector GetTerminalTextPosition(unsigned line);												//pobranie pozycji tekstu w terminalu

	//static void ShowFPS();																	//wyœwietlenie aktualnej liczby FPS
	//static unsigned int GetFPS();															//pobranie aktulanej wartoœci FPS

	//static void DrawCollisionBoxes();														//wyœwietalnie bry³ kolizji postaci [klasy 'Character' i 'Player']

	//static void ShowInputProccessTime();													//wyœwietlenie czasu wykonywania operacji pobrania sygna³ów wejœciwoych
	//static void ShowPhysicsProcessTime();													//wyœwietlenie czasu wykonania operacji obliczenia 'fizyki' gry
	//static void ShowGraphicsProccessTime();													//wyœwietlenie czasu wykonania operacji wyœwietlenia grafiki

	//static void ShowTimer();																//wyœwietlanie pomiaru czasu
	//static void GetTimerVal(char* buffer);													//zapis wartoœci zmierzonego czasu do bufora
	//static void ResetTimer();																//zresetowanie timera

	//static void ShowPlayerPos();

	//static bool IsFuncEnabled(int func) { return (enabledFunc & func); }					//sprawdzenie czy dana funkcja jest 'w³¹czona'
	//static void EnableFunc(int func) { enabledFunc |= func; }								//w³¹czenie funkcji
	//static void DisableFunc(int func) { enabledFunc &= ~func; }								//wy³¹czenie funkcji

	static void CountTextScreenParams();											//obliczenie parametrów opisuj¹cych wymiary okna OpenGL

	//static Vector GetTextScreenPosition(alignment alin, unsigned int line);
	//static void WriteTextOnScreen(Vector position, std::string buffer, Vector color, const FONT& font_=consoleFont);

public:
	static void Initialize();																//inicjalizacja konsoli

	static void ShowConsoleOutput();														//wyœwietlenie aktywnych 'funkcji' konsoli

	static Actions* GetActionsModule() { return &actions; }

	static void ShowTerminal() { status = true; }						//w³¹czenie terminala

	static void HideTerminal() { status = false; }						//wy³¹czenie terminala

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