#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "MyException.h"

class Matrix
{
	private:
		double** elements;
		int columns;
		int rows;
		Matrix(const Matrix& M);
		double* getOneColumn(int& c) const;
		Matrix LUDecomp() const;
		void swapRows(int& r1, int& r2);
		Matrix cutMatrix(int& column, int& row) const;
		Matrix selfcutMatrix(int& column, int& row);
		void insertColumnVector(const double* X, int& c);
		Matrix makeI();
		void copyMatrix(const Matrix& M);
	public:
		Matrix();
		Matrix(const int& c, const int& r);
		~Matrix();
		Matrix& operator=(const Matrix& M);
		Matrix operator+(const Matrix& M) const;
		Matrix operator+=(const Matrix& M);
		Matrix operator-(const Matrix& M) const;
		Matrix operator-=(const Matrix& M);
		Matrix operator*(const Matrix& M) const;
		Matrix operator*=(const Matrix& M);
		Matrix operator*(const double& d) const;
		Matrix operator*=(const double& d);
		Matrix operator/(const double& d) const;
		Matrix operator/=(const double& d);
		double* solveEq(double* R) const;
		Matrix inverse() const;
		Matrix LUinverse() const;
		double LUdeterminant() const;
		double determinant() const;
		int getColumns() const;
		int getRows() const;
		Matrix transpone() const;
		Matrix selftranspone();
		Matrix randomize();
		friend std::ostream& operator<<(std::ostream& out, const Matrix& M);
		friend std::istream& operator>>(std::istream& in, Matrix& M);
};
