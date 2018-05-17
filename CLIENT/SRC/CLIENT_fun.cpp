#include "CLIENT_fun.h"

void ClientInitialization() {

	InitializeLights();
	InitializeMaterials();

	InitializePlayer();
	InitializePlayerInput();
	InitializeConsoleInput();
	//InitializeBots();
	//InitializeCharacters();
	InitializeMaps();

	InitializeCamera();
	InitializeCameraInput();
}

//inicjalizacja o�wietlenia sceny
void InitializeLights() {
	//stworzenie testowego �r�d�a �wiat�a
	Light TEST_LIGHT(GL_LIGHT0, lightPosition | ambientLight | diffuseLight);
	TEST_LIGHT.SetAmbientParams((float)0.4, (float)0.4, (float)0.4, (float)1.0);
	TEST_LIGHT.SetDiffuseParams((float)0.4, (float)0.4, (float)0.4, (float)1.0);
	TEST_LIGHT.SetPosition(0.0, 100.0, 5.0);

	TEST_LIGHT.Initialize();													//inicjalziacja �wiat�a
	TEST_LIGHT.EnableLight();													//'w��czenie' �r�d�a �wiat�a

	GameObjects::lights.push_back(TEST_LIGHT);									//dodanie �r�d�a �wiat�a do odpowiedniego wektora
	GraphicsMODULE::RegisterLight(GameObjects::lights[0]);
}

