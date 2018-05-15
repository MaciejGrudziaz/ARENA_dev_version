#include "BulletCollision.h"

BulletCollision* BulletCollision::instance = NULL;
std::vector<Gun*> BulletCollision::gunRegister;

//pobranie instancji modelu
BulletCollision* BulletCollision::GetInstance() {
	if (instance == NULL)																								//je�li isntancja modelu nie zosta�a jeszcze stworzona	
		instance = new BulletCollision();																				//stw�rz j�

	return instance;																									//zwr�� instancj� modelu
}

//wyrejestrowanie obiektu broni
void BulletCollision::UnregisterGun(Gun* _gun) {
	for (auto it = gunRegister.begin(); it != gunRegister.end(); it++) {												
		if (*it == _gun) {																								//je�li wska�nik broni w rejestrze jest r�wny danemu wsk�nikowi '_gun'
			gunRegister.erase(it);																						//usu� dany element z wektora
		}
	}
}

//przetworzenie modelu fizyki
void BulletCollision::Process() {
	AnalyzeShotsFired();																								//analiza wszystkich wystrzelonych pocisk�w [z zarejestrowanych broni]
}

//funkcja analizuj�ca wszystkie wystrzelone pociski
void BulletCollision::AnalyzeShotsFired() {
	for (Gun* gun : gunRegister) {																						//z rejestr zarejestrowanych broni
		if (gun->GetShotsFiredCount() > 0) {																			//je�li dana bro� posiada wystrzelone pociski
			for (unsigned i = 0; i < gun->GetShotsFiredCount(); i++) {
				if (!gun->GetBullet(i).hit)																				//je�li pocisk jeszcze nie zderzy� si� z �adnym obiektem
					BulletRayCastAlgorithm(gun->GetBullet(i), BULLET::DYNAMIC);											//wykonaj dla niego algorytm RayCast [w wersji dynamicznej]
			}
			gun->UpdateBullets();																						//aktualizuj wszytkie wystrzelone pociski dla danej broni
		}
	}
}

//wykonanie algorytmu RayCast dla danego pocisku
void BulletCollision::BulletRayCastAlgorithm(Bullet& bullet,BULLET::RayCastVer version) {
	Map* map = CharacterRegister::GetMap();																				//pobierz obiekt mapy z g��wnego rejestru

	if (map->IsEnabled()) {																								//je�li mapa jest odblokowana
		switch (version) {																								//wybierz dan� wersj� algirytmu RayCast
		case BULLET::INSTANT:																							//INSTANT - kolizja natychmiastowa badana w tej samej klatce co wystrzelono pocisk
			BulletRayCastInstantHit(*map, bullet);																		//wywo�anie alogorytmu RayCAst w wersji INSTANT
			break;
		case BULLET::DYNAMIC:																							//DYNAMIC - pocisk jest przesuwany w ka�dej kl., kolzija badana jest dla jego akt. poz.
			BulletRayCastDynamic(*map, bullet);																			//wywo�anie algorytmu RayCast w wersji DYNAMIC
			break;
		}
	}
}

//g��wne cia�o algorytmu RayCast w wersji INSTANT [kolizja pocisku badana jest w tej samej klatce w kt�rej zosta� wystrzelony, dla wszystkich pocisk�w na jego torze lotu] 
void BulletCollision::BulletRayCastInstantHit(Map& map, Bullet& bullet) {
	IdxPair mainSectorIdx = map.GetSectorIdx(bullet.startPos);															//indeks sekotra podstawowego [w kt�rym aktualnie znajduje si� pocisk]
	bool collisionOccured = false;																						//zmienna okre�laj�ca czy kolizja zasz�a
	BULLET::newSector newSectorIdxAndPositon;																			//struktura przechowuj�ca dane o nowym sektorze i pozycji pocisku															

	double shift;																										//wart. przesuni�cia dla pocisku w kolejnych iteracjach algorytmu
	std::pair<double, double> sectorShift = map.GetSectorShift();														//pobranie wymiar�w (X,Z) sektora mapy
	if (bullet.direction.x > bullet.direction.z) shift = sectorShift.first;												//przypisanie do zmiennej 'shift' wymiaru dla kt�rego pocisk przebywa wi�ksz� drog� 
	else shift = sectorShift.second;

	while (!collisionOccured) {																							//dop�ki nie zasz�a kolizja pocisku
		std::vector<IdxPair> neighboursIdx;																	
		neighboursIdx = BulletRayCastInstantHit_GetSectorNeighbours(map, bullet, mainSectorIdx);						//pobierz indeksy s�siad�w dla aktualnego sektora podstawowego

		if (BulletRayCastInstantHit_CheckCollision(bullet, map, mainSectorIdx, neighboursIdx))							//sprawdzenie czy zachodzi kolizja w sektorze podstawowym lub w sek. s�siad�w
			collisionOccured = true;
											
		newSectorIdxAndPositon = BulletRayCastInstantHit_GetNewMainSectorIdx(mainSectorIdx, bullet, shift, map);		//pobranie nowego sektora podstawowego i pozycji pocisku
		if (!newSectorIdxAndPositon.insideMap) {																		//je�li nowowyznaczona pozycja pocisku znajduje si� poza granicami mapy
			bullet.hitPos = newSectorIdxAndPositon.position;															//przypisz j� jako pozycj� kolziji pocisku
			bullet.hit = true;																				
			collisionOccured = true;																					//zako�cz wykonywanie algorytmu
		} 
		else if (BulletRayCastInstantHit_CheckGroundCol(map, bullet, newSectorIdxAndPositon.position))					//je�li zachodzi kolizja z pod�o�em mapy
			collisionOccured = true;																					//zako�cz wykonywanie algorytmu

		mainSectorIdx = newSectorIdxAndPositon.sectorIdx;																//przypisz now� wart. indeksu podstawowego sektora
		bullet.actualPos = newSectorIdxAndPositon.position;																//przypisz now� wart. pozycji pocisku
	}
}

