#pragma once
#include "ActionsImpl.h"

struct LookUpAction :public ActionImpl {
	DynamicCharacter* character;
	double t;
	int* mouseMove;
	LookUpAction(DynamicCharacter* character_, int* mouseMoveBuff) :character(character_), mouseMove(mouseMoveBuff), ActionImpl("LookUp") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
	}
	void operator()() {
		double xRot = (*mouseMove) * t * character->GetTurnSensitivity() * 360.0;						//xRot - k¹t obrotu w osi X, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce w osi Y
																										//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		double lookAngle = character->GetLookAngle();
		lookAngle -= xRot;
		if (lookAngle > 90.0) lookAngle = 90.0;
		character->SetLookAngle(lookAngle);
	}
};

struct LookDownAction :public ActionImpl {
	DynamicCharacter* character;
	double t;
	int* mouseMove;
	LookDownAction(DynamicCharacter* character_, int* mouseMoveBuff) :character(character_), mouseMove(mouseMoveBuff), ActionImpl("LookDown") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
	}
	void operator()() {
		double xRot = (*mouseMove) * t * character->GetTurnSensitivity()*360.0;							//xRot - k¹t obrotu w osi X, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce w osi Y
																												//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		double lookAngle = character->GetLookAngle();
		lookAngle -= xRot;
		if (lookAngle < -90) lookAngle = -90.0;
		character->SetLookAngle(lookAngle);
	}
};

struct LookLeftAction :public ActionImpl {
	DynamicCharacter* character;
	double t;
	int* mouseMove;
	LookLeftAction(DynamicCharacter* character_, int* mouseMoveBuff) :character(character_), mouseMove(mouseMoveBuff), ActionImpl("LookLeft") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
	}
	void operator()() {
		Vector orient = character->getOrientation();
		character->SetPreviousOrientation(orient);
		double yRot = (*mouseMove) * t * character->GetTurnSensitivity() * 360.0;							//yRot - k¹t obrotu w osi Y, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce w osi X
																												//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		orient.y -= yRot;																//ustawienie nowej wartoœci orientacji postaci w osi Y
		if (orient.y > 360.0)															//sprawdzenie czy wartoœæ orientacji przekroczy³a zakres
			orient.y = 0.0;
		character->setOrientation(orient);
	}
};

struct LookRightAction :public ActionImpl {
	DynamicCharacter* character;
	double t;
	int* mouseMove;
	LookRightAction(DynamicCharacter* character_, int* mouseMoveBuff) :character(character_), mouseMove(mouseMoveBuff), ActionImpl("LookRight") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
	}
	void operator()() {
		Vector orient = character->getOrientation();
		character->SetPreviousOrientation(orient);
		double yRot = (*mouseMove) * t * character->GetTurnSensitivity() * 360.0;							//yRot - k¹t obrotu, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce
																												//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		orient.y -= yRot;																//ustawienie nowej wartoœci orientacji postaci gracza w osi Y
		if (orient.y < 0)																//sprawdzenie czy wartoœæ orientacji przekroczy³a zakres
			orient.y = 360.0;
		character->setOrientation(orient);
	}
};

struct SetNextPositionAction :public ActionImpl {
	DynamicCharacter* character;
	Vector nextPos;
	SetNextPositionAction(DynamicCharacter* character_) :character(character_), nextPos(Vector()), ActionImpl("SetNextPosition") {}
	void Set(Vector nextPos_) { nextPos = nextPos_; }
	void operator()() {
		character->SetNextPosition(nextPos);
	}
};

struct AirAction :public ActionImpl {
	bool enable;
	Vector position;
	Vector shift;
	Vector size;
	double time;
	double frameTime;
	double G_val;
	double yMapVal;
	DynamicCharacter* character;

