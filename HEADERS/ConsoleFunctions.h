#pragma once
#include "CONSOLE.h"

class ShowFPS :public ConsoleFunHandler<TYPELIST_1(int)> {
	bool display;
	double timeBuffer;
	unsigned probes;
	const unsigned maxProbes = 1000.0;

	FONT fpsFont;
	double fontHeight;
	Vector color;
	CONSOLE::ScreenParameters screenParams;
public:
	ShowFPS() :display(false),probes(0),timeBuffer(0.0),ConsoleFunHandler("ShowFPS") {
		fpsFont.Initilize("Arial", 24, WinAPIwindow::hDC);
		fontHeight = CONSOLE::GetScreenFontHeight(24);
		color = { 0,1,0 };
	}

	void Launch() {
		if (val1 == 1) display = true;
		else if (val1 == 0) display = false;
		else {
			error.code = 1;
			error.msg = "Wrong value. Only 0 and 1 accepted!";
		}
	}

	void Display() {
		if (display) {
			timeBuffer += ((double)(TIMER::GetTime("FPS")) / 1000000.0);
			++probes;
			int fps = (int)(1.0 / (timeBuffer / (double)probes));

			screenParams = CONSOLE::GetScreenParameters();
			Vector pos = { screenParams.textScreenWidth - 5.0*fontHeight,screenParams.textScreenHeight - fontHeight, screenParams.textScreenDepth };
			CONSOLE::WriteTextOnScreen(pos, "FPS: "+std::to_string(fps), color, fpsFont);

			if (probes > maxProbes) { 
				probes = 0;
				timeBuffer = 0;
			}
		}
	}
};