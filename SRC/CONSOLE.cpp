#include "CONSOLE.h"

//inicjalizacja statycznych sk�adowych klasy
Actions CONSOLE::actions;
FONT CONSOLE::consoleFont;
unsigned int CONSOLE::enabledFunc = 0;
Vector CONSOLE::terminalSize = { 0, 0, 0};
Vector CONSOLE::terminalPixelSize = { 500,26,0 };
std::string CONSOLE::terminalCommand = "";
unsigned int CONSOLE::terminalTextSize = 0;
char CONSOLE::terminalText[maxTerminalTextSize+1] = "";
double CONSOLE::textScreenWidth = 0;
double CONSOLE::textScreenHeight = 0;
double CONSOLE::textScreenRatio = 0;
double CONSOLE::textScreenAdjust = 0;
unsigned long CONSOLE::timer = 0;
std::vector<unsigned> CONSOLE::FPSval;

//inicjalizacja konsoli
void CONSOLE::Initialize() {
	consoleFont.Initilize("Arial", 24, WinAPIwindow::hDC);										//inicjalizacja czionki ['Arial', rozmiar - 24]
}

//wy�wietlenie aktywnych 'funkcji' konsoli
void CONSOLE::ShowConsoleOutput() {
	if (IsFuncEnabled(ShowTerminal_FUNC))
		ShowConsoleTerminal();												//wy�wietlenie terminala konsoli

	CountTextScreenParams(1);												//obliczenie parametr�w opisuj�cych ekran OpenGL dla wy�wietlania tekstu
	if (IsFuncEnabled(FPS_FUNC))
		ShowFPS();															//wy�wietlenie aktualnej warto�ci FPS
	if (IsFuncEnabled(CollisionBox_FUNC))
		DrawCollisionBoxes();												//wy�wietlenie bry� kolizji dla wszystkich obiekt�w w grze
	if (IsFuncEnabled(InputProccesTime_FUNC))
		ShowInputProccessTime();											//wy�wietlenie czasu przetwarzania sygna��w wej�ciowych
	if (IsFuncEnabled(PhysicsProccesTime_FUNC))
		ShowPhysicsProcessTime();											//wy�wietlenie czasu przetwarzania 'fizyki'  gry
	if (IsFuncEnabled(GraphicsProccesTime_FUNC))
		ShowGraphicsProccessTime();											//wy�wietlenie czasu przetwarzania grafiki
	if (IsFuncEnabled(Timer_FUNC))
		ShowTimer();
}

//wczytanie znaku do terminala
void CONSOLE::GetTerminalInput(char a) {
	if (a != 0x08 && a!=0x0A) {												//je�li nie wczytanu znku 'BACKSPACE' lub 'ENTER'
		if (terminalTextSize < maxTerminalTextSize) {						//je�li nie przekroczono maksymalnego zakresu terminala
			terminalText[terminalTextSize] = a;								//wczytaj nowy znak do terminala
			terminalTextSize++;													
		}
	}
	else {
		if (a == 0x08) {													//je�li wczytano znak 'BACKSPACE'
			if (terminalTextSize > 0) {										//je�li istniej� znaki w terminalu
				terminalText[terminalTextSize - 1] = 0x00;					//usu� ostatni znak
				terminalTextSize--;
			}
		} 
		if (a == 0x0A) {													//je�li wczytano znak 'ENTER'
			for (unsigned int i = 0; i < terminalTextSize; i++)
				terminalCommand.push_back(terminalText[i]);					//wczytaj tekst z terminala do stringa komend

			CheckCommand();													//sprawd� wprowadzon� komend�
		}
	}
}

//sprawdzenie wprowadzonej komendy do terminala
void CONSOLE::CheckCommand() {
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
}