	AirAction(DynamicCharacter* character_) :character(character_), enable(false), time(0.0), ActionImpl("Air") {
		size = character->getCollisionBox().size;
		frameTime = PHYSICSCONST::targetFrameTime / 1000000.0;
		G_val = PHYSICSCONST::G;
	}
	void Fall() {
		enable = true;
		position = character->getPosition();
		shift = character->getPosition()-character->GetPreviousPosition();
		time = 0.0;
	}
	void Jump() {
		enable = true;
		position = character->getPosition();
		shift = character->getPosition()-character->GetPreviousPosition();
		shift.y = character->GetJumpStrength();
		time = 0.0;
	}
	void Land() {
		if (enable) {
			Vector charPos = character->getPosition();
			if ((charPos.y - position.y) > 0.01*size.y || charPos.y < position.y) {
				enable = false;
				Vector nextPos = character->GetNextPosition();
				nextPos.y = yMapVal;
				character->SetNextPosition(nextPos);
			}
		}
		else {
			Vector nextPos = character->GetNextPosition();
			nextPos.y = yMapVal;
			character->SetNextPosition(nextPos);
		}
	}
	void Set_yMapVal(double yMapVal_) { yMapVal = yMapVal_; }

	void operator()() {
		if (enable) {
			time += frameTime;
			Vector pos = character->GetNextPosition();

			pos.x += shift.x / 1.33;
			pos.z += shift.z / 1.33;

			double val1 = shift.y*time;
			double val2 = 0.5*G_val*(time*time)*character->GetWeight();

			pos.y = position.y + val1 - val2;
			character->SetNextPosition(pos);
		}
	}
};

struct JumpAction :public ActionImpl {
	AirAction* air;

	JumpAction(ActionImpl* air_) :ActionImpl("Jump") {
		air = static_cast<AirAction*>(air_);
	}

	void operator()() {
		if (!air->enable)
			air->Jump();
	}
};

struct FallAction :public ActionImpl {
	AirAction* air;

	FallAction(ActionImpl* air_):ActionImpl("Fall") {
		air= static_cast<AirAction*>(air_);
	}

	void operator()() {
		if (!air->enable)
			air->Fall();
	}
};

struct ForwardAction :public ActionImpl {
	DynamicCharacter* character;
	AirAction* air;
	double t;
	Vector size;
	ForwardAction(DynamicCharacter* character_,ActionImpl* air_) :character(character_), ActionImpl("Forward") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		air= static_cast<AirAction*>(air_);
		size = character->getCollisionBox().size;
	}
	void operator()() {
		if (!air->enable) {
			double s = character->GetSpeed()*t;
			double Yangle = character->getOrientation().y / 360.0*2.0*3.1415;
			Vector nextPos = character->GetNextPosition();
			nextPos.x -= s*sin(-Yangle);
			nextPos.z += s*cos(-Yangle);
			character->SetNextPosition(nextPos);
		}
	}
};

struct BackwardAction :public ActionImpl {
	DynamicCharacter* character;
	AirAction* air;
	double t;
	Vector size;
	BackwardAction(DynamicCharacter* character_,ActionImpl* air_) :character(character_), ActionImpl("Backward") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		air= static_cast<AirAction*>(air_);
		size = character->getCollisionBox().size;
	}
	void operator()() {
		if (!air->enable) {
			double s = character->GetSpeed()*t;																//s - wartoœæ przemieszczenia, speed - prêdkoœæ postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
			double Yangle = character->getOrientation().y / 360.0*2.0*3.1415;
			Vector nextPos = character->GetNextPosition();
			nextPos.x += s*sin(-Yangle);
			nextPos.z -= s*cos(-Yangle);
			character->SetNextPosition(nextPos);
		}
	}
};

struct LeftAction :public ActionImpl {
	DynamicCharacter* character;
	AirAction* air;
	double t;
	Vector size;
	LeftAction(DynamicCharacter* character_, ActionImpl* air_) :character(character_), ActionImpl("Left") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		air= static_cast<AirAction*>(air_);
		size = character->getCollisionBox().size;
	}
	void operator()() {
		if (!air->enable) {
			double s = character->GetSpeed()*t;																	//s - wartoœæ przemieszczenia, speed - prêdkoœæ postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
			double Yangle = character->getOrientation().y / 360.0*2.0*3.1415;
			Vector nextPos = character->GetNextPosition();
			nextPos.x += s*cos(-Yangle);
			nextPos.z += s*sin(-Yangle);
			character->SetNextPosition(nextPos);
		}
	}
};

