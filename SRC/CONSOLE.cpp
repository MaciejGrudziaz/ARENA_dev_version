#include "CONSOLE.h"

//inicjalizacja statycznych sk�adowych klasy
bool CONSOLE::status;
CONSOLE::Prompt CONSOLE::prompt;
ConsoleFunVec CONSOLE::consoleFunVec;
LineAnalyzer CONSOLE::lineAnalyzer;
Actions CONSOLE::actions;
FONT CONSOLE::consoleFont;
std::string CONSOLE::currentTerminalText = "";
std::vector<CONSOLE::TerminalTextStruct> CONSOLE::terminalTextLines;
unsigned CONSOLE::maxTerminaTextSize=0;
unsigned CONSOLE::maxTerminalLinesCount=0;
CONSOLE::ScreenParameters CONSOLE::params;

//inicjalizacja konsoli
void CONSOLE::Initialize() {
	consoleFont.Initilize("Arial", fontSize, WinAPIwindow::hDC);										//inicjalizacja czionki ['Arial', rozmiar - 24]
	maxTerminaTextSize = ((int)params.terminalPixelSize.x / consoleFont.GetFontSize())*2 - 7;			//7 - 2 znaki, �eby wyr�wna� do pe�nej ramki, 2 znaki odst�pu od kraw�dzi ramki, 3 znaki dla znaku ">> "
	maxTerminalLinesCount = ((int)params.terminalPixelSize.y / consoleFont.GetFontSize()) - 2;			//2 - 1 znak odst�pu od dolnej kraw�dzi, 1 znak na lini� komend

	params.terminalFontSize = fontSize;
	params.terminalPixelSize = TerminalSize;
	CountTextScreenParams();												//obliczenie parametr�w opisuj�cych ekran OpenGL dla wy�wietlania tekstu
	params.textScreenDepth = ConsoleDepthVal;
}

//wy�wietlenie aktywnych 'funkcji' konsoli
void CONSOLE::ShowConsoleOutput() {
	if (status)
		ShowConsoleTerminal();

	consoleFunVec.DisplayAll();
}

//wczytanie znaku do terminala
void CONSOLE::Insert(char a) {
	if (a != 0x08 && a!=0x0A) {												//je�li nie wczytanu znku 'BACKSPACE' lub 'ENTER'
		if (currentTerminalText.size() < maxTerminaTextSize) {						//je�li nie przekroczono maksymalnego zakresu terminala
			//terminalText[terminalTextSize] = a;								//wczytaj nowy znak do terminala
			currentTerminalText.push_back(a);													
		}
		else {
			AddTerminalTextLine(currentTerminalText,TerminalTextStruct::USER);
		}
	}
	else {
		if (a == 0x08) {													//je�li wczytano znak 'BACKSPACE'
			if (currentTerminalText.size() > 0) {										//je�li istniej� znaki w terminalu
				//terminalText[terminalTextSize - 1] = 0x00;					//usu� ostatni znak
				currentTerminalText.pop_back();
			}
		} 
		if (a == 0x0A) {													//je�li wczytano znak 'ENTER'
			ExecuteCommand();
		}
	}
}

//sprawdzenie wprowadzonej komendy do terminala
/*void CONSOLE::CheckCommand() {
	if (terminalCommand == "show.fps=1")
		EnableFunc(FPS_FUNC);
	if (terminalCommand == "show.fps=0")
		DisableFunc(FPS_FUNC);
	if (terminalCommand == "show.colbox=1")
		EnableFunc(CollisionBox_FUNC);
	if (terminalCommand == "show.colbox=0")
		DisableFunc(CollisionBox_FUNC);
	if (terminalCommand == "show.input.time=1")
		EnableFunc(InputProccesTime_FUNC);
	if (terminalCommand == "show.input.time=0")
		DisableFunc(InputProccesTime_FUNC);
	if (terminalCommand == "show.physics.time=1")
		EnableFunc(PhysicsProccesTime_FUNC);
	if (terminalCommand == "show.physics.time=0")
		DisableFunc(PhysicsProccesTime_FUNC);
	if (terminalCommand == "show.graphics.time=1")
		EnableFunc(GraphicsProccesTime_FUNC);
	if (terminalCommand == "show.graphics.time=0")
		DisableFunc(GraphicsProccesTime_FUNC);
	if (terminalCommand == "show.timer=1")
		EnableFunc(Timer_FUNC);
	if (terminalCommand == "show.timer=0") {
		DisableFunc(Timer_FUNC);
		ResetTimer();
	}

	terminalCommand = "";
}*/

