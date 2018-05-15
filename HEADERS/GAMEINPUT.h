#pragma once
#include "InputDevImpl.h"
#include "InputSystemImpl.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------GAMEINPUT-----------------------------------------------------------------------------------
//--------------------------------------------------------klasa wysokiego poziomu s�u��ca za system wej�cia dla aplikacji-------------------------------------------------------
//-----------------------------------------zadekalrowane w niej s� funkcje za pomoc� kt�rych u�ytkownik odwo�uje si� do systemu wej�cia-----------------------------------------
//--------------------definiecje tych funkcji s� odwo�aniem do konkretnych funkcji klas ni�szego poziomu pochodz�cych z wybranego API [Direct Input, WinAPI]--------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class GAMEINPUT {
	static MouseImpl* mouse;
	static KeyboardImpl* keyboard;
	static ControllerImpl* controller;
	static InputSystemImpl* inputSys;

public:
	static void Register(MouseImpl* mouse_) { mouse = mouse_; }
	static void Register(KeyboardImpl* keyboard_) { keyboard = keyboard_; }
	static void Register(ControllerImpl* controller_) { controller = controller_; }
	static void Register(InputSystemImpl* inputSys_) { inputSys = inputSys_; }
	static void RegisterStandardInput() {
		Register(new Mouse());
		Register(new Keyboard());
		Register(new Controller());
		Register(new StandardInputSystem());
	}

	static void Init() { inputSys->Init(); mouse->mousePos = mouse->GetMouseAbsPos(); }
	static void Update() { inputSys->Update(); }
	static void Shutdown() { inputSys->Shutdown(); }

	static MouseImpl* GetMouse() { return mouse; }
	static KeyboardImpl* GetKeyboard() { return keyboard; }
	static ControllerImpl* GetConroller() { return controller; }

	static bool CheckRegistration() {
		if (mouse == nullptr || keyboard == nullptr || controller == nullptr) return false;
	}
};