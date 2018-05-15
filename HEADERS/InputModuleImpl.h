#pragma once

class InputModuleImpl {
	std::string moduleName;
public:
	InputModuleImpl(std::string moduleName_) :moduleName(moduleName_){}

	std::string GetName() { return moduleName; }

	virtual void Process() = 0;
	virtual ~InputModuleImpl() {}
};