//wy�wietlenie terminalu konsoli
void CONSOLE::ShowConsoleTerminal() {
	CountTextScreenParams(2);												//obliczenie parametr�w opisuj�cych ekran OpenGL dla wy�wietlenia 't�a' terminala							
	DrawTerminalBackground();												//wy�wietlenie 't�a' terminala

	CountTextScreenParams(1);												//obliczenie parametr�w opisuj�cych ekran OpenGL dla wy�wietlania tekstu
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
	glVertex3d(-terminalSize.x / 2.0, terminalSize.y / 2.0, 0.0);
	glVertex3d(-terminalSize.x / 2.0, -terminalSize.y / 2.0, 0.0);
	glVertex3d(terminalSize.x / 2.0, -terminalSize.y / 2.0, 0.0);
	glVertex3d(terminalSize.x / 2.0, terminalSize.y / 2.0, 0.0);
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
	Vector move(-(textScreenWidth - terminalSize.x / 2.0 - 0.05*textScreenHeight), 0, -2);

	//ustalenie wielko�ci terminala w OpenGL ze wzgl�du na wielko�� terminalu w pikselach, rozdzielczo�� ekranu oraz wielko�� ekranu w OpenGL
	terminalSize.x = terminalPixelSize.x / (double)WinAPIwindow::screenWidth * 2 * textScreenWidth;
	terminalSize.y = terminalPixelSize.y / (double)WinAPIwindow::screenHeight * 2 * textScreenHeight;

		//ustalenie pozycji Y terminalu dla trybu pe�noekranowego
		move.y = textScreenHeight - terminalSize.y / 2.0 - 0.05*textScreenHeight;	


	return move;
}

//wy�wietlenie tekstu w terminalu
void CONSOLE::TerminalText() {
	Vector move = GetTerminalTextPosition();								//pobranie pozycji tekstu w terminalu

	WriteTextOnScreen(move, terminalText, CONSOLE_white);
}

//pobranie pozycji tekstu w terminalu
Vector CONSOLE::GetTerminalTextPosition() {
	Vector move(-(textScreenWidth - 0.07*textScreenHeight), 0, -1);			//ustalenie pozycji X i Z tekstu

		//ustalenie pozycji Y na podstawie wielko�ci ekranu oraz terminala w OpenGL
		move.y = textScreenHeight - terminalSize.y / 2.0 - 0.05*textScreenHeight + textScreenAdjust / 4.0;
		//ustalenie pozycji Y tekstu dla trybu okienkowego

	return move;
}

//wy�wietlenie aktualnej liczby FPS
void CONSOLE::ShowFPS() {
	char buffer[10];														//bufor s�u�acy do wy�wietlenia aktualnej ilo�ci FPS
	Vector color;

	unsigned fps = GetFPS();
	
	_itoa_s(fps, buffer, 10);												//pobranie aktualnej liczby FPS, przekonwertowanie jej do tablicy zankowej char i zapisanie w buforze

	if (fps >= 60) color = CONSOLE_green;
	else if (fps >= 30) color = CONSOLE_yellow;
	else color = CONSOLE_red;

	Vector move = GetTextScreenPosition(RIGHT, 1);

	WriteTextOnScreen(move, buffer,color);
}

//pobranie aktulanej warto�ci FPS
unsigned int CONSOLE::GetFPS() {
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
}

//wy�wietalnie bry� kolizji postaci [klasy 'Character' i 'Player']
void CONSOLE::DrawCollisionBoxes() {
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
}

//wy�wietlenie czasu wykonywania operacji pobrania sygna��w wej�ciwoych
void CONSOLE::ShowInputProccessTime() {
	char buffer[10];														//bufor dla wy�wietlania
	_itoa_s(TIMER::GetTime("Input"), buffer, 10);							//pobranie warto�ci czasu przetwarzania sygna��w wej�ciowych i zapisanie jej do buforu

	Vector move = GetTextScreenPosition(RIGHT, 3);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}

//wy�wietlenie czasu wykonania operacji obliczenia 'fizyki' gry
void CONSOLE::ShowPhysicsProcessTime() {
	char buffer[10];														//bufor dla warto�ci wy�wietlanej
	_itoa_s(TIMER::GetTime("Physics"), buffer, 10);							//pobranie warto�ci czasu przetwarzania 'fizyki' gry i wstawienie jej do bufora

	Vector move = GetTextScreenPosition(RIGHT, 4);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}