//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z innym obiektem
bool BulletCollision::BulletRayCastInstantHit_CheckCollision(Bullet& bullet,Map& map, IdxPair mainSectorIdx, std::vector<IdxPair>& neighboursIdx) {
	BULLET::BulletColStruct bulletCol;																					//struktura przechowuj�ca dane na temat kolizji pocisku
	bulletCol = CheckSectorBulletCollision(mainSectorIdx, bullet);														//sprawdzenie kolizji pocisku w sekotrze podstawowym
	if (bulletCol.collisionOccured) {																					//je�li kolizja zasz�a
		if (bulletCol.charHitPtr != NULL)																				
			bulletCol.charHitPtr->disableCharacter();																	//wy��cz obiekt z kt�rym zasz�a kolizja		
		bullet.hitPos = bulletCol.collisionPos;																			//przypisz wart. wsp. kolizji pocisku
		bullet.hit = true;																								//ustaw potwierdzenie kolizji dla pocisku

		return true;
	}
	else {																												//je�li nie wykryto kolizji w sektorze podstawowym
		for (IdxPair sectorIdx : neighboursIdx) {																		//sprawd� sekotry s�siaduj�ce
			bulletCol = CheckSectorBulletCollision(sectorIdx, bullet);													//sprawdzenie kolizji w danym sekotrze s�siednim
			if (bulletCol.collisionOccured) {																			//jesli kolzija zasz�a
				if (bulletCol.charHitPtr != NULL)	
					bulletCol.charHitPtr->disableCharacter();															//wy��cz obiekt z kt�ym zasz�a kolizja
				bullet.hitPos = bulletCol.collisionPos;																	//przypisz wart. wsp. kolizji pocsiku
				bullet.hit = true;																						//ustaw potwierdzenie kolizji dla pocisku

				return true;
			}
		}
	}

	return false;
}

//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z pod�o�em
bool BulletCollision::BulletRayCastInstantHit_CheckGroundCol(Map& map, Bullet& bullet, Vector newPos) {
	Vector mapSize = map.GetMaxPoint() - map.GetMinPoint();																//wielko�� mapy
	double dist;																	
	if (mapSize.x < mapSize.z)																							//zdefiniwoanie zmiennej 'dist' jako najmniejszego wymiaru sektora mapy wsp. Y
		dist = mapSize.x / MAP::stdMapDiv;
	else
		dist = mapSize.z / MAP::stdMapDiv;

	Vector actNewVec = newPos - bullet.actualPos;																		//wektor przesuni�cia mi�dzy now�, a poprzedni� pozycj� pocisku
	Vector checkPos = bullet.actualPos + bullet.direction*dist;															//nowa pozycja do sprawdzenia kolizji z pod�o�em
	Vector shift = newPos - checkPos;																					//wektor przesuni�cia mi�dzy now� pozycj�, a pozycj� sprawdzan� pocisku

	while (actNewVec.DotProduct(shift) >= 0) {																			//'checkPos' nie min�a jeszcze 'newPos'
		if (checkPos.y < map.Get_Y_Pos(checkPos)) {																		//je�li wart. wsp. y dla sprawdzanej pozycji jest mniejsza ni� wart. wsp. Y dla mapy
			bullet.hitPos = checkPos;																					//przypisz t� wsp. jako wsp. kolizji pocisku
			bullet.hit = true;																							//ustaw potwierdzenie kolizji pocisku
			return true;
		}
		checkPos += bullet.direction*dist;																				//w przeciwnhym wypadku wyznacz now� wart. wsp. pozycji do sprawdzenia
		shift = newPos - checkPos;																						//oblicz now� wart. wektora przesuni�cia od pomi�dzy sprawdzan�, a now� pozycj� pocisku
	}

	return false;
}

