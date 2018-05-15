#include "StandardCollision.h"

//przetwarzanie 'fizyki' gry
void StandardCollision::Process() {
	if(character->IsEnabled())
		character->AddCollisionState(CheckCharacterCollisions(*CharacterRegister::GetMap(), *character));
}

GAMEPHYSICS::CollisionStatus StandardCollision::CheckCharacterCollisions(const Map& map, const DynamicCharacter& character) {
	GAMEPHYSICS::CollisionStatus colStatus; 
	if (map.IsEnabled() && character.IsEnabled()) {
		GAMEPHYSICS::specialNormals normals;														//wektor 'specjalnych' normalnych [noramlna+dodatkowe informacje o kolizji]											
		Vector position = character.getPosition();													//pobranie aktualnej pozycji gracza
		double yMapVal = map.Get_Y_Pos(position);													//wczytanie wart. wsp. Y mapy dla danej pozycji w (X,Z)

		normals = LoadCharacterCollisionNormals(map, character);									//wczytanie normalnych do wszystkich �cian z kt�rymi zachodzi kolizja

		if (normals.size() == 0) {
			GAMEPHYSICS::CollisionVectorCheck mapBoundriesCol = CheckMapBoundries(map, character);
			NoCollisionState(character, map, yMapVal,mapBoundriesCol);								//funkcja stanu dla braku kolizji
			colStatus.mapBoundriesCol.collisionOccured = mapBoundriesCol.collisionOccured;
		}
		else {
			Vector newNextPos;																		//nowa warto�� nast�pnej pozycji gracza ['nextPosition']

			GAMEPHYSICS::ColContain_AllColTypeVec allColStruct;
			allColStruct = CreateDotProductVectors(map, character, normals);						//inicjalizacja wekotr�w dla wszystkich typ�w kolizji

			AdjustNextPos(allColStruct, character, map, yMapVal);						//obliczenie nowej pozycji gracza na podstawie wczytanych wektor�w kolizji

			colStatus = LoadCollisionStatusRetVal(allColStruct);
		}
	}

	return colStatus;
}

//pobranie normalnych z obiektami z kt�rymi zasz�a kolizja
GAMEPHYSICS::specialNormals StandardCollision::LoadCharacterCollisionNormals(const Map& map, const DynamicCharacter& character) {
	GAMEPHYSICS::specialNormals normals;
	ModelCollision col;																							//struktura reprezentuj�ca kolizj�
	std::vector<unsigned> charIdx = map.GetSectorCharactersIdx(character.getPosition(), 
		character.getCollisionBox().radius);																		//wczytanie indeks�w obiekt�w 'Character' z danego sektora mapy
	for (unsigned idx : charIdx) {
		col = CollisionDetection::CheckCollision3D(character, map.GetCharacter(idx));								//sprawdzenie czy zasz�a kolizja z danym obiektem 'Character'
		if (col.status) {																						//je�li zasz�a kolizja
			CollisionNormals charNormals = CollisionDetection::GetCollisonFaceNormals(character,
				map.GetCharacter(idx), col);																	//wczytaj wszystkie normalne dla kolizji z danym obiektem
			for (std::pair<Vector, unsigned> charN : charNormals) {
				GAMEPHYSICS::SpecialNormalStruct newN;															//stworzenie 'specjanej' struktury dla danej normalnej kolizji
				newN.normal = charN.first;
				newN.linesCrossed = charN.second;
				newN.charIdx = idx;
				newN.objIdx = -1;
				normals.push_back(newN);																		//dodanie 'specjalnej' normalnej do wektora zwracanego
			}
		}
	}
	std::vector<unsigned> objIdx = map.GetSectorObjectsIdx(character.getPosition(),
		character.getCollisionBox().radius);																		//wczytanie indeks�w podstawowych obiekt�w z danego sektora mapy  
	for (unsigned idx : objIdx) {
		col = CollisionDetection::CheckCollision3D(character, map, idx);												//sprawdenie czy zasz�a kolizja z danym obiektem mapy
		if (col.status) {																						//je�li zasz�a kolizja
			CollisionNormals objNormals = CollisionDetection::GetCollisonFaceNormals(character, map, col);			//wczytanie wszystkie normalne dla kolizji z danym obiektem
			for (std::pair<Vector, unsigned> charN : objNormals) {
				GAMEPHYSICS::SpecialNormalStruct newN;															//stworzenie 'specjalnej' struktury dla danej normalnej kolizji
				newN.normal = charN.first;
				newN.linesCrossed = charN.second;
				newN.objIdx = idx;
				newN.charIdx = -1;
				normals.push_back(newN);																		//dodanie specjalnej normalnej do wektora zwracanego
			}
		}
	}
	
	return normals;
}