//wy�wietlenie terminalu konsoli
void CONSOLE::ShowConsoleTerminal() {						
	DrawTerminalBackground();												//wy�wietlenie 't�a' terminala

	TerminalText();															//wy�wietlenie tekstu w terminalu
}

//narysowanie 't�a' terminalu konsoli
void CONSOLE::DrawTerminalBackground() {
	Vector move=GetTerminalBackgroundPosition();							//pobranie pozycji 't�a' terminalu

	glPushMatrix();

	glLoadIdentity();

	glDisable(GL_LIGHTING);													//wy��czenie o�wietlenia sceny
	//funkcje pozwalaj�ce wy�wietla� przezroczyste obiekty
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);														
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4d(0.3, 0.3, 0.3, 0.3);											//kolor 't�a' terminala
	glTranslated(move.x, move.y, move.z);									//ustawienie pozycji terminala
	
	//narysowanie terminala
	glBegin(GL_POLYGON);
	glVertex3d(-params.terminalSize.x / 2.0, params.terminalSize.y / 2.0, 0.0);
	glVertex3d(-params.terminalSize.x / 2.0, -params.terminalSize.y / 2.0, 0.0);
	glVertex3d(params.terminalSize.x / 2.0, -params.terminalSize.y / 2.0, 0.0);
	glVertex3d(params.terminalSize.x / 2.0, params.terminalSize.y / 2.0, 0.0);
	glEnd();

	glColor3d(0.8, 0.8, 0.8);												//przywr�cenie standardowej kolorystyki 
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);													//w��czenie o�wietlenia sceny

	glPopMatrix();
}

//pobranie pozycji 't�a' terminalu konsoli
Vector CONSOLE::GetTerminalBackgroundPosition() {
	//ustawienie pozzycji x i z terminala
	Vector move(-(params.textScreenWidth - params.terminalSize.x / 2.0 - params.terminalScreenFontHeight), 0, ConsoleDepthVal);

	//ustalenie wielko�ci terminala w OpenGL ze wzgl�du na wielko�� terminalu w pikselach, rozdzielczo�� ekranu oraz wielko�� ekranu w OpenGL
	params.terminalSize.x = params.terminalPixelSize.x / (double)WinAPIwindow::screenWidth * 2 * params.textScreenWidth;
	params.terminalSize.y = params.terminalPixelSize.y / (double)WinAPIwindow::screenHeight * 2 * params.textScreenHeight;

		//ustalenie pozycji Y terminalu dla trybu pe�noekranowego
	move.y = params.textScreenHeight - params.terminalSize.y / 2.0 - params.terminalScreenFontHeight;


	return move;
}

//wy�wietlenie tekstu w terminalu
void CONSOLE::TerminalText() {
	Vector move = GetTerminalTextPosition(0);								//pobranie pozycji tekstu w terminalu
	prompt.Update();

	WriteTextOnScreen(move, ">> "+currentTerminalText+prompt.sign, CONSOLE_white);

	unsigned terminalTextLinesCount = terminalTextLines.size();
	unsigned linesToDisplay = maxTerminalLinesCount;
	if (terminalTextLinesCount < maxTerminalLinesCount) linesToDisplay = terminalTextLinesCount;
	for (unsigned i = 1; i < linesToDisplay +1; ++i) {
		move= GetTerminalTextPosition(i);
		WriteTextOnScreen(move, terminalTextLines[terminalTextLinesCount-i].line, CONSOLE_white);
	}
}

