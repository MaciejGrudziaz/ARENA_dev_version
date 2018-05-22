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

	for (KeyboardInputCode& input : inputCodesVec) {
		Register(new KeyboardInputSignal(input.code),
			new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
			new PlayerSignalHandler(CONSOLE::GetActionsModule(), input.sign));
	}

	/*Register(new KeyboardInputSignal(KeyboardInputSignal::Code::A),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "a"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::B),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "b"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::C),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "c"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::D),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "d"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::E),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "e"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::F),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "f"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::G),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "g"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::H),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "h"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::I),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "i"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::J),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "j"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::K),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "k"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::L),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "l"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::M),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "m"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::N),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "n"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::O),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "o"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::P),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "p"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::Q),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "q"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::R),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "r"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::S),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "s"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::T),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "t"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::U),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "u"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::V),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "v"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::W),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "w"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::X),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "x"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::Y),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "y"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::Z),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "z"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::_0),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "0"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::_1),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "1"));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::_9),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "9"));*/


	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::EQUALS),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "="));
	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::DECIMAL_POINT),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CONSOLE::GetActionsModule(), "."));
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