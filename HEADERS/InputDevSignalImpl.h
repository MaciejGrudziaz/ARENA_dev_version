#pragma once
#include <dinput.h>

class InputSignalImpl {
public:
	unsigned value;

	InputSignalImpl(unsigned value_) :value(value_) {}
	InputSignalImpl(unsigned value1, unsigned value2) {
		value = (value1 << 8) + value2;
	}

	bool operator==(const InputSignalImpl& sig) const {
		if (sig.value == value) return true;
		else return false;
	}
	bool operator<(const InputSignalImpl& sig) const {
		if (value < sig.value) return true;
		else return false;
	}

	virtual ~InputSignalImpl() {}
};

struct KeyboardInputSignal :public InputSignalImpl {
	enum Code {
		A = DIK_A,
		B = DIK_B,
		C = DIK_C,
		D = DIK_D,
		E = DIK_E,
		F = DIK_F,
		G = DIK_G,
		H = DIK_H,
		I = DIK_I,
		J = DIK_J,
		K = DIK_K,
		L = DIK_L,
		M = DIK_M,
		N = DIK_N,
		O = DIK_O,
		Q = DIK_Q,
		P = DIK_P,
		R = DIK_R,
		S = DIK_S,
		T = DIK_T,
		U = DIK_U,
		V = DIK_V,
		W = DIK_W,
		X = DIK_X,
		Y = DIK_Y,
		Z = DIK_Z,

		_0 = DIK_0,
		_1 = DIK_1,

		ESC = DIK_ESCAPE,
		BACKSPACE = DIK_BACKSPACE,
		ENTER = DIK_RETURN,
		DECIMAL_POINT = DIK_PERIOD,
		EQUALS = DIK_EQUALS,
		SPACE = DIK_SPACE,
		TILDE = DIK_GRAVE,
		LCTRL=DIK_LCONTROL,
		RCTRL=DIK_RCONTROL,
		UP=DIK_UP,
		DOWN=DIK_DOWN
	};

	KeyboardInputSignal(Code val) :InputSignalImpl(val) {}
	KeyboardInputSignal(Code val1, Code val2) : InputSignalImpl(val1, val2) {}
};

struct MouseInputSignal :public InputSignalImpl {
	enum Code {
		MOUSE_UP = 0x100,
		MOUSE_DOWN = 0x101,
		MOUSE_LEFT = 0x102,
		MOUSE_RIGHT = 0x103,
		MOUSE_LEFT_BUT = 0x104,
		MOUSE_RIGHT_BUT = 0x105
	};

	MouseInputSignal(Code val) :InputSignalImpl(val) {}
};

struct ControllerInputSignal :public InputSignalImpl {
	enum Code {};

	ControllerInputSignal(Code val) :InputSignalImpl(val) {}
};