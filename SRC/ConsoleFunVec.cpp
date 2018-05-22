#include "ConsoleFunVec.h"

ConsoleFunData* ConsoleFunVec::GetData(std::string command_) {
	for (ConsoleFunData* data : dataVec) {
		if (data->command == command_)
			return data;
	}
	return nullptr;
}

void ConsoleFunVec::LaunchFunction(std::string command) {
	for (ConsoleFunImpl* fun_ : fun) {
		if (fun_->command == command)
			fun_->Launch();
	}
}

ConsoleFunError ConsoleFunVec::GetFunError(std::string command_) {
	for (ConsoleFunImpl* fun_ : fun) {
		if (fun_->command == command_)
			return fun_->GetError();
	}

	throw std::exception();
	//return ConsoleFunError();
}

ConsoleFunVec::~ConsoleFunVec() {
	for (ConsoleFunImpl* fun_ : fun)
		delete fun_;
	for (ConsoleFunData* data : dataVec)
		delete data;
}

ConsoleFunData::~ConsoleFunData() {
	for (ValImpl* param : params)
		delete param;
}
