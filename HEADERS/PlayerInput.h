#pragma once
#include "GAMEINPUT.h"
#include "PlayerSignal.h"
#include "InputFunImpl.h"
#include "InputModuleImpl.h"

class PlayerInput:public InputModuleImpl{
public:
	struct InputSignalStruct {
		InputSignalImpl* inputSignal;
		InputFunImpl* inputFun;
		PlayerSignalImpl* playerSignal;

		InputSignalStruct(InputSignalImpl* inputSignal_, InputFunImpl* inputFun_, PlayerSignalImpl* playerSignal_) {
			inputSignal = inputSignal_;
			inputFun = inputFun_;
			playerSignal = playerSignal_;
		}
	};

private:
	typedef std::vector<InputSignalStruct> InputSignalVec;
	InputSignalVec signals;

public:

	PlayerInput(std::string moduleName) :InputModuleImpl(moduleName) {}

	void Process();									//przetwarzanie sygna³ów wejœciowych

	void Register(InputSignalImpl* inputSignal, InputFunImpl* inputFun, PlayerSignalImpl* playerSignal) {
		signals.push_back(InputSignalVec::value_type(inputSignal, inputFun, playerSignal));
	}
};