//pobranie indeks�w sektor�w s�siad�w do aktualnego sektora
std::vector<IdxPair> BulletCollision::BulletRayCastInstantHit_GetSectorNeighbours(Map& map, const Bullet& bullet, const IdxPair& sectorIdx) {
	std::vector<IdxPair> neighboursIdx;																					//wektor indeks�w sektor�w s�siad�w
	IdxPair neighbour;																									//indeks sektora
	if (bullet.direction.x >= 0 && bullet.direction.z >= 0) {															//je�li pocisk skierowany jest wzd�u� dodatnich osi X i Z
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::TOP);														//pobranie 'g�rnego' s�siada dla danego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);													//je�li s�siad istnieje dodaj go do wektora
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::TOP_RIGHT);												//pobranie 'prawego-g�rnego' s�siada dla danego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::RIGHT);													//pobranie 'prawego' s�siada dla danego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
	}
	if (bullet.direction.x >= 0 && bullet.direction.z < 0) {															//jesli pocisk jest skierowany wzd�uz dodatniej osi X i ujemnej Z
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::RIGHT);													//pobranie 'prawego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::BOTTOM_RIGHT);											//pobranie 'prawego-dolnego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::BOTTOM);													//pobranie 'dolnego' sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
	}
	if (bullet.direction.x < 0 && bullet.direction.z < 0) {																//je�li pocisk skierowany jest wzd�u� ujemnych osi X i Z
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::BOTTOM);													//pobranie 'dolnego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::BOTTOM_LEFT);												//pobranie 'lewego-dolnego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::LEFT);													//pobranie 'lewego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
	}
	if (bullet.direction.x < 0 && bullet.direction.z >= 0) {															//jesli pocisk jest skierowany wzd�u� ujemnej osi X i dodatniej osi Z
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::LEFT);													//pobranie 'lewego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::TOP_LEFT);												//pobranie 'g�rnego-lewego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
		neighbour = map.GetSectorNeighbourIdx(sectorIdx, MAP::TOP);														//pobranie 'g�rnego' s�siedniego sektora
		if (neighbour != sectorIdx) neighboursIdx.push_back(neighbour);
	}

	return neighboursIdx;
}

//pobranie nowego sektora do algorytmu
BULLET::newSector BulletCollision::BulletRayCastInstantHit_GetNewMainSectorIdx(const IdxPair& mainSectorIdx, const Bullet& bullet, const double shift, Map& map) {
	BULLET::newSector retVal;																							//wart. zwracana nowego sektora
	IdxPair newMainSectorIdx = mainSectorIdx;																			//indeks nowego sektora podstawowego
	Vector newPos = bullet.actualPos;																					//nowa pozycja pocisku
	Vector minMap = map.GetMinPoint(), maxMap = map.GetMaxPoint();														//min. i maks. wsp�rz�dne mapy

	while (newMainSectorIdx == mainSectorIdx) {																			//dop�ki nowo wyznaczony sektor jest identyczny z aktulanym sektorem
		newPos += bullet.direction*shift;																				//wyznacz now� pozycje pocisku
		retVal.position = newPos;
		if (newPos.x > maxMap.x || newPos.z > maxMap.z || newPos.y>1000.0)												//jesli nowowyznaczona pozycja jest poza granicami mapy
			return retVal;																								//zako�cz poszuiwanie nowego punktu
		if (newPos.x < minMap.x || newPos.z < minMap.z || newPos.y<-1000.0)
			return retVal;
		newMainSectorIdx = map.GetSectorIdx(newPos);																	//w przecienym wypadku wyznacz indeks sektora dla nowowyznaczonej pozycji
	}

	retVal.sectorIdx = newMainSectorIdx;																				//przypisz indeks sektora do wart. zwracanej
	retVal.insideMap = true;																							//ustaw potweirdzenie �e nowa pozycja pocisku znajduje si� wewn�trz mapy

	return retVal;
}

//g��wne cia�o algorytmu RayCast w wersji DYNAMIC [w ka�dej kolejnej klatce pocisk jest przesuwany i badana jest kolizja w stosunku do jego aktualnej pozycji]
void BulletCollision::BulletRayCastDynamic(Map& map, Bullet& bullet) {
	if (!BulletRayCastDynamic_CheckMapBoundries(map,bullet)){
		IdxPair mainSectorIdx = map.GetSectorIdx(bullet.actualPos);														//indeks sektora dla aktualnej pozycji
		IdxPair prevPosSecIdx = map.GetSectorIdx(bullet.previousPos);													//indeks sektora dla poprzedniej pozycji
			
		BulletRayCastDynamic_CheckCollision(map, bullet, mainSectorIdx, bullet.actualPos);								//sprawd� kolizj� pocisku w aktualnym sektorze

		if (prevPosSecIdx != mainSectorIdx && !bullet.hit)																//je�li indeksy poprz.o i akt. sektora nie s� sobie r�wne i nie zasz�al kolizja
			BulletRayCastDynamic_CheckCollision(map, bullet, prevPosSecIdx, bullet.actualPos);							//sprawd� kolizj� pocisku w poprzednim sektorze

		BulletRayCastDynamic_CheckGroundCol(map, bullet);																//sprawd� kolizj� pocisku z pod�o�em
	}
}

//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z innym obiektem
bool BulletCollision::BulletRayCastDynamic_CheckCollision(Map& map, Bullet& bullet,MAP::IdxPair sectorIdx, Vector bulletPos) {
	BULLET::BulletColStruct bulletCol = CheckSectorBulletCollision(sectorIdx, bullet);									//sprawdzenie kolizji pocisku w danym sektorze
	Vector startActShift, actColShift, prevColShift;																					

	if (bulletCol.collisionOccured) {
		startActShift = bullet.actualPos - bullet.startPos;																//wektor od pozycji startowej do aktualnej pocisku
		actColShift = bulletCol.collisionPos - bullet.actualPos;														//wektor od aktualnej pozycji pocisku do pozycji w kt�rej zasz�a kolizja

		if (startActShift.DotProduct(actColShift) < 0 ) {																//je�li punkt kolizji znajduje si� 'przed' aktualn� pozycj� pocisku															
			if (bulletCol.charHitPtr != NULL) {																			//je�li wyznaczono wska�nik na obiekt z kt�rym zasz�a kolizja
				//bulletCol.charHitPtr->disableCharacter();																//'wy��cz' dany obiekt
				if (bulletCol.charHitPtr->IsEnabled())
					bulletCol.charHitPtr->SubstractHealth(static_cast<unsigned>(bullet.damage));
			}
			
			bullet.hitPos = bulletCol.collisionPos;																		//przypisz wart. do poz. kolizji pocisku
			bullet.hit = true;																							//przypisz potwierdzenie trafienia do pocisku
			return true;
		}
	}
	return false;
}

