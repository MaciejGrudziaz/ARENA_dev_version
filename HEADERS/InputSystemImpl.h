#pragma once
#include "DIRECTINPUT.h"

struct InputSystemImpl {
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

	virtual ~InputSystemImpl() {}
};

struct StandardInputSystem :public InputSystemImpl {
	void Init();
	void Update();
	void Shutdown();
	virtual ~StandardInputSystem() {}
};