//pobranie pozycji tekstu w terminalu
Vector CONSOLE::GetTerminalTextPosition(unsigned line) {
	Vector terminalMove = GetTerminalBackgroundPosition();

	Vector move(-(params.textScreenWidth - 2.0*params.terminalScreenFontHeight), 0, ConsoleDepthVal);			//ustalenie pozycji X i Z tekstu
		//ustalenie pozycji Y na podstawie wielko�ci ekranu oraz terminala w OpenGL
		move.y = params.textScreenHeight - params.terminalSize.y + line*params.terminalScreenFontHeight;
		//ustalenie pozycji Y tekstu dla trybu okienkowego

	return move;
}

//wy�wietlenie aktualnej liczby FPS
/*void CONSOLE::ShowFPS() {
	char buffer[10];														//bufor s�u�acy do wy�wietlenia aktualnej ilo�ci FPS
	Vector color;

	unsigned fps = GetFPS();
	
	_itoa_s(fps, buffer, 10);												//pobranie aktualnej liczby FPS, przekonwertowanie jej do tablicy zankowej char i zapisanie w buforze

	if (fps >= 60) color = CONSOLE_green;
	else if (fps >= 30) color = CONSOLE_yellow;
	else color = CONSOLE_red;

	Vector move = GetTextScreenPosition(RIGHT, 1);

	WriteTextOnScreen(move, buffer,color);
}*/

//pobranie aktulanej warto�ci FPS
/*unsigned int CONSOLE::GetFPS() {
	unsigned long t = TIMER::GetTime("FPS");								//pobranie czasu trwania poprzedniej kaltki z odpowiedniego Timera

	//obliczenie warto�ci FPS
	unsigned int FPS;
	if (t != 0) 
		FPS = 1000000 / t;
	else FPS = 999999;

	if (FPSval.size() < 20)
		FPSval.push_back(FPS);
	else {
		FPSval.erase(FPSval.begin());
		FPSval.push_back(FPS);
	}
	FPS = 0;
	for (unsigned i : FPSval)
		FPS += i;
	FPS /= FPSval.size();

	return FPS;																//zwr�cenie warto�ci FPS
}*/

//wy�wietalnie bry� kolizji postaci [klasy 'Character' i 'Player']
/*void CONSOLE::DrawCollisionBoxes() {
	for (unsigned i = 0; i < CharacterRegister::GetStaticCharacterCount(); ++i)
		if (CharacterRegister::GetStaticCharacter(i)->IsEnabled())
			CharacterRegister::GetStaticCharacter(i)->DrawCollisionBox();

	for (unsigned i = 0; i < CharacterRegister::GetDynamicCharacterCount(); ++i)
		if (CharacterRegister::GetDynamicCharacter(i)->IsEnabled())
			CharacterRegister::GetDynamicCharacter(i)->DrawCollisionBox();

	for (unsigned i = 0; i < CharacterRegister::GetBotCount(); ++i)
		if (CharacterRegister::GetBot(i)->IsEnabled())
			CharacterRegister::GetBot(i)->DrawCollisionBox();
	
	if (CharacterRegister::GetPlayer()->IsEnabled())
		CharacterRegister::GetPlayer()->DrawCollisionBox();
}*/

//wy�wietlenie czasu wykonywania operacji pobrania sygna��w wej�ciwoych
/*void CONSOLE::ShowInputProccessTime() {
	char buffer[10];														//bufor dla wy�wietlania
	_itoa_s(TIMER::GetTime("Input"), buffer, 10);							//pobranie warto�ci czasu przetwarzania sygna��w wej�ciowych i zapisanie jej do buforu

	Vector move = GetTextScreenPosition(RIGHT, 3);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}*/

//wy�wietlenie czasu wykonania operacji obliczenia 'fizyki' gry
/*void CONSOLE::ShowPhysicsProcessTime() {
	char buffer[10];														//bufor dla warto�ci wy�wietlanej
	_itoa_s(TIMER::GetTime("Physics"), buffer, 10);							//pobranie warto�ci czasu przetwarzania 'fizyki' gry i wstawienie jej do bufora

	Vector move = GetTextScreenPosition(RIGHT, 4);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}*/