//funkcja sprawdzaj�ca czy pocisk wyszed� poza granice mapy
bool BulletCollision::BulletRayCastDynamic_CheckMapBoundries(Map& map, Bullet& bullet) {
	Vector minMap = map.GetMinPoint(), maxMap = map.GetMaxPoint();														//pobrnie min. i max. punktu mapy
	if (bullet.actualPos.x > maxMap.x || bullet.actualPos.z > maxMap.z || bullet.actualPos.y > 1000.0 ||				//sprawdzenie czy aktualna pozycja pocisku nie mie�ci si� w granicach mapy
		bullet.actualPos.x < minMap.x || bullet.actualPos.z < minMap.z || bullet.actualPos.y < -1000.0) {
		bullet.hitPos = bullet.actualPos;																				//je�li tak to przypisz aktualn� pozycj� pocisku jako pozycj� kolizji 
		bullet.hit = true;																								//przypisz potwierdzenie trafienia dla pocisku

		return true;

	}
	else return false;
}

//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z pod�o�em
bool BulletCollision::BulletRayCastDynamic_CheckGroundCol(Map& map, Bullet& bullet) {
	if (bullet.actualPos.y < map.Get_Y_Pos(bullet.actualPos)-0.1) {														//je�li aktulana pozycja pocisku znajduje si� pod powierzchni� mapy
		bullet.hitPos = bullet.actualPos;																				//przypisz pozycj� kolizji pocisku jako aktualn� pozycj�
		bullet.hit = true;																								//przypisz potwierdzenie trafienia dla pocisku
		return true;
	}
	
	//w przeciwnym wypadku
	Vector shift = bullet.actualPos - bullet.previousPos;																//oblicz wektor przesuni�cia od poprzedniej do aktualnej pozycji pocisku
	Vector newPos = bullet.actualPos - bullet.direction*(shift.MOD() / 3.0);											//oblicz now� poz. do testu znajduj�c� si� w 1/3 pomi�dzy akt. a poprz. poz.

	if (newPos.y < map.Get_Y_Pos(newPos)-0.1) {																			//je�li pozycja testowa znajduje si� pod powierzchni� mapy
		bullet.hitPos = newPos;																							//przypisz pozycj� kolizji pocisku jako pozycj� testow�
		bullet.hit = true;																								//przypisz potwierdzenie trafienia dla pocisku
		return true;
	}

	newPos = bullet.actualPos - bullet.direction*(2.0*shift.MOD() / 3.0);												//oblicz now� poz. do testu znajduj�c� si� w 2/3 pomi�dzy akt. a poprz. poz.

	if (newPos.y < map.Get_Y_Pos(newPos)-0.1) {																			//je�li pozycja testowa znajduje si� pod powierzchni� mapy
		bullet.hitPos = newPos;																							//przypisz pozycj� kolizji pocsiku jako pozycj� testow�
		bullet.hit = true;																								//przypisz potwierdzenie trafienia dla pocisku
		return true;
	}

	return false;
}

//sprawdzenie kolziji pocisku w danym sektorze
BULLET::BulletColStruct BulletCollision::CheckSectorBulletCollision(IdxPair sectorIdx, Bullet& bullet) {
	BULLET::BulletColStruct mapColStruct, charactersColStruct;															//struktury kolizji dla kolizji z obiektami mapy oraz pozosta�ymi obiektami
	Vector mapShift, charactersShift;																					//wektory przesuni�cia dla wykrytych kolizji
		
	mapColStruct = CheckSectorBulletCollision_Map(sectorIdx, bullet);													//sprawdzenie kolizji z obiektami mapy
	charactersColStruct = CheckSectorBulletCollision_Characters(sectorIdx, bullet);										//sprawdzenie kolziji z pozosta�ymi obiektami

	if (mapColStruct.collisionOccured) {																				//je�li zasz�a kolizja z obeiktem mapy
		if (charactersColStruct.collisionOccured) {																		//je�li zasz�a kolizja z pozosta�ymi obiektami �wiata gry
			mapShift = mapColStruct.collisionPos - bullet.startPos;														//oblicz wektory przesuni�cia dla wykrytych kolizji							
			charactersShift = charactersColStruct.collisionPos - bullet.startPos;
			if (mapShift.MOD() < charactersShift.MOD())																	//wybierz kolizj� kt�ra zasz�a bli�ej od punktu startowego pocisku
				return mapColStruct;
			else return charactersColStruct;
		}
		else return mapColStruct;																						//je�li nie wykryto kolizji z innymi obiektami, zwr�� kolizj� z ob. mapy
	}
	else {																												//je�li nie zasz�a kolizja z obiektem mapy
		if (charactersColStruct.collisionOccured)																		//ale zasz�a kolizja z innym obiektem �wiata gry
			return charactersColStruct;																					//zwr�� struktur� tej kolizji
		else return BULLET::BulletColStruct();																			//w przeciwnym wypadku zwr�� pust� struktur� kolizji
	}
}