//wy�wietlenie czasu wykonania operacji wy�wietlenia grafiki
void CONSOLE::ShowGraphicsProccessTime() {
	char buffer[10];														//bufor dla warto�ci wy�wietlanej
	_itoa_s(TIMER::GetTime("Graphics"), buffer, 10);						//pobranie warto�ci czasu przetwarzania grafiki OpenGL i wstawienie jej do bufora

	Vector move = GetTextScreenPosition(RIGHT, 5);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}

void CONSOLE::ShowTimer() {
	char buffer[13];														//bufor dla warto�ci wy�wietlanej

	timer += TIMER::GetTime("FPS");											//zaktualizowanie timera

	GetTimerVal(buffer);													//wype�nienie bufora aktualn� warto�ci� timera

	Vector move = GetTextScreenPosition(LEFT, 1);

	WriteTextOnScreen(move, buffer, CONSOLE_white);
}

//zapis warto�ci zmierzonego czasu do bufora
void CONSOLE::GetTimerVal(char* buffer) {
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
}

//zresetowanie timera
void CONSOLE::ResetTimer() {
	timer = 0;
}

void CONSOLE::ShowPlayerPos() {
	//buffer
}

//obliczenie parametr�w opisuj�cych wymiary okna OpenGL
void CONSOLE::CountTextScreenParams(double z) {
	//obliczenie parametr�w ekranu OpenGL w zale�no�ci od parametru 'z' [przesuni�cia wg��b ekranu]
	//wysoko�� ekranu
	textScreenHeight = z*tan((WinAPIwindow::FOV / 360.0 * 2 * 3.1415) / 2.0);
	//stosunek rozdzielczo�ci ekranu [szeroko�� / wysoko��]
	textScreenRatio = (double)WinAPIwindow::screenWidth / (double)WinAPIwindow::screenHeight;
	//szeroko�� ekranu
	textScreenWidth = textScreenHeight*textScreenRatio;
	//r�nica mi�dzy wielko�ci� 't�a' ekranu, a wielko�ci� tekstu
	textScreenAdjust = terminalSize.y - ((double)consoleFont.GetFontSize() / (double)WinAPIwindow::screenHeight) * 2 * textScreenHeight;
}

Vector CONSOLE::GetTextScreenPosition(alignment alin, unsigned int line) {
	Vector move;
	if (alin == LEFT) {
		move.x = -(0.95*textScreenWidth); move.z = -1;

		move.y = textScreenHeight - terminalSize.y - line*0.05*textScreenHeight + textScreenAdjust / 4.0 - 0.05;
	}
	else {		
		move.x = 0.85*textScreenWidth; move.z = -1;
																				
		move.y = textScreenHeight - terminalSize.y / 2.0 - line*0.05*textScreenHeight + textScreenAdjust / 4.0;
	}

	return move;
}

void CONSOLE::WriteTextOnScreen(Vector position, char buffer[],Vector color) {
	glPushMatrix();															//zapisanie macierzy widoku OepnGL ['MODELVIEW'] na stosie 

	glLoadIdentity();

	glDisable(GL_LIGHTING);													//wy��czenie o�wietlenia sceny					
	glDisable(GL_DEPTH_TEST);

	glColor3f(static_cast<GLfloat>(color.x), static_cast<GLfloat>(color.y), 
		static_cast<GLfloat>(color.z));										//wybranie koloru wy�wietlanego napisu [bia�y]
	glTranslated(position.x, position.y, position.z);						//ustawienie odpowiedniej pozycji								
	glRasterPos2d(0.0, 0.0);
	consoleFont.PrintString(buffer);										//wy�wietlenie napisu

	glColor3d(0.8, 0.8, 0.8);												//przywr�cenie podstawowych kolor�w dla wy�wietlania modeli

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);													//w��czenie o�wieltenia sceny

	glPopMatrix();															//przywr�cenie macierzy widoku OpenGL ze stosu
}