//rozdzielenie wektora normalnych kolizji na podstawie iloczynu skalarnego z [0,1,0]
GAMEPHYSICS::ColContain_AllColTypeVec StandardCollision::CreateDotProductVectors(const Map& map, const DynamicCharacter& character, GAMEPHYSICS::specialNormals& normals) {
	GAMEPHYSICS::ColContain_AllColTypeVec colRetStruct;
	//colRetStruct.allColCont.standardCol.clear(); colRetStruct.allColCont.negativeCol.clear(); colRetStruct.allColCont.groundCol.clear();
	Vector Y(0, 1, 0);
	for (GAMEPHYSICS::SpecialNormalStruct& colN : normals) {
		colN.dotY = colN.normal.DotProduct(Y);																	//obliczenie iloczynu skalarnego normalnej z wektorem [0,1,0]
		
		if (colN.dotY < 0) colRetStruct.allColVec.negativeCol.push_back(colN);															//przydzielenie wekotra do odpowiedniej grupy 																				
		else if (colN.dotY <= 0.5) colRetStruct.allColVec.standardCol.push_back(colN);													//na podstawie obliczonego iloczynu sklaranego
		else colRetStruct.allColVec.groundCol.push_back(colN);
	}

	//posortowanie wekotr�w normalnych dla ka�dego typu w zalezno�ci od wyniku testu RayCast
	SortVector(colRetStruct.allColVec.standardCol);
	SortVector(colRetStruct.allColVec.negativeCol);
	SortVector(colRetStruct.allColVec.groundCol);

	colRetStruct.allColType.standardCol = StandardColState(colRetStruct.allColVec.standardCol, character);
	colRetStruct.allColType.negativeCol = NegativeColState(colRetStruct.allColVec.negativeCol, character);
	colRetStruct.allColType.groundCol = GroundColState(colRetStruct.allColVec.groundCol, character);
	colRetStruct.allColType.mapBoundriesCol = CheckMapBoundries(map, character);

	return colRetStruct;
}

//posortowanie wektora normalnych ze wzgl�du na param. 'linesCrossed'
void StandardCollision::SortVector(GAMEPHYSICS::specialNormals& colVec) {
	if(colVec.size()>1)
		sort(colVec.begin(), colVec.end(), 
			[](GAMEPHYSICS::SpecialNormalStruct& a, GAMEPHYSICS::SpecialNormalStruct& b)->bool {return a.linesCrossed > b.linesCrossed; });
}

//funkcja stanu dla braku kolizji
void StandardCollision::NoCollisionState(const DynamicCharacter& character, const Map& map, double yMapVal, const GAMEPHYSICS::CollisionVectorCheck& mapBoundriesCol) {
	Vector position = character.getPosition(), nextPosition = character.GetNextPosition();
	Vector minPoint = character.getCollisionBox().minPoint;
	/*if (position.y+minPoint.y >= yMapVal+0.1) {																	//je�li gracz znajduje si� nad poweirzchni� mapy
		if (!character.CheckAirAction()) {																		//je�li dla psotaci gracza nie ma aktualnie akcji spadania
			FALL_ACTION fall(position, nextPosition-position);													//stw�rz akcj� spadania
			character.AddAction(fall);																				//dodaj j� do akcji gracza
		}
	}
	else {																										//w przeciwnym wypadku 
		nextPosition.y = yMapVal - minPoint.y;																	//wyznacz nast�pn� pozycj� Y gracza								
		character.RemoveAirAction();																				//usu� akcj� spadania gracza
	}*/

	commManager->AddPacket(*actions, Actions::Perform, "Air");
	Vector size = character.getCollisionBox().size;
	if (mapBoundriesCol.collisionOccured) {
		static_cast<SetNextPositionAction*>(actions->Get("SetNextPosition"))->Set(mapBoundriesCol.nextPos);
		commManager->AddPacket(*actions, Actions::Perform, "SetNextPosition");
	}
	else {
		if (position.y + minPoint.y >= yMapVal+0.01*size.y) 
			commManager->AddPacket(*actions, Actions::Perform, "Fall");
		else {
			nextPosition.y = yMapVal - minPoint.y;
			static_cast<AirAction*>(actions->Get("Air"))->Set_yMapVal(yMapVal-minPoint.y);
			commManager->AddPacket(*actions, Actions::Perform, "Land");
		}
	}
}

