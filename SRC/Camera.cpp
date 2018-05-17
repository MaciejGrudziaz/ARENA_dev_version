#include "Camera.h"

//inicjalizacja sk³adowych staycznych klasy
//Vector Camera::position = { 0.0, 0.0, 0.0 };
//Vector Camera::orientation = { 0.0,0.0,0.0 };
//Vector Camera::center = { 0.0, 0.0, -10.0 };
//Vector Camera::upvector = { 0.0, 0.0, 0.0 };
//Vector Camera::relativePos = { 0.0,0.0,0.0 };
//Vector Camera::relativeCenter = { 0.0,0.0,0.0 };

Camera::Camera() {
	position = { 0.0, 0.0, 0.0 };
	orientation = { 0.0,0.0,0.0 };
	center = { 0.0, 0.0, 0.0 };
	upvector = { 0.0, 0.0, 0.0 };
	relativePos = { 0.0,0.0,0.0 };
	relativeCenter = { 0.0,0.0,0.0 };
	mode = FREE;
	character = nullptr;
}

Camera::Camera(Vector Position, Vector Center, Vector upVector, Mode mode_){
	position = Position;
	center = Center;
	upvector = upVector;
	mode = mode_;
	character = nullptr;
}

Camera::Camera(double xPos, double yPos, double zPos, double xCen, double yCen, double zCen, double xUpVec, double yUpVec, double zUpVec, Mode mode_) {
	position = { xPos,yPos,zPos };
	center = { xCen,yCen,zCen };
	upvector = { xUpVec,yUpVec,zUpVec };
	mode = mode_;
	character = nullptr;
}

//inicjalizacja kamery przy pomocy wektorów
void Camera::Initialize(Vector Position, Vector Center, Vector UpVector, Mode mode_)
{
	position = Position;
	center = Center;
	upvector = UpVector;
	mode = mode_;
}

//inicjalizacja kamery przy pomocy zmiennych opisuj¹cych dane wspó³rzêdne
void Camera::Initialize(double xPos, double yPos, double zPos, double xCen, double yCen, double zCen, double xUpVec, double yUpVec, double zUpVec, Mode mode_)
{
	position.x = xPos;
	position.y = yPos;
	position.z = zPos;

	center.x = xCen;
	center.y = yCen;
	center.z = zCen;

	upvector.x = xUpVec;
	upvector.y = yUpVec;
	upvector.z = zUpVec;

	mode = mode_;
}

void Camera::Update() {
	assert(!(mode == BOUND && character == nullptr));

	UpdateCameraPosition();
	UpdateCameraOrientation();
}

//ustawienie kamery w scenie OpenGL
void Camera::SetCamera()
{
	//funkcja ustwaij¹ca kamerê z biblioteki GLU
	gluLookAt(position.x, position.y, position.z, center.x, center.y, center.z, upvector.x, upvector.y, upvector.z);
}

//ustawienie kamery z perspektywy gracza
void Camera::SetFirstPerson() {
	Vector size = character->getCollisionBox().size;
	relativePos = { 0.0,0.8*size.y,0.25 };
}

//ustawienie kamery zza pleców gracza
void Camera::SetThirdPerson() {
	relativePos = { 0.0,5.0,-8.0 };
}

void Camera::UpdateCameraPosition() {
	if (mode == BOUND) {
		if (character->IsEnabled()) {
			Vector charPos= character->getPosition();			//pobranie pozycji postaci
			Vector charOrient= character->getOrientation();		//pobranie orienatcji postaci

			double angle = charOrient.y / 360.0 * 2.0 * 3.1415;				//k¹t obrotu postaci wokó³ osi y [w radianach; 2.0 * 3.1415 -> 2 * PI]
			charPos.x -= relativePos.z*sin(-angle);							//wartoœæ pozycji kamery w osi x w stosunku do pozycji postaci
			charPos.y += relativePos.y;										//wartoœæ pozycji kamery w osi y w stosunku do pozycji postaci
			charPos.z += relativePos.z*cos(-angle);							//wartoœæ pozycji kamery w osi z w stosunku do pozycji postaci

			position = charPos;
		}
	}
}

void Camera::UpdateCameraOrientation() {
	if (mode == BOUND) {
		if (character->IsEnabled()) {
			Vector characterOrient = character->getOrientation();
			orientation.y = characterOrient.y;
			orientation.x = character->GetLookAngle();

			//przeliczenie orientacji kamery na radiany
			orientation.x = orientation.x / 360.0 * 2.0 *3.1415;
			orientation.y = orientation.y / 360.0 * 2.0 *3.1415;
			orientation.z = orientation.z / 360.0 * 2.0 *3.1415;

			//wyliczenie wspó³rzêdnych punktu 'wycentrowania' kamery ze wzoru:
			//y = R * sin( -orientation.x ), x = r * sin( orientation.y ), z = r * cos( orientation.y )
			//gdzie: R - odleg³oœæ od œrodka kamery do punktu 'wycentrowania', r - rzutowanie odleg³oœci R na p³aszczyznê (X,Z), obliczona zgodnie ze wzorem: r = sqrt( R^2 + y^2 )
			double R = sqrt((-relativePos.z + relativeCenter.z)*(-relativePos.z + relativeCenter.z) + relativePos.y*relativePos.y);

			center.y = R*sin(-orientation.x);

			double r = sqrt(R*R + center.y*center.y);

			center.x = position.x + r*sin(orientation.y);
			center.y = position.y - center.y;
			center.z = position.z + r*cos(orientation.y);
		}
	}
}