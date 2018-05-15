#pragma once
#include "PhysicsModelImpl.h"
#include "SpecialMath.h"
#include "CharacterRegister.h"

//-----------------------------------------------------------------------------------------
//------------------------------MODEL FIZYKI KOLIZJI POCISK�W------------------------------
//-----------------------------------------------------------------------------------------

namespace BULLET {
	//struktura opisuj�ca kolizj� pocisku
	struct BulletColStruct {
		bool collisionOccured;																									//zmienna okre�laj�ca czy kolizja zasz�a
		Vector collisionPos;																									//wsp�rz�dne punktu kolizji
		Character* charHitPtr;																									//wska�nik na obiekt z kt�rym zasz�a kolizja

		BulletColStruct() :collisionOccured(false), collisionPos(Vector(0, 0, 0)), charHitPtr(NULL) {}
		BulletColStruct(bool _collisionOccured, Vector _collisionPos) :collisionOccured(_collisionOccured), collisionPos(_collisionPos), charHitPtr(NULL) {}
		BulletColStruct(bool _collisionOccured, Vector _collisionPos, Character* charPtr) :collisionOccured(_collisionOccured), collisionPos(_collisionPos), charHitPtr(charPtr) {}
	};

	//struktura zwracana przez fun. BulletCollision::GetNewMainSectorIdx(..)
	struct newSector {
		bool insideMap;																											//sprawdzenie czy nowa pozycja pocisku znajduje si� w obr�bie mapy
		Vector position;																										//nowa pozycja pocisku
		IdxPair sectorIdx;																										//indeks sektora dla wsp�rz�dnych 'position'

		newSector():insideMap(false), position(Vector(0,0,0)), sectorIdx(0,0){}
	};

	enum RayCastVer{INSTANT,DYNAMIC};																							//typ wyliczeniowy dla rodzaj�w algorytmu BulletCollision
}

//KOLIZJA POCISK�W
class BulletCollision :public PhysicsModelImpl {
	BulletCollision() {}
	BulletCollision(const BulletCollision& bulletCol) {}
	BulletCollision& operator=(const BulletCollision& bulletCol) {}

	static BulletCollision* instance;																							//instancja singletonu
	static std::vector<Gun*> gunRegister;																						//rejestr broni kt�rych pociski b�d� sprawdzane

	void AnalyzeShotsFired();																									//funkcja analizuj�ca wszystkie wystrzelone pociski

	void BulletRayCastAlgorithm(Bullet& bullet, BULLET::RayCastVer version);													//wykonanie algorytmu RayCast dla danego pocisku

	//algorytm RayCast w trybie INSTANT
	void BulletRayCastInstantHit(Map& map, Bullet& bullet);																		//g��wne cia�o algorytmu								
	bool BulletRayCastInstantHit_CheckCollision(Bullet& bullet, Map& map, IdxPair mainSectorIdx, 
		std::vector<IdxPair>& neighboursIdx);																					//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z innym obiektem
	bool BulletRayCastInstantHit_CheckGroundCol(Map& map, Bullet& bullet, Vector newPos);										//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z pod�o�em
	std::vector<IdxPair> BulletRayCastInstantHit_GetSectorNeighbours(Map& map, const Bullet& bullet, const IdxPair& sectorIdx);	//pobranie indeks�w sektor�w s�siad�w do aktualnego sektora
	BULLET::newSector BulletRayCastInstantHit_GetNewMainSectorIdx(const IdxPair& mainSectorIdx, const Bullet& bullet, 
		const double shift, Map& map);																							//pobranie nowego sektora do algorytmu

	//algorytm RayCast w trybie DYNAMIC
	void BulletRayCastDynamic(Map& map, Bullet& bullet);																		//g��wne cia�o algorytmu
	bool BulletRayCastDynamic_CheckCollision(Map& map, Bullet& bullet, MAP::IdxPair sectorIdx, Vector bulletPos);				//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z innym obiektem
	bool BulletRayCastDynamic_CheckMapBoundries(Map& map, Bullet& bullet);														//funkcja sprawdzaj�ca czy pocisk wyszed� poza granice mapy
	bool BulletRayCastDynamic_CheckGroundCol(Map& map, Bullet& bullet);															//funkcja sprawdzaj�ca czy zasz�a kolizja pocisku z pod�o�em

	BULLET::BulletColStruct CheckSectorBulletCollision(IdxPair sectorIdx, Bullet& bullet);										//sprawdzenie kolziji pocisku w danym sektorze

	BULLET::BulletColStruct CheckSectorBulletCollision_Map(IdxPair sectorIdx, Bullet& bullet);									//sprawdzenie kolizji pocisku z obiektami umieszczonymi na mapie
	BULLET::BulletColStruct CheckSectorBulletCollision_Characters(IdxPair sectorIdx, Bullet& bullet);							//sprawdzenie kolizji pocisku z pozosta�ymi obiektami �wiata gry
	bool CheckSectorBulletCollision_CheckNewCol(BULLET::BulletColStruct &bulletCol, double& distance, Bullet& bullet);			//sprawdzenie nowo wykrytej kol. [czy jest 'lepsza' od wcze�niejszej]

	BULLET::BulletColStruct CheckBulletCollision(Character& character, Bullet& bullet);											//sprawdzenie kolizji pocisku z obiektem 'character'
	BULLET::BulletColStruct CheckBulletCharacterCollision_CheckObject(Character& character, const Bullet& bullet, int objIdx);	//sprawdzenie kolizji pocisku z obiektem modelu 'character'
	BULLET::BulletColStruct CheckBulletCharacterCollision_CheckObjectColBox(Character& character, 
		const Bullet& bullet, CollisionBox& objColBox);																			//sprawdzenie kolizji pocisku z hitboxem obiektu modelu 'character'

	BULLET::BulletColStruct CheckBulletCollision(Map& map, unsigned objIdx, Bullet& bullet);									//sprawdzenie kolizji pocisku z obiektem 'objIdx' mapy
	BULLET::BulletColStruct CheckBulletObjectCollision_CheckObjectReach(Map& map, Bullet& bullet, CollisionBox& objColBox);		//sprawdzenie czy obiekt znajduje si� wewn�trz zasi�gu pocisku 
	BULLET::BulletColStruct CheckBulletObjectCollision_CheckColBox(Map& map, Bullet& bullet, CollisionBox& objColBox);			//sprawdzenie bry�y kolziji danego obiektu mapy

public:
	~BulletCollision() { delete instance; }
	static BulletCollision* GetInstance();																						//pobranie instancji modelu
	
	static void RegisterGun(Gun* _gun) { gunRegister.push_back(_gun); }															//zarejestrowanie obiektu broni
	static void UnregisterGun(Gun* _gun);																						//wyrejestrowanie obiektu broni

	void Process();																												//przetworzenie modelu fizyki
};