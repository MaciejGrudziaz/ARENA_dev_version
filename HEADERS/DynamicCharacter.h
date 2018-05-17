#pragma once
#include <memory>
#include <queue>
#include "Character.h"
#include "TIMER.h"
//#include "Camera.h"
#include "LOGFILE.h"
#include "PhysicsModuleConst.h"
#include "GamePhysicsStruct.h"

//-------------------------------------------------------------------------------------
//------------------------------KLASA POSTACI DYNAMICZNEJ------------------------------
//----------------------------------[klasa wirtualna]----------------------------------
//-------------------------------------------------------------------------------------

class DynamicCharacter :public Character{
protected:
	std::queue<GAMEPHYSICS::CollisionStatus> lastCol;
	double basicSpeed;
	double speed;																				//pr�dko�� przemieszczenia postaci
	double turnSensitivity;																		//czu�o�� obrotu i rozgl�dania si� postaci	
	double weight;
	double jumpStrength;																		//warto�� si�y wyskoku

	double lookAngle;																			//k�t 'widzenia' postaci [odchylenie kamery wzd�u� osi 'x' uk�ady lokalnego modelu]

public:

	//konstruktory
	DynamicCharacter(const std::string& filename);
	DynamicCharacter(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation);

	void SetDefaultValues();																	//ustawienie domy�lnych warto�ci dla sk�adowych klasy

	void UpdateTransformMatrix();																//aktualizacja macierzy przekszta�ce� postaci

	void AdjustMoveAction(Vector k);															//dostosowanie akcji przemieszczenia

	void UpdatePosition();																		//aktualizacja pozycji
	void UpdateOrientation();																	//aktualizacja orientacji

	void Update();

	//pobranie warto�ci sk�adowych klasy
	double GetBasicSpeed() const { return basicSpeed; }
	double GetSpeed() const { return speed; }															//pobranie warto�ci pr�dko�ci postaci gracza
	double GetTurnSensitivity() const { return turnSensitivity; }										//pobranie warto�ci czu�o�ci obrotu postaci gracza
	double GetWeight() const { return weight; }
	double GetJumpStrength() const { return jumpStrength; }
	//IdxPair GetSectorIdx() { return sectorIdx; }
	double GetLookAngle() const { return lookAngle; }
	const GAMEPHYSICS::CollisionStatus& GetLastCol() const { return lastCol.back(); }
	unsigned GetLastColSize()const { return lastCol.size(); }

	//ustwienie odpowiednich warto�ci sk�adowych klasy
	void SetBasicSpeed(double speed_) { basicSpeed = speed_; speed = speed_; }
	void SetSpeed(double Speed) { speed = Speed; }												//ustawienie warto�ci pr�dko�ci postaci gracza
	void SetTurnSensitivity(double Sensitivity) { turnSensitivity = Sensitivity; }				//ustawienie warto�ci czu�o�ci obrotu gracza
	void SetWeight(double _weight) { weight = _weight; }
	void SetJumpStrength(double JumpStrength) { jumpStrength = JumpStrength; }
	void SetSectorIdx(const IdxPair& newIdx) { sectorIdx = newIdx; }
	void SetLookAngle(double lookAngle_) { lookAngle = lookAngle_; }

	void AddCollisionState(GAMEPHYSICS::CollisionStatus col);

	virtual ~DynamicCharacter() {}
};
