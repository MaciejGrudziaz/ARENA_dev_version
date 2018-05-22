#pragma once
#include "PlayerInput.h"
#include "ConsoleInputActions.h"

class ConsoleInput:public PlayerInput{
	unsigned long delay;

	struct KeyboardInputCode {
		std::string sign;
		KeyboardInputSignal::Code code;
		KeyboardInputCode(std::string sign_, KeyboardInputSignal::Code code_) :sign(sign_), code(code_) {}
	};

	std::vector<KeyboardInputCode> inputCodesVec;

public:

	ConsoleInput(std::string moduleName);

	void Init();

	void Process();
};
