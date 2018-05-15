#include "InputSystemImpl.h"

void StandardInputSystem::Init() {
	if (WinAPIwindow::fullscreen) DIRECTINPUT::Initialize();								//je�li apliakcja znajduje si� w trybie pe�noekranowym to wywo��j inicjalizacj� z trybem 'ekskluzywnym'
	else DIRECTINPUT::Initialize(false);													//jesli nie to wy��cz tryb 'ekskluzywny'
	//TRYB EKSKLUZYWNY:
	//	tryb w kt�ym nie wida� myszy na ekranie oraz jest ona na wy��czno�� obecnej apliakcji
}

void StandardInputSystem::Update() {
	DIRECTINPUT::Update();
}

void StandardInputSystem::Shutdown() {
	DIRECTINPUT::Shutdown();
}