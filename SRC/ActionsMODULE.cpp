#include "ActionsMODULE.h"

Actions ActionsMODULE::actions;
std::map<std::string, InputModuleImpl*> ActionsMODULE::inputModules;
InputModuleImpl* ActionsMODULE::currentInputModule=nullptr;
std::vector<PlayerInput::InputSignalStruct> ActionsMODULE::signals;
std::string ActionsMODULE::currentInputModuleName="";
std::string ActionsMODULE::lastInputModuleName="";

void ActionsMODULE::Process() {
	GAMEINPUT::Update();

	for (const PlayerInput::InputSignalStruct& input:signals) {
		unsigned code = input.inputSignal->value;
		InputFunImpl* inputFun = input.inputFun;
		PlayerSignalImpl* playerSig = input.playerSignal;
		if ((*inputFun)(code))
			(*playerSig)();
	}

	actions.PerformAllActions();

	if (currentInputModule != nullptr)
		currentInputModule->Process();
	else throw std::exception();
}