//sprawdzenie kolizji pocisku z obiektami umieszczonymi na mapie
BULLET::BulletColStruct BulletCollision::CheckSectorBulletCollision_Map(IdxPair sectorIdx, Bullet& bullet) {
	Map* map = CharacterRegister::GetMap();																				//pobranie wska�nika na aktualn� map�
	std::vector<unsigned> charactersIdx = map->GetSectorCharactersIdx(sectorIdx);										//pobranie indeks�w obiekt�w 'Character' w danym sektorze mapy
	std::vector<unsigned> objIdx = map->GetSectorObjectsIdx(sectorIdx);													//pobranie indeks�w podst. obiekt�w w danym sektorze mapy
	BULLET::BulletColStruct bulletCol;																					//struktury oisuj�ce kolizj� pocisku
	BULLET::BulletColStruct bulletColRet;
	double dist = -1;																									//mininmalny dystans od punktu startowego pocisku do punktu kolizji																								

	/*for (unsigned idx : charactersIdx) {																				//sprawdzenie wszystkich obiekt�w 'Character' w danym sektorze
		if (map->GetCharacter(idx).IsEnabled()) {																		//je�li obiekt jest 'odblokowany'
			bulletCol = CheckBulletCollision(map->GetCharacter(idx), bullet);											//sprawd� kolizj� pocisku z danym obiektem
			if (bulletCol.collisionOccured)																				//je�li kolizja zasz�a
				if (CheckSectorBulletCollision_CheckNewCol(bulletCol, dist, bullet))									//sprawd� czy jest 'lepsza' od poprzedniej 'najlepszej' wykrytej kolizji
					bulletColRet = bulletCol;
		}
	}*/

	for (unsigned idx : objIdx) {																						//sprawdzenie wszystkich podstawowych obiekt�w w danym sektorze
		bulletCol = CheckBulletCollision(*map, idx, bullet);															//sprawd� kolizj� pocisku z danym obiektem
		if (bulletCol.collisionOccured)																					//je�lli kolizja zasz�a
			if (CheckSectorBulletCollision_CheckNewCol(bulletCol, dist, bullet))										//sprawd� czy jest 'lepsza' od poprzedniej 'najlepszej' wykrytej kolizji
				bulletColRet = bulletCol;
	}

	return bulletColRet;																								//zwr�� struktur� kolizji dla obiekt�w mapy w danym sektorze
}

//sprawdzenie kolizji pocisku z pozosta�ymi obiektami �wiata gry
BULLET::BulletColStruct BulletCollision::CheckSectorBulletCollision_Characters(IdxPair sectorIdx, Bullet& bullet) {
	Map* map = CharacterRegister::GetMap();																				//pobierz wska�nik na aktualn� map�
	BULLET::BulletColStruct bulletCol, bulletColRet;																	//struktury opisuj�ce kolizj� pocisku
	double dist = -1;																									//minimalny dystans od punktu startowego pocisku do punktu kolizji
	std::vector<Character*> allObjectsVec;																				//wektor wszystkich obiekt�w do sprawdzenia w sektorze
	Character* _char;																									//wska�nik na dany obiekt

	for (unsigned i = 0; i < CharacterRegister::GetStaticCharacterCount(); i++) {
		_char = CharacterRegister::GetStaticCharacter(i);																//pobranie statycznego obiektu
		if (_char->IsEnabled() && _char->GetSectorIdx() == sectorIdx)													//sprawdzenie czy obiekt jest odbl. i czy znajduje si� w aktualnym sektorze
			allObjectsVec.push_back(_char);																				//je�li tak - dodaj obiekt do kontenera 
	}

	for (unsigned i = 0; i < CharacterRegister::GetDynamicCharacterCount(); i++) {
		_char = static_cast<Character*>(CharacterRegister::GetDynamicCharacter(i));										//pobranie dynamicznego obiektu
		if (_char->IsEnabled() && _char->GetSectorIdx() == sectorIdx)													//sprawdzenie czy obiekt jest odbl. i czy znajduje si� w aktualnym sektorze
			allObjectsVec.push_back(_char);																				//je�li tak - dodaj obiekt do kontenera
	}

	for (unsigned i = 0; i < CharacterRegister::GetBotCount(); i++) {	
		_char = static_cast<Character*>(CharacterRegister::GetBot(i));													//pobranie obiektu bota
		if (_char->IsEnabled() && _char->GetSectorIdx() == sectorIdx)													//sprawdzenie czy obiekt jest odbl. i czy znajduje si� w aktualnym sektorze
			allObjectsVec.push_back(_char);																				//je�li tak - dodaj obiekt do kontenera
	}

	_char = static_cast<Character*>(CharacterRegister::GetPlayer());													//pobranie obiektu postaci gracza
	if (_char->IsEnabled() && _char->GetSectorIdx() == sectorIdx)														//sprawdzenie czy obiekt jest odbl. i czy znajduje si� w aktualnym sektorze
		allObjectsVec.push_back(_char);																					//je�li tak - dodaj obiekt do kontenera

	for (Character* _char : allObjectsVec) {																			//dla wszystkich obiekt�w z kontenera
		bulletCol= CheckBulletCollision(*_char, bullet);																//sprawd� kolizj� dla danego obiektu
		if (bulletCol.collisionOccured)																					//je�li kolizja zachodzi
			if (CheckSectorBulletCollision_CheckNewCol(bulletCol, dist, bullet))										//sprawdzenie czy nowa kolizja jest 'lepsza' od poprzedniej 'najlepszej'
				bulletColRet = bulletCol;																				//je�li tak - przypisz dan� kolizj� jako now� 'najlepsz�'
	}

	return bulletColRet;																								//zwr�� struktur� kolizji dla pozosta�ych obiekt�w w danym sektorze
}

