#pragma once
#include <vector>
#include "Vector.h"

//---------------------------------------------------------------------------------------------------------------------------
//------------------------------STRUKTURY U�YWANE PRZEZ PODSTAWOWY MODEL FIZYKI ['GamePhysics']------------------------------
//---------------------------------------------------------------------------------------------------------------------------

namespace GAMEPHYSICS {
	//struktura opisuj�ca nast�pn� pozycj� postaci po danej kolizji
	struct CollisionVectorCheck {
		Vector nextPos;																									//pozycja postaci po kolizji
		bool collisionOccured;																							//zmienna okre�laj�ca czy kolizja zasz�a

		int charIdx;																									//indeks postaci z mapy z kt�r� zasz�a kolizja
		int objIdx;																										//indeks obiektu podstawowego z mapy z kt�rym zasz�a kolizja

		CollisionVectorCheck():nextPos(Vector(0,0,0)),collisionOccured(false),charIdx(-1),objIdx(-1){}
	};

	//struktura 'specjalnej' normalnej [normalna �ciany z kt�ra zasz�a kolizja + dodatkowe parametry; podstawowa struktura detekcji kolizji]
	struct SpecialNormalStruct {
		Vector normal;																									//normalna �ciany z kt�r� zasz�a kolizja
		unsigned linesCrossed;																							//liczba prostych kt�re przeci�y �cian� podczas testu RayCast
		double dotY;																									//iloczyn skalarny normalnej z wektorem [0, 1, 0] - okre�la typ kolizji

		int charIdx;																									//indeks postaci z mapy z kt�r� zasz�a kolizja
		int objIdx;																										//indeks obiektu podstawowego z mapy z kt�rym zasz�a kolizja

		SpecialNormalStruct() :normal(Vector(0, 0, 0)), linesCrossed(0), dotY(0), charIdx(-1), objIdx(-1) {}
	};

	typedef std::vector<SpecialNormalStruct> specialNormals;															//wektor dla struktur 'specjalnych' normalnych

	//struktura grupuj�ca wektory 'CollisionVectorCheck' dla ka�dego typu kolizji
	struct AllCollisionsTypesVec {
		CollisionVectorCheck standardCol;																				//kolizja standardowa [ze �cian�]
		CollisionVectorCheck negativeCol;																				//kolizja negatywna [ze sko�nym/zwyk�ym sufitem]
		CollisionVectorCheck groundCol;																					//kolizja z obiektem pod�o�a [kolizja z podstawy postaci z dowolnym obiektem]
		CollisionVectorCheck mapBoundriesCol;																			//kolizja z granicami mapy
	};

	//struktura zwracaj�ca normaln� do �cainy z kt�r� zasz�a kolizja
	struct CollisionRetVal {
		Vector collisionNormal;																							//normalna do �ciany kolizji
		bool collisionOccured;																							//zmienna okre�laj�ca czy kolizja zasz�a

		CollisionRetVal() :collisionOccured(false), collisionNormal(Vector(0, 0, 0)) {}
	};

	//struktura grupuj�ca struktury 'CollisionRetVal' dla ka�dego typu kolizji
	struct CollisionStatus {
		CollisionRetVal standardCol;																					//kolizja standardowa [�ciany]
		CollisionRetVal negativeCol;																					//kolizja 'negatywna' [sufit/skos]
		CollisionRetVal groundCol;																						//kolizja z obiektem pod�o�a [kolizja dla podstawy obiektu postaci]
		CollisionRetVal mapBoundriesCol;																				//kolizja z granicami mapy
	};

	//struktura grupuj�ca wektory przechowuj�ce 'specjalne' struktury normalnych kolizji
	struct CollisionVectors {
		specialNormals standardCol;																					
		specialNormals negativeCol;
		specialNormals groundCol;
	};

	//struktura grupuj�ca struktury 'AllCollisionVectorCheck' [obliczone nowe pozycje postaci dla ka�dgo typu kolizji] oraz 'CollisionVectors' [czyste dane prosto z detekcji kolizji] 
	struct ColContain_AllColTypeVec {
		AllCollisionsTypesVec allColType;
		CollisionVectors allColVec;
	};
}