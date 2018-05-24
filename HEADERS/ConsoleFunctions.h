#pragma once
#include "CONSOLE.h"
#include "ActionsMODULE.h"
#include "GraphicsMODULE.h"

class ShowFPS :public ConsoleFunHandler<TYPELIST_1(int)> {
	bool display;
	double timeBuffer;
	unsigned probes;
	const unsigned maxProbes = 1000;

	FONT font;
	unsigned fontSize;
	double fontHeight;
	Vector color;
	CONSOLE::ScreenParameters screenParams;
	HDC hDC;
public:
	ShowFPS() :display(false),probes(0),fontSize(18),timeBuffer(0.0),ConsoleFunHandler("ShowFPS") {
		hDC = WinAPIwindow::hDC;
		font.Initilize("Arial", fontSize, hDC);
		fontHeight = CONSOLE::GetScreenFontHeight(font.GetFontSize());
		color = { 0,1,0 };
	}

	void Launch() {
		if (val1 == 1) display = true;
		else if (val1 == 0) display = false;
		else {
			error.code = 1;
			error.msg = "Wrong value: 0 - hide fps, 1 - show fps";
		}
	}

	void Display() {
		if (display) {
			if (hDC != WinAPIwindow::hDC) {
				hDC = WinAPIwindow::hDC;
				font.Initilize("Arial", fontSize, hDC);
			}

			timeBuffer += ((double)(TIMER::GetTime("FPS")) / 1000000.0);
			++probes;
			int fps = (int)(1.0 / (timeBuffer / (double)probes));

			screenParams = CONSOLE::GetScreenParameters();
			Vector pos = { screenParams.textScreenWidth - 5.0*fontHeight,screenParams.textScreenHeight - fontHeight, screenParams.textScreenDepth };
			CONSOLE::WriteTextOnScreen(pos, "FPS: "+std::to_string(fps), color, font);

			if (probes > maxProbes) { 
				probes = 0;
				timeBuffer = 0;
			}
		}
	}
};

class CameraMode :public ConsoleFunHandler<TYPELIST_1(int)> {
	Camera* camera;
	std::string cameraInputModuleName;
	bool launch;
	bool reset;
public:
	CameraMode(Camera* camera_, std::string cameraInputModuleName_) :camera(camera_), cameraInputModuleName(cameraInputModuleName_), launch(false), reset(false), ConsoleFunHandler("CameraMode") {}

	void Launch() {
		if (val1 == 1) {
			camera->SetMode(Camera::Mode::FREE);
			launch = true;
		}
		else if (val1 == 0) {
			camera->SetMode(Camera::Mode::BOUND);
			reset = true;
		}
		else {
			error.code = 1;
			error.msg = "Wrong value: 0 - free camera, 1 - bound camera";
			launch = false;
			reset = false;
		}
	}

	void Display() {
		if (launch && !CONSOLE::GetTerminalStatus()) {
			ActionsMODULE::SetCurrentInputModule(cameraInputModuleName);
			launch = false;
		}
		if (reset && !CONSOLE::GetTerminalStatus()) {
			ActionsMODULE::SetCurrentInputModule("PlayerInput");
			reset = false;
		}
	}
};