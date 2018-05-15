#include "CLIENT_Player.h"

//konstruktor pobieraj�cy jedynie nazw� pliku przechowuj�cego model postaci [reszcie parametr�w przypisuje si� warto�ci domy�lne]
Player::Player(const std::string& filename) : DynamicCharacter(filename) {									//wywo�anie odpowiedniego konstruktora klasy Character
	lookAngle = Camera::GetOrientation().x;
}

//konstruktor pobieraj�cy nazw� pliku, nazw�, pozycj� oraz orientacj� postaci
Player::Player(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation) :
	DynamicCharacter(filename, Name, Position, Orientation) {									//wywo�anie odpwiedniego konstrukotra klasy DynamicCharacter
	lookAngle = Camera::GetOrientation().x;
}

//dodanie broni dla postaci
void Player::AddWeapon(const std::string& weaponName) {
//iniclaizacja sprytnego wska�nika broni
	weapon = WeaponPtr(new Gun(weaponName, name, collisionBox.midPoint, position, orientation));
	weapon->enableCharacter();															//odblokowanie obiektu broni
}

//aktualizacja pozycji postaci
void Player::UpdatePosition() {
	DynamicCharacter::UpdatePosition();													//uaktualnienie pozycji postaci						
	if (weapon != nullptr)
		weapon->SetNextPosition(position);													//uaktualnienie pozycji broni postaci
}

//aktualizacja orientacji postaci
void Player::UpdateOrientation() {
	DynamicCharacter::UpdateOrientation();												//uaktualnienie orientacji postaci
	if (weapon != nullptr) {																//uaktualnienie orientacji broni
		Vector weaponOrient = orientation;
		weaponOrient.x = -lookAngle;
		weapon->setOrientation(weaponOrient);
	}
}

void Player::Update() {
	UpdatePosition();
	UpdateOrientation();
	//ActionsModulesRegister::GetModule(this)->UpdateActionsVariables();

	if (weapon != nullptr) {
		weapon->Update();
	}
}

//narysowanie modelu
void Player::DrawModel() {
	OBJmodel::DrawModel();
	if (weapon != NULL)
		weapon->DrawModel();
};