//obliczenie nowej pozycji dla standardowej kolizji
GAMEPHYSICS::CollisionVectorCheck StandardCollision::StandardColState(GAMEPHYSICS::specialNormals& standardCol, const DynamicCharacter& character) {
	Vector position = character.getPosition(), nextPosition = character.GetNextPosition();
	GAMEPHYSICS::CollisionVectorCheck standardColPair;															//struktura przechowuj�ca now� pozycj� gracza dla danej kolizji 
																												//oraz inf. czy kolizja na pewno zasz�a
	standardColPair.collisionOccured = false;
	GAMEPHYSICS::specialNormals newStandardCol;																	//wektor pomocniczy

	if (standardCol.size() > 0) {
		//przefiltrowanie wektora 'specjalnych' normalnych [usuni�cie wekotr�w o podobnym zwrocie]
		for (GAMEPHYSICS::SpecialNormalStruct& n : standardCol) {
			if (!CollisionDetection::GettingOutOfCollision(character, n.normal)) {								//je�li posta� nie 'wychodzi' z kolizji
				if (newStandardCol.size() > 0) {																//jesli zosta� ju� dodany obiekt do wektora pomocniczego
					double dotProduct = newStandardCol[0].normal.DotProduct(n.normal);							//oblicz iloczyn skalarny normalnej z wekotra pomocniczego z aktualnie badan� normaln�  
					if (dotProduct < 0.9) {																		//jesli jest on mniejszy od 0.9 [normaln� rozbiegaj� si�]
						newStandardCol.push_back(n);															//dodaj dan� normaln� do wektora pomocniczego
					}
				}
				else newStandardCol.push_back(n);																//dodanie pierwsego el. do wektora pomocniczego
			}
		}
		if (newStandardCol.size()==1) {																			//je�li w wyniku przefiltrowania zosta� tylko jeden wektor
			Vector move = CollisionDetection::GettingIntoCollision(character, newStandardCol[0].normal);		//na jego podstawie oblicz now� pozycj� gracza dla kolizji standardowej
			nextPosition.x = position.x + move.x;
			nextPosition.z = position.z + move.z;
			standardColPair.collisionOccured = true;															//potwierd� �e zasz�a kolizja
			standardColPair.charIdx = newStandardCol[0].charIdx;
			standardColPair.objIdx = newStandardCol[0].objIdx;
		}
		else {																									//w przeciwnym wypadku
			if(newStandardCol.size()>1) nextPosition = position;												//zablokuj posta� gracza [zderzenie ze �cianami w r�nych p�aszczyznach]
			standardColPair.collisionOccured = true;															//potwierd� �e zasz�a kolizja
		}
	}

	standardColPair.nextPos = nextPosition;																		//przypisanie wart. nowej pozycji gracza dla kolizji standardowej
	return standardColPair;
}

