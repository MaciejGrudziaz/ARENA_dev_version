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
			CONSOLE::GetTerminalInput(value);
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
			CONSOLE::GetTerminalInput(0x08); 
			delay = (*mainDelay);
		}
	}
};

struct PressEnter :public ActionImpl {
	unsigned long delay;
	unsigned long* mainDelay;
	PressEnter(unsigned long* mainDelay_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), ActionImpl("Enter") {}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::GetTerminalInput(0x0A);
			delay = (*mainDelay);
		}
	}
};