//wy�wietlenie czasu wykonania operacji wy�wietlenia grafiki
/*void CONSOLE::ShowGraphicsProccessTime() {
	char buffer[10];														//bufor dla warto�ci wy�wietlanej
	_itoa_s(TIMER::GetTime("Graphics"), buffer, 10);						//pobranie warto�ci czasu przetwarzania grafiki OpenGL i wstawienie jej do bufora

	Vector move = GetTextScreenPosition(RIGHT, 5);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}*/

/*void CONSOLE::ShowTimer() {
	char buffer[13];														//bufor dla warto�ci wy�wietlanej

	timer += TIMER::GetTime("FPS");											//zaktualizowanie timera

	GetTimerVal(buffer);													//wype�nienie bufora aktualn� warto�ci� timera

	Vector move = GetTextScreenPosition(LEFT, 1);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}*/

//zapis warto�ci zmierzonego czasu do bufora
/*void CONSOLE::GetTimerVal(char* buffer) {
	int h, m, s, ms;

	unsigned long timerTmp = timer;
	h = timer / 3600000000;													//liczba godzin				
	timerTmp -= h * 3600000000;
	m = timerTmp / 60000000;												//liczba minut
	timerTmp -= m * 60000000;
	s = timerTmp / 1000000;													//liczba sekund
	timerTmp -= s * 1000000;
	ms = timerTmp / 1000;													//liczba milisekund

	//wype�nienie bufora
	buffer[0] = h / 10 + 0x30;
	buffer[1] = h - 10 * (h / 10) + 0x30;
	buffer[2] = ':';
	buffer[3] = m / 10 + 0x30;
	buffer[4] = m - 10 * (m / 10) + 0x30;
	buffer[5] = ':';
	buffer[6] = s / 10 + 0x30;
	buffer[7] = s - 10 * (s / 10) + 0x30;
	buffer[8] = '.';
	buffer[9] = ms / 100 + 0x30;
	buffer[10] = (ms - 100 * (ms / 100))/10 + 0x30;
	buffer[11] = NULL;
}*/

//zresetowanie timera
/*void CONSOLE::ResetTimer() {
	timer = 0;
}

void CONSOLE::ShowPlayerPos() {
	//buffer
}*/

//obliczenie parametr�w opisuj�cych wymiary okna OpenGL
void CONSOLE::CountTextScreenParams() {
	//obliczenie parametr�w ekranu OpenGL w zale�no�ci od parametru 'z' [przesuni�cia wg��b ekranu]
	//wysoko�� ekranu
	params.textScreenHeight = -ConsoleDepthVal*tan((WinAPIwindow::FOV / 360.0 * 2 * 3.1415) / 2.0);
	//stosunek rozdzielczo�ci ekranu [szeroko�� / wysoko��]
	params.textScreenRatio = (double)WinAPIwindow::screenWidth / (double)WinAPIwindow::screenHeight;
	//szeroko�� ekranu
	params.textScreenWidth = params.textScreenHeight*params.textScreenRatio;
	//r�nica mi�dzy wielko�ci� 't�a' ekranu, a wielko�ci� tekstu
	//params.textScreenAdjust = params.terminalSize.y - ((double)consoleFont.GetFontSize() / (double)WinAPIwindow::screenHeight) * 2 * params.textScreenHeight;

	params.terminalScreenFontHeight = ((double)params.terminalFontSize / (double)WinAPIwindow::screenHeight)*2.0*params.textScreenHeight;
}

void CONSOLE::ExecuteCommand() {
	lineAnalyzer.LoadLine(currentTerminalText, consoleFunVec);
	LineAnalyzer::Errors errors = lineAnalyzer.GetErrors();
	DisplayLineAnalyzerErrors(errors);
	if (errors.semanticError == 0 && errors.typeError == 0)
		DisplayFunErrors(consoleFunVec.GetFunError(lineAnalyzer.GetCommand()));
	AddTerminalTextLine(currentTerminalText, TerminalTextStruct::USER);
}