//sprawdzenie nowo wykrytej kolizji [czy jest 'lepsza' od wcze�niejszej]
bool BulletCollision::CheckSectorBulletCollision_CheckNewCol(BULLET::BulletColStruct &bulletCol, double& distance, Bullet& bullet) {
	BULLET::BulletColStruct bulletColRet;																				//zwracana struktura kolizji
	Vector shift;

	if (bulletCol.collisionOccured) {																					//je�li dana kolzija zachodzi
		shift = bulletCol.collisionPos - bullet.startPos;																//oblicz wektor przesuni�cia od poz. startowej pocisku do poz. kolizji
		if (distance == -1) {																							//je�li min. dystans = -1 [nie wykryto jeszcze wcze�niej kolizji]																				
			distance = shift.MOD();																						//przypisz dyst. pomi�dzy pkt. kol. a pkt. start. pocisku jako min. dyst.
			return true;
		}
		else {																											//je�li wcze�niej wykryo kolizj�
			if (shift.MOD() < distance) {																				//sprawd� czy odl. do poz. akt. kolizji jest mniejsza ni� poprz. min. dyst.	
				distance = shift.MOD();																					//przypisz j� jako minimalna odleg�o�� do pozycji kolizji
				return true;
			}
		}
	}

	return false;
}

//sprawdzenie kolizji pocisku z obiektem 'character'
BULLET::BulletColStruct BulletCollision::CheckBulletCollision(Character& character, Bullet& bullet) {
	Vector charPos = character.getPosition();																			//aktualna pozycja danego obiektu
	Vector charMidPt = character.getCollisionBox().midPoint+charPos;													//ppzycja �rodka obiektu
	double charR = character.getCollisionBox().radius;																	//promie� sfery ograniczaj�cej obiekt
	BULLET::BulletColStruct retColStruct;																				//struktura kolizji z obiektem

	Vector PpPi = charMidPt - bullet.startPos;																			//wektor od pkt. start. poc. do pkt. �rodkowego obiektu
	PpPi.NORM();																										//normalizacja wektora
	double dotProdPpPiDir = PpPi.DotProduct(bullet.direction);															//iloczyn sklarany obliczonego wektora z kierunkiem toru pocisku

	if (dotProdPpPiDir >= 0) {																							//je�li pocisk leci w kierunku obiektu
		Vector r = PpPi.CrossProduct(Vector(0, 1, 0));																	//wektor prostopad�y do wek. wskazuj�cego od pkt. start. poc. do �r. obiektu
		r.NORM();																										//normalizacja wektora
		Vector Pir = charMidPt + r*charR;																				//obliczenie pkt. oddalonego o R od pkt. �r. postaci w kierunku wek. 'r'
		Vector PpPir = Pir - bullet.startPos;																			//obl. wek. od pkt. start. poc. do pkt. znajduj�cego si� na sf. ogr. obiekt
		PpPir.NORM();																									//normalizacja wektora
		double dotProdPpPiPpPir = PpPi.DotProduct(PpPir);																//iloczyn skalarny pomi�dzy wekotrami PpPi oraz PpPir

		unsigned objColBoxCount = 0;																					//ilo�� podst. bry� kolziji wchodz�cych w sk�ad pojedynczego obiektu modelu
		if (dotProdPpPiDir >= dotProdPpPiPpPir) {																		//je�li wek. kierunku toru pocisku wskazuje na dany obiekt
			for (unsigned i = 0; i < character.getObjectsCount(); i++) {												//dla wszystkich podstawowych obiekt�w wchodz�cych w sk�ad modelu
				objColBoxCount += character.getObjectCollisionBoxCount(i);												//dodaj ilo�� podst. bry� kolizji wchodz�cych w sk�ad danego obiektu
				retColStruct=CheckBulletCharacterCollision_CheckObject(character, bullet, i);							//sprawd� kolzij� pocisku z danym obiektem podstawowym
				if (retColStruct.collisionOccured)																		//je�li kolzija zachodzi
					return retColStruct;																				//zwr�� otrzymany obiekt kolizji
			}
			if (objColBoxCount == 0) {																					//je�li w sk�ad modelu nie wchodz� �adne podst. bry�y kolizji
				retColStruct = CheckBulletCharacterCollision_CheckObject(character, bullet, -1);						//sprawd� kolizj� z g��wn� bry�� kolizji obiektu
				if (retColStruct.collisionOccured)																		//je�li kolizja zachodzi
					return retColStruct;																				//zwr�� otrzymany obiekt kolizji
			}
		}
		else return BULLET::BulletColStruct();																			//je�li wektor toru pocisku nie jest skierowany do obiektu																
	}																													//zwr�� pusty obiekt kolizji
	else return BULLET::BulletColStruct();																				//je�li wektor toru pocisku jest skierowany w kierunku odwrotnym ni� obiekt
																														//zwr�� pusty obiekt kolizji	
	return BULLET::BulletColStruct();																					//zwr�� pusty obiekt kolizji
}

