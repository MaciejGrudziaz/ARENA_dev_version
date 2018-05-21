#include "ConsoleInput.h"

void ConsoleInput::Process() {
	delay += (unsigned long)PHYSICSCONST::targetFrameTime;
	PlayerInput::Process();
}

void ConsoleInput::Init() {
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'a'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'b'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'c'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'d'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'e'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'f'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'g'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'h'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'i'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'j'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'k'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'l'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'m'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'n'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'o'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'p'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'q'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'r'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'s'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'t'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'u'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'v'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'w'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'x'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'y'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'z'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'0'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'1'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'.'>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new Press<'='>(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new PressBackspace(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new NextCommand(&delay));
	CONSOLE::GetActionsModule()->RegisterAction(new PreviousCommand(&delay, CONSOLE::GetActionsModule()->Get("NextCommand")));
	CONSOLE::GetActionsModule()->RegisterAction(new PressEnter(&delay, CONSOLE::GetActionsModule()->Get("NextCommand")));

	Register(new KeyboardInputSignal(KeyboardInputSignal::Code::A),
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
}