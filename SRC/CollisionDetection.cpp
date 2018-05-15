#include "CollisionDetection.h"

//sprawdzanie kolizji pomi�dzy dwoma modelami
//sprawdzenie nast�puje pomi�dzy g��wn� bry�� kolizji modelu pierwszego ['model1'] ,a wszystkimi mo�liwymi bry�ami kolizji modelu drugiego ['model2']
//ModelCollision CollisionDetection::CheckCollision(const Character& model1, const Character& model2) {
ModelCollision CollisionDetection::CheckCollision3D(const Character& model1, const Character& model2) {
	if (model1.IsEnabled() && model2.IsEnabled()) {																	//sprawdzanie kolizji tylko dla 'odblokowanych' postaci
		CollisionBox colBoxPlayer = model1.getCollisionBox(), colBoxChar = model2.getCollisionBox();				//pobranie bry� kolizji dla obu modeli
		Vector shift((colBoxPlayer.midPoint + model1.getPosition()) - (colBoxChar.midPoint + model2.getPosition()));//obliczenie przesuni�cia mi�dzy �rodkami bry� kolizji
		double distance = shift.MOD();																				//obliczenie odleg�o�ci pomi�dzy �rodkami bry� kolizji
		std::vector<Vector> colBoxPlayerVertices;																	//wektor przechowuj�cy punkty dla bry�y kolizji modelu Player
		ModelCollision newCol;																						//obiekt przechowuj�cy informacje zebrane z detekcji kolizji

		if (distance > (colBoxPlayer.radius + colBoxChar.radius)) {													//sprawdzenie czy sfery kolizji modeli si� przecinaj� 
			newCol.status = false;																					//status kolizji = FALSE
			return newCol;
		}

		for (unsigned int i = 0; i < colBoxPlayer.verticesIdx.size(); i++)											//uzupe�nienie wektora przechowuj�cego punkty dla bry�y kolizji modelu Player
			colBoxPlayerVertices.push_back(model1.getTransformedVertice(colBoxPlayer.verticesIdx[i]));

		if (CollisionDetection_CharChar_CheckMainColBoxCollision(model2, colBoxPlayerVertices)) {					//sprawdzenie czy zachodzi kolizja pomi�dzy g��wnymi hitboxami modeli
			return (CollisionDetection_CharChar_LoadNewCol(model2, colBoxPlayerVertices));							//je�li tak sprawd� z kt�rymi dok�adnie hitboxami modelu 2 zachodzi kolizja
		}
		else {																										//w przeciwnym wypadku
			newCol.status = false;																					//status kolizji = FALSE
			return newCol;
		}
	}
	else return ModelCollision();																					//je�li postacie nie s� odblokowane - zwr�� wart. domy�ln� kolizji
}

//sprawdzenie kolizji pomi�dzy modelem, a wybranym obiektem z drugiego modelu
//sprawdzenie nast�puje pomi�dzy g��wn� bry�� kolizji modelu pierwszego ['model1'] ,a wszystkimi mo�liwymi bry�ami kolizji wybranego obiektu modelu drugiego ['model2']
//ModelCollision CollisionDetection::CheckCollision(const Character& model1, const Character& model2, unsigned model2ObjIdx) {
ModelCollision CollisionDetection::CheckCollision3D(const Character& model1, const Character& model2, unsigned model2ObjIdx) {
	CollisionBox colBoxMod1=model1.getCollisionBox(), colBoxObj=model2.getObjectMainCollisionBox(model2ObjIdx);	//pobranie bry� kolizji dla modelu 1 oraz danego obiektu modelu 2
	Vector shift((colBoxMod1.midPoint+model1.getPosition()) - colBoxObj.midPoint);								//obliczenie przesuni�cia mi�dzy �rodkami bry� kolizji
	double distance = shift.MOD();																				//obliczenie odleg�o�ci pomi�dzy �rodkami bry� kolizji
	std::vector<Vector> colBoxMod1Vertices;																		//wektor przechowuj�cy punkty dla bry�y kolizji modelu Player
	ModelCollision newCol;																						//obiekt przechowuj�cy informacje zebrane z detekcji kolizji

	if (distance > (colBoxMod1.radius + colBoxObj.radius)) {													//sprawdzenie czy sfery kolizji modeli si� przecinaj� 
		newCol.status = false;																					//je�li tak, status kolizji = FALSE
		return newCol;
	}

	for (unsigned int i = 0; i < colBoxMod1.verticesIdx.size(); i++)
		colBoxMod1Vertices.push_back(model1.getTransformedVertice(colBoxMod1.verticesIdx[i]));					//uzupe�nienie wektora przechowuj�cego punkty dla bry�y kolizji modelu Player

	if(CollisionDetection_CharObj_CheckMainColBoxCollision(model2,model2ObjIdx,colBoxMod1Vertices)){			//sprawdzenie czy zachodzi kolizja pomi�dzy g��wnymi hitboxami modelu i obiektu
		return ( CollisionDetection_CharObj_LoadNewCol(model2, model2ObjIdx, colBoxMod1Vertices) );				//je�li tak sprawd� z kt�rymi dok�adnie hitboxami obiektu zachodzi kolizja
	}
	else {																										//w przeciwnym wypdaku
		newCol.status = false;																					//status kolizji = FALSE
		return newCol;
	}
}

//pobranie normalnej do �ciany obiektu z kt�rym zasz�a kolizja
CollisionNormals CollisionDetection::GetCollisonFaceNormals(const Character& model1, const Character& model2,ModelCollision col) {
	if (col.status) {																							//je�li zasz�a kolizja z jakimkolwiek obiektem
		if (col.mainColBox) {																					//je�li zasz�a kolizja z g��wnym hitboxem modelu/obiektu
			return GetCollisonFaceNormal_MainHitboxCol(model1, model2, col);									//oblicz normaln� do �ciany kolizji dla g��wnego hitboxa modelu/obiektu
		}
		else {																									//w przeciwnym wypadku
			return GetCollisonFaceNormal_StandardHitboxCol(model1, model2, col);								//oblicz normaln� do �ciany kolizji dla standardowego hitboxa modelu/obiektu
		}
	}
	else
	{
		CollisionNormals normals;
		return normals;																				//je�li nie zasz�a kolizja z �adnym obiektem zwr�� wektor (0,0,0)
	}
}