void CONSOLE::DisplayLineAnalyzerErrors(LineAnalyzer::Errors& errors) {
	if (errors.semanticError != 0) {
		std::string errorMsg = "Semantic error code: " + std::to_string(errors.semanticError) + "; " + errors.semanticErrorMsg;
		AddTerminalTextLine(errorMsg, TerminalTextStruct::SYSTEM);
	}
	if (errors.typeError != 0) {
		std::string errorMsg = "Type error code: " + std::to_string(errors.semanticError) + "; " + errors.typeErrorMsg;
		AddTerminalTextLine(errorMsg, TerminalTextStruct::SYSTEM);
	}	
}

void CONSOLE::DisplayFunErrors(ConsoleFunError& funError) {
	if (funError.code != 0) {
		std::string errorMsg = "Function " + funError.fun + " error code: " + std::to_string(funError.code) + "; " + funError.msg;
		AddTerminalTextLine(errorMsg, TerminalTextStruct::SYSTEM);
	}
}

/*Vector CONSOLE::GetTextScreenPosition(alignment alin, unsigned int line) {
	Vector move;
	if (alin == LEFT) {
		move.x = -(0.95*params.textScreenWidth); move.z = ConsoleDepthVal;

		move.y = params.textScreenHeight - params.terminalSize.y - line*0.05*params.textScreenHeight + params.textScreenAdjust / 4.0 - 0.05;
	}
	else {		
		move.x = 0.85*params.textScreenWidth; move.z = ConsoleDepthVal;
																				
		move.y = params.textScreenHeight - params.terminalSize.y / 2.0 - line*0.05*params.textScreenHeight + params.textScreenAdjust / 4.0;
	}

	return move;
}*/

void CONSOLE::WriteTextOnScreen(Vector position, std::string buffer,Vector color,const FONT& font_) {
	glPushMatrix();															//zapisanie macierzy widoku OepnGL ['MODELVIEW'] na stosie 

	glLoadIdentity();

	glDisable(GL_LIGHTING);													//wy��czenie o�wietlenia sceny					
	glDisable(GL_DEPTH_TEST);

	glColor3f(static_cast<GLfloat>(color.x), static_cast<GLfloat>(color.y), 
		static_cast<GLfloat>(color.z));										//wybranie koloru wy�wietlanego napisu [bia�y]
	glTranslated(position.x, position.y, position.z);						//ustawienie odpowiedniej pozycji								
	glRasterPos2d(0.0, 0.0);
	font_.PrintString(const_cast<char*>(buffer.c_str()));										//wy�wietlenie napisu

	glColor3d(0.8, 0.8, 0.8);												//przywr�cenie podstawowych kolor�w dla wy�wietlania modeli

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);													//w��czenie o�wieltenia sceny

	glPopMatrix();															//przywr�cenie macierzy widoku OpenGL ze stosu
}

double CONSOLE::GetScreenFontHeight(unsigned fontSize) {
	double screenFontSize = ((double)fontSize / (double)WinAPIwindow::screenHeight)*2.0*params.textScreenHeight;
	return screenFontSize;
}

void CONSOLE::AddTerminalTextLine(std::string line,TerminalTextStruct::Source source_) {
	if (terminalTextLines.size() < TerminalLinesBufferCapacity) {
		terminalTextLines.push_back(TerminalTextStruct(line,source_));
	}
	else {
		terminalTextLines.erase(terminalTextLines.begin());
		terminalTextLines.push_back(TerminalTextStruct(line,source_));
	}

	if(source_==TerminalTextStruct::USER) currentTerminalText = "";
}

void CONSOLE::Prompt::Update() {
	time += TIMER::GetTime("FPS");
	if (time > promptTimeBreak) {
		show = !show;
		time = 0;
	}
	if (show) sign = activeSign;
	else sign = notActiveSign;
}