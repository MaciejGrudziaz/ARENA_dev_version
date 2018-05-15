#include "CLIENT_Player.h"

//konstruktor pobieraj¹cy jedynie nazwê pliku przechowuj¹cego model postaci [reszcie parametrów przypisuje siê wartoœci domyœlne]
Player::Player(const std::string& filename) : DynamicCharacter(filename) {									//wywo³anie odpowiedniego konstruktora klasy Character
	lookAngle = Camera::GetOrientation().x;
}

//konstruktor pobieraj¹cy nazwê pliku, nazwê, pozycjê oraz orientacjê postaci
Player::Player(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation) :
	DynamicCharacter(filename, Name, Position, Orientation) {									//wywo³anie odpwiedniego konstrukotra klasy DynamicCharacter
	lookAngle = Camera::GetOrientation().x;
}

//dodanie broni dla postaci
void Player::AddWeapon(const std::string& weaponName) {
//iniclaizacja sprytnego wskaŸnika broni
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