#pragma once
#include <math.h>
//---------------------------------------------------------------------------------------------
//-------------------------------------WEKTOR [GEOMETRIA]--------------------------------------
//--------------------struktura opisuj�ca tr�jwymiarowy wektor geometryczny--------------------
//---------------------------------------------------------------------------------------------

enum VecType { FREE, BOUND };

struct POSITION {
	int x;
	int y;
};

struct Vector {
	double x;																	//wsp�rz�dne wektora
	double y;
	double z;
	VecType type;

	Vector() { x = 0.0; y = 0.0; z = 0.0; type = BOUND; }						//konstruktor domy�lny

	Vector(VecType type_) { x = 0.0; y = 0.0; z = 0.0; type = type_; }

	Vector(double setX, double setY, double setZ, VecType type_=BOUND) {		//konstruktor wczytuj�cy od razu warto�ci wsp�rz�dnych
		x = setX; y = setY; z = setZ; type = type_;
	}

	Vector(const Vector& a) {
		x = a.x; y = a.y; z = a.z; type = a.type;
	}

	Vector& ABS();

	double MOD() const;

	double DotProduct(Vector v) const;

	Vector Negate() const;

	void NORM();

	Vector CrossProduct(Vector v) const;

	Vector& operator= (const Vector& a);

	Vector operator+(const Vector& a) const;

	Vector& operator+= (const Vector& a);

	Vector operator-(const Vector& a) const;

	Vector& operator-=(const Vector& a);

	Vector operator*(double a) const;

	Vector& operator*=(double a);

	Vector operator/(double a) const;

	Vector& operator/=(double a);

	double& operator[](unsigned int a);

	bool operator!=(Vector a) const{
		if (a.x != x) return true;
		if (a.y != y) return true;
		if (a.z != z) return true;
		return false;
	}

	bool operator==(Vector a) const{
		if (a.x != x) return false;
		if (a.y != y) return false;
		if (a.z != z) return false;
		return true;
	}
};