//sprawdzenie czy model postaci 'wychodzi' ze stanu kolizji
bool CollisionDetection::GettingOutOfCollision(const Character& model, Vector n) {
	Vector p = model.GetNextPosition() - model.getPosition();													//wektor opisuj�cy 'przysz�e' przesuni�cie postaci gracza

	if (n == Vector(0, 0, 0)) return false;																		//je�li �adne przemiszczenie nie zachodzi zwr�� FALSE

	if (n.DotProduct(p) >= 0.0)																					//je�li iloczyn skalrny normalnej i wektora przesuni�cia jest wi�kszy od zera
		return true;																							//oznacza to �e wektor przesuni�cia jest skierowany w tym samym kierunku co normalna
																												// - posta� wychodzi z kolizji - zwr�� TRUE 
	else return false;																							//w przeciwnym wypadku zwr�� FALSE
}

//zwr�cenie warto�ci wektora dla postaci kt�ra znajduje si� w stanie kolizji [wekotr ten jest proponowan� �cie�k� dla postaci kt�ra wesz�a w kolizj�]
Vector CollisionDetection::GettingIntoCollision(const Character& model,Vector n) {
	Vector playerVec = model.GetNextPosition() - model.getPosition();											//wektor opisuj�cy 'przysz�e' przesuni�cie postaci gracza
	Vector crossVec = playerVec.CrossProduct(n);																//iloczyn wektorowy: crossVec = playerVec x n
	Vector moveVec = n.CrossProduct(crossVec);																	//iloczyn wektorowy: moveVec = n x crossVec
																												//opisuje on wektor wzd�u� kt�ego posta� ma si� przesuwa� b�d�c w kolizji z dan� �cian�
	if (moveVec.MOD() == 0)																						//je�li wektor ten jest zerowy - posta� jest skierowana prosto w �cian� 
		return Vector(0, 0, 0);
	moveVec /= moveVec.MOD();																					//normalizacja wektora przesuni�cia
	double d = playerVec.MOD();																					//d�ugo�� wektora 'przysz�ego' przesuni�cia postaci
	if (d == 0)																									//je�li posta� nie przemie�ci si� - zwr�� wektor zerowy
		return Vector(0, 0, 0);																							
	playerVec /= d;																								//normalizacja wektora przysz�ego przesuni�cia gracza
	double a = playerVec.DotProduct(moveVec);																	//iloczyn skalarny opisuj�cy w jakim stopniu wektor 'playerVec' jest odchylony
																												//od wektora 'moveVec' - im warto�� bli�sza '1' tym mniejsze odchylenie
	moveVec = moveVec*a*d;																						//obliczenie wektora przesuni�cia dla gracza kt�ry wszed� w kolizj� z dan� �cian�

	return moveVec;
}

//g��wna funkcja algorytmu GJK
bool CollisionDetection::GJK(std::vector<Vector>&model1, std::vector<Vector>&model2) {
	unsigned GJK_it_limit = static_cast<unsigned>((model1.size()*model2.size())/2.0);												//g�rna granica ilo�ci iteracji dla algorytmu GJK
	unsigned int iterations = 0;																				//zmienna przechowuj�ca aktualn� warto�� iteracji algorytmu
																												//zabezpiecza przed ap�tleniem si� algorytmu
	std::vector<Vector> Simplex;																				//vector opisuj�cy 'Sympleks' algorytmu GJK - punkty opisujace czworo�cian

	Vector d = GJK_StartVector(model1, model2);																	//obliczenie startowego wektora kierunkowego dla algorytmu GJK

	Simplex.push_back(GJK_SupportFunction(model1, model2, d));													//dodanie pierwszego punktu do Sympleksu przy u�yciu 'Support function' dla GJK

	d = d.Negate();																								//zmienienie zwrotu wektora kierunkowego

	while (true) {
		if (iterations > GJK_it_limit)																			//je�li algorytm si� zap�tli�
			return true;																						//przerwij i zwr�� warto�� TRUE - kolizja zachodzi
																												//[je�li kolizja by nie zachodzi�a, zosta�oby to du�o wcze�niej wykryte]
			
			Simplex.push_back(GJK_SupportFunction(model1, model2, d));											//dodanie kolejnego punktu do Sympleksu

			if (Simplex[Simplex.size() - 1].DotProduct(d) < 0) {												//je�li dodany punkt nie przeszed� przez �rodek uk�adu
				return false;																					//kolizja nie zachodzi - zwr�� FALSE
			}
			else {																								//w przeciwnym wypadku
				if (GJK_SimplexContainsORIGIN(Simplex)) {														//sprawd� czy punkt (0,0,0) jest zawartty w Sympleksie
					return true;																				//je�li tak - kolizja zachodzi, zwr�� TRUE
				}
				else 																							//w przeciwnym wypadku
					d = GJK_GetDirection(Simplex);																//oblicz now� warto�� wektora kierunkowego
			}
		iterations++;																							//zwi�ksz licznik iteracji algorytmu
	}
}

//wyliczanie pocz�tkowego wektora kierunkowego
Vector CollisionDetection::GJK_StartVector(std::vector<Vector>&model1, std::vector<Vector>&model2) {
	//obliczenie punkt�w �rodkowych dla obu modeli przekazanych jako wektory punkt�w
	Vector midPoint1(0, 0, 0);
	Vector midPoint2(0, 0, 0);	
	if (model1.size() >= model2.size()) {											
		for (unsigned int i = 0; i < model1.size(); i++) {
			if (i < model2.size())
				midPoint2 += model2[i];
			midPoint1 += model1[i];
		}
	}
	else {
		for (unsigned int i = 0; i < model2.size(); i++) {
			if (i < model1.size())
				midPoint1 += model1[i];
			midPoint2 += model2[i];
		}
	}

	midPoint1 /= model1.size();
	midPoint2 /= model2.size();

	return (midPoint2 - midPoint1);																				//zwr�cenie wektora przesuni�cia miedzy �rodkami modelu 1 ,a modelu 2
}