struct RightAction :public ActionImpl {
	DynamicCharacter* character;
	AirAction* air;
	double t;
	Vector size;
	RightAction(DynamicCharacter* character_,ActionImpl* air_) :character(character_), ActionImpl("Right") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		air= static_cast<AirAction*>(air_);
		size = character->getCollisionBox().size;
	}
	void operator()() {
		if (!air->enable) {
			double s = character->GetSpeed()*t;																	//s - wartoœæ przemieszczenia, speed - prêdkoœæ postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
			double Yangle = character->getOrientation().y / 360.0*2.0*3.1415;
			Vector nextPos = character->GetNextPosition();
			nextPos.x -= s*cos(-Yangle);
			nextPos.z -= s*sin(-Yangle);
			character->SetNextPosition(nextPos);
		}
	}
};

struct LandAction :public ActionImpl {
	AirAction* air;
	LandAction(ActionImpl* air_) :ActionImpl("Land") {
		air= static_cast<AirAction*>(air_);
	}
	void operator()() {
		air->Land();
	}
};

struct MoveToPosAction :public ActionImpl {
	DynamicCharacter* character;
	AirAction* airAction;
	bool land;
	bool air;
	Vector nextPos;
	
	MoveToPosAction(DynamicCharacter* character_, ActionImpl* airAction_) :character(character_), land(false), ActionImpl("MoveToPos") {
		airAction =static_cast<AirAction*>(airAction_);
	}
	void operator()() {		
		if (land) {
			airAction->Set_yMapVal(nextPos.y);
			airAction->Land();
			land = false;
		}
		if (air) {
			(*airAction)();
			Vector charNextPos = character->GetNextPosition();
			nextPos.y = charNextPos.y;
			air = false;
		}

		character->SetNextPosition(nextPos);
	}
};

struct HalfSpeedAction :public ActionImpl {
	DynamicCharacter* character;
	double speed;

	HalfSpeedAction(DynamicCharacter* character_) :character(character_), ActionImpl("HalfSpeed") {
		speed = character->GetBasicSpeed() / 2.0;
	}

	void operator()() {
		character->SetSpeed(speed);
	}
};

struct FullSpeedAction :public ActionImpl {
	DynamicCharacter* character;
	double speed;

	FullSpeedAction(DynamicCharacter* character_) :character(character_), ActionImpl("FullSpeed") {
		speed = character->GetBasicSpeed();
	}

	void operator()() {
		character->SetSpeed(speed);
	}
};

struct ForceFallAction :public ActionImpl {
	AirAction* air;

	ForceFallAction(ActionImpl* air_):ActionImpl("ForceFall") {
		air = static_cast<AirAction*>(air_);
	}

	void operator()() {
		if(air->enable && air->character->getPosition().y > air->character->GetPreviousPosition().y)
			air->Fall();
	}
};

struct CameraForwardAction: public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	CameraForwardAction(Camera* camera_):camera(camera_),ActionImpl("CameraForward") {
		t= PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double s = speed*t;
		double Yangle = camera->GetOrientation().y;
		Vector nextPos = camera->GetPosition();

		nextPos.x -= s*sin(-Yangle);
		nextPos.z += s*cos(-Yangle);

		camera->SetPosition(nextPos);
	}
};

struct CameraBackwardAction : public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	CameraBackwardAction(Camera* camera_) :camera(camera_), ActionImpl("CameraBackward") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double s = speed*t;
		double Yangle = camera->GetOrientation().y;
		Vector nextPos = camera->GetPosition();

		nextPos.x += s*sin(-Yangle);
		nextPos.z -= s*cos(-Yangle);

		camera->SetPosition(nextPos);
	}
};

struct CameraLeftAction : public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	CameraLeftAction(Camera* camera_) :camera(camera_), ActionImpl("CameraLeft") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double s = camera->GetSpeed()*t;																	//s - wartoœæ przemieszczenia, speed - prêdkoœæ postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
		double Yangle = camera->GetOrientation().y;
		Vector nextPos = camera->GetPosition();
		nextPos.x += s*cos(-Yangle);
		nextPos.z += s*sin(-Yangle);
		
		camera->SetPosition(nextPos);
	}
};

