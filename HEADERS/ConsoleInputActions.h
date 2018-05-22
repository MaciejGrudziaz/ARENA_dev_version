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

struct PressRShift :public ActionImpl {
	bool pressed;
	PressRShift() :pressed(false),ActionImpl("PressRShift") {}

	void operator()() {
		pressed = true;
	}
};

struct ReleaseRShift :public ActionImpl {
	bool* pressed;
	ReleaseRShift(ActionImpl* pressLShift_) :ActionImpl("ReleaseRShift") {
		pressed = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}

	void operator()() {
		*pressed = false;
	}
};


template<char value_, char specialValue_>
struct Press :public ActionImpl {
	char basicValue;
	char specialValue;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressRShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), specialValue(specialValue_),basicValue(value_), ActionImpl((Char2String(value_)).str) {
		pressRShift = &(static_cast<PressRShift*>(pressRShift_)->pressed);
	}
	void operator()() {
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			char value;
			if (*pressRShift) value = specialValue;
			else value = basicValue;
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

/*template<>
struct Press<'0'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_,ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('0'), ActionImpl("0") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = ')';
		else value = '0';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'1'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('1'), ActionImpl("1") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '!';
		else value = '1';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'2'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('2'), ActionImpl("2") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '@';
		else value = '2';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'3'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('3'), ActionImpl("3") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '#';
		else value = '3';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'4'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('4'), ActionImpl("4") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '$';
		else value = '4';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'5'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('5'), ActionImpl("5") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '%';
		else value = '5';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'6'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('6'), ActionImpl("6") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '^';
		else value = '6';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'7'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('7'), ActionImpl("7") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '&';
		else value = '7';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'8'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('8'), ActionImpl("8") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '*';
		else value = '8';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};

template<>
struct Press<'9'> :public ActionImpl {
	char value;
	unsigned long delay;
	unsigned long* mainDelay;
	bool* pressRShift;
	Press(unsigned long* mainDelay_, ActionImpl* pressLShift_) :delay(TerminalReadDelayVal), mainDelay(mainDelay_), value('0'), ActionImpl("9") {
		pressRShift = &(static_cast<PressRShift*>(pressLShift_)->pressed);
	}
	void operator()() {
		if (*pressRShift) value = '(';
		else value = '9';
		if ((*mainDelay) - delay >= TerminalReadDelayVal) {
			CONSOLE::Insert(value);
			delay = (*mainDelay);
		}
	}
};*/

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

