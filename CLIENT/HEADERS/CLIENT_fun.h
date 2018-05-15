#pragma once
#include <GAMElogic.h>
#include "CLIENT_GameObjects.h"

void ClientInitialization();

void InitializeLights();									
void InitializeMaterials();

void InitializePlayer();								
void InitializeBots();									
void InitializeCharacters();								
void InitializeMaps();			
void InitializeCamera();

void InitializePlayerInput();

void InitializeConsoleInput();

void AddNewBot(const Vector& position, const Vector& orientation);