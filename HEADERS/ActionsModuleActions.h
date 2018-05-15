#pragma once
#include "ActionsMODULE.h"
#include "CONSOLE.h"

struct Press_tilde :public ActionImpl {
	bool status;
	Press_tilde() :status(true), ActionImpl("press_tilde") {}

	void operator()() {
		if (status) {
			if (!CONSOLE::GetTerminalStatus()) {
				CONSOLE::ShowTerminal();
				ActionsMODULE::SetCurrentInputModule("Console");
			}
			else {
				CONSOLE::HideTerminal();
				ActionsMODULE::SetCurrentInputModule("PlayerInput");
			}
			status = false;
		}
	}
};

struct Release_tilde :public ActionImpl {
	Press_tilde* press;
	Release_tilde(ActionImpl* press_) :ActionImpl("release_tilde") {
		press = static_cast<Press_tilde*>(press_);
	}

	void operator()() {
		press->status = true;
	}
};