//'Support function' dla GJK zwracaj�ca kolejny punkt do Sympleksu ze wzgl�du na wektor 'd'
Vector CollisionDetection::GJK_SupportFunction(std::vector<Vector>&model1, std::vector<Vector>&model2, Vector d) {
	//-------------------------------------------------------------------------------------------------OPIS----------------------------------------------------------------------------------------------
	//algorytm 'Support function' znajduje punkt w bryle 'model1' najbardziej oddalony w kierunku 'd' oraz punkt w bryle 'model2' najbardziej oddalony w kierunku '-d'
	//nast�pnie wyznacza punkt do Sympleksu poprzez r�nic� mi�dzy tymi dwoma punktami [wyznaczony punkt jest najbardziej oddalonym punktem w bryle r�nicy Minkowskiego dla modeli 1 i 2 w kierunku 'd']
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Vector _d = d.Negate();																						//stworzenie wektora o przeciwnym zwrocie do wektora kierunkowego d
	double dotProductResult1 = model1[0].DotProduct(d), dotProductResult2 = model2[0].DotProduct(_d);			//zainicjalizowanie warto�ci dla przeszukiwania zbioru punkt�w
	unsigned int idx1 = 0, idx2 = 0;

	for (unsigned int i = 1; i < model1.size(); i++) {
		if (model1[i].DotProduct(d) > dotProductResult1) {														//je�li iloczyn skalarny danego punktu z wek. 'd' jest wi�kszy od wcze�niejszego max
			idx1 = i;																							//to znaczy �e dany punkt jest bardziej oddalony w kierunku 'd' ni� wcze�niejsz
			dotProductResult1 = model1[i].DotProduct(d);														//zaktualizuj wart. dla najbardziej oddalonego punktu
		}
	}

	for (unsigned int i = 1; i < model2.size(); i++) {															
		if (model2[i].DotProduct(_d) > dotProductResult2) {														//je�li iloczyn skalarny danego punktu z wek. '-d' jest wi�kszy od wcze�niejszego max
			idx2 = i;																							//to znaczy �e dany punkt jest bardziej oddalony w kierunku '-d' ni� wcze�niejszy				
			dotProductResult2 = model2[i].DotProduct(_d);														//zaktualizuj wart. dla najbardziej oddalonego punktu
		}
	}

	return (model1[idx1] - model2[idx2]);																		//wyznacz punkt b�d�cy r�nic� Minkowskiego dla znalezionych punkt�w dla modeli 1 i 2
}

//sprawdzanie czy Sympleks zawiera punkt (0,0,0)
bool CollisionDetection::GJK_SimplexContainsORIGIN(std::vector<Vector>& Simplex) {
	if (Simplex.size() < 4)																						//je�li wielko�� Sympleksu jest mniejsz ni� 4
		return false;																							//Sympleks nie jest bry�a zwr�� FALSE
	else {
		Vector n[4];																							//normalne dla �cian Symplesku - skierowane na zewn�trz bry�y

		GJK_SimplexContainsORIGIN_CreateNormals(Simplex, n);													//za�adowanie normalnych 

		double Surface[4][4];																					//tablica opisuj�ca powierzchnie Sympleksu 

		GJK_SimplexContainsORIGIN_CreateSurfaces(Simplex, n, Surface);											//za�adowanie warto�ci tablicy 'Surface' - obliczenie wsp��zynnik�w powierzchni
		//------------------------------------------------------------------------ALGORYTM-------------------------------------------------------------------------
		//je�li parametr 't' dla prostej parametrycznej zaczynaj�cej si� w punkcie (0,0,0) i skierowanje w kierunku normalnej dla danej �ciany jest mniejszy od '0'
		//punkt (0,0,0) nie znajduje si� wewn�trz Sympleksu - zwr�� FALSE
		//je�li dla ka�dej normalnej paramtr 't' prostej jest wi�kszy od '0' - punkt (0,0,0)  znajduje si� wewn�trz Sympleksu - zwr�� TRUE
		//---------------------------------------------------------------------------------------------------------------------------------------------------------
		//zapis skr�cony powy�szego algorytmu po wyprowadzeniu konkretnych warunk�w dla znaku parametru 't'
		
		double t_mian[4], t_licz[4];
		for (unsigned i = 0; i < 4; i++) {																		//obliczenie wart. dla licznika i mianownika param. 't' dla ka�dej �ciany
			t_licz[i] = Surface[i][3];
			t_mian[i] = Surface[i][0] * n[i].x + Surface[i][1] * n[i].y + Surface[i][2] * n[i].z;
		}
		
		if ((t_licz[0] < 0 && t_mian[0] < 0) || (t_licz[0] > 0 && t_mian[0] > 0))								//sprawdzenie warunk�w czy 't < 0' dla ka�dej �ciany
			return false;
		if ((t_licz[1] < 0 && t_mian[1] < 0) || (t_licz[1] > 0 && t_mian[1] > 0))
			return false;
		if ((t_licz[2] < 0 && t_mian[2] < 0) || (t_licz[2] > 0 && t_mian[2] > 0))
			return false;
		if ((t_licz[3] < 0 && t_mian[3] < 0) || (t_licz[3] > 0 && t_mian[3] > 0))
			return false;

		return true;																							//je�li dla ka�dej �ciany parametr 't' ma warto�� dodatni�
																												//punkt (0,0,0) jest wewn�trz Sympleksu - zwr�� 'TRUE'
	}
}

//funkcja pomocnicza - budowanie normalnych dla Sympleksa
void CollisionDetection::GJK_SimplexContainsORIGIN_CreateNormals(std::vector<Vector>& Simplex,Vector n[]) {
	//obliczenie normalnych do ka�dej �ciany Sympleksu
	Vector tmp1(Simplex[3] - Simplex[2]), tmp2(Simplex[1] - Simplex[2]);
	n[0] = tmp1.CrossProduct(tmp2);
	tmp2 = Simplex[0] - Simplex[2];
	n[1] = tmp1.CrossProduct(tmp2);
	tmp1 = Simplex[3] - Simplex[1]; tmp2 = Simplex[0] - Simplex[1];
	n[2] = tmp1.CrossProduct(tmp2);
	tmp1 = Simplex[2] - Simplex[1];
	n[3] = tmp1.CrossProduct(tmp2);

	//sprawdzenie czy ka�da normalna wskazuje na zewn�trz bry�y
	if (n[0].DotProduct(Simplex[0]) > n[0].DotProduct(Simplex[3]))
		n[0] = n[0].Negate();
	if (n[1].DotProduct(Simplex[1]) > n[1].DotProduct(Simplex[3]))
		n[1] = n[1].Negate();
	if (n[2].DotProduct(Simplex[2]) > n[2].DotProduct(Simplex[3]))
		n[2] = n[2].Negate();
	if (n[3].DotProduct(Simplex[3]) > n[3].DotProduct(Simplex[2]))
		n[3] = n[3].Negate();
}

