#include "Matrix.h"

//konsturktor domy�lny
Matrix::Matrix() {
	rows = 0; columns = 0;												//inicajlizacja macierzy
	matrix = NULL;
}

//konstruktor wczytuj�cy ilo�� wierszy i kolumn
Matrix::Matrix(unsigned int Rows, unsigned int Columns) {
	rows = Rows;														//przypisanie warto�ci wierszy i kolumn
	columns = Columns;

	matrix = new double* [rows];										//inicjalizacja tablicy macierzy
	for (unsigned int i = 0; i < rows; i++)
		matrix[i] = new double[columns];

	for (unsigned int i = 0; i < rows; i++)								//uzupe�nienie macierzy warto�ciami zerowymi
		for (unsigned int j = 0; j < columns; j++)
			matrix[i][j] = 0.0;
}

//kosntruktor kopiuj�cy
Matrix::Matrix(const Matrix& m) {
	rows = m.rows;														//przypisanie warto�ci wierszy i kolumn
	columns = m.columns;

	matrix = new double*[rows];											//inicjalizacja tablicy macierzy
	for (unsigned int i = 0; i < rows; i++)
		matrix[i] = new double[columns];

	for (unsigned int i = 0; i < m.rows; i++)							//przypisz warto�ci z danej macierzy 'm'
		for (unsigned int j = 0; j < m.columns; j++)
			matrix[i][j] = m.matrix[i][j];
}

//destruktor
Matrix::~Matrix() {
	if (matrix != NULL) {												//je�li macierz zosta�a zainicjalizowana 
		for (unsigned int i = 0; i < rows; i++)							//usu� ka�dy wiersz macierzy
			delete[] matrix[i];

		delete[] matrix;												//usu� macierz
	}
}

//inicjalizacja macierzy
void Matrix::Initilize(unsigned int Rows, unsigned int Columns) {
	if (matrix != NULL) {												//jesli macierz zosta�a zainicjalizowana
		for (unsigned int i = 0; i < rows; i++)							//usu� j�
			delete[] matrix[i];
		delete[] matrix;
	}

	rows = Rows;														//wczytaj now� liczb� wierszy i kolumn
	columns = Columns;

	matrix = new double*[rows];											//zainicjalizuj tablic� macierzy
	for (unsigned int i = 0; i < rows; i++)
		matrix[i] = new double[columns];

	for (unsigned int i = 0; i < rows; i++)								//uzpe�nienie macierzy warto�ciami zerowymi
		for (unsigned int j = 0; j < columns; j++)
			matrix[i][j] = 0.0;
}

//za�adowanie macierzy jednostkowej
void Matrix::LoadIdentity() {
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < columns; j++) {
			if (i == j) matrix[i][j] = 1.0;
			else matrix[i][j] = 0.0;
		}
	}
}

//za�adowanie macierzy zerowej
void Matrix::LoadZeros() {
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < columns; j++)
			matrix[i][j] = 0.0;
}

//-----------------------------------------------------------------------------------
//------------------------------PRZECI��ENIE OPERATOR�W------------------------------
//-----------------------------------------------------------------------------------

Matrix& Matrix::operator=(const Matrix& m) {
	if (m.rows == rows && m.columns == columns) {
		for (unsigned int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < columns; j++)
				matrix[i][j] = m.matrix[i][j];
		}

		return *this;
	}
	else return *this;
}

Matrix Matrix::operator*(const Matrix& m) {
	if (columns != m.rows)
		return Matrix(0,0);

	Matrix m2(rows, m.columns);

	for(unsigned int i=0;i<rows;i++)
		for (unsigned int j = 0; j < m.columns; j++) {
			for (unsigned int k = 0; k < columns; k++)
				m2.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
		}

	return m2;
}

Vector Matrix::operator*(const Vector& v) {
	if ((columns != 3 && columns != 4) || columns != rows)
		return Vector();

	Vector v2;

	v2.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z;
	v2.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z;
	v2.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z;

	if(columns==4 && v.type==BOUND) {
		v2.x += matrix[0][3];
		v2.y += matrix[1][3];
		v2.z += matrix[2][3];
	}

	return v2;
}

Matrix Matrix::operator+(const Matrix& m) {
	if (rows != m.rows || columns != m.columns)
		return Matrix(0, 0);

	Matrix m2(rows, columns);
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < columns; j++)
			m2.matrix[i][j] = matrix[i][j] + m.matrix[i][j];

	return m2;
}

Matrix Matrix::operator-(const Matrix& m) {
	if (rows != m.rows || columns != m.columns)
		return Matrix(0, 0);

	Matrix m2(rows, columns);
	for (unsigned int i = 0; i < rows; i++)
		for (unsigned int j = 0; j < columns; j++)
			m2.matrix[i][j] = matrix[i][j] - m.matrix[i][j];

	return m2;
}

double* Matrix::operator[](const unsigned int a) {
	if (a < rows)
		return matrix[a];
	else return NULL;
}