#include "PlayerInput.h"

void PlayerInput::Process() {
	for(const InputSignalStruct& input:signals){
		unsigned code = input.inputSignal->value;
		InputFunImpl* inputFun = input.inputFun;
		PlayerSignalImpl* playerSig = input.playerSignal;
		if ((*inputFun)(code))
			(*playerSig)();
	}
}
