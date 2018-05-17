#pragma once
#include <windows.h>
#include <gl/glu.h>
#include "Vector.h"
#include "DynamicCharacter.h"

//------------------------------------------------------------------------------------------------------
//------------------------------------------------KAMERA------------------------------------------------
//--------------------klasa opisuj¹ca obecne po³o¿enie i orientacjê kamery dla sceny--------------------
//------------------------------------------------------------------------------------------------------

class Camera {
	Vector position;									//pozycja kamery
	Vector orientation;								//orientacja kamery
	Vector center;									//pozycja punktu w kierunku którym 'patrzy' kamera
	Vector upvector;									//wektor wskazuj¹cy 'górê' kamery

	Vector relativePos;								//pozycja kamery wzglêdem postaci gracza
	Vector relativeCenter;							//pozycja punktu w kierunku którym 'patrzy' kamera wzglêdem postaci gracza

	enum Mode{FREE,BOUND};
	Mode mode;

	DynamicCharacter* character;

public:
	Camera();
	Camera(Vector Position, Vector Center, Vector upVector, Mode mode_);
	Camera(double xPos, double yPos, double zPos, double xCen, double yCen, double zCen, double xUpVec, double yUpVec, double zUpVec, Mode mode_);

	//inicjalizacja kamery przy pomocy wektorów
	void Initialize(Vector Position, Vector Center, Vector upVector,Mode mode_);
	//inicjalizacja kamery przy pomocy zmiennych opisuj¹cych ka¿d¹ wspó³rzêdn¹
	void Initialize(double xPos, double yPos, double zPos, double xCen, double yCen, double zCen, double xUpVec, double yUpVec, double zUpVec,Mode mode_);
	//inicjalizacja postaci przypisanej do kamery
	void InitializeCharacter(DynamicCharacter& character_) { character = &character_; }
	//ustawienie kamery
	void SetCamera();

	//funkcje ustawiaj¹ce odpowiednie wartoœci dla wpsó³rzêdnych kamery 
	void SetPosition(double x, double y, double z) { position.x = x; position.y = y; position.z = z; }
	void SetOrientation(double x, double y, double z) { orientation.x = x; orientation.y = y; orientation.z = z; }
	void SetCenter(double x, double y, double z) { center.x = x; center.y = y; center.z = z; }
	void SetUpVector(double x, double y, double z) { upvector.x = x; upvector.y = y; upvector.z = z; }
	void SetRelativePosition(double x, double y, double z) { relativePos.x = x; relativePos.y = y; relativePos.z = z; }
	void SetRelativeCenter(double x, double y, double z) { relativeCenter.x = x; relativeCenter.y = y; relativeCenter.z = z; }

	//funkcje pobieraj¹ce odpowiednie wartoœci wspó³rzêdnych kamery
	Vector GetPosition() const { return position; }
	Vector GetOrientation() const { return orientation; }
	Vector GetCenter() const { return center; }
	Vector GetUpVector() const { return upvector; }
	Vector GetRelativePosition() const { return relativePos; }
	Vector GetRelativeCenter() const { return relativeCenter; }
};