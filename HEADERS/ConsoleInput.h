#pragma once
#include "PlayerInput.h"
#include "ConsoleInputActions.h"

class ConsoleInput:public PlayerInput{
	unsigned long delay;

public:

	ConsoleInput(std::string moduleName) : delay(0), PlayerInput(moduleName) {}

	void Init();

	void Process();
};
