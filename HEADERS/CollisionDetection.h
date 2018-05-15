#pragma once
#include <time.h>
#include "CharacterRegister.h"

//------------------------------------------------------------------------------------------------------
//-------------------------------------------DETEKCJA KOLIZJI-------------------------------------------
//--------------------klasa odpowiadaj�ca ze detekcj� kolizji obiekt�w w �wiecie gry--------------------
//------------------------------------------------------------------------------------------------------

const unsigned int RayCastLinesNum = 128;																					//liczba prostych u�ywanych przy algorytmie 'Ray Cast'

struct ModelCollision {
	bool status;																											//status kolizji: TRUE - kolizja zasz�a, FALSE - nie by�o kolizji
	//sk�adowe klasy okre�laj�ce detekcj� kolizji tylko z g��wnym hitboxem modelu/obiektu
	//u�ywane je�li dany model/obiekt posiada TYLKO g��wnego hitboxa
	//je�li zaszla kolizja z g��wnym hitboxem modelu ['Character']:						'mainColBox = TRUE', 'mainColBoxObjIdx = -1'
	//je�li zasz�a kolizja z g��wnym hitboxem obiektu ['Object' dla klasy 'Character']: 'mainColBox = TRUE', 'mainColBoxObjIdx = indeks_obiektu'
	bool mainColBox;																										//status kolizji z g��wnym hitboxem modelu/obiektu
	int mainColBoxObjIdx;																									//indeks obiektu dla kt�rego zasz�a kolizja z g��wnym hitboxem
	//wektor przechowuj�cy pary (objIdx, colBoxIdx)
	//'objIdx' - indeks obiektu z kt�ym zasz�a kolizja dla aktualnie sprawdzanego modelu
	//'colBoxIdx' - indeks dla bry�y kolizji dla obiektu opisanego poprzez 'indeks obiektu' z kt�r� zasz�a kolizja dla aktualnie sprawdzanego modelu
	std::vector<std::pair<unsigned int, unsigned int>> colIdx;

	ModelCollision() :status(false), mainColBox(false), mainColBoxObjIdx(-1) {}
};

//wektor przechowuj�cy pary (normal, linesCrossed) dla danej pary (objIdx,colBoxIdx)
//'normal' - wektor normalny do �ciany badanej bry�y kolizji ('colBoxIdx')
//'linesCrossed' - liczba prostych przechodz�cych przez �cian� opisan� przez normaln� 'normal' podczas testu 'Ray Cast' dla aktualnie badanej bry�y kolizji
typedef std::vector<std::pair<Vector, unsigned int>> CollisionNormals;

class CollisionDetection {
	//-----------------------------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------ALGORYTM GJK---------------------------------------------------------
	//------------------------------------------------funckje tworz�ce algorytm GJK------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------
	bool GJK(std::vector<Vector>&model1, std::vector<Vector>&model2);												//g��wna funkcja algorytmu GJK

	Vector GJK_StartVector(std::vector<Vector>&model1, std::vector<Vector>&model2);									//wyliczanie pocz�tkowego wektora kierunkowego

	Vector GJK_SupportFunction(std::vector<Vector>&model1, std::vector<Vector>&model2,Vector d);						//'Support function' dla GJK

	bool GJK_SimplexContainsORIGIN(std::vector<Vector>& Simplex);													//sprawdzanie czy Sympleks zawiera punkt (0,0,0)
	void GJK_SimplexContainsORIGIN_CreateNormals(std::vector<Vector>& Simplex, Vector n[]);							//funkcja pomocnicza - budowanie normalnych dla Sympleksa
	void GJK_SimplexContainsORIGIN_CreateSurfaces(std::vector<Vector>& Simplex, Vector n[], double Surface[][4]);	//funkcja pomocnicza - budowanie powierzchni dla Sympleksa

	Vector GJK_GetDirection(std::vector<Vector>&Simplex);															//funkcja wyznaczaj�ca wektor kierunkowy w kolejnych iteracjach algorytmu

	//Iteracja 1 [2 punkty w Sympleksie]
	Vector GJK_GetDirection_Iteration_1(std::vector<Vector>&Simplex);
	//Iteracja 2 [3 punkty w Sympleksie]
	Vector GJK_GetDirection_Iteration_2(std::vector<Vector>&Simplex);												
	Vector GJK_GetDirection_Iteration_2_AB(std::vector<Vector>&Simplex, Vector AB, Vector AC, Vector A0);
	Vector GJK_GetDirection_Iteration_2_AC(std::vector<Vector>&Simplex, Vector AB, Vector AC, Vector A0);
	Vector GJK_GetDirection_Iteration_2_CBA(Vector AB, Vector AC, Vector A0);
	Vector GJK_GetDirection_Iteration_2_ABC(Vector AB, Vector AC, Vector A0);
	//Iteracja 3 [4 punkty w Sympleksie]
	Vector GJK_GetDirection_Iteration_3(std::vector<Vector>&Simplex);
	Vector GJK_GetDirection_Iteration_3_AB(std::vector<Vector>&Simplex, Vector AB, Vector AC, Vector A0);
	Vector GJK_GetDirection_Iteration_3_AC(std::vector<Vector>&Simplex, Vector AB, Vector AC, Vector A0);
	Vector GJK_GetDirection_Iteration_3_AD(std::vector<Vector>&Simplex, Vector AC, Vector AD, Vector A0);
	Vector GJK_GetDirection_Iteration_3_ABC(std::vector<Vector>&Simplex, Vector AC, Vector AB, Vector A0);
	Vector GJK_GetDirection_Iteration_3_ABD(std::vector<Vector>&Simplex, Vector AB, Vector AD, Vector A0);
	Vector GJK_GetDirection_Iteration_3_ACD(std::vector<Vector>&Simplex, Vector AD, Vector AC, Vector A0);

