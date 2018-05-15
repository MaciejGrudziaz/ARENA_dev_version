#include "DynamicCharacter.h"

DynamicCharacter::DynamicCharacter(const std::string& filename):Character(filename){
	SetDefaultValues();
}

DynamicCharacter::DynamicCharacter(const std::string& filename, const std::string& Name, const Vector& Position, const Vector& Orientation):
	Character(filename,Name,Position,Orientation){
	SetDefaultValues();
}

//ustawienie domyœlnych wartoœci dla sk³adowych klasy
void DynamicCharacter::SetDefaultValues() {
	position.y += collisionBox.midPoint.y;
	speed = 1.0;
	turnSensitivity = 1.0;
	previousPosition = position;
	nextPosition = position;
	previousOrientation = orientation;
	weight = 1;
	jumpStrength = 25.0;
	lookAngle = 0.0;
}

//aktualizacja macierzy przekszta³ceñ postaci
void DynamicCharacter::UpdateTransformMatrix() {
	Vector angle(orientation); angle = angle / 360.0 * 2.0 * 3.1415;						//zamiana wartoœci k¹tów obrotu wokó³ danych osi na radiany
	//wyzanczenie kwaternionów dla ka¿dej osi obrotu
	Quaternion q_x(cos(angle.x / 2.0), Vector(1, 0, 0)*sin(angle.x / 2.0));
	Quaternion q_y(cos(angle.y / 2.0), Vector(0, 1, 0)*sin(angle.y / 2.0));
	Quaternion q_z(cos(angle.z / 2.0), Vector(0, 0, 1)*sin(angle.z / 2.0));
	//z³o¿enie wszystkich obrotów i wyznaczenie kwaternionu orientacji
	Quaternion Q = q_z.CrossProduct(q_y);
	Q.CrossProduct(q_x);

	transform = Q.CreateMatrix();															//wyznacznie macierzy jednorodnej z kwaternionu orientacji

	for (unsigned int i = 0; i < 3; i++)
		transform[i][3] = position[i];														//dodanie do macierzy jednorodnej wektor przesuniêcia
}

//dostosowanie akcji przemieszczenia
void DynamicCharacter::AdjustMoveAction(Vector k) {
	nextPosition = position + k;
}

//aktualizacja pozycji postaci
void DynamicCharacter::UpdatePosition() {
	previousPosition = position;
	position = nextPosition;
	nextPosition = position;
}

//aktualizacja orientacji postaci
void DynamicCharacter::UpdateOrientation() {
	previousOrientation = orientation;
}

void DynamicCharacter::Update() {
	UpdatePosition();
	UpdateOrientation();

	if (lastCol.size() >= 5)
		lastCol.pop();
}

void DynamicCharacter::AddCollisionState(GAMEPHYSICS::CollisionStatus col) {
	lastCol.push(col);
}
