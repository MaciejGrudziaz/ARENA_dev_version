#include "InputSystemImpl.h"

void StandardInputSystem::Init() {
	if (WinAPIwindow::fullscreen) DIRECTINPUT::Initialize();								//jeœli apliakcja znajduje siê w trybie pe³noekranowym to wywo³¹j inicjalizacjê z trybem 'ekskluzywnym'
	else DIRECTINPUT::Initialize(false);													//jesli nie to wy³¹cz tryb 'ekskluzywny'
	//TRYB EKSKLUZYWNY:
	//	tryb w któym nie widaæ myszy na ekranie oraz jest ona na wy³¹cznoœæ obecnej apliakcji
}

void StandardInputSystem::Update() {
	DIRECTINPUT::Update();
}

void StandardInputSystem::Shutdown() {
	DIRECTINPUT::Shutdown();
}