//sprawdzenie kolizji pocisku z obiektem modelu 'character'
BULLET::BulletColStruct BulletCollision::CheckBulletCharacterCollision_CheckObject(Character& character, const Bullet& bullet, int objIdx) {
	CollisionBox charColBox;																							//struktura opisuj�ca bry�� kolizji
	BULLET::BulletColStruct retColStruct;																				//struktura opisuj�ca kolizj�
	if (objIdx == -1) {																									//je�li arg. indeksu obiektu jest -1
		charColBox = character.getCollisionBox();																		//wczytaj g��wna bry�� kolizji obiektu
		retColStruct = CheckBulletCharacterCollision_CheckObjectColBox(character, bullet, charColBox);					//sprawd� kolizj� z tym hitboxem
		if (retColStruct.collisionOccured)																				//je�li kolizja zachodzi
			return retColStruct;																						//zwr�� obiekt kolizji
	}
	else if(objIdx >= 0 && static_cast<unsigned>(objIdx) < character.getObjectsCount()) {								//je�li podany indeks okre�la kt�ry� z obiekt�w podstawowych
		unsigned charColBoxCount = character.getObjectCollisionBoxCount(objIdx);										//wczytaj liczb� bry� kolizji dla takiego obiektu
		for (unsigned i = 0; i < charColBoxCount; i++) {																//dla wszystkich bry� kolizji
			charColBox = character.getObjectCollisionBox(objIdx,i);														//pobierz dan� bry�e kolizji
			retColStruct = CheckBulletCharacterCollision_CheckObjectColBox(character, bullet, charColBox);				//sprawd� kolizj� dla wybranego hitboxa
			if (retColStruct.collisionOccured)																			//je�li zachodzi kolizja
				return retColStruct;																					//zwr�� obiekt kolizji
		}
	}

	return BULLET::BulletColStruct();																					//je�li ni wykryto kolizji - zwr�� pusty obiekt kolizji
}

//sprawdzenie kolizji pocisku z hitboxem obiektu modelu 'character'
BULLET::BulletColStruct BulletCollision::CheckBulletCharacterCollision_CheckObjectColBox(Character& character, const Bullet& bullet, CollisionBox& objColBox) {
	Face face;																											//struktura opisuj�ca powierzchni� [tr�jk�t]
	Vector vertices[3];																									//tablica wierzcho�k�w wchodz�cych w sk�ad danej powierzchni
	Vector normal;																										//normalna do powierzchni
	Vector pointProjection;																								//rzut punktu na powierzchni�
	unsigned faceCount = objColBox.facesIdx.size();																		//liczba poweirzchni wchodz�cych w sk�ad hitboxa
	for (unsigned i = 0; i < faceCount; i++) {																			//dla wszystkich powierzchni
		face = character.getFace(objColBox.facesIdx[i]);																//pobierz obiekt powierzchni
		normal = character.getTransformedNormal(face.NormalIdx);														//pobierz normaln�
		for (unsigned j = 0; j < 3; j++)											
			vertices[j] = character.getTransformedVertice(face.PointsIdx[j]);											//pobierz wsp�rz�dne wierzcho�k�w powierzchni

		if (normal.DotProduct(bullet.direction) < 0) {																	//je�li normalna do powierzchni jest skierowana odwrotnie do kierunku pocisku
			pointProjection = PointSurfaceProjection(vertices, normal, bullet.startPos, bullet.direction);				//wyznacz rzut pozycji start. pocisku na powierzchni� wzd�u� jego toru lotu

			if (CheckPointInTriangle(pointProjection, vertices, normal))												//je�li rzutowany punkt znajduje sie wewn�trz powierzchni
				return BULLET::BulletColStruct(true, pointProjection,&character);										//zwr�� obiekt kolizji
		}
	}

	return BULLET::BulletColStruct();																					//je�li nie wykryto kolizji - zwr�� pusty obiekt kolizji
}

//sprawdzenie kolizji pocisku z obiektem 'objIdx' mapy
BULLET::BulletColStruct BulletCollision::CheckBulletCollision(Map& map, unsigned objIdx, Bullet& bullet) {
	CollisionBox objColBox;																								//struktura opisuj�ca bry�� kolizji
	BULLET::BulletColStruct bulletCol;																					//struktura opisuj�ca kolizj� pocisku

	if (map.getObjectCollisionBoxCount(objIdx) > 0) {																	//je�li obiekt posiada sk�adowe bry�y kolizji
		for (unsigned i = 0; i < map.getObjectCollisionBoxCount(objIdx); i++) {											//dla ka�dej takiej bry�y kolizji
			objColBox = map.getObjectCollisionBox(objIdx, i);															//pobierz dan� bry� kolizji

			bulletCol = CheckBulletObjectCollision_CheckObjectReach(map, bullet, objColBox);							//sprawd� czy zachodzi kolizja

			if (bulletCol.collisionOccured)																				//je�li tak
				return bulletCol;																						//zwr�� pobrany obiekt kolizji
		}
		return BULLET::BulletColStruct();																				//jesli nie wykryto kolizji - zwr�� pusty obiekt kolizji
	}
	else {																												//je�li obiekt nie posiada sk��dowych bry� kolizji
		objColBox = map.getObjectMainCollisionBox(objIdx);																//pobierz g��wny hitbox obiektu

		return CheckBulletObjectCollision_CheckObjectReach(map, bullet, objColBox);										//sprawd� czy zachodzi kolizja i zwr�c obiekt kolizji [pusty je�li nie zachodzi]
	}
}