//funkcja pomocnicza - budowanie powierzchni dla Sympleksa
void CollisionDetection::GJK_SimplexContainsORIGIN_CreateSurfaces(std::vector<Vector>& Simplex, Vector n[],double Surface[][4]) {
	//przypisanie wsp�rz�dnych normalnych jako pierwszych 3 parametr�w dla ka�dej powierzchni (A, B, C)
	for (unsigned int i = 0; i < 3; i++) {
		Surface[0][i] = n[0][i];
		Surface[1][i] = n[1][i];
		Surface[2][i] = n[2][i];
		Surface[3][i] = n[3][i];
	}

	//obliczenie parametru D dla ka�dej powierzchni
	Surface[0][3] = -Surface[0][0] * Simplex[3].x - Surface[0][1] * Simplex[3].y - Surface[0][2] * Simplex[3].z;
	Surface[1][3] = -Surface[1][0] * Simplex[3].x - Surface[1][1] * Simplex[3].y - Surface[1][2] * Simplex[3].z;
	Surface[2][3] = -Surface[2][0] * Simplex[3].x - Surface[2][1] * Simplex[3].y - Surface[2][2] * Simplex[3].z;
	Surface[3][3] = -Surface[3][0] * Simplex[2].x - Surface[3][1] * Simplex[2].y - Surface[3][2] * Simplex[2].z;
}

//funkcja wyznaczaj�ca wektor kierunkowy w kolejnych iteracjach algorytmu
Vector CollisionDetection::GJK_GetDirection(std::vector<Vector>&Simplex) {
	switch (Simplex.size()) {									
	case 2:																										//dla Sympleksu o wielko�ci 2
		return GJK_GetDirection_Iteration_1(Simplex);															//pierwsza iteracja algorytmu GJK
		break;
	case 3:																										//dla Sympleksu o weilko�ci 3
		return GJK_GetDirection_Iteration_2(Simplex);															//druga iteracja algorytmu GJK
		break;
	case 4:																										//dla Sympleksu o wielko�ci 4
		return GJK_GetDirection_Iteration_3(Simplex);															//trzecia iteracja algorytmu GJK
		break;
	default:
		return Vector(0.0, 0.0, 0.0);																			//dla ka�dej innej warto�ci Sympleksu zwr�� wektor zerowy - ochrona przed b��dami
		break;
	}
}

//Iteracja 1 [2 punkty w Sympleksie]
Vector CollisionDetection::GJK_GetDirection_Iteration_1(std::vector<Vector>&Simplex) {
	//punkt A - ostatni punkt dodany do Sympleksu, B - pierwszy punkt dodany do Sympleksu,  d - wyznaczany wektor kierunkowy
	Vector d, ORIGIN(0, 0, 0), AB, A0;

	//obliczenie wektora 'd' na podstawie danych punkt�w w Sympleksie, oraz wiedzy �e punkt A znajduje si� po 'drugiej' stronie uk�adu wsp�rz�dnych ni� punkt B
	AB = Simplex[0] - Simplex[1];																				
	A0 = ORIGIN - Simplex[1];
	d = AB.CrossProduct(A0);
	d = d.CrossProduct(AB);																						
	return d;
}

//Iteracja 2 [3 punkty w Sympleksie]
Vector CollisionDetection::GJK_GetDirection_Iteration_2(std::vector<Vector>&Simplex) {
	//punkt A - ostatni dodany punkt do Sympleksa, B - punkt dodany przed A, C - piewrszy punkt w Sympleksie
	Vector d, ORIGIN(0,0,0), AB, AC, A0;
	AB = Simplex[1] - Simplex[2]; AC = Simplex[0] - Simplex[2];													//inicjalizacja wektor�w
	A0 = ORIGIN - Simplex[2];

	//ustalenie nowej warto�ci wektora kierunkowego
	d = GJK_GetDirection_Iteration_2_AB(Simplex, AB, AC, A0);													//normlana do odcinka AB
	if (d!=ORIGIN) 
		return d;
	else {
		d = GJK_GetDirection_Iteration_2_AC(Simplex, AB, AC, A0);												//normalna do odcinka AC
		if (d != ORIGIN)
			return d;
		else {
			d = GJK_GetDirection_Iteration_2_CBA(AB, AC, A0);													//normalna do powierzchni CBA
			if (d!=ORIGIN)
				return d;
			else {
				d = GJK_GetDirection_Iteration_2_ABC(AB, AC,A0);												//normalna do poweirzchni ABC
				return d;
			}
		}
	}
}

