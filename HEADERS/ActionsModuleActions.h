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
				ActionsMODULE::SetCurrentInputModule(ActionsMODULE::GetLastInputModuleName());
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

struct SetCameraFree: public ActionImpl{
	Camera* camera;
	std::string cameraInputModuleName;
	bool status;

	SetCameraFree(Camera* camera_, std::string camerInputModuleName_) :status(true), camera(camera_), cameraInputModuleName(camerInputModuleName_), ActionImpl("SetCameraFree") { }

	void operator()() {
		if (status && !CONSOLE::GetTerminalStatus()) {
			if (camera->GetMode() == Camera::Mode::BOUND) {
				camera->SetMode(Camera::Mode::FREE);
				ActionsMODULE::SetCurrentInputModule("Camera");
			}
			else {
				camera->SetMode(Camera::Mode::BOUND);
				ActionsMODULE::SetCurrentInputModule("PlayerInput");
			}
			status = false;
		}
	}
};

struct ResetCameraFree :public ActionImpl {
	SetCameraFree* setCameraFree;

	ResetCameraFree(ActionImpl* setCamera_) :ActionImpl("ResetCameraFree") {
		setCameraFree = static_cast<SetCameraFree*>(setCamera_);
	}

	void operator()() {
		setCameraFree->status = true;
	}
};