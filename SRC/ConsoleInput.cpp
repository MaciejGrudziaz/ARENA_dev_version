#include "ConsoleInput.h"


ConsoleInput::ConsoleInput(std::string moduleName) : delay(0), PlayerInput(moduleName) {
	inputCodesVec.push_back(KeyboardInputCode("a", KeyboardInputSignal::Code::A));
	inputCodesVec.push_back(KeyboardInputCode("b", KeyboardInputSignal::Code::B));
	inputCodesVec.push_back(KeyboardInputCode("c", KeyboardInputSignal::Code::C));
	inputCodesVec.push_back(KeyboardInputCode("d", KeyboardInputSignal::Code::D));
	inputCodesVec.push_back(KeyboardInputCode("e", KeyboardInputSignal::Code::E));
	inputCodesVec.push_back(KeyboardInputCode("f", KeyboardInputSignal::Code::F));
	inputCodesVec.push_back(KeyboardInputCode("g", KeyboardInputSignal::Code::G));
	inputCodesVec.push_back(KeyboardInputCode("h", KeyboardInputSignal::Code::H));
	inputCodesVec.push_back(KeyboardInputCode("i", KeyboardInputSignal::Code::I));
	inputCodesVec.push_back(KeyboardInputCode("j", KeyboardInputSignal::Code::J));
	inputCodesVec.push_back(KeyboardInputCode("k", KeyboardInputSignal::Code::K));
	inputCodesVec.push_back(KeyboardInputCode("l", KeyboardInputSignal::Code::L));
	inputCodesVec.push_back(KeyboardInputCode("m", KeyboardInputSignal::Code::M));
	inputCodesVec.push_back(KeyboardInputCode("n", KeyboardInputSignal::Code::N));
	inputCodesVec.push_back(KeyboardInputCode("o", KeyboardInputSignal::Code::O));
	inputCodesVec.push_back(KeyboardInputCode("p", KeyboardInputSignal::Code::P));
	inputCodesVec.push_back(KeyboardInputCode("q", KeyboardInputSignal::Code::Q));
	inputCodesVec.push_back(KeyboardInputCode("r", KeyboardInputSignal::Code::R));
	inputCodesVec.push_back(KeyboardInputCode("s", KeyboardInputSignal::Code::S));
	inputCodesVec.push_back(KeyboardInputCode("t", KeyboardInputSignal::Code::T));
	inputCodesVec.push_back(KeyboardInputCode("u", KeyboardInputSignal::Code::U));
	inputCodesVec.push_back(KeyboardInputCode("v", KeyboardInputSignal::Code::V));
	inputCodesVec.push_back(KeyboardInputCode("w", KeyboardInputSignal::Code::W));
	inputCodesVec.push_back(KeyboardInputCode("x", KeyboardInputSignal::Code::X));
	inputCodesVec.push_back(KeyboardInputCode("y", KeyboardInputSignal::Code::Y));
	inputCodesVec.push_back(KeyboardInputCode("z", KeyboardInputSignal::Code::Z));
	inputCodesVec.push_back(KeyboardInputCode("0", KeyboardInputSignal::Code::_0));
	inputCodesVec.push_back(KeyboardInputCode("1", KeyboardInputSignal::Code::_1));
	inputCodesVec.push_back(KeyboardInputCode("2", KeyboardInputSignal::Code::_2));
	inputCodesVec.push_back(KeyboardInputCode("3", KeyboardInputSignal::Code::_3));
	inputCodesVec.push_back(KeyboardInputCode("4", KeyboardInputSignal::Code::_4));
	inputCodesVec.push_back(KeyboardInputCode("5", KeyboardInputSignal::Code::_5));
	inputCodesVec.push_back(KeyboardInputCode("6", KeyboardInputSignal::Code::_6));
	inputCodesVec.push_back(KeyboardInputCode("7", KeyboardInputSignal::Code::_7));
	inputCodesVec.push_back(KeyboardInputCode("8", KeyboardInputSignal::Code::_8));
	inputCodesVec.push_back(KeyboardInputCode("9", KeyboardInputSignal::Code::_9));
}

void ConsoleInput::Process() {
	delay += (unsigned long)PHYSICSCONST::targetFrameTime;
	PlayerInput::Process();
}

void ConsoleInput::Init() {
	CONSOLE::GetActionsModule()->RegisterAction(new PressBackspace(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new NextCommand(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new PreviousCommand(&delay, CONSOLE::GetActionsModule()->Get("NextCommand")));
	CONSOLE::GetActionsModule()->RegisterAction(new PressEnter(&delay, CONSOLE::GetActionsModule()->Get("NextCommand")));
	CONSOLE::GetActionsModule()->RegisterAction(new PressRShift());
	CONSOLE::GetActionsModule()->RegisterAction(new ReleaseRShift(CONSOLE::GetActionsModule()->Get("PressRShift")));

	CONSOLE::GetActionsModule()->RegisterAction(new Press<'a', 'A'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'b', 'B'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'c', 'C'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'d', 'D'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'e', 'E'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'f', 'F'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'g', 'G'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'h', 'H'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'i', 'I'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'j', 'J'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'k', 'K'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'l', 'L'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'m', 'M'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'n', 'N'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'o', 'O'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'p', 'P'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'q', 'Q'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'r', 'R'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'s', 'S'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'t', 'T'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'u', 'U'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'v', 'V'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'w', 'W'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'x', 'X'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'y', 'Y'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'z', 'Z'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));

	CONSOLE::GetActionsModule()->RegisterAction(new Press<'0',')'>(&delay,CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'1','!'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'2','@'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'3','#'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'4','$'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'5','%'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'6','^'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'7','&'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'8','*'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'9','('>(&delay,CONSOLE::GetActionsModule()->Get("PressRShift")));

	CONSOLE::GetActionsModule()->RegisterAction(new Press < '.', '>'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press < ',', '<'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'\'', '"'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'=', '+'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'-', '_'>(&delay, CONSOLE::GetActionsModule()->Get("PressRShift")));

	for (KeyboardInputCode& input : inputCodesVec) {
		Register(new KeyboardInputSignal(input.code),
			new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
			new PlayerSignalHandler(CONSOLE::GetActionsModule(), input.sign));
	}

	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::EQUALS),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "="));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::PERIOD),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "."));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::COMMA),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), ","));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::APOSTROPHE),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "'"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::MINUS),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "-"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::BACKSPACE),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "Backspace"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::ENTER),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "Enter"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::UP),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "NextCommand"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::DOWN),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "PreviousCommand"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::RSHIFT),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "PressRShift"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::RSHIFT),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyUp),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "ReleaseRShift"));
}