//obliczenie nowej pozycji dla 'negatywnej' kolziji
GAMEPHYSICS::CollisionVectorCheck StandardCollision::NegativeColState(GAMEPHYSICS::specialNormals& negativeCol, const DynamicCharacter& character) {
	Vector position = character.getPosition(), nextPosition = character.GetNextPosition();
	GAMEPHYSICS::CollisionVectorCheck negativeColPair;															//struktura przechowuj�ca now� pozycj� gracza dla danej kolizji 
																												//oraz inf. czy kolizja na pewno zasz�a
	negativeColPair.collisionOccured = false;													
	if (negativeCol.size() > 0) {																				
		if (!CollisionDetection::GettingOutOfCollision(character, negativeCol[0].normal)) {						//je�li posta� nie wychodzi z kolizji
			nextPosition.y = position.y;																		//zablokowanie postaci w aktualnej pozycji Y
			Vector adjustedNormal = negativeCol[0].normal;														//pobranie normalnej z najwiekszym wynikiem dla testu RayCast
			adjustedNormal.y = 0;																				//wyzerowanie wsp. Y [interesuje nas tylko przesuniecie w (X,Z)]
			Vector move = CollisionDetection::GettingIntoCollision(character, adjustedNormal);						//obliczenie nowego wektora przesuni�cia dla kolizji
			nextPosition.x = position.x + move.x;																//obliczeni nowej pozycji gracza na podsatwie kolizji
			nextPosition.z = position.z + move.z;

			negativeColPair.collisionOccured = true;															//potwierd� �e kolizja zasz�a
		}
	}
		
	negativeColPair.nextPos = nextPosition;																		//przypisanie nowej pozycji gracza dla danej kolizji																
	return negativeColPair;
}

//obliczenie nowej pozycji dla pozycji z obiektem pod�o�a
GAMEPHYSICS::CollisionVectorCheck StandardCollision::GroundColState(GAMEPHYSICS::specialNormals& groundCol, const DynamicCharacter& character) {
	Vector position = character.getPosition(), nextPosition = character.GetNextPosition();
	GAMEPHYSICS::CollisionVectorCheck groundColPair;															//struktura przechowuj�ca now� pozycj� gracza dla danej kolizji
																												//oraz inf. czy kolizja na pewno zasz�a
	groundColPair.collisionOccured = false;
	if (groundCol.size() > 0) {
		if (!CollisionDetection::GettingOutOfCollision(character, groundCol[0].normal)) {							//je�li posta� nie wychodzi z kolizji
			Vector move = CollisionDetection::GettingIntoCollision(character, groundCol[0].normal);				//obliczenie nowego wektora przesuni�cia dla kolizji
			nextPosition.x = position.x + move.x;
			nextPosition.z = position.z + move.z;
			nextPosition.y = position.y + move.y;

			groundColPair.collisionOccured = true;																//potwierd� �e kolizja zasz�a
		}
	}

	groundColPair.nextPos = nextPosition;																		//przypisanie nowej pozycji gracza dla danej kolizji
	return groundColPair;
}

