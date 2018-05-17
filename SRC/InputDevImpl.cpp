#include "InputDevImpl.h"

bool Mouse::MouseButtonDown(unsigned key) {
	return(DIRECTINPUT::ButtonDown(key));
}

bool Mouse::MouseButtonUp(unsigned key) {
	return(DIRECTINPUT::ButtonUp(key));
}

bool Mouse::GetMouseMove(unsigned key) {
	DIRECTINPUT::GetMouseMovement(mouseMove.x, mouseMove.y);
	switch (key) {
	case MouseInputSignal::Code::MOUSE_UP:
		if (mouseMove.y < 0) return true;
		else return false;
		break;
	case MouseInputSignal::Code::MOUSE_DOWN:
		if (mouseMove.y > 0)
			return true;
		else return false;
		break;
	case MouseInputSignal::Code::MOUSE_RIGHT:
		if (mouseMove.x > 0) return true;
		else return false;
		break;
	case MouseInputSignal::Code::MOUSE_LEFT:
		if (mouseMove.x < 0) return true;
		else return false;
	default:
		return false;
	}
}

POSITION Mouse::GetMouseAbsPos() {
	return(WinAPImessages::GetMousePos());
}

bool Keyboard::KeyDown(unsigned key) {
	return(DIRECTINPUT::KeyDown(key));
}

bool Keyboard::KeyUp(unsigned key) {
	return(DIRECTINPUT::KeyUp(key));
}

bool Keyboard::KeyDownCombo(unsigned key) {
	unsigned key1 = key >> 8;
	unsigned key2 = key & 0xFF;

	return (DIRECTINPUT::KeyDown(key1) && DIRECTINPUT::KeyDown(key2));
}

bool Keyboard::KeyUpCombo(unsigned key) {
	unsigned key1 = key >> 8;
	unsigned key2 = key & 0xFF;

	return (DIRECTINPUT::KeyUp(key1) && DIRECTINPUT::KeyUp(key2));
}