//inicjalizacja materia��w [funkcja testowa]
void InitializeMaterials() {
	GraphicsMODULE::RegisterMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

//inicjalizacja postaci gracza [klasa Player]
void InitializePlayer() {
	Vector position = { 4.0,1.0,6.0 };											//pozycja
	Vector orientation = { 0.0,0.0,0.0 };										//orientacja

	for (Map& map : GameObjects::maps) {
		if (map.IsEnabled()) {
			position.y = map.Get_Y_Pos(position);
			break;
		}
	}
	Player* PLAYER = new Player("PLAYER_MODEL_1.obj", "PLAYER", position, orientation);

	//Player PLAYER("PLAYER_MODEL_1.obj", "PLAYER", position, orientation);		//inicajlizacja obiektu gracza
	PLAYER->SetBasicSpeed(15.0);
	//PLAYER->SetSpeed(15.0);														//ustawienie odpowiedniej warto�ci pr�dko�ci
	PLAYER->SetTurnSensitivity(0.1);												//ustawienie odpowiedniej warto�ci czu�o�ci obrotu
	PLAYER->SetJumpStrength(30.0);
	PLAYER->SetWeight(9.0);
	//PLAYER.AddWeapon("GUN_1");
	PLAYER->enableCharacter();													//uruchomienie postaci

	GameObjects::players.push_back(PLAYER);										//dodanie nowej postaci do kontenera przechowuj�cego wszystkie postacie

	Player* player = GameObjects::players[GameObjects::players.size() - 1];
	CharacterRegister::RegisterPlayer(player);
	CharacterPhysicsModelsRegister::Register(player);
	CharacterPhysicsModelsRegister::GetCharacterPhysicsModels(player)->RegisterModel(new StandardCollision());
	//BulletCollision::RegisterGun(&(static_cast<GunImpl&>(*(GameObjects::players[GameObjects::players.size() - 1].GetWeapon()))));
}

//inicjalizacja wszystkich bot�w
void InitializeBots() {
	Vector position = { 10.0,1.0, 5.0 };
	Vector orientation = { 0.0,-45.0,0.0 };

	srand(static_cast<unsigned>(time(0)));

	for (unsigned int i = 0; i <20; i++) {
		orientation.y = rand() % 180;
		position.x = (rand() % 60) - 30;
		position.z = (rand() % 60) - 30;
		AddNewBot(position, orientation);
	}

	for (Bot& bot : GameObjects::bots)
		CharacterRegister::RegisterBot(&bot);
}

//inicjalizacja postaci [klasa Character]
void InitializeCharacters() {

}

//inicjalizacja map [klasa Map]
void InitializeMaps() {
	Map MAP("MAP2.obj");
	MAP.enableCharacter();

	Character TEST1("model5.obj", "TEST1", Vector(0, 2, 25), Vector(0, 90, 0));
	TEST1.enableCharacter();
	Character TEST2("model6.obj", "TEST2", Vector(8, 0, 15), Vector(0, 0, 0));
	TEST2.enableCharacter();
	Character TEST3("model6.obj", "TEST3", Vector(6, 0, 12), Vector(0, 0, 0));
	TEST3.enableCharacter();
	Character TEST4("model6.obj", "TEST4", Vector(25, -2, -30), Vector(0, 45, 0));
	TEST4.enableCharacter();
	Character TEST5("model6.obj", "TEST5", Vector(30, -2, -32), Vector(0, 0, 0));
	TEST5.enableCharacter();
	Character TEST6("model5.obj", "TEST6", Vector(-8, 2, 15), Vector(0, 180, 0));
	TEST6.enableCharacter();
	Character TEST7("model5.obj", "TEST7", Vector(0, 2, 15), Vector(0, 0, 0));
	TEST7.enableCharacter();
	Character TEST8("model7.obj", "TEST8", Vector(-3, 4, 30), Vector(180, 0, 0));
	TEST8.enableCharacter();
	Character TEST9("model7.obj", "TEST9", Vector(5, 1, 0), Vector(0, 0, 0));
	TEST9.enableCharacter();
	Character TEST10("model8.obj", "TEST10", Vector(10, 1, 40), Vector(0, 0, 0));
	TEST10.enableCharacter();
	Character TEST11("model9.obj", "TEST11", Vector(20, 2, 30), Vector(0, 45, 0));
	TEST11.enableCharacter();

	MAP.LoadCharacter(TEST1);
	MAP.LoadCharacter(TEST2);
	MAP.LoadCharacter(TEST3);
	MAP.LoadCharacter(TEST4);
	MAP.LoadCharacter(TEST5);
	MAP.LoadCharacter(TEST6);
	MAP.LoadCharacter(TEST7);
	MAP.LoadCharacter(TEST8);
	MAP.LoadCharacter(TEST9);
	MAP.LoadCharacter(TEST10);
	MAP.LoadCharacter(TEST11);

	MAP.Initialize();

	GameObjects::maps.push_back(MAP);

	CharacterRegister::RegisterMap(&GameObjects::maps[GameObjects::maps.size() - 1]);
}

//inicjalizacja kamery w �wiecie gry
void InitializeCamera() {
	Camera* camera = new Camera(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0, Camera::Mode::BOUND);

	camera->SetRelativeCenter(0.0, 0.0, 32.0);									//ustawienie pozycji punktu w kirunku kt�rym 'patrzy' kamera wzgl�dem gracza

	camera->InitializeCharacter(*(CharacterRegister::GetPlayer()));

	camera->SetThirdPerson();

	camera->SetName("Main");
	camera->SetSpeed(20.0);
	camera->SetTurnSensitivity(0.2);

	GraphicsMODULE::RegisterCamera(camera);
	GraphicsMODULE::SetMainCamera(camera);
}

//dodanie nowego bota
void AddNewBot(const Vector& position, const Vector& orientation) {
	Vector botPos = position;
	for (Map& map : GameObjects::maps) {
		if (map.IsEnabled()) {
			botPos.y = map.Get_Y_Pos(botPos);
			break;
		}
	}

	Bot newBot("PLAYER_MODEL_1.obj", "BOT_" + std::to_string(GameObjects::bots.size()), botPos, orientation);
	newBot.SetSpeed(10.0);
	newBot.SetWeight(9.0);
	newBot.SetTurnSensitivity(0.1);
	newBot.enableCharacter();
	GameObjects::bots.push_back(newBot);
}

void InitializePlayerInput() {
	GAMEINPUT::RegisterStandardInput();

	Player* player = GameObjects::players[0];

	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new LookLeftAction(player,&GAMEINPUT::GetMouse()->mouseMove.x));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new LookRightAction(player, &GAMEINPUT::GetMouse()->mouseMove.x));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new LookUpAction(player, &GAMEINPUT::GetMouse()->mouseMove.y));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new LookDownAction(player, &GAMEINPUT::GetMouse()->mouseMove.y));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new SetNextPositionAction(player));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new AirAction(player));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new JumpAction(CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new FallAction(CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new LandAction(CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new ForwardAction(player, CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new BackwardAction(player, CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new LeftAction(player, CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new RightAction(player, CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new MoveToPosAction(player, CharacterRegister::GetPlayerActionsModule()->Get("Air")));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new HalfSpeedAction(player));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new FullSpeedAction(player));
	CharacterRegister::GetPlayerActionsModule()->RegisterAction(new ForceFallAction(CharacterRegister::GetPlayerActionsModule()->Get("Air")));

	PlayerInput* input = static_cast<PlayerInput*>(ActionsMODULE::GetInputModule("PlayerInput"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::W),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(),"Forward"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::S),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "Backward"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::A),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "Left"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::D),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "Right"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_LEFT),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "LookLeft"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_RIGHT),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "LookRight"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_UP),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "LookUp"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_DOWN),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "LookDown"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::SPACE),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "Jump"));


	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::W, KeyboardInputSignal::Code::A),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDownCombo),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "HalfSpeed"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::W, KeyboardInputSignal::Code::D),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDownCombo),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "HalfSpeed"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::S, KeyboardInputSignal::Code::A),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDownCombo),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "HalfSpeed"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::S, KeyboardInputSignal::Code::D),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDownCombo),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "HalfSpeed"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::W, KeyboardInputSignal::Code::S),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyUpCombo),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "FullSpeed"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::A, KeyboardInputSignal::Code::D),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyUpCombo),
		new PlayerSignalHandler(CharacterRegister::GetPlayerActionsModule(), "FullSpeed"));
}

