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

		if (pos != prevPos || orient != prevOrient) {										//je�li pozycja lub orientacja gracza nie zgadzaj� si� z poprzedni� pozycja lub orientacj�
			character->UpdateTransformMatrix();								//aktualizuj macierz przekszta�cenia gracza
			character->UpdateCollisionBoxVertices();							//aktualizuj wsp�rz�dne wierzcho�k�w bry� kolizji gracza
			character->UpdateCollisionBoxNormals();
		}
	}
}