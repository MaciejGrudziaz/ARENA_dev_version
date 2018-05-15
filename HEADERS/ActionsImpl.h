#pragma once
#include "GameObjects.h"
#include <map>

struct ActionImpl{
	std::string name;
	ActionImpl(std::string name_) :name(name_){}
	virtual void operator()() = 0;
	bool operator==(std::string str) {
		if (str == name) return true;
		else return false;
	}
	virtual ~ActionImpl() {}
};

class Actions:public ActionManager {
	typedef std::map<std::string, ActionImpl*> ActionsMap;
	ActionsMap actions;
public:
	typedef void(Actions::*ActionsFun)(std::string);
	static ActionsFun Perform;

	void RegisterAction(ActionImpl* action_) { 
		actions.insert(ActionsMap::value_type(action_->name, action_)); 
	}
	ActionImpl* Get(std::string actionName){
		ActionsMap::iterator it = actions.find(actionName);
		if (it != actions.end())
			return (*it).second;
		else throw std::exception();
	}
	void operator()(std::string actionName) {
		ActionsMap::iterator it = actions.find(actionName);
		if (it != actions.end())
			(*(*it).second)();
		else {
			std::string msg = actionName + " no action Found!";
			throw std::exception(msg.c_str());
		}
	}
};