//sprawdzenie czy wektor normalny do odcinka AB jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_2_AB(std::vector<Vector>&Simplex,Vector AB, Vector AC, Vector A0) {
	Vector d;
	d = AC.CrossProduct(AB);
	d = d.CrossProduct(AB);																						//wyznaczenie wektora normalnego do odcinka AB

	if (d.DotProduct(A0) > 0) {																					//sprawdzenie czy wektor 'd' jest skierowany do �rodka uk�adu
		Simplex.erase(Simplex.begin());																			//jesli tak usu� pierwszy punkt z Sympleksu [C]
		return d;																								//zwr�� now� warto�� wektora kierunkowego
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do odcinka AC jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_2_AC(std::vector<Vector>&Simplex,Vector AB, Vector AC, Vector A0) {
	Vector d;
	d = AB.CrossProduct(AC);
	d = d.CrossProduct(AC);																						//wyznaczenie wektora normlanego do odcinka AC

	if (d.DotProduct(A0) > 0) {																					//sprawdzenie czy wektor 'd' jest skierowany do �rodka uk�adu
		Simplex.erase(Simplex.begin() + 1);																		//jesli tak usu� drugi element z Sympleksu [B]
		return d;																								//zwr�� now� warto�� wektora kierunkowego
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do powierzchni CBA jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_2_CBA(Vector AB,Vector AC,Vector A0) {
	Vector d;
	d = AC.CrossProduct(AB);																					//wyznaczenie wektora normalnego do poweirzchni CBA

	if (d.DotProduct(A0) > 0)																					//je�li wektor 'd' jest skierowny do �rodka uk�adu
		return d;																								//zachowaj wszystkie elementy Sympleksu i zwr�� now� warto�� wektora kierunkowego

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do powierzchni ABC jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_2_ABC(Vector AB,Vector AC,Vector A0) {
	Vector d;																									
	d = AB.CrossProduct(AC);																					//wyznaczenie wektora normalnego do powierzchni ABC

	return d;																									//zwr�� wektor 'd' jako now� warto�� wektora kierunkowego
																												//ostatni warunek w 2 iteracji algorytmu - nie przeprowadza si� �adnych dodatkowych test�w
}

//Iteracja 3 [4 punkty w Sympleksie]
Vector CollisionDetection::GJK_GetDirection_Iteration_3(std::vector<Vector>&Simplex) {
	Vector d, ORIGIN(0,0,0), AB, AC, AD, A0;
	AB = Simplex[2] - Simplex[3]; AC = Simplex[1] - Simplex[3];
	AD = Simplex[0] - Simplex[3]; A0 = ORIGIN - Simplex[3];

	//ustalenie nowej warto�ci wektora kierunkowego
	d = GJK_GetDirection_Iteration_3_AB(Simplex, AB, AC, A0);													//normalna do odcinka AB									
	if (d != ORIGIN)
		return d;
	else {
		d = GJK_GetDirection_Iteration_3_AC(Simplex, AB, AC, A0);												//normalna do odcinka AC
		if (d != ORIGIN)
			return d;
		else {
			d = GJK_GetDirection_Iteration_3_AD(Simplex, AC, AD, A0);											//normalna do odcinka AD
			if (d != ORIGIN)
				return d;
			else {
				d = GJK_GetDirection_Iteration_3_ABC(Simplex, AB, AC, A0);										//normalna do p�aszczyzny ABC
				if (d != ORIGIN)
					return d;
				else {
					d = GJK_GetDirection_Iteration_3_ABD(Simplex, AB, AD, A0);									//normalna do p�aszczyzny ABD
					if (d != ORIGIN)
						return d;
					else {
						d = GJK_GetDirection_Iteration_3_ACD(Simplex, AD, AC,A0);									//normalna do p�aszczyzny ACD
							return d;
					}
				}
			}
		}
	}
}

//sprawdzenie czy wektor normalny do odcinka AB jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_3_AB(std::vector<Vector>&Simplex,Vector AB,Vector AC,Vector A0) {
	Vector d;
	d = AC.CrossProduct(AB);
	d = d.CrossProduct(AB);																						//wyznaczenie wektora normlanego do odcinka AB

	if (d.DotProduct(A0) > 0) {																					//je�li wektor 'd' jest skierowany do punktu (0,0,0)
		Simplex.erase(Simplex.begin());																			//usu� dwa pierwsze elementy z Sympleksu (C i D)
		Simplex.erase(Simplex.begin());
		return d;																								//zwr�� now� warto�� wektora kierunkowego 
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do odcinka AC jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_3_AC(std::vector<Vector>&Simplex,Vector AB,Vector AC,Vector A0) {
	Vector d;
	d = AB.CrossProduct(AC);
	d = d.CrossProduct(AC);																						//wyznaczenie wektora normalnego do odcinka AC

	if (d.DotProduct(A0) > 0) {																					//je�li wektor 'd' jest skierowany do punktu (0,0,0)
		Simplex.erase(Simplex.begin());																			//usu� pierwszy i trzeci punkt z Sympleksu (D i B)
		Simplex.erase(Simplex.begin()+1);
		return d;																								//zwr�� now� warto�� wektora kierunkowego
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do odcinka AD jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_3_AD(std::vector<Vector>&Simplex,Vector AC,Vector AD, Vector A0) {
	Vector d;
	d = AC.CrossProduct(AD);
	d = d.CrossProduct(AD);																						//wyznaczenie wektora normalnego do odcinka AD

	if (d.DotProduct(A0) > 0) {																					//je�li wektor 'd' jest skierowany do punktu (0,0,0)
		Simplex.erase(Simplex.begin() + 1);																		//usu� drugi i trzeci punkt z Sympleksu (B i C)
		Simplex.erase(Simplex.begin() + 1);
		return d;																								//zwr�� now� warto�� wektora kierunkowego
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do poweirzchni ABC jest skierowany do punktu (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_3_ABC(std::vector<Vector>&Simplex,Vector AB,Vector AC,Vector A0) {
	Vector d;
	d = AC.CrossProduct(AB);																					//wyznaczenie wektora normalnego do powierzchni  ABC 

	if (d.DotProduct(Simplex[0]) > d.DotProduct(Simplex[3]))													//sprawdzenie czy normalna jest skierowana na zewn�trz Sympleksu
		d = d.Negate();																							

	if (d.DotProduct(A0) > 0) {																					//je�li wektor 'd' jest skierowany do punktu (0,0,0)
		Simplex.erase(Simplex.begin());																			//usu� pierwszy punkt z Sympleksu (D)
		return d;																								//zwr�� now� warto�� wektora kierunkowego
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do powierzchni ABD jest skierowany do (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_3_ABD(std::vector<Vector>&Simplex,Vector AB,Vector AD,Vector A0) {
	Vector d;
	d = AD.CrossProduct(AB);																					//wyznaczenie wektora normalnego do poweirzchni ABD
	
	if (d.DotProduct(Simplex[1]) > d.DotProduct(Simplex[3]))													//sprawdzenie czy normalna jest skierowana na zewn�trz Sympleksu
		d = d.Negate();

	if (d.DotProduct(A0) > 0) {																					//je�li wektor 'd' jest skierowany do punktu (0,0,0) 
		Simplex.erase(Simplex.begin() + 1);																		//usu� drugi element z Sympleksu (C)
		return d;																								//zwr�� now� warto�� wektora kierunkowego
	}

	return Vector(0, 0, 0);																						//w przeciwnym wypadku zwr�� wektor zerowy
}

//sprawdzenie czy wektor normalny do powierzchni ACD jest skierowany do (0,0,0)
Vector CollisionDetection::GJK_GetDirection_Iteration_3_ACD(std::vector<Vector>&Simplex,Vector AD,Vector AC, Vector A0) {
	Vector d;
	d = AD.CrossProduct(AC);																					//wyznaczenie wektora normalnego do poweirzchni ACD

	if (d.DotProduct(Simplex[2]) > d.DotProduct(Simplex[3]))													//sprawdzenie czy normalna jest skierowana na zewn�trz Sympleksu
		d = d.Negate();

	Simplex.erase(Simplex.begin() + 2);																			//usu� 3 element z Sympleksu
	return d;																									//zwr�� now� warto�� wektora kierunkowego
																												//ostatni warunek 3 iteracji algorytmu - nie jest sprawdzany �aden dodatkowy warunek
}

//sprawdzenie czy zasz�a kolizja z g��wnym hitboxem badanego modelu
bool CollisionDetection::CollisionDetection_CharChar_CheckMainColBoxCollision(const Character& model2, std::vector<Vector>& colBoxPlayerVertices) {
	CollisionBox colBoxChar = model2.getCollisionBox();															//za�adowanie g��wnego hitboxa dla modelu 2											
	std::vector<Vector> colBoxCharVertices;																		//wektora przechowuj�cy wierzcho�ki wchodz�ce w sk�ad hitboxa modelu 2
	for (unsigned int i = 0; i < colBoxChar.verticesIdx.size(); i++)
		colBoxCharVertices.push_back(model2.getTransformedVertice(colBoxChar.verticesIdx[i]));					//za�adowanie wierzcho�k�w hitboxa do wektora

	if (GJK(colBoxPlayerVertices, colBoxCharVertices)) return true;												//sprawdzenie algorytmem GJK czy zachodzi kolizja pomi�dzy g��wnymi hitboxami
	else return false;
}

//za�adowanie warto�ci dla obiektu detekcji kolizji 'ModelCollision'
ModelCollision CollisionDetection::CollisionDetection_CharChar_LoadNewCol(const Character& model2, std::vector<Vector>& colBoxPlayerVertices) {
	CollisionBox colBoxChar;																					//hitbox dla modelu 2
	std::vector<Vector> colBoxCharVertices;																		//wektora przechowuj�cy wierzcho�ki dla hitboxa modelu 2
	ModelCollision newCol;																						//obiekt przechowuj�cy informacje zebrane z detekcji kolizji
	unsigned sum = 0;																							//suma pomocnicza, okre�laj�ca ile hitbox�w wchodzi w sk�ad modelu [opr�cz g��wnego]

	for(unsigned int i=0;i<model2.getObjectsCount();i++)
		sum += model2.getObjectCollisionBoxCount(i);															//obliczenie sumy hitbox�w modelu 2
	if (sum == 0) {																								//je�li w sk��d modelu 2 nie wchodzi �aden inny hitbox poza g��wnym
		newCol.status = true; newCol.mainColBox = true; newCol.mainColBoxObjIdx = -1;							//ustaw odpowiednie statusy kolizji
		return newCol;
	}

	for (unsigned int i = 0; i < model2.getObjectsCount(); i++) {												//dla ka�dego obiektu z modelu Character
		for (unsigned int j = 0; j < model2.getObjectCollisionBoxCount(i); j++) {
			colBoxChar = model2.getObjectCollisionBox(i, j);													//pobranie bry�y kolizji 'j' dla obiektu 'i'
			colBoxCharVertices.clear();
			for (unsigned int k = 0; k < colBoxChar.verticesIdx.size(); k++)									//uzupe�nienie wektora przechowuj�cego punkty dla bry�y kolizji modelu Character
				colBoxCharVertices.push_back(model2.getTransformedVertice(colBoxChar.verticesIdx[k]));

			if (GJK(colBoxPlayerVertices, colBoxCharVertices)) {												//sprawdzenie czy zachodzi kolizja
				std::pair<unsigned int, unsigned int> objIdx_ColboxIdx;											//je�li tak, dodaj indeks obiektu oraz danej bry�y kolizji do wektor�w
				objIdx_ColboxIdx.first = i;
				objIdx_ColboxIdx.second = j;
				newCol.colIdx.push_back(objIdx_ColboxIdx);														//dodaj indeks obiektu oraz indeks bry�y kolizji obektu 'ModelCollision'
			}
		}
	}
	if (newCol.colIdx.size() > 0) {																				//je�li zasz�a kolizja z conajmniej jednym hitboxem modelu
		newCol.status = true; newCol.mainColBox = false;														//status kolizji = TRUE, status kolizji z g��wn�ym hitboxem = FALSE
	}
	else newCol.status = false;																					//w przeciwnym wypadku, statu kolizji = FALSE
	return newCol;
}

//sprawdzenie czy zasz�a kolizja z g��wnym hitboxem badanego obiektu
bool CollisionDetection::CollisionDetection_CharObj_CheckMainColBoxCollision(const Character& model2, unsigned model2ObjIdx, std::vector<Vector>& colBoxMod1Vertices) {
	CollisionBox colBoxObj=model2.getObjectMainCollisionBox(model2ObjIdx);										//za�adowanie g��wnego hitboxa dla obiektu z modelu 2
	std::vector<Vector> colBoxObjVertices;																		//wektor przechowuj�cy wierzcho�ki wchodz�ce w sk�ad hitboxa obiektu

	for (unsigned int i = 0; i < colBoxObj.verticesIdx.size(); i++)
		colBoxObjVertices.push_back(model2.getTransformedVertice(colBoxObj.verticesIdx[i]));					//za��dowanie wierzcho�k�w hitboxa do wektora

	if (GJK(colBoxMod1Vertices, colBoxObjVertices)) return true;												//sprawdzenie algorytmem GJK czy zachodzi kolizja pomi�dzy g��wnymi hitboxami
	else return false;
}

//za�adownie warto�ci dla obiektu detekcji kolizji 'ModelCollision'
ModelCollision CollisionDetection::CollisionDetection_CharObj_LoadNewCol(const Character& model2, unsigned model2ObjIdx, std::vector<Vector>& colBoxMod1Vertices) {
	CollisionBox colBoxObj;																						//hitbox dla obiektu
	std::vector<Vector> colBoxObjVertices;																		//wektor przechowuj�cy wierzcho�ki wchodz�ce w sk�ad hitboxa obiektu
	ModelCollision newCol;																						//obiekt przechowuj�cy informacje zebrane z detekcji kolizji

	if (model2.getObjectCollisionBoxCount(model2ObjIdx) == 0) {													//je�li obiekt nie posiada �adnego hitboxa [opr�cz g��wnego]
		newCol.status = true; newCol.mainColBox = true; newCol.mainColBoxObjIdx = model2ObjIdx;					//ustaw odpowiednie statusy kolizji
		return newCol;
	}
																	
	for (unsigned int i = 0; i < model2.getObjectCollisionBoxCount(model2ObjIdx); i++) {						//dla ka�dego hitboxa obiektu
		colBoxObj = model2.getObjectCollisionBox(model2ObjIdx, i);												//za�aduj nowego hitboxa obiektu
		colBoxObjVertices.clear();																				//wyczy�� wektor wierzcho�k�w hitboxa
		for (unsigned int j = 0; j < colBoxObj.verticesIdx.size(); j++)
			colBoxObjVertices.push_back(model2.getTransformedVertice(colBoxObj.verticesIdx[j]));				//za�aduj nowe warto�ci wierzcho�k�w hitboxa do wektora

		if (GJK(colBoxMod1Vertices, colBoxObjVertices)) {														//sprawdzenie czy zachodzi kolizja
			std::pair<unsigned int, unsigned int> objIdx_ColboxIdx;												//je�li tak, dodaj indeks obiektu oraz danej bry�y kolizji do wektor�w
			objIdx_ColboxIdx.first = model2ObjIdx;
			objIdx_ColboxIdx.second = i;
			newCol.colIdx.push_back(objIdx_ColboxIdx);															
		}
	}

	if (newCol.colIdx.size() > 0) {																				//je�li zasz�a kolizja z conajmniej jednym hitboxem obiektu
		newCol.status = true; newCol.mainColBox = false;														//ustaw status kolizji = TRUE, a status kolizji z g��wnym hitboxem = FALSE
	}
	else newCol.status = false;																					//w przeciwnym wypadku status kolizji = FALSE
	return newCol;
}

//pobranie normalnej do powierzchni kolizji dla standardowego hitboxa
CollisionNormals CollisionDetection::GetCollisonFaceNormal_StandardHitboxCol(const Character& model1, const Character& model2,ModelCollision& col) {
	CollisionNormals normals;																					//wektor przechowuj�cy inf. z algorytmu RayCast dla danych wektor�w normalnych
	std::pair<Vector,unsigned> normal;

	for (unsigned int i = 0; i < col.colIdx.size(); i++) {														//dla wszystkich obiekt�w z kt�ymi zasz�a kolizja												
		CollisionBox colBoxChar = model2.getObjectCollisionBox(col.colIdx[i].first,
			col.colIdx[i].second);																				//pobierz bry�� kolizji dla obiektu z kt�rym zasz�a kolizja

		normal = GetCollisionFaceNormal_GetNormal(model1, model2, colBoxChar);
		if(normal.first!=Vector(0,0,0))
			normals.push_back(normal);																			//dodanie nowej warto�ci do wektora przechowuj�cego inf. z alg. RayCast
	
	}

	return normals;
}

//pobranie normalnej do powierzchni kolizji dla g��wnego hitboxa
CollisionNormals CollisionDetection::GetCollisonFaceNormal_MainHitboxCol(const Character& model1, const Character& model2, ModelCollision& col) {
	CollisionBox colBoxChar;																					//g��wny hitbox dla modelu/obiektu
	std::pair<Vector, unsigned int> normal;																		//obiekt przechowuj�cy inf. z algorytmu RayCast dla danego wektora normalnego
	CollisionNormals normalOut;

	if (col.mainColBoxObjIdx == -1)																				//je�li badanym g��wnym hitboxem jest hitbox modelu
		colBoxChar = model2.getCollisionBox();																	//za�aduj g��wny hitbox modelu
	else colBoxChar = model2.getObjectMainCollisionBox(col.mainColBoxObjIdx);									//w przeciwnym wypadku za�aduj g��wny hitbox obiektu danego indeksem 'col.mainColBoxObjIdx'

	normal=GetCollisionFaceNormal_GetNormal(model1, model2, colBoxChar);										//pobranie warto�ci noramlnej przez algorytm 'RayCast'

	if (normal.second > 0 && normal.first != Vector(0, 0, 0))
		normalOut.push_back(normal);

	return normalOut;
}

//funkcja pomocnicza sprawdzaj�ca czy dany punkt znajduje si� wewn�trz tr�jk�ta
bool CollisionDetection::CheckPointInTriangle(Vector point, Vector triangle[], Vector normal) {					//tr�jk�t opisany jest przy pomocy 3 kolejno podanych punkt�w ['triangle'] oraz normalnej
	Vector n[3], AB, BC, CA;																					
	AB = triangle[1] - triangle[0]; BC = triangle[2] - triangle[1]; CA = triangle[0] - triangle[2];				//inicjalizacja wektor�w opisuj�cych kolejne ramiona tr�jk�ta
	n[0] = AB.CrossProduct(normal);																				//obliczenie normalnych do ka�dego boku tr�jk�ta (wskazuj� one na zewn�trz tr�jk�ta)
	n[1] = BC.CrossProduct(normal);																			
	n[2] = CA.CrossProduct(normal);

	for (unsigned int i = 0; i < 3; i++) {																		//dla ka�dego boku
		double A, B, C, D;															
		A = n[i].x; B = n[i].y; C = n[i].z;																		//wyzanczamy parametry powierzchni opisuj�cej dany bok	
		D = -A*triangle[i].x - B*triangle[i].y - C*triangle[i].z;												//[przy pomocy normalnej do danego boku oraz punkt�w wchodz�cych w jego sk�ad]

		double t = -D - A*point.x - B*point.y - C*point.z;														//obliczenie parametru 't' dla parametrycznego r�wnania prostej	
		t /= A*n[i].x + B*n[i].y + C*n[i].z;																	//zaczynaj�cej si� w punkcie 'point' i skierowanej zgodnie z wektorem normalnym

		if (t < 0) return false;																				//je�li warto�c ta jest ujemna - punkt nie zanjduje si� wewn�trz tr�jk�ta - zwr�� FALSE
	}

	return true;																								//je�li wszystkie warto�ci parametru 't' by�y dodatnie - punkt znajduje si� wewn�trz tr�jk�ta
}

//pobranie normalnej do powierzchni obiektu z kt�r� zasz�a kolizja
//[argumenty: 'model2' - obiekt z kt�rym zasz�a kolizja, 'move' - wekotr przesuni�cia postaci, 'point' - wektor wyznaczonych punkt�w z=startowych dla 'Ray cast', 'colBoxChar' - bry�a kolziji obiektu 'model2']
std::pair<Vector, unsigned> CollisionDetection::GetCollisionFaceNormal_GetNormal(const Character &model1, const Character& model2, CollisionBox &colBoxChar) {
	Vector nRet,point[RayCastLinesNum];
	unsigned int linesCrossed = 0, checkCrossed = 0;
	double R= model1.getCollisionBox().radius, surface[4];
																		
	GetCollisionFaceNormal_LoadPoints(point, model1);															//za�adowanie tablicy 'point' losowymi punktami startowymi dla prostych w algorytmie 'RayCast'

	for (unsigned int i = 0; i < colBoxChar.facesIdx.size(); i++) {
		Vector newN = model2.getTransformedNormal(model2.getFace(colBoxChar.facesIdx[i]).NormalIdx);			//pobranie aktulanej warto�ci normalnej do danej �ciany																						//zresetowanie warto�ci zmiennej pomocniczej
		Vector faceP[3];
		for (unsigned int j = 0; j < 3; j++)
			faceP[j] = model2.getTransformedVertice(model2.getFace(colBoxChar.facesIdx[i]).PointsIdx[j]);		//pobranie punkt�w wchodz�cych w sk�ad danej �ciany

		surface[0] = newN.x; surface[1] = newN.y; surface[2] = newN.z;
		surface[3] = -surface[0]*faceP[0].x - surface[1]*faceP[0].y - surface[2]*faceP[0].z;					//wyznaczenie parametr�w powierzchni opisanej przez dan� �cian�
				
		checkCrossed=GetCollisionFaceNormal_GetNormal_RayCast(faceP, point, newN, surface,R);					//algorytm 'RayCast' - wyznaczenie ile losowo wybranych prostych przechodzi przez dan� pow.

		if(checkCrossed!=-1)																					//je�li algorytm zako�czy� si� sukcesem
			if (checkCrossed > linesCrossed) {																	//je�li przez aktualn� poweirzchni� przesz�o wi�cej prostych ni� poprzednie maksimum
				linesCrossed = checkCrossed;																	//zaktualizuj nowe maksimum
				nRet = newN;																					//zaktualizuj warto�c zwracanaego wektora normalnego
			}
	}
	std::pair<Vector, unsigned> normal_linesCrossed;															//utw�rz par� ('normal', 'linesCrossed')											
	normal_linesCrossed.first = nRet;																			//[normaln� �ciany z kt�r� zasz�a kolizja oraz liczb� prostych kt�re przez ni� przesz�y]
	normal_linesCrossed.second = linesCrossed;
	return normal_linesCrossed;
}

//za�adowanie punkt�w pocz�tkowych dla prostych do algorytmu 'Ray Casting'
//[argumety: 'point' - tablica przechowuj�ca wyzanczone punkty, 'R' - promie� dla sfery kolizji postaci, 'playerPos' - aktualna pozycja postaci, 'playerMidPoint' - �rodek sfery kolizji postaci]
void CollisionDetection::GetCollisionFaceNormal_LoadPoints(Vector point[], const Character& model1) {
	srand(static_cast<unsigned int>(time(0)));
	Vector shift(model1.getCollisionBox().maxPoint - model1.getCollisionBox().midPoint);						//wektor przesuni�cia ze �rodka bry�y kolizji do najbardziej wysuni�tego punktu
	Vector midPt = model1.getCollisionBox().midPoint, playerPos = model1.getPosition();

	for (unsigned int i = 0; i < RayCastLinesNum / 8; i++) {													//wyznaczenie punkt�w startowych dla 'RayCast'
		for (unsigned int j = 0; j < 3; j++) {																	//wylosowaniew warto�ci wsp�rz�dnych punkt�w ograniczonych przez wektor 'shift' 
			int tmpR = static_cast<int>(shift[j] * 100);
			point[i][j] = (rand() % tmpR)/100.0;																//wylosowanie wsp�rz�dnych punktu dla 'RayCast' przy ograniczeniach nak�adanych przez 'dist'
		}

		unsigned int j = i + RayCastLinesNum / 8;																//wyznaczenie warto�ci punkt�w dla ka�dej pozostalych 7 cz�ci sfery jako odbi� punktu bazowego
		point[j] = point[i]; point[j].y = -point[j].y;															//[punkt bazowy: x > 0, y > 0, z > 0]
		j = j + RayCastLinesNum / 8;
		point[j] = point[i]; point[j].z = -point[j].z;
		j = j + RayCastLinesNum / 8;
		point[j] = point[i]; point[j].y = -point[j].y; point[j].z = -point[j].z;
		j = j + RayCastLinesNum / 8;
		point[j] = point[i]; point[j].x = -point[j].x;
		j = j + RayCastLinesNum / 8;
		point[j] = point[i]; point[j].x = -point[j].x; point[j].y = -point[j].y;
		j = j + RayCastLinesNum / 8;
		point[j] = point[i]; point[j].x = -point[j].x; point[j].z = -point[j].z;
		j = j + RayCastLinesNum / 8;
		point[j] = point[i].Negate();
	}

	for (unsigned int i = 0; i < RayCastLinesNum; i++)
		point[i] = model1.getTransformMatrix()*point[i];														//przekszta�cenie wylosowanych punkt�w zgodnie z macierz� przekszta�ce� modelu
}

//wykonanie algorytmu 'RayCast' dla funkcji pobierania normalnej
//[argumenty: 'faceP' - punkty opisuj�ce dan� powierzchni� (tr�jk�t), 'point' - losowe punkty startowe dla prostych w algorytmie 'RayCast', 'normal' - normalna do pow., 'surface' - param. powierzchni]
int CollisionDetection::GetCollisionFaceNormal_GetNormal_RayCast(Vector faceP[],Vector point[],Vector normal,double surface[],double R) {
	bool tError = false;
	unsigned int checkCrossed = 0;

	for (unsigned int j = 0; j < RayCastLinesNum; j++) {													//rozpocz�cie algorytmu 'RayCast'
		double t;																							//parametr 't' dla r�wnania parametrycznego prostej
		double licz = -surface[3] - surface[0] * point[j].x - surface[1] * point[j].y - 
			surface[2] * point[j].z;																		//licznik parametru 't'
		double mian = surface[0] * normal.x + surface[1] * normal.y + surface[2] * normal.z;				//mianownik parametru 't'
		if (mian == 0.0) t = 0.0;																			//zabezpieczenie przed dzieleniem przez '0'			
		else t = licz / mian;																				//wyznacz parametr 't'

		Vector newPoint = normal*t + point[j];																//wyznaczenie rzutu punktu 'point[j]' na opisan� wcze�niej powierzchni� wzd�u� jej normalnej
		if (t <=0 ) {																						//je�li parametr 't' jest dodatni
			if (CheckPointInTriangle(newPoint, faceP, normal))												//je�li punkt znajduje si� wewn�trz powierzchni					
				checkCrossed++;																				//zwi�ksz licznik prostych dla testu raycast
		}																									//[oznacza to �e �ciana ta nie znajduje si� naprzeciw postaci - wtedy 't' < 0]
	}
	return checkCrossed;
}