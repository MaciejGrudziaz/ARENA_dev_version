#pragma once
#include <string>
#include <vector>
#include "ConsoleFunVec.h"

class LineAnalyzer {
public:
	struct Errors {
		int semanticError;
		std::string semanticErrorMsg;
		int typeError;
		std::string typeErrorMsg;
		Errors() :semanticError(0), semanticErrorMsg(""), typeError(0), typeErrorMsg("") {}
		void Clear() { semanticError = 0; semanticErrorMsg = ""; typeError = 0; typeErrorMsg = ""; }
	};
private:
	enum ParamType { NULLTYPE, INT, DOUBLE, BOOL, STRING };

	struct Param {
		std::string paramString;
		ParamType type;

		Param() :paramString(""), type(NULLTYPE) {}
		Param(std::string paramString_) :paramString(paramString_), type(NULLTYPE) {}
	};

	Errors errors;

	std::string command;
	std::vector<Param> params;

	void GetCommand(std::string line);
	void GetParams(std::string line);
	void ClearParams();

	void LoadParams(ConsoleFunVec& vec);
	void LoadParams_CheckString(Param& param, ValImpl* dataVal);
	void SendParams(ConsoleFunVec& vec);

	template<class Param, class DataParam>
	void CheckType(DataParam dataParam);

	void DisectLine(std::string line);

	void AnalyzeParams(ConsoleFunVec& vec);

	void LineAnalyzer::Clear() {
		command = "";
		params.clear();
		errors.Clear();
	}

public:
	LineAnalyzer() :command("") {}

	void LoadLine(std::string line, ConsoleFunVec& vec);
	Errors GetErrors() { return errors; }
	std::string GetCommand() { return command; }
};

template<class Param, class DataParam>
void LineAnalyzer::CheckType(DataParam dataParam) {
	Val<Param>* ptr = nullptr;
	ptr = dynamic_cast<Val<Param>*>(dataParam);

	if (ptr == nullptr) {
		errors.typeError = 1;
		errors.typeErrorMsg.append(" - wrong type! Expected type: " + dataParam->valType);
	}
}
