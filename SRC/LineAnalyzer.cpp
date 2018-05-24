#include "LineAnalyzer.h"

void LineAnalyzer::LoadLine(std::string line, ConsoleFunVec& vec) {
	Clear();
	DisectLine(line);
	if (errors.semanticError == 0)
		AnalyzeParams(vec);
}

void LineAnalyzer::DisectLine(std::string line) {
	GetCommand(line);

	if (errors.semanticError == 0)
		GetParams(line);
}

void LineAnalyzer::GetCommand(std::string line) {
	size_t pos = line.find('(');
	size_t endPos = line.find(')');

	if (endPos < pos) {
		errors.semanticError = 1;
		errors.semanticErrorMsg.append("Expexted ( before )");
	}
	else if (pos == std::string::npos) {
		errors.semanticError = 3;
		errors.semanticErrorMsg.append("Expexted (");
	}
	else if (endPos == std::string::npos) {
		errors.semanticError = 2;
		errors.semanticErrorMsg.append("Expected )");
	}
	if (errors.semanticError != 0) return;

	for (unsigned i = endPos + 1; i < line.size(); ++i) {
		if (line[i] != ' ') {
			errors.semanticError = 4;
			errors.semanticErrorMsg.append("Expected no signs after command!");
			break;
		}
	}

	command.append(line, 0, pos);

	while (command.find(' ') == 0)
		command.erase(0, 1);

	if (command.find(' ') != std::string::npos) {
		errors.semanticError = 5;
		errors.semanticErrorMsg.append("Expected (");
		return;
	}
}

void LineAnalyzer::GetParams(std::string line) {
	size_t pos = line.find('(');
	size_t endPos = line.find(')');
	std::string allParams;
	allParams.append(line, pos + 1, endPos - pos - 1);

	size_t prevPos=0;
	std::string paramStr;

	pos = 0;
	while (pos != std::string::npos) {
		prevPos = pos;
		pos = allParams.find(',', pos);
		if (pos != std::string::npos) {
			paramStr.clear();
			paramStr.append(allParams, prevPos, pos - prevPos);
			params.push_back(Param(paramStr));
			++pos;
		}
	}
	paramStr.clear();
	paramStr.append(allParams, prevPos);
	params.push_back(Param(paramStr));

	ClearParams();
}

void LineAnalyzer::ClearParams() {
	size_t pos;
	for (unsigned i = 0; i < params.size(); ++i) {
		while (params[i].paramString.find(' ') == 0)
			params[i].paramString.erase(0, 1);
		pos = params[i].paramString.find('"');
		if (pos == std::string::npos) {
			pos = params[i].paramString.find(' ');
			if (pos != std::string::npos) {
				for (unsigned j = pos; j<params[i].paramString.size(); ++j)
					if (params[i].paramString[j] != ' ') {
						errors.semanticError = 6;
						errors.semanticErrorMsg.append("Expected ,");
						break;
					}
				params[i].paramString.erase(pos);
			}
		}
		else {
			if (pos != 0) {
				errors.semanticError = 7;
				errors.semanticErrorMsg.append("Expected \"");
			}
			else {
				size_t pos2 = params[i].paramString.find('"', 1);
				if (pos2 == std::string::npos) {
					errors.semanticError = 8;
					errors.semanticErrorMsg.append("Expected \"");
				}
				else {
					for (unsigned j = pos2 + 1; j < params[i].paramString.size(); ++j) {
						if (params[i].paramString[j] != ' ') {
							errors.semanticError = 9;
							errors.semanticErrorMsg.append("Expected ,");
							break;
						}
					}
				}
			}
		}

	}
	if (errors.semanticError != 0) return;

	for (unsigned i = 0; i < params.size(); ++i) {
		if (params[i].paramString == "") {
			if (params.size() > 1) {
				errors.semanticError = 10;
				errors.semanticErrorMsg.append("Expected )");
				return;
			}
			else {
				params.clear();
			}
		}
	}
}

void LineAnalyzer::AnalyzeParams(ConsoleFunVec& vec) {
	ConsoleFunData* data = vec.GetData(command);
	if (data == nullptr) {
		errors.typeError = 3;
		errors.typeErrorMsg.append(command + " - command does not exist!");
		return;
	}
	if (data->params.size() != params.size()) {
		errors.typeError = 4;
		errors.typeErrorMsg.append("Expected " + std::to_string(data->params.size()) + " parameters!");
		return;
	}

	LoadParams(vec);

	if (errors.typeError != 0) return;

	SendParams(vec);

	vec.LaunchFunction(command);
}

void LineAnalyzer::LoadParams(ConsoleFunVec& vec) {
	for (unsigned i = 0; i < params.size(); ++i) {
		bool number = true;
		bool special = false;
		bool ifBool = false;
		for (unsigned j = 0; j < params[i].paramString.size(); ++j) {
			if (params[i].paramString[j]<(int)'0' || params[i].paramString[j]>(int)'9') {
				if (params[i].paramString[j] == '.' && special == false) special = true;
				else number = false;
			}
		}
		if (!number) {
			if (params[i].paramString == "true" || params[i].paramString == "false") ifBool = true;
		}

		ConsoleFunData* funData = vec.GetData(command);

		if (number) {
			if (special) {
				params[i].type = DOUBLE;
				CheckType<double>(funData->params[i]);
			}
			else {
				params[i].type = INT;
				CheckType<int>(funData->params[i]);
			}
		}
		else {
			if (ifBool) {
				params[i].type = BOOL;
				CheckType<bool>(funData->params[i]);
			}
			else {
				LoadParams_CheckString(params[i], funData->params[i]);
			}
		}
		if (errors.typeError != 0) {
			errors.typeErrorMsg = "Variable: " + params[i].paramString + errors.typeErrorMsg;
			return;
		}
	}
}

void LineAnalyzer::SendParams(ConsoleFunVec& vec) {
	typedef bool(*FunPtr)(std::string);
	FunPtr GetBool = [](std::string paramStr)->bool {if (paramStr == "true") return true; else return false; };

	for (unsigned i = 0; i < params.size(); ++i)
		switch (params[i].type) {
		case INT:
			vec.LoadParamVal(command, i, atoi(params[i].paramString.c_str()));
			break;
		case DOUBLE:
			vec.LoadParamVal(command, i, static_cast<double>(atof(params[i].paramString.c_str())));
			break;
		case BOOL:
			vec.LoadParamVal(command, i, GetBool(params[i].paramString));
			break;
		case STRING:
			vec.LoadParamVal(command, i, params[i].paramString);
			break;
		default:
			break;
		}
}

void LineAnalyzer::LoadParams_CheckString(Param& param, ValImpl* dataVal) {
	if (param.paramString[0] == '"' && param.paramString[param.paramString.size() - 1] == '"') {
		param.type = STRING;
		param.paramString.erase(param.paramString.begin());
		param.paramString.erase(param.paramString.end() - 1);
		CheckType<std::string>(dataVal);
	}
	else {
		errors.typeError = 2;
		errors.typeErrorMsg.append(" - undefined type!");
	}
}
