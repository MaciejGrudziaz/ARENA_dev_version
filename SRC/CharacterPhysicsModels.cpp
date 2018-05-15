#include "CharacterPhysicsModels.h"

void CharacterPhysicsModels::ProcessModels() {
	UpdateCollisionBox();

	for (PhysicsModelImpl* model : physicsModels) {
		if (model != nullptr)
			model->Process();
	}
}

CharacterPhysicsModels::~CharacterPhysicsModels() {
	delete character;
	for (PhysicsModelImpl* model : physicsModels)
		delete model;
}

void CharacterPhysicsModels::UpdateCollisionBox() {
	if (character->IsEnabled()) {
		Vector pos, prevPos, orient, prevOrient;
		pos = character->getPosition();										//wczytanie obecnej pozycji gracza
		prevPos = character->GetPreviousPosition();							//wczytanie poprzedniej pozycji gracza
		orient = character->getOrientation();									//wczytanie orientacji gracza
		prevOrient = character->GetPreviousOrientation();						//wczytanie poprzedniej orientacji gracza

		if (pos != prevPos || orient != prevOrient) {										//jeœli pozycja lub orientacja gracza nie zgadzaj¹ siê z poprzedni¹ pozycja lub orientacj¹
			character->UpdateTransformMatrix();								//aktualizuj macierz przekszta³cenia gracza
			character->UpdateCollisionBoxVertices();							//aktualizuj wspó³rzêdne wierzcho³ków bry³ kolizji gracza
			character->UpdateCollisionBoxNormals();
		}
	}
}