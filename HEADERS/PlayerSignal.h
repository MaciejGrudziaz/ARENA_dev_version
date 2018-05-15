#pragma once
#include <TypeList.h>
#include "Manager.h"
#include "ActionsImpl.h"

class PlayerSignalImpl {
public:
	virtual void operator()() = 0;
	virtual ~PlayerSignalImpl() {}
};

class PlayerSignalHandler: public PlayerSignalImpl {
	std::string actionName;
	Actions* action;
public:
	PlayerSignalHandler(Actions* action_,std::string actionName_) :action(action_),actionName(actionName_) { }
	PlayerSignalHandler(const PlayerSignalHandler& handler) :actionName(handler.actionName), action(handler.action) {}
	void operator()() { communicationManager::Instance().AddPacket(*action, &Actions::operator(), actionName); }
};