struct CameraRightAction : public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	CameraRightAction(Camera* camera_) :camera(camera_), ActionImpl("CameraRight") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double s = camera->GetSpeed()*t;																	//s - wartoœæ przemieszczenia, speed - prêdkoœæ postaci, t/1000000.0 - czas trwania poprzedniej klatki w sek.
		double Yangle = camera->GetOrientation().y;
		Vector nextPos = camera->GetPosition();
		nextPos.x -= s*cos(-Yangle);
		nextPos.z -= s*sin(-Yangle);

		camera->SetPosition(nextPos);
	}
};

struct CameraUpAction : public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	CameraUpAction(Camera* camera_) :camera(camera_), ActionImpl("CameraUp") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double s = speed*t;
		Vector nextPos = camera->GetPosition();

		nextPos.y += s;

		camera->SetPosition(nextPos);
	}
};

struct CameraDownAction : public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	CameraDownAction(Camera* camera_) :camera(camera_), ActionImpl("CameraDown") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double s = speed*t;
		Vector nextPos = camera->GetPosition();

		nextPos.y -= s;

		camera->SetPosition(nextPos);
	}
};

struct CameraLookUp :public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	int* mouseMove;
	CameraLookUp(Camera* camera_,int* mouseMoveBuf) :camera(camera_), mouseMove(mouseMoveBuf), ActionImpl("CameraLookUp") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double xRot = (*mouseMove) * t * camera->GetTurnSensitivity()*2.0*3.1415;						//xRot - k¹t obrotu w osi X, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce w osi Y
																										//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		Vector camOrient = camera->GetOrientation();
		camOrient.x -= xRot;
		if (camOrient.x > 1.57) camOrient.x = 1.57;
		camera->SetOrientation(camOrient);
	}
};

struct CameraLookDown :public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	int* mouseMove;
	CameraLookDown(Camera* camera_, int* mouseMoveBuf) :camera(camera_), mouseMove(mouseMoveBuf), ActionImpl("CameraLookDown") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		double xRot = (*mouseMove) * t * camera->GetTurnSensitivity()*2.0*3.1415;						//xRot - k¹t obrotu w osi X, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce w osi Y
																							//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		Vector camOrient = camera->GetOrientation();
		camOrient.x -= xRot;
		if (camOrient.x < -1.57) camOrient.x = -1.57;
		camera->SetOrientation(camOrient);
	}
};

struct CameraLookLeft :public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	int* mouseMove;
	CameraLookLeft(Camera* camera_, int* mouseMoveBuf) :camera(camera_), mouseMove(mouseMoveBuf), ActionImpl("CameraLookLeft") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		Vector camOrient = camera->GetOrientation();
		double yRot = (*mouseMove) * t * camera->GetTurnSensitivity()*2.0*3.1415;							//yRot - k¹t obrotu, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce
																								//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		camOrient.y -= yRot;																//ustawienie nowej wartoœci orientacji postaci gracza w osi Y
		if (camOrient.y >6.28)																//sprawdzenie czy wartoœæ orientacji przekroczy³a zakres
			camOrient.y = 0;
		camera->SetOrientation(camOrient);
	}
};

struct CameraLookRight :public ActionImpl {
	Camera* camera;
	double speed;
	double t;
	int* mouseMove;
	CameraLookRight(Camera* camera_, int* mouseMoveBuf) :camera(camera_), mouseMove(mouseMoveBuf), ActionImpl("CameraLookRight") {
		t = PHYSICSCONST::targetFrameTime / 1000000.0;
		speed = camera->GetSpeed();
	}

	void operator()() {
		Vector camOrient = camera->GetOrientation();
		double yRot = (*mouseMove) * t * camera->GetTurnSensitivity()*2.0*3.1415;							//yRot - k¹t obrotu, Action.param[0] - wartoœæ przemieszczenia myszy w poprzedniej klatce
																											//t/1000000.0 - czas trwania poprzedniej klatki w sek., turnSensitivity - czu³oœæ obrotu postaci
		camOrient.y -= yRot;																//ustawienie nowej wartoœci orientacji postaci gracza w osi Y
		if (camOrient.y < 0)																//sprawdzenie czy wartoœæ orientacji przekroczy³a zakres
			camOrient.y = 6.28;
		camera->SetOrientation(camOrient);
	}
};
