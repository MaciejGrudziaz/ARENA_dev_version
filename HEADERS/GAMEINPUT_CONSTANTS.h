#pragma once
#include <dinput.h>

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------ZMIENNE U�YWANE W SYSTEMIE WEJ�CIA GRY [GAMEINPUT]----------------------------------------
//-------------------------------------zmienne u�ywane do sprawdzania stanu wybranych klawiszy--------------------------------------
//--------------------zdefiniowanie nowych nazw klawiszy w celu u�atwienia u�ytkowania systemu wej�cia GAMEINPUT--------------------
//------------------[g��wny system wej�cia gry niezale�ny od aktualnie u�ywanego systemu wej�cia np. DirectInput]-------------------
//----------------------------------------------------------------------------------------------------------------------------------

namespace INPUTCONST {
	//pozycje poszczeg�lnych symboli w tablicy 'keyPressed[..]' dla systemu wej�cia WinAPI
	//zmiana definicji w celu ��twiejszego odwo�ywania si� do danych pozycji
	const int WIN_TAB = VK_ESCAPE;
	const int WIN_ESC = VK_ESCAPE;
	const int WIN_tylda = VK_OEM_3;
	const int WIN_A = 0x41;
	const int WIN_V = 0x56;
	const int WIN_1 = 0x31;
	const int WIN_2 = 0x32;

	//zmiana definicji kod�w przycisk�w dla Direct Input [�atwiejsze odwo�ywanie si� do danych sygna��w wej�ciowych]
	const int A = DIK_A;
	const int B = DIK_B;
	const int C = DIK_C;
	const int D = DIK_D;
	const int E = DIK_E;
	const int F = DIK_F;
	const int G = DIK_G;
	const int H = DIK_H;
	const int I = DIK_I;
	const int J = DIK_J;
	const int K = DIK_K;
	const int L = DIK_L;
	const int M = DIK_M;
	const int N = DIK_N;
	const int O = DIK_O;
	const int P = DIK_P;
	const int R = DIK_R;
	const int S = DIK_S;
	const int T = DIK_T;
	const int U = DIK_U;
	const int V = DIK_V;
	const int W = DIK_W;
	const int X = DIK_X;
	const int Y = DIK_Y;
	const int Z = DIK_Z;

	const int _0 = DIK_0;
	const int _1 = DIK_1;
	
	const int ESC = DIK_ESCAPE;
	const int BACKSPACE = DIK_BACKSPACE;
	const int ENTER = DIK_RETURN;
	const int DECIMAL_POINT = DIK_PERIOD;
	const int EQUALS = DIK_EQUALS;
	const int SPACE = DIK_SPACE;

	const int MOUSE_UP = 0x100;
	const int MOUSE_DOWN = 0x101;
	const int MOUSE_LEFT = 0x102;
	const int MOUSE_RIGHT = 0x103;
	const int MOUSE_LEFT_BUT = 0x104;
	const int MOUSE_RIGHT_BUT = 0x105;
}