//sprawdzenie czy obiekt znajduje si� wewn�trz zasi�gu pocisku 
BULLET::BulletColStruct BulletCollision::CheckBulletObjectCollision_CheckObjectReach(Map& map, Bullet& bullet, CollisionBox& objColBox) {
	BULLET::BulletColStruct retColStruct;																				//struktura opisuj�ca kolizj� pocisku
	//Vector mapPos = map.getPosition();																				//pobranie pozycji mapy
	Vector objMidPt = objColBox.midPoint;// +mapPos;																	//pobranie punktu �rodkowego hitboxa obiektu	
	double objR = objColBox.radius;																						//pobrnaie promienia ograniczaj�cego hitboxa

	Vector PpPi = objMidPt - bullet.startPos;																			//wektor opisuj�ca przemieszczenie z pkt. start. pocisku do �rodka hitboxa
	PpPi.NORM();																										//normalizacja wektora
	double dotProdPpPiDir = PpPi.DotProduct(bullet.direction);															//iloczyn skalarny wektora PpPi z wekotrem kierunku lotu pocisku

	if (dotProdPpPiDir >= 0) {																							//je�li obiekt znajduje si� wzgl. pocisku w tym samym kierunku co jego tor lotu
		Vector r = PpPi.CrossProduct(Vector(0, 1, 0));																	//wektor prostopad�y do PpPi - wskazuj�cy na zewn�trz obiektu od jego �rodka
		r.NORM();																										//normalizacja
		Vector Pir = objMidPt + r*objR;																					//obliczenie punktu znajduj�cego si� na granicy sfery ograniczaj�cej obiekt
		Vector PpPir = Pir - bullet.startPos;																			//obliczenie wekotra rzesuni�cia od �r. pocisku do tego punktu
		PpPir.NORM();																									//normalizacja
		double dotProdPpPiPpPir = PpPi.DotProduct(PpPir);																//iloczyn skalrny PpPi oraz PpPir

		if (dotProdPpPiDir >= dotProdPpPiPpPir) {																		//je�li wektor toru lotu pocisku jest pomi�dzy wektorem PpPi oraz PpPir
			retColStruct = CheckBulletObjectCollision_CheckColBox(map, bullet, objColBox);								//sprawd� kolizj� z danym hitboxem
			if (retColStruct.collisionOccured)																			//je�li kolizja zachodzi 
				return retColStruct;																					//zwr�� pobrany obiekt kolizji
		}
	}

	return BULLET::BulletColStruct();																					//je�li nie weykryto kolizji - zwr�� pusty obiekt kolizji
}

//sprawdzenie bry�y kolziji danego obiektu mapy
BULLET::BulletColStruct BulletCollision::CheckBulletObjectCollision_CheckColBox(Map& map, Bullet& bullet, CollisionBox& objColBox) {
	Face face;																											//struktura opisuj�ca powierzchni� [tr�jk�t]
	Vector vertices[3];																									//wsp�rz�dne wierzcho�k�w powierzchni
	Vector normal;																										//normalna do powierzchni
	Vector pointProjection;																								//rzut punktu na powierzchni�
	unsigned faceCount = objColBox.facesIdx.size();																		//liczba poweirzchni wchodz�cych w sk�ad obiektu
	for (unsigned i = 0; i < faceCount; i++) {																			//dla ka�dej powierzchni
		face = map.getFace(objColBox.facesIdx[i]);																		//pobierz obiekt powierzchni
		normal = map.getTransformedNormal(face.NormalIdx);																//pobierz normaln�
		for (unsigned j = 0; j < 3; j++)	
			vertices[j] = map.getTransformedVertice(face.PointsIdx[j]);													//pobierz wsp�z�dne wierzcho�k�w

		if (normal.DotProduct(bullet.direction) < 0) {																	//je�li normalna do pwoerzchni jest skierowana przeciwnie do toru lotu pocisku
			pointProjection = PointSurfaceProjection(vertices, normal, bullet.startPos, bullet.direction);				//wyznacz rzut pikt. start. pocisku na dan� powierzchni� wzd�u� jego toru lotu 
			if (CheckPointInTriangle(pointProjection, vertices, normal))												//je�li wyznaczony punk znajduje si� wewn�trz powierzchni [kolizja zachodzi]
				return BULLET::BulletColStruct(true, pointProjection);													//zwr�� obiekt kolizji
		}
	}

	return BULLET::BulletColStruct();																					//je�li nie wykryto kolizji - zwr�� pusty obiekt kolizji
}