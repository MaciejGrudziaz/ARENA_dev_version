#pragma once
#include "Vector.h"

//-----------------------------------------------------------------------------------------
//---------------------------------IMPLEMENTACJA MACIERZY----------------------------------
//------------------------------klasa implementująca macierze------------------------------
//-----------------------------------------------------------------------------------------

class Matrix {
	unsigned int rows;												//liczba wierszy								
	unsigned int columns;											//liczba kolumn

	double** matrix;												//tablica opisująca macierz										

public:

	//konstruktory
	Matrix();														

	Matrix(unsigned int Rows, unsigned int Columns);	

	Matrix(const Matrix& m);

	~Matrix();														//destruktor

	void Initilize(unsigned int Rows, unsigned int Columns);		//inicjalziacja macierzy

	void LoadIdentity();											//załadowanie macierzy jednostkowej

	void LoadZeros();												//załadowanie macierzy zerowej

	//przeciążenie operatorów
	Matrix& operator=(const Matrix& m);

	Matrix operator*(const Matrix& m);

	Vector operator*(const Vector& v);

	Matrix operator+(const Matrix& m);

	Matrix operator-(const Matrix& m);

	double* operator[](const unsigned int a);
};