	//-----------------------------------------------------------------------------------------------------------------------------
	//--------------------------FUNKCJE POMOCNICZE DLA METOD DETECKCJI KOLIZJI ['CollisionDetection(..)']--------------------------
	//-----------------------------------------------------------------------------------------------------------------------------

	//'CollisionDetection(..)' dla dw�ch modeli 'Character'
	bool CollisionDetection_CharChar_CheckMainColBoxCollision(const Character& model2,
		std::vector<Vector>& colBoxPlayerVertices);																			//sprawdzenie czy zasz�a kolizja z g��wnym hitboxem badanego modelu
	ModelCollision CollisionDetection_CharChar_LoadNewCol(const Character& model2,
		std::vector<Vector>& colBoxPlayerVertices);																			//za�adowanie warto�ci dla obiektu detekcji kolizji 'ModelCollision'

	//'CollisionDetection(..)' dla modelu 'Character' z obiektem 'Object' wchodz�cym w sk�ad modelu 'Character'
	bool CollisionDetection_CharObj_CheckMainColBoxCollision(const Character& model2,
		unsigned model2ObjIdx, std::vector<Vector>& colBoxMod1Vertices);													//sprawdzenie czy zasz�a kolizja z g��wnym hitboxem badanego obiektu
	ModelCollision CollisionDetection_CharObj_LoadNewCol(const Character& model2,
		unsigned model2ObjIdx, std::vector<Vector>& colBoxMod1Vertices);													//za�adownie warto�ci dla obiektu detekcji kolizji 'ModelCollision'

	//-----------------------------------------------------------------------------------------------------------------------------
	//-----------FUNKCJE POMOCNICZE DLA METODY ODNAJDYWANIA NORMALNEJ DO POWIERZCHNI KOLIZJI ['GetCollisionFaceNormal']------------
	//-----------------------------------------------------------------------------------------------------------------------------

	CollisionNormals GetCollisonFaceNormal_StandardHitboxCol(const Character& model1, const Character& model2, ModelCollision& col);		//pobranie normalnej do powierzchni kolizji dla standardowego hitboxa
	CollisionNormals GetCollisonFaceNormal_MainHitboxCol(const Character& model1, const Character& model2, ModelCollision& col);			//pobranie normalnej do powierzchni kolizji dla g��wnego hitboxa

	//-----------------------------------------------------------------------------------------------------------------------------

	bool CheckPointInTriangle(Vector point, Vector triangle[], Vector normal);										//funkcja pomocnicza sprawdzaj�ca czy dany punkt znajduje si� wewn�trz tr�jk�ta

	std::pair<Vector, unsigned> GetCollisionFaceNormal_GetNormal(const Character &model1,
		const Character& model2,CollisionBox &colBoxChar);																		//pobranie normalnej do powierzchni obiektu z kt�r� zasz�a kolizja
	void GetCollisionFaceNormal_LoadPoints(Vector points[], const Character& model1);										//za�adowanie punkt�w pocz�tkowych dla prostych do algorytmu 'Ray Casting'
	int GetCollisionFaceNormal_GetNormal_RayCast(Vector faceP[], Vector point[], 
		Vector normal, double surface[],double R);																			//wykonanie algorytmu 'RayCast' dla funkcji pobierania normalnej

public:
	//ModelCollision CheckCollision(const Character& model1, const Character& model2);												//sprawdzanie kolizji pomi�dzy dwoma modelami
	ModelCollision CheckCollision3D(const Character& model1, const Character& model2);
	ModelCollision CheckCollision2D(const Character& model1, const Character& model2);

	//ModelCollision CheckCollision(const Character& model1, const Character& model2, unsigned model2ObjIdx);						//sprawdzenie kolizji pomi�dzy modelem, a wybranym obiektem z drugiego modelu	
	ModelCollision CheckCollision3D(const Character& model1, const Character& model2, unsigned model2ObjIdx);
	ModelCollision CheckCollision2D(const Character& model1, const Character& model2, unsigned model2ObjIdx);

	CollisionNormals GetCollisonFaceNormals(const Character& model1, const Character& model2, ModelCollision col);							//pobranie normalnej do �ciany obiektu z kt�rym zasz�a 

	bool GettingOutOfCollision(const Character& model, Vector n);															//sprawdzenie czy model postaci 'wychodzi' ze stanu kolizji

	Vector GettingIntoCollision(const Character& model, Vector n);										//zwr�cenie warto�ci wektora dla postaci kt�ra znajduje si� w stanie kolizji
																															//[wekotr ten jest proponowan� �cie�k� dla postaci kt�ra wesz�a w kolizj�]						
};