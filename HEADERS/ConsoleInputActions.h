#pragma once
#include "ActionsImpl.h"
#include "CONSOLE.h"

namespace {
	const int TerminalReadDelayVal = 150000;

	struct Char2String {
		std::string str;
		Char2String(char c) {
			char* str2;
			str2 = new char[2];
			str2[0] = c;
			str2[1] = NULL;
			str = std::string(str2);
			delete[]str2;
		}
	};
}

template<char value_>
struct Press :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	Press(unsigned long* mainDelay_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value(value_), ActionImpl((Char2String(value_)).str) {}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

struct PressBackspace :public ActionImpl {
	unsigned long delay;
	unsigned long* mainDelay;
	PressBackspace(unsigned long* mainDelay_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), ActionImpl("Backspace") {}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(0x08); 
			delay = (*mainDelay);
		}
	}
};

struct NextCommand :public ActionImpl {
	unsigned long delay;
	unsigned long* mainDelay;
	bool reset;
	int commandIdx;
	NextCommand(unsigned long* mainDelay_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), reset(true), commandIdx(-1), ActionImpl("NextCommand") {}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			std::string line="";
			unsigned terminalLinesNum = CONSOLE::GetTerminalTextLinesSize();
			if (reset) {
				commandIdx = terminalLinesNum;
				reset = false;
			}
			CONSOLE::TerminalTextStruct terminalLine;

			if (--commandIdx < 0) commandIdx = 0;
			terminalLine = CONSOLE::GetTerminalText(commandIdx);

			if (terminalLine.line != "") CONSOLE::SetCurrentTerminalText(terminalLine.line);

			delay = (*mainDelay);
		}
	}
};

struct PreviousCommand :public ActionImpl {
	unsigned long delay;
	unsigned long* mainDelay;
	int* commandIdx;
	bool* reset;
	PreviousCommand(unsigned long* mainDelay_,ActionImpl* nextCommand_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), ActionImpl("PreviousCommand") {
		commandIdx = &(static_cast<NextCommand*>(nextCommand_)->commandIdx);
		reset = &(static_cast<NextCommand*>(nextCommand_)->reset);
	}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			std::string line = "";
			unsigned terminalLinesNum = CONSOLE::GetTerminalTextLinesSize();
			CONSOLE::TerminalTextStruct terminalLine;

			if (*reset == true) {
				*commandIdx = terminalLinesNum;
				*reset = false;
			}

			if (++(*commandIdx) >= terminalLinesNum) *commandIdx = terminalLinesNum-1;
			terminalLine = CONSOLE::GetTerminalText(*commandIdx); 

			if (terminalLine.line != "") CONSOLE::SetCurrentTerminalText(terminalLine.line);
			delay = (*mainDelay);
		}
	}
};

struct PressEnter :public ActionImpl {
	unsigned long delay;
	unsigned long* mainDelay;
	bool* nextCommandActionReset;
	PressEnter(unsigned long* mainDelay_,ActionImpl* nextCommand_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), ActionImpl("Enter") {
		nextCommandActionReset = &(static_cast<NextCommand*>(nextCommand_)->reset);
	}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(0x0A);
			*nextCommandActionReset = true;
			delay = (*mainDelay);
		}
	}
};