//dosotosowanie obliczonego wektora nowej pozycji ze wzgl�du na obecne kolizje
void StandardCollision::AdjustNextPos(const GAMEPHYSICS::ColContain_AllColTypeVec& allColstruct, const DynamicCharacter& character, const Map& map, double yMapVal) {
	Vector position = character.getPosition(), nextPosition = character.GetNextPosition();
	Vector newNextPos;
	if (allColstruct.allColType.mapBoundriesCol.collisionOccured)
		newNextPos = allColstruct.allColType.mapBoundriesCol.nextPos;
	else {

		//----------------------------------------------------------
		bool colChecked = false;
		if (allColstruct.allColType.standardCol.charIdx != -1 || allColstruct.allColType.standardCol.objIdx != -1) {
			if (allColstruct.allColType.standardCol.charIdx != -1) {
				Vector colCharMax = map.GetCharacter(allColstruct.allColType.standardCol.charIdx).getCollisionBox().maxPoint;
				Vector colCharPos = map.GetCharacter(allColstruct.allColType.standardCol.charIdx).getPosition();
				Vector colCharMaxTransform = colCharMax + colCharPos;
				Vector charSize = character.getCollisionBox().size;
				Vector charMin = character.getCollisionBox().minPoint;

				if (position.y + charSize.y / 10.0 > colCharMaxTransform.y) {
					newNextPos = nextPosition;
					newNextPos.y = colCharMaxTransform.y - charMin.y;
					colChecked = true;
				}
			}
			else {
				Vector colObjMax = map.getObjectMainCollisionBox(allColstruct.allColType.standardCol.objIdx).maxPoint;
				Vector charSize = character.getCollisionBox().size;
				Vector charMin = character.getCollisionBox().minPoint;

				if (position.y + charSize.y / 10.0 > colObjMax.y) {
					newNextPos = nextPosition;
					newNextPos.y = colObjMax.y - charMin.y;
					colChecked = true;
				}
			}
		}
		//----------------------------------------------------------

		if (!colChecked) {
			if (allColstruct.allColType.standardCol.collisionOccured) {													//je�li zasz�a standardowa kolizja
				if (allColstruct.allColType.negativeCol.collisionOccured) {												//je�li zasz�a 'negatywna' kolizja
					newNextPos = position;																				//zablokuj ruch postaci gracza
				}
				else if (allColstruct.allColType.groundCol.collisionOccured) {											//je�li zasz�a kolizja z obiektem z obiektem pod�o�a
					newNextPos = position;																				//pozostaw pozyche w (X,Z) bez zmian
					newNextPos.y = allColstruct.allColType.groundCol.nextPos.y;											//zmie� pozycj� w Y zgodnie z groundCol
				}
				else {
					newNextPos = allColstruct.allColType.standardCol.nextPos;											//je�li zasz�a kolizja tylko z obiektem pod�o�a, wyznacz na jej podstawie now� poz.	
				}
			}
			else if (allColstruct.allColType.negativeCol.collisionOccured) {											//je�li nie szasz�a standardowa kolizja, ale zasz�a koliza 'negatywna'
				if (allColstruct.allColType.groundCol.collisionOccured)													//je�li zasz�a kolizja z obiektem pod�o�a
					newNextPos = position;																				//zablokuj ruch postaci gracza
				else newNextPos = allColstruct.allColType.negativeCol.nextPos;											//je�li zasz�a tylko 'negatywna' kolizja - wyznacz na jej podst. now� poz.
			}
			else if (allColstruct.allColType.groundCol.collisionOccured)												//je�li zasz�a tylko kolzizja z obiektem pod�o�a
				newNextPos = allColstruct.allColType.groundCol.nextPos;													//wyznacz na jej podstawie now� pozycj� postaci
			else newNextPos = nextPosition;																				//je�li nie zasz�a �adna kolizja pozostaw now� posta� gracza bez zmian

		}
	}

	AdjustNextPos_AdjustGroundCollisionAndFallAction(character, newNextPos, yMapVal,allColstruct);		//dostosuj wyznaczon� now� posta� gracza ze wzgl�du na akcj� spadania i kolizj�
																													//z obiektem pod�o�a
	//return newNextPos;
}

