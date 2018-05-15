#pragma once
#include "DIRECTINPUT.h"
#include "InputDevSignalImpl.h"

struct MouseImpl {
	POSITION mouseMove;
	POSITION mousePos;
	bool keyMap[10];

	MouseImpl() :mouseMove(POSITION()), keyMap{ false } {}

	virtual bool MouseButtonDown(unsigned key) = 0;
	virtual bool MouseButtonUp(unsigned key) = 0;
	virtual bool GetMouseMove(unsigned key) = 0;
	virtual POSITION GetMouseAbsPos() = 0;

	virtual ~MouseImpl() {}
};

struct KeyboardImpl {
	bool keyMap[256];

	KeyboardImpl() :keyMap{ false } {}

	virtual bool KeyDown(unsigned key) = 0;
	virtual bool KeyUp(unsigned key) = 0;
	virtual bool KeyDownCombo(unsigned key) = 0;
	virtual bool KeyUpCombo(unsigned key) = 0;

	virtual ~KeyboardImpl() {}
};

struct ControllerImpl {
	virtual ~ControllerImpl() {}
};

class Mouse :public MouseImpl {
public:

	bool MouseButtonDown(unsigned key);
	bool MouseButtonUp(unsigned key);
	bool GetMouseMove(unsigned key);
	POSITION GetMouseAbsPos();

	Mouse() { mousePos = GetMouseAbsPos(); }
	virtual ~Mouse() {}
};

class Keyboard :public KeyboardImpl {
public:
	bool KeyDown(unsigned key);
	bool KeyUp(unsigned key);
	bool KeyDownCombo(unsigned key);
	bool KeyUpCombo(unsigned key);

	virtual ~Keyboard() {}
};

class Controller :public ControllerImpl {
	virtual ~Controller() {}
};