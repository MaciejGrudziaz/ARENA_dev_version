#pragma once
#include <string>
#include <TypeList.h>

struct ConsoleFunError{
	int code;
	std::string msg;
	std::string fun;
	ConsoleFunError() :code(0), msg(""), fun("") {}
	ConsoleFunError(std::string funName) :fun(funName), code(0), msg("") {}
	void Clear() { code = 0; msg = ""; }
};

struct ConsoleFunImpl {
	std::string command;
	int enable;
	ConsoleFunError error;
	ConsoleFunImpl(std::string command_) :command(command_), enable(0),error(command_) {}
	virtual void Display() = 0;
	virtual ConsoleFunError GetError() { ConsoleFunError errorRet = error; error.Clear(); return errorRet; }
	virtual void Launch() { enable = 1;}
	virtual ~ConsoleFunImpl() {}
};

template<class TList> struct ConsoleFunHandler;

template<>
struct ConsoleFunHandler<NullType> :public ConsoleFunImpl {
	enum { paramNum = 0 };
	ConsoleFunHandler(std::string command_) :ConsoleFunImpl(command_) {}
};

template<class T1>
struct ConsoleFunHandler<TYPELIST_1(T1)> :public ConsoleFunImpl {
	enum { paramNum = 1 };
	typedef T1 Parm1;
	T1 val1;
	ConsoleFunHandler(std::string command_) :ConsoleFunImpl(command_) {}
	ConsoleFunHandler(T1 val, std::string command_) :val1(val), ConsoleFunImpl(command_) {}
};

template<class T1, class T2>
struct ConsoleFunHandler<TYPELIST_2(T1, T2)> :public ConsoleFunImpl {
	enum { paramNum = 2 };
	typedef T1 Parm1;
	typedef T2 Parm2;
	T1 val1;
	T2 val2;
	ConsoleFunHandler(std::string command_) :ConsoleFunImpl(command_) {}
	ConsoleFunHandler(T1 val1_, T2 val2_, std::string command_) :val1(val1_), val2(val2_), ConsoleFunImpl(command_) {}
};