//dostosowanie obliczonego wektora nowej pozycji ze wzgl�du na kolzij� z pod�o�em i akcji spadania gracza
void StandardCollision::AdjustNextPos_AdjustGroundCollisionAndFallAction(const DynamicCharacter& character, const Vector& adjustedNextPos, double yMapVal, 
	const GAMEPHYSICS::ColContain_AllColTypeVec& allColStruct) {
	unsigned groundColVecSize = allColStruct.allColVec.groundCol.size();
	Vector position = character.getPosition(), nextPosition = character.GetNextPosition();
	Vector minPt = character.getCollisionBox().minPoint;
	Vector newNextPos = adjustedNextPos;

	//----------------------------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------TODO------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------
	/*if (position.y + minPt.y > yMapVal + 0.1) {																	//je�li posta� gracza znajduje si� nad pod�o�em mapy
		if (groundColVecSize==0) {																				//je�li nie znalezniono �adnego wektora kolziji z obiektem pod�o�a
			if (character.CheckAirAction()) {																	//je�li dla postaci istnieje akacja 'powietrzna'
				if(!allColStruct.allColType.negativeCol.collisionOccured)										//je�li nie zasz�a 'ujemna' kolizja
					newNextPos.y = nextPosition.y;																//nowa pozycja Y postaci gracza pochodzi z akcji spadania
				else {
					character.RemoveAirAction();																//usuni�cie aktualnej akcji 'powietrznej'
					FALL_ACTION fall(position, (nextPosition - position));										//stw�rz akcj� spadania
					character.AddAction(fall);																	//dodaj j� do akcji postaci
				}
			}
			else {																								//w przeciwnym wypadku
				FALL_ACTION fall(position, (nextPosition - position));											//stw�rz akcj� spadania
				character.AddAction(fall);																		//dodaj j� do akcji postaci
			}
		}
		else {																									//je�li zachodzi jakakolwiek kolzija z obiektem pod�o�a [nawet 'wyj�cie' z kolizji]
			character.RemoveAirAction();																		//usu� akcj� spadania postaci
		}
	}

	if (position.y + minPt.y <= yMapVal) {																		//je�li posta� znajduje si� pod poweirzchni� mapy
		if (groundColVecSize == 0) {																			//je�li nie zachodzi jakakolwiek kolizja z obiektem pod�o�a
			newNextPos.y = yMapVal - minPt.y;																	//wczytaj now� pozycj� Y postaci przy pomocy mapy
			character.RemoveAirAction();																		//usu� akcj� spadania dla postaci
		}
	}*/

	Vector size = character.getCollisionBox().size;
	if (position.y + minPt.y > yMapVal+size.y*0.01) {
		if (groundColVecSize == 0) {
			if (allColStruct.allColVec.negativeCol.size()>0)
				commManager->AddPacket(*actions, Actions::Perform, "ForceFall");
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->air = true;
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->nextPos = newNextPos;
			commManager->AddPacket(*actions, Actions::Perform, "MoveToPos");
		}
		else {
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->land = true;
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->nextPos = newNextPos;
			commManager->AddPacket(*actions, Actions::Perform, "MoveToPos");
			commManager->AddPacket(*actions, Actions::Perform, "Air");
		}
	}
	else {
		if (groundColVecSize == 0) {
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->land = true;
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->nextPos = newNextPos;
			commManager->AddPacket(*actions, Actions::Perform, "MoveToPos");
		}
		else {
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->land = true;
			static_cast<MoveToPosAction*>(actions->Get("MoveToPos"))->nextPos = newNextPos;
			commManager->AddPacket(*actions, Actions::Perform, "MoveToPos");
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------

	//return newNextPos;
}

//sprawdzenie czy posta� nie wyjdzie poza granice mapy
GAMEPHYSICS::CollisionVectorCheck StandardCollision::CheckMapBoundries(const Map& map, const DynamicCharacter& character) {
	Vector nextPosition = character.GetNextPosition();
	GAMEPHYSICS::CollisionVectorCheck retVal;
	retVal.nextPos = nextPosition;
	Vector mapMaxPt = map.GetMaxPoint();
	Vector mapMinPt = map.GetMinPoint();
	double r = character.getCollisionBox().radius;
	for (unsigned int i = 0; i < 3; i++) {																		//dla wsp�rz�nych (X,Z)
		if (i != 1 && nextPosition[i] + r >= mapMaxPt[i]) {														//je�li nast�pna pozycja gracza b�dzie poza granicami mapy (z b��dem r�wnym R postaci)
			retVal.nextPos = character.getPosition();															//zablokuj ruch postaci
			retVal.collisionOccured = true;
		}
		if (i != 1 && nextPosition[i] - r <= mapMinPt[i]){
			retVal.nextPos = character.getPosition();
			retVal.collisionOccured = true;
		}
	}

	return retVal;
}

//za�adowanie statusu zwracanego dla badanej kolizji
GAMEPHYSICS::CollisionStatus StandardCollision::LoadCollisionStatusRetVal(const GAMEPHYSICS::ColContain_AllColTypeVec& allColStruct) {
	GAMEPHYSICS::CollisionStatus colStatus;

	colStatus.groundCol.collisionOccured = allColStruct.allColType.groundCol.collisionOccured;				//status dla kolizji z obiektem 'pod�o�a'
	if (allColStruct.allColVec.groundCol.size() > 0) colStatus.groundCol.collisionNormal = allColStruct.allColVec.groundCol[0].normal;
	colStatus.negativeCol.collisionOccured = allColStruct.allColType.negativeCol.collisionOccured;			//status dla 'neagtywnej' kolizji
	if (allColStruct.allColVec.negativeCol.size() > 0) colStatus.negativeCol.collisionNormal = allColStruct.allColVec.negativeCol[0].normal;
	colStatus.standardCol.collisionOccured = allColStruct.allColType.standardCol.collisionOccured;			//status dla standardowej kolizji
	if (allColStruct.allColVec.standardCol.size() > 0) colStatus.standardCol.collisionNormal = allColStruct.allColVec.standardCol[0].normal;
	colStatus.mapBoundriesCol.collisionOccured = allColStruct.allColType.mapBoundriesCol.collisionOccured;	//status dla kolizji z granic� mapy

	return colStatus;
}
