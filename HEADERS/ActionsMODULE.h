#pragma once
#include "PlayerInput.h"

class ActionsMODULE {
	ActionsMODULE() {}
	ActionsMODULE(const ActionsMODULE&) {}
	ActionsMODULE& operator=(const ActionsMODULE&) {}

	static Actions actions;

	typedef std::map<std::string, InputModuleImpl*> InputModulesMap;
	static InputModulesMap inputModules;
	static InputModuleImpl* currentInputModule;

	//typedef std::pair<InputFunImpl*, PlayerSignalImpl* > InputSignalPair;
	//typedef std::map<InputSignalImpl*, InputSignalPair> PlayerSignalMap;
	//static PlayerSignalMap signals;

	typedef std::vector<PlayerInput::InputSignalStruct> InputSignalVec;
	static InputSignalVec signals;

public:
	static void RegisterInputModule(InputModuleImpl* inputModule) {
		inputModules.insert(InputModulesMap::value_type(inputModule->GetName(),inputModule));
	}

	static void SetCurrentInputModule(std::string moduleName) {
		InputModulesMap::iterator it = inputModules.find(moduleName);
		if (it != inputModules.end())
			currentInputModule = (*it).second;
		else throw std::exception();
	}

	static InputModuleImpl* GetInputModule(std::string moduleName) {
		InputModulesMap::iterator it = inputModules.find(moduleName);
		if (it != inputModules.end())
			return (*it).second;
		else throw std::exception();
	}

	static void RegisterInputSignal(InputSignalImpl* inputSignal, InputFunImpl* inputFun, PlayerSignalImpl* playerSignal) {
		//signals.insert(PlayerSignalMap::value_type(*inputSignal, InputSignalPair(inputFun, playerSignal)));
		signals.push_back(InputSignalVec::value_type(inputSignal, inputFun, playerSignal));
	}

	static Actions* GetActionsModule() { return &actions; }

	static void Process();
};
