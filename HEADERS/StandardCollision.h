#pragma once
#include "CollisionDetection.h"
#include "GamePhysicsStruct.h"
#include "PhysicsModelImpl.h"
#include "StandardActions.h"

//------------------------------------------------------------------------------------------------
//-------------------------------------------FIZYKA GRY-------------------------------------------
//--------------------klasa odpowiadaj¹ca za przetwarzanie 'fizyki' gry m.in.:--------------------
//-----------------------------------WYKONYWANIE AKCJI POSTACI------------------------------------
//------------------------------------------------------------------------------------------------

class StandardCollision:public PhysicsModelImpl, public CollisionDetection {
	//-------------------------------------------------------------CheckCharacterCollisions()--------------------------------------------------------------
	GAMEPHYSICS::CollisionStatus CheckCharacterCollisions(const Map& map, const DynamicCharacter& character);		//sprawdzenie kolizji dla danej postaci
	//GAMEPHYSICS::AllCollisionsTypesVec LoadAllCollisionTypesVec(Map& map, DynamicCharacter& character, GAMEPHYSICS::specialNormals standardColVec)
	GAMEPHYSICS::specialNormals LoadCharacterCollisionNormals(const Map& map, const DynamicCharacter& character);	//pobranie normalnych z obiektami z którymi zasz³a kolizja
	GAMEPHYSICS::ColContain_AllColTypeVec CreateDotProductVectors(const Map& map, const DynamicCharacter& character, 
		GAMEPHYSICS::specialNormals& normals);																	//rozdzielenie wekotra normalnych kolizji na podstawie iloczynu skalarnego z [0,1,0]
	void SortVector(GAMEPHYSICS::specialNormals& colVec);												//posortowanie wektora normalnych ze wzglêdu na param. 'linesCrossed'
	void NoCollisionState(const DynamicCharacter& character, const Map& map, double yMapVal, 
		const GAMEPHYSICS::CollisionVectorCheck& mapBoundriesCol);												//funkcja stanu dla braku kolizji
	GAMEPHYSICS::CollisionVectorCheck StandardColState(GAMEPHYSICS::specialNormals& standardCol, const DynamicCharacter& character);	//obliczenie nowej pozycji dla standardowej kolizji
	GAMEPHYSICS::CollisionVectorCheck NegativeColState(GAMEPHYSICS::specialNormals& negativeCol, const DynamicCharacter& character);	//obliczenie nowej pozycji dla 'negatywnej' kolziji
	GAMEPHYSICS::CollisionVectorCheck GroundColState(GAMEPHYSICS::specialNormals& groundCol, const DynamicCharacter& character);		//obliczenie nowej pozycji dla pozycji z obiektem pod³o¿a
	void AdjustNextPos(const GAMEPHYSICS::ColContain_AllColTypeVec& allColstruct, const DynamicCharacter& character, const Map& map, double yMapVal);														//dosotosowanie obliczonego wektora nowej pozycji ze wzglêdu na obecne kolizje
	void AdjustNextPos_AdjustGroundCollisionAndFallAction(const DynamicCharacter& character, const Vector& adjustedNextPos,
		double yMapVal, const GAMEPHYSICS::ColContain_AllColTypeVec& allColstruct);								//dostosowanie obliczonego wektora nowej pozycji ze wzglêdu na kolzijê z pod³o¿em
																												//i akcji spadania gracza
	GAMEPHYSICS::CollisionVectorCheck CheckMapBoundries(const Map& map, const DynamicCharacter& character);			//sprawdzenie czy postaæ nie wyjdzie poza granice mapy
	GAMEPHYSICS::CollisionStatus LoadCollisionStatusRetVal(const GAMEPHYSICS::ColContain_AllColTypeVec& allColStruct);			//za³adowanie statusu zwracanego dla badanej kolizji

public:
	StandardCollision(): PhysicsModelImpl() {}

	void Process();																				//przetwarzanie 'fizyki' œwiata gry
};