void InitializeCameraInput() {
	Actions* mainCamActionsMod = GraphicsMODULE::GetMainCameraActionsModule();
	Camera* mainCam = GraphicsMODULE::GetMainCamera();
	ActionsMODULE::RegisterInputModule(new PlayerInput("Camera"));
	PhysicsMODULE::RegisterAdditionalActionsModules(mainCamActionsMod);

	ActionsMODULE::GetActionsModule()->RegisterAction(new SetCameraFree(mainCam,"Camera"));
	ActionsMODULE::GetActionsModule()->RegisterAction(new ResetCameraFree(ActionsMODULE::GetActionsModule()->Get("SetCameraFree")));

	ActionsMODULE::RegisterInputSignal(new KeyboardInputSignal(KeyboardInputSignal::Code::RCTRL),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(ActionsMODULE::GetActionsModule(), "SetCameraFree"));

	ActionsMODULE::RegisterInputSignal(new KeyboardInputSignal(KeyboardInputSignal::Code::RCTRL),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyUp),
		new PlayerSignalHandler(ActionsMODULE::GetActionsModule(), "ResetCameraFree"));

	mainCamActionsMod->RegisterAction(new CameraForwardAction(mainCam));
	mainCamActionsMod->RegisterAction(new CameraBackwardAction(mainCam));
	mainCamActionsMod->RegisterAction(new CameraRightAction(mainCam));
	mainCamActionsMod->RegisterAction(new CameraLeftAction(mainCam));
	mainCamActionsMod->RegisterAction(new CameraUpAction(mainCam));
	mainCamActionsMod->RegisterAction(new CameraDownAction(mainCam));
	mainCamActionsMod->RegisterAction(new CameraLookUp(mainCam, &GAMEINPUT::GetMouse()->mouseMove.y));
	mainCamActionsMod->RegisterAction(new CameraLookDown(mainCam, &GAMEINPUT::GetMouse()->mouseMove.y));
	mainCamActionsMod->RegisterAction(new CameraLookLeft(mainCam, &GAMEINPUT::GetMouse()->mouseMove.x));
	mainCamActionsMod->RegisterAction(new CameraLookRight(mainCam, &GAMEINPUT::GetMouse()->mouseMove.x));

	PlayerInput* input = static_cast<PlayerInput*>(ActionsMODULE::GetInputModule("Camera"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::W),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(mainCamActionsMod, "CameraForward"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::S),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(mainCamActionsMod, "CameraBackward"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::D),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(mainCamActionsMod, "CameraRight"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::A),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(mainCamActionsMod, "CameraLeft"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::SPACE),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(mainCamActionsMod, "CameraUp"));

	input->Register(new KeyboardInputSignal(KeyboardInputSignal::Code::LCTRL),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(mainCamActionsMod, "CameraDown"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_UP),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(mainCamActionsMod, "CameraLookUp"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_DOWN),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(mainCamActionsMod, "CameraLookDown"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_LEFT),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(mainCamActionsMod, "CameraLookLeft"));

	input->Register(new MouseInputSignal(MouseInputSignal::Code::MOUSE_RIGHT),
		new InputFunHandler<MouseImpl>(GAMEINPUT::GetMouse(), &MouseImpl::GetMouseMove),
		new PlayerSignalHandler(mainCamActionsMod, "CameraLookRight"));
}

void InitializeConsoleInput() {
	ActionsMODULE::GetActionsModule()->RegisterAction(new Press_tilde());
	ActionsMODULE::GetActionsModule()->RegisterAction(new Release_tilde(ActionsMODULE::GetActionsModule()->Get("press_tilde")));

	ActionsMODULE::RegisterInputSignal(new KeyboardInputSignal(KeyboardInputSignal::Code::TILDE),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyDown),
		new PlayerSignalHandler(ActionsMODULE::GetActionsModule(), "press_tilde"));

	ActionsMODULE::RegisterInputSignal(new KeyboardInputSignal(KeyboardInputSignal::Code::TILDE),
		new InputFunHandler<KeyboardImpl>(GAMEINPUT::GetKeyboard(), &KeyboardImpl::KeyUp),
		new PlayerSignalHandler(ActionsMODULE::GetActionsModule(), "release_tilde"));
}