#pragma once
#include <string>
#include <vector>
#include <TypeList.h>
#include "ConsoleFunImpl.h"

struct ValImpl {
	std::string valType;
	virtual void LoadVal(ValImpl* val) = 0;
	virtual ValImpl* GetVal() = 0;

	virtual ~ValImpl() {}
};

template<class T> struct Val;

template<>
struct Val<int> : public ValImpl {
	int* val;
	Val() :val(nullptr) { valType = "int"; }
	Val(int* val_) :val(val_) { valType = "int"; }

	void LoadVal(ValImpl* val_) { *(val) = *(dynamic_cast<Val<int>*>(val_)->val); }
	Val<int>* GetVal() { return this; }
	operator int() { return *val; }

	~Val() {}
};

template<>
struct Val<double> : public ValImpl {
	double* val;
	Val() :val(nullptr) { valType = "double"; }
	Val(double* val_) :val(val_) { valType = "double"; }

	void LoadVal(ValImpl* val_) { *(val) = *(dynamic_cast<Val<double>*>(val_)->val); }
	Val<double>* GetVal() { return this; }
	operator double() { return *val; }

	~Val() {}
};

template<>
struct Val<bool> : public ValImpl {
	bool* val;
	Val() :val(nullptr) { valType = "bool"; }
	Val(bool* val_) :val(val_) { valType = "bool"; }

	void LoadVal(ValImpl* val_) { *(val) = *(dynamic_cast<Val<bool>*>(val_)->val); }
	Val<bool>* GetVal() { return this; }
	operator bool() { return *val; }

	~Val() {}
};

template<>
struct Val<std::string> : public ValImpl {
	std::string* val;
	Val() :val(nullptr) { valType = "std::string"; }
	Val(std::string* val_) :val(val_) { valType = "std::string"; }

	void LoadVal(ValImpl* val_) { *(val) = *(dynamic_cast<Val<std::string>*>(val_)->val); }
	Val<std::string>* GetVal() { return this; }
	operator std::string() { return *val; }

	~Val() {}
};

struct ConsoleFunData {
	std::string command;
	std::vector<ValImpl*> params;

	ConsoleFunData() :command("") {}
	ConsoleFunData(int vecIdx_, int idx_) :command("") {}

	~ConsoleFunData();
};

class ConsoleFunVec {
	std::vector<ConsoleFunData*> dataVec;
	std::vector<ConsoleFunImpl*> fun;

	template<int i, class T>
	struct Load;

	template<class Type>
	struct Load<0, Type> {
		Load() {}
		Load(ConsoleFunData& data_, Type& obj) {}
	};

	template<class Type>
	struct Load<1, Type> {
		Load() {}
		Load(ConsoleFunData& data, Type& obj) {
			data.params.push_back(new Val<Type::Parm1>(&obj.val1));
		}
	};

	template<class Type>
	struct Load<2, Type> {
		Load() {}
		Load(ConsoleFunData& data, Type& obj) {
			data.params.push_back(new Val<Type::Parm1>(&obj.val1));
			data.params.push_back(new Val<Type::Parm2>(&obj.val2));
		}
	};

public:
	template<class Fun> void Register(Fun* obj);

	int Find(std::string command_) {
		for (unsigned i = 0; i < dataVec.size(); ++i)
			if (dataVec[i]->command == command_) return i;

		return -1;
	}

	template<typename Param> void LoadParamVal(std::string command_, unsigned paramIdx, Param param_);

	ConsoleFunData* GetData(std::string command_);
	void LaunchFunction(std::string command);
	ConsoleFunError GetFunError(std::string command_);

	void DisplayAll() {
		for (ConsoleFunImpl* fun_ : fun)
			fun_->Display();
	}

	~ConsoleFunVec();
};

template<class Fun>
void ConsoleFunVec::Register(Fun* obj) {
	fun.push_back(dynamic_cast<ConsoleFunImpl*>(obj));

	ConsoleFunData* data = new ConsoleFunData();
	data->command = obj->command;
	Load<Fun::paramNum, Fun> load(*data, *obj);
	dataVec.push_back(data);
}

template<typename Param>
void ConsoleFunVec::LoadParamVal(std::string command_, unsigned paramIdx, Param param_) {
	for (ConsoleFunData* data : dataVec) {
		if (data->command == command_) {
			Val<Param>* param = dynamic_cast<Val<Param>*>(data->params[paramIdx]);
			//if (param != nullptr) {
			*(param->val) = param_;
			return;
			//return true;
			//}
			//else return false;*/
		}
	}
}

