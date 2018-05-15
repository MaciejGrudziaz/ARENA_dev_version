#pragma once

class InputFunImpl {
public:
	virtual bool operator()(unsigned key) = 0;
	virtual ~InputFunImpl() {}
};

template<class InputDev>
class InputFunHandler :public InputFunImpl {
	typedef bool(InputDev::*DevFunPtr)(unsigned);
	InputDev* dev;
	DevFunPtr devFun;
public:
	InputFunHandler(InputDev* dev_, DevFunPtr devFunPtr) :dev(dev_), devFun(devFunPtr) {}
	bool operator()(unsigned key) {
		return ((*dev).*(devFun))(key);
	}
};