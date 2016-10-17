#include "Help.h"
#include "Matrix.h"
#include "MyException.h"

//auto start = std::chrono::steady_clock::now();
//auto end = std::chrono::steady_clock::now();
//cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;

using namespace std;

void help()
{
	cout << "Format wpisywania komendy:" << endl;
	cout << "c1 c2 c3" << endl << endl;
	cout << "Komendy ogolne" << endl;
	cout << "show - wyswietla macierze M1 i M2"<<endl;
	cout << "help - wyswietla wszystkie potrzebne komendy" << endl;
	cout << "exit - konczy dzialanie programu" << endl << endl;
	cout << "Komendy c1:" << endl;
	cout << "M1 - operacja na macierzy nr 1" << endl;
	cout << "M2 - operacja na macierzy nr 2" << endl << endl;
	cout << "Komendy c2:" << endl;
	cout << "fill, wypelnij - pozwala wpisac dane do wskazanej macierzy" << endl;
	cout << "+,add,dodaj - dodaje wskazana macierz do drugiej" << endl;
	cout << "-,subtract,odejmij - odejmuje od wskazanej macierzy druga" << endl;
	cout << "*,multiplicate,pomnoz - mnozy wskazana macierz przez druga" << endl;
	cout << "s*,smultiplicate,spomnoz - mnozy wskazana macierz przez skalar" << endl;
	cout << "s,sdivide,spodziel - dzieli wskazana macierz przez skalar" << endl;
	cout << "inverse, odwroc - odwraca wskazana macierz (rekurencyjnie)" << endl;
	cout << "LUinverse, LUodwroc - odwraca wskazana macierz (metoda LU)" << endl;
	cout << "transpose,transponuj - transponuje wskazana macierz" << endl;
	cout << "solve,rozwiaz - rozwiazuje uklad rownan wskazanej macierzy (tylko dla jednego rozw.)" << endl;
	cout << "determinant,wyznacznik - oblicza wyznacznik wskazanej macierzy (rekurencyjnie)" << endl;
	cout << "LUdeterminant, LUwyznacznik - oblicza wyznacznik wskazanej macierzy (metoda LU)" << endl << endl;
	cout << "Komendy c3:" << endl;
	cout << "z - wynik operacji MACIERZOWEJ nadpisuje na wskazana macierz" << endl << endl;
	cout << "t - wypisuje czas operacji w milisekundach" << endl;
	system("PAUSE");
	system("cls");
}

void author()
{
	cout << "**************************************************" << endl;
	cout << "*                  Lukasz Lepak                  *" << endl;
	cout << "*              Kalkulator macierzowy             *" << endl;
	cout << "*                      v1.0                      *" << endl;
	cout << "**************************************************" << endl << endl << endl;
}

string toLower(string& s)
{
	string low;
	for (unsigned int i = 0;i < s.length();i++)
		low+=tolower(s[i]);
	return low;
}

void execute()
{
	Matrix* M1;
	Matrix* M2;
	M1 = new Matrix;
	M2 = new Matrix;
	bool primary = true;
	auto start=chrono::steady_clock::now();
	auto end=chrono::steady_clock::now();
	while (true)
	{
		try
		{
			author();
			string cmd, c1, c2, c3;
			int i = 0; //loop execution
			cout << "Wpisz komende (help wyswietli dostepne komendy)" << endl;
			getline(cin, cmd, '\n');
			cmd = toLower(cmd);
			for (i = 0;cmd[i] != ' ' && cmd[i] != '\0';i++)
				c1 += cmd[i];
			while (cmd[i] == ' ')
				i++;
			for (i;cmd[i] != ' ' && cmd[i] != '\0';i++)
				c2 += cmd[i];
			while (cmd[i] == ' ')
				i++;
			for (i;cmd[i] != '\0';i++)
				c3 += cmd[i];
			if (cmd == "help" || cmd == "pomoc")
			{
				help();
				continue;
			}
			else if (cmd == "exit" || cmd == "wyjdz")
				break;
			else if (cmd == "show" || cmd == "wyswietl")
			{
				cout << "M1:" << endl << *M1 << endl << "M2:" << endl << *M2 << endl;
				system("PAUSE");
				system("cls");
				continue;
			}
			if (c1 == "m1")
				primary = true;
			else if (c1 == "m2")
				primary = false;
			else
				throw MyException("Niepoprawna komenda c1");
			if (c2 == "fill" || c2 == "wypelnij")
			{
				int col, row;
				cout << "Podaj liczbe rzedow: ";
				cin >> row;
				cout << "Podaj liczbe kolumn: ";
				cin >> col;
				if (col < 1 || row < 1)
					throw MyException("Blad - macierz musi miec minimalny rozmiar 1x1");
				if (primary)
				{
					delete M1;
					M1 = new Matrix(col, row);
					cin >> *M1;
				}
				else
				{
					delete M2;
					M2 = new Matrix(col, row);
					cin >> *M2;
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "randomize" || c2 == "losuj")
			{
				int col, row;
				cout << "Podaj liczbe rzedow: ";
				cin >> row;
				cout << "Podaj liczbe kolumn: ";
				cin >> col;
				if (col < 1 || row < 1)
					throw MyException("Blad - macierz musi miec minimalny rozmiar 1x1");
				if (primary)
				{
					delete M1;
					M1 = new Matrix(col, row);
					M1->randomize();
				}
				else
				{
					delete M2;
					M2 = new Matrix(col, row);
					M2->randomize();
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "+" || c2 == "add" || c2 == "dodaj")
			{
				if (c3 == "t")
					start = chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 += *M2;
						cout << *M1 << endl;
					}
					else
					{
						*M2 += *M1;
						cout << *M2 << endl;
					}
				}
				else cout << *M1 + *M2 << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "-" || c2 == "subtract" || c2 == "odejmij")
			{
				if (c3 == "t")
					start = chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 -= *M2;
						cout << *M1 << endl;
					}
					else
					{
						*M2 -= *M1;
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << *M1 - *M2 << endl;
				else
					cout << *M2 - *M1 << endl;
				if (c3=="t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "*" || c2 == "multiplicate" || c2 == "pomnoz")
			{
				if (c3 == "t")
					start = chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 *= *M2;
						cout << *M1 << endl;
					}
					else
					{
						*M2 *= *M1;
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << *M1 * *M2 << endl;
				else
					cout << *M2 * *M1 << endl;
				if (c3=="t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "s*" || c2 == "smultiplicate" || c2 == "spomnoz")
			{
				double s = 0.0;
				cout << "Podaj skalar:" << endl;
				cin >> s;
				if (c3 == "t")
					start = chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 *= s;
						cout << *M1 << endl;
					}
					else
					{
						*M2 *= s;
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << *M1 * s << endl;
				else
					cout << *M2 * s << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "s/" || c2 == "sdivide" || c2 == "spodziel")
			{
				double s = 0.0;
				cout << "Podaj skalar:" << endl;
				cin >> s;
				if (c3 == "t")
					start = chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 /= s;
						cout << *M1 << endl;
					}
					else
					{
						*M2 /= s;
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << *M1 / s << endl;
				else
					cout << *M2 / s << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "inverse" || c2 == "odwroc" || c2=="-1")
			{
				if (c3 == "t")
					start = chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 = M1->inverse();
						cout << *M1 << endl;
					}
					else
					{
						*M2 = M2->inverse();
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << M1->inverse() << endl;
				else
					cout << M2->inverse() << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "luinverse" || c2 == "luodwroc" || c2=="lu-1")
			{
				if (c3 == "t")
					start = std::chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						*M1 = M1->LUinverse();
						cout << *M1 << endl;
					}
					else
					{
						*M2 = M2->LUinverse();
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << M1->LUinverse() << endl;
				else
					cout << M2->LUinverse() << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "transpose" || c2 == "transponuj")
			{
				if (c3 == "t")
					start = std::chrono::steady_clock::now();
				if (c3 == "z")
				{
					if (primary)
					{
						M1->selftranspone();
						cout << *M1 << endl;
					}
					else
					{
						M2->selftranspone();
						cout << *M2 << endl;
					}
				}
				else if (primary)
					cout << M1->transpone() << endl;
				else
					cout << M2->transpone() << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "solve" || c2 == "rozwiaz")
			{
				Matrix*& Mr1 = primary ? M1 : M2;
				if (Mr1->getColumns() != Mr1->getRows())
					throw MyException("Blad - nie podano macierzy kwadratowej");
				const int e = Mr1->getColumns();
				double *y = new double[e];
				for (int i = 0;i < e;i++)
				{
					cout << "Podaj wynik rownania nr " << i + 1 << ": ";
					cin >> y[i];
				}
				if (c3 == "t")
					start = std::chrono::steady_clock::now();
				double* x = Mr1->solveEq(y);
				for (int i = 0;i < e;i++)
					cout << "x" << i << "=" << x[i] << endl;
				delete[] x;
				delete[] y;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "determinant" || c2 == "wyznacznik" || c2=="det")
			{
				if (c3 == "t")
					start = chrono::steady_clock::now();
				cout << (primary ? M1->determinant() : M2->determinant()) << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else if (c2 == "ludeterminant" || c2 == "luwyznacznik" || c2=="ludet")
			{
				if (c3 == "t")
					start = chrono::steady_clock::now();
				cout << (primary ? M1->LUdeterminant() : M2->LUdeterminant()) << endl;
				if (c3 == "t")
				{
					end = std::chrono::steady_clock::now();
					cout << "Czas wykonania w milisekundach: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
				}
				system("PAUSE");
				system("cls");
			}
			else
				throw MyException("Niepoprawna komenda c2");
		}
		catch (MyException& e)
		{
			cout << e.what() << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("PAUSE");
			system("cls");
		}
		catch (exception& e)
		{
			cout << e.what() << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("PAUSE");
			system("cls");
		}
		catch (...)
		{
			cout << "Niezdefiniowany blad - wylaczenie programu" << endl;
			delete M1;
			delete M2;
			exit(-1);
		}
	}
	cout << "Dziekuje za skorzystanie z programu c:" << endl;
	delete M1;
	delete M2;
}