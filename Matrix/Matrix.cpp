#include "Matrix.h"

using namespace std;

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(const int& c, const int& r) : columns(c), rows(r)
{
	elements = new double*[rows];
	for (int i = 0;i < rows;i++)
		elements[i] = new double[columns];
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			elements[i][j] = 0;
}

Matrix::Matrix(const Matrix& M) : columns(M.columns), rows(M.rows)
{
	elements = new double*[rows];
	for (int i = 0;i < rows;i++)
		elements[i] = new double[columns];
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			elements[i][j] = M.elements[i][j];
}

Matrix::~Matrix()
{
	for (int i = 0;i < rows;i++)
		delete elements[i];
	delete elements;
}

Matrix& Matrix::operator=(const Matrix& M)
{
	copyMatrix(M);
	return *this;
}

Matrix Matrix::operator+(const Matrix& M) const
{
	int max_col, min_col, max_row, min_row;
	if (columns > M.columns)
	{
		max_col = columns;
		min_col = M.columns;
	}
	else
	{
		max_col = M.columns;
		min_col = columns;
	}
	if (rows > M.rows)
	{
		max_row = rows;
		min_row = M.rows;
	}
	else
	{
		max_row = M.rows;
		min_row = rows;
	}
	Matrix sumM(max_col, max_row);
	for (int i = 0;i < min_row;i++)
		for (int j = 0;j < min_col;j++)
			sumM.elements[i][j] = elements[i][j] + M.elements[i][j];
	if (max_col == columns)
	{
		for (int i = 0;i < rows;i++)
			for (int j = min_col;j < max_col;j++)
				sumM.elements[i][j] = elements[i][j];
	}
	else
	{
		for (int i = 0;i < M.rows;i++)
			for (int j = min_col;j < max_col;j++)
				sumM.elements[i][j] = M.elements[i][j];
	}
	if (max_row == rows)
	{
		for (int i = min_row;i < max_row;i++)
			for (int j = 0;j < columns;j++)
				sumM.elements[i][j] = elements[i][j];
	}
	else
	{
		for (int i = min_row;i < max_row;i++)
			for (int j = 0;j < M.columns;j++)
				sumM.elements[i][j] = M.elements[i][j];
	}
	return sumM;
}

Matrix Matrix::operator+=(const Matrix& M)
{
	*this = *this + M;
	return *this;
}

Matrix Matrix::operator-(const Matrix& M) const
{
	int max_col, min_col, max_row, min_row;
	if (columns > M.columns)
	{
		max_col = columns;
		min_col = M.columns;
	}
	else
	{
		max_col = M.columns;
		min_col = columns;
	}
	if (rows > M.rows)
	{
		max_row = rows;
		min_row = M.rows;
	}
	else
	{
		max_row = M.rows;
		min_row = rows;
	}
	Matrix sumM(max_col, max_row);
	for (int i = 0;i < min_row;i++)
		for (int j = 0;j < min_col;j++)
			sumM.elements[i][j] = elements[i][j] - M.elements[i][j];
	if (max_col == columns)
	{
		for (int i = 0;i < rows;i++)
			for (int j = min_col;j < max_col;j++)
				sumM.elements[i][j] = elements[i][j];
	}
	else
	{
		for (int i = 0;i < M.rows;i++)
			for (int j = min_col;j < max_col;j++)
				sumM.elements[i][j] = -M.elements[i][j];
	}
	if (max_row == rows)
	{
		for (int i = min_row;i < max_row;i++)
			for (int j = 0;j < columns;j++)
				sumM.elements[i][j] = elements[i][j];
	}
	else
	{
		for (int i = min_row;i < max_row;i++)
			for (int j = 0;j < M.columns;j++)
				sumM.elements[i][j] = -M.elements[i][j];
	}
	return sumM;
}

Matrix Matrix::operator-=(const Matrix& M)
{
	*this = *this - M;
	return *this;
}

Matrix Matrix::operator*(const Matrix& M) const
{
	if (columns != M.rows)
		throw MyException("Nie mozna pomnozyc tych macierzy - ilosc kolumn pierwszej rozna od ilosci rzedow drugiej");
	Matrix prodM(M.columns, rows);
	double sum = 0;
	for (int i = 0;i < prodM.rows;i++)
		for (int j = 0;j < prodM.columns;j++)
		{
			sum = 0;
			for (int k = 0;k < columns;k++)
				sum += elements[i][k]*M.elements[k][j];
			prodM.elements[i][j] = sum;
		}
	return prodM;
}

Matrix Matrix::operator*=(const Matrix& M)
{
	*this = *this*M;
	return *this;
}

Matrix Matrix::operator*(const double& d) const
{
	Matrix prodM(columns, rows);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			prodM.elements[i][j] = d*elements[i][j];
	return prodM;
}

Matrix Matrix::operator*=(const double& d)
{
	*this = *this*d;
	return *this;
}

Matrix Matrix::operator/(const double& d) const
{
	if (d == 0.0)
		throw MyException("Blad - nie mozna dzielic przez 0");
	Matrix prodM(columns, rows);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			prodM.elements[i][j] = elements[i][j] / d;
	return prodM;
}

Matrix Matrix::operator/=(const double& d)
{
	*this = *this / d;
	return *this;
}

void Matrix::insertColumnVector(const double* X, int& c)
{
	for (int i = 0;i < rows;i++)
		elements[i][c] = X[i];
}

double* Matrix::solveEq(double* R) const
{
	int p = 0;
	Matrix LU;
	try
	{
		LU = LUPDecomp(p);
	}
	catch (MyException e)
	{
		delete R;
		throw;
	}
	catch (double& d)
	{
		cout << "Wyznacznik macierzy wynosi " << d << ", zatem istnieje oo wiele rozw. lub nie istnieje zadne rozwiazanie" << endl;
	}
	double* X = new double[columns];
	double sum = 0;
	X[0] = R[0];
	for (int i = 1;i < columns;i++)
	{
		sum = 0;
		for (int j = 0;j < i;j++)
			sum += LU.elements[i][j] * X[j];
		X[i] = R[i] - sum;
	}
	if (LU.elements[rows - 1][columns - 1] == 0)
	{
		delete R;
		delete X;
		throw MyException("Blad - wystapi dzielenie przez 0");
	}
	X[columns - 1] /= LU.elements[rows - 1][columns - 1];
	for (int i = columns - 2;i >= 0;i--)
	{
		if (LU.elements[i][i] == 0)
		{
			delete R;
			delete X;
			throw MyException("Blad - wystapi dzielenie przez 0");
		}
		sum = 0;
		for (int j = i + 1;j < columns;j++)
			sum += LU.elements[i][j] * X[j];
		X[i] = (X[i] - sum) / LU.elements[i][i];
	}
	return X;
}

double* Matrix::getOneColumn(int& c) const
{
	double* X = new double[rows];
	for (int i = 0;i < rows;i++)
		X[i] = elements[i][c];
	return X;
}

void Matrix::swapRows(int& r1, int& r2)
{
	double temp = 0;
	for (int i = 0;i < columns;i++)
	{
		temp = elements[r1][i];
		elements[r1][i] = elements[r2][i];
		elements[r2][i] = temp;
	}
}

Matrix Matrix::LUDecomp() const
{
	if (columns != rows)
		throw MyException("Blad - nie podano macierzy kwadratowej");
	Matrix LU = *this;
	for (int i = 0;i < columns - 1;i++)
	{
		if (LU.elements[i][i] == 0)
			throw MyException("Blad - wystapi dzielenie przez 0");
		for (int j = i + 1;j < columns;j++)
			LU.elements[j][i] /= LU.elements[i][i];
		for (int j = i + 1;j < columns;j++)
			for (int k = i + 1;k < columns;k++)
				LU.elements[j][k] -= LU.elements[j][i] * LU.elements[i][k];
	}
	return LU;
}

Matrix Matrix::LUPDecomp(int& p) const
{
	if (columns != rows)
		throw MyException("Blad - nie podano macierzy kwadratowej");
	Matrix LU = *this;
	p = 0;
	for (int i = 0; i < columns - 1; i++)
	{
		double maxrowvalue = elements[i][i];
		int maxrow = i;
		for (int j = 1; j < rows; j++)
		{
			if (abs(LU.elements[i][j]) > abs(maxrowvalue))
			{
				maxrowvalue = LU.elements[i][j];
				maxrow = j;
			}
		}
		if (maxrow != i)
		{
			LU.swapRows(i, maxrow);
			p++;
		}
		if (LU.elements[i][i] == 0)
			throw 0.0;
		for (int j = i + 1; j < columns; j++)
			LU.elements[j][i] /= LU.elements[i][i];
		for (int j = i + 1; j < columns; j++)
			for (int k = i + 1; k < columns; k++)
				LU.elements[j][k] -= LU.elements[j][i] * LU.elements[i][k];
	}
	return LU;
}

double Matrix::LUdeterminant() const
{
	int permutations = 0;
	Matrix LU;
	try
	{
		LU = LUPDecomp(permutations);
	}
	catch (double& d)
	{
		return d;
	}
	double determinant = LU.elements[0][0];
	for (int i = 1;i < columns;i++)
		determinant *= LU.elements[i][i];
	determinant *= pow(-1, permutations);
	return determinant;
}

double Matrix::determinant() const
{
	if (columns != rows)
		throw MyException ("Blad - nie podano macierzy kwadratowej");
	double determinant = 0.0;
	if (columns == 1)
		return determinant = elements[0][0];
	else
	{
		for (int i = 0;i < columns;i++)
		{
			int r = 0;
			Matrix cutM = cutMatrix(i, r);
			determinant += elements[r][i] * pow(-1, i) * cutM.determinant();
		}
		return determinant;
	}
}

Matrix Matrix::inverse() const
{
	if (columns != rows)
		throw MyException("Blad - nie podano macierzy kwadratowej");
	double det = determinant();
	if (det == 0)
		throw MyException("Nie mozna odwrocic macierzy");
	Matrix inversedM(columns, rows);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			inversedM.elements[i][j] = pow(-1, i + j)*cutMatrix(j, i).determinant();
	inversedM.selftranspone();
	inversedM /= det;
	return inversedM;
}

Matrix Matrix::LUinverse() const
{
	if (columns!=rows)
		throw MyException("Blad - nie podano macierzy kwadratowej");
	double det = LUdeterminant();
	if (det == 0)
		throw MyException("Nie mozna odwrocic macierzy");
	Matrix inversedM(columns, rows);
	inversedM.makeI();
	for (int i = 0;i < columns;i++)
	{
		double* X = inversedM.getOneColumn(i);
		double* Y = solveEq(X);
		inversedM.insertColumnVector(Y, i);
		delete[] X;
		delete[] Y;
	}
	return inversedM;
}

Matrix Matrix::cutMatrix(int& column, int& row) const
{
	//if (columns <= 1 || rows <= 1)
		//throw MyException("Nie mozna bardziej zmniejszyc macierzy");
	Matrix cutM(columns-1, rows-1);
	int ir = 0;
	for (int i = 0;i < rows;i++)
	{
		if (i == row)
			continue;
		int ic = 0;
		for (int j = 0;j < columns;j++)
		{
			if (j == column)
				continue;
			cutM.elements[ir][ic] = elements[i][j];
			ic++;
		}
		ir++;
	}
	return cutM;
}

Matrix Matrix::selfcutMatrix(int& column, int& row)
{
	Matrix cutM=cutMatrix(column, row);
	/*Matrix cutM(columns-1, rows-1);
	int ir = 0;
	for (int i = 0;i < rows;i++)
	{
		if (i == row)
			continue;
		int ic = 0;
		for (int j = 0;j < columns;j++)
		{
			if (j == column)
				continue;
			cutM.elements[ir][ic] = elements[i][j];
			ic++;
		}
		ir++;
	} */
	copyMatrix(cutM);
	return *this;
	
}

Matrix Matrix::transpone() const
{
	Matrix transponedM(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			transponedM.elements[j][i] = elements[i][j];
	return transponedM;
}

Matrix Matrix::selftranspone()
{
	Matrix transponedM = transpone();
	/*Matrix transponedM(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			transponedM.elements[j][i] = elements[i][j];*/
	copyMatrix(transponedM);
	return *this;

}

Matrix Matrix::makeI()
{
	if (columns != rows)
		throw MyException("Blad - nie podano macierzy kwadratowej");
	for (int i = 0;i < rows;i++)
	{
		for (int j = 0;j < columns;j++)
			elements[i][j] = 0;
		elements[i][i] = 1;
	}
	return *this;
}

void Matrix::copyMatrix(const Matrix& M)
{
	for (int i = 0;i < rows;i++)
		delete elements[i];
	delete elements;
	columns = M.columns;
	rows = M.rows;
	elements = new double*[rows];
	for (int i = 0;i < rows;i++)
		elements[i] = new double[columns];
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			elements[i][j] = M.elements[i][j];
}

Matrix Matrix::randomize()
{
	srand((unsigned int)time(NULL));
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			elements[i][j] = rand() % 101;
	return *this;
}

int Matrix::getColumns() const
{
	return columns;
}

int Matrix::getRows() const
{
	return rows;
}

ostream& operator<<(ostream& out, const Matrix& M)
{
	out << fixed << setprecision(3);
	for (int i = 0;i < M.rows;i++)
	{
		for (int j = 0;j < M.columns - 1;j++)
			out << setw(7) << left << M.elements[i][j] << " ";
		out << setw(7) << left << M.elements[i][M.columns-1] << endl;
	}
	return out;
}

istream& operator>>(istream& in, Matrix& M)
{
	for (int i = 0;i < M.rows;i++)
		for (int j = 0;j < M.columns;j++)
		{
			cout << "Wiersz " << i + 1 << " kolumna " << j + 1 << ": ";
			in >> M.elements[i][j];
		}
	return in;
}