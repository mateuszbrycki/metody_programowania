/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i

Program obliczaj�cy ca�k� oznaczon� z funkcji wielomianowej jednej zmiennej w zadanym przedziale.
*/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/* funkcja losuj�ca n punkt�w (x, y) z przedzia�u <b, c> o warto�ciach z przedzia�u <0, max>
@param points tablica, w kt�rej punkty zostan� zapisane
@param n ilo�� losowanych punkt�w
@param b pocz�tek przedzia�u argument�w (x)
@param c koniec przedzia�u argument�w (x)
@param max koniec przedzia�u warto�ci (y)
*/
void getPoints(float ** points, const int& n, const int& b, const int& c, const float& max)
{
	srand(time(NULL)); //ziarno

	for (int x = 0; x < n; x++)
	{
		points[x][0] = (float)b + (float)(rand() / (float)(RAND_MAX))*(float)(c-b); //losujemy x z przedzia�u <b, c>
		points[x][1] = (float)(rand() / (float)(RAND_MAX))*max; //losujemy y z przedzia�u <0, max>
	}
}

/* funkcja zwracaj�ca warto�� wielomianu w punkcie x
@param x argument, dla kt�rego b�dzie obliczana warto�� wielomianu
@param coff lista wsp�czynnik�w wielomianu
*/
float polynomialValue(const float& x, const vector<int>& coff)
{
	int n = coff.size()-1; //wielomian jest stopnia n, ale w coff jest wyraz wolny
	float value = 0;

	//obliczanie warto�ci przy kolejnych wsp�czynnikach wielomianu
	for (float z = 0; z < n; ++z)
	{
		value += coff[z] * (float)(pow(x, n - z));
	}
	
	value += (float)(coff[n]); //warto�� wyrazu wolnego

	return value;
}

/* funkcja zwracaj�ca krok obliczania warto�ci wielomianu
@param start pocz�tek przedzia�u
@param end koniec przedzia�u
*/
double getStep(const double& start, const double& end)
{
	return fabs((end - start) / 10000);
}

/* funkcja zwracaj�ca maksymaln� warto�� wielomianu w przedziale b, c
@param coff lista wsp�czynnik�w wielomianu
@param b pocz�tek rozpatrywanego przedzia�u
@param c koniec rozpatrywanego przedzia�u
*/
float getMax(vector<int>& coff, const double& b, const double& c)
{
	float max = -99999999;
	double step = getStep(b, c);

	for (double x = b; x < c; x += step)
	{
		float value = polynomialValue(x, coff);

		if (value > max)
			max = value;
	}

	return max;
}
/* spradzanie czy podany punkt znajduje si� pomi�dzy osi� OX a "wielomianem"
@param coff lista wsp�czynnik�w wielomianu
@param x argument wielomianu - warto�� wylosowanego punktu
@param y warto�� wylosowanego punktu w x
*/
bool isBelow(const vector<int>& coff, const float& x, const float& y)
{
	if (polynomialValue(x, coff) >= y && y >= 0)
	{
		return true;
	} 
	else {
		return false;
	}
}

int main()
{
	vector<int> in;
	int degree = 0, //stopien wielomianu
		n = 0; //ilo�� losowanych element�w

	double b, c;

	cout << "Podaj dokladnosc metody calkowania (0 - inf), im wiecej tym lepiej: ";
	cin >> n;


	//generowanie tablicy na punkty
	float **points = reinterpret_cast<float**>(new(nothrow) float[n]);

	if (points)
	{
		for (int z = 0; z < n; z++)
		{
			points[z] = reinterpret_cast<float*>(new(nothrow) float[2]);
		}

		cout << endl << "Podaj stopien wielomianu: ";
		cin >> degree;

		cout << endl << "Podaj kolejne wspolczynniki przy zmiennych wielomianu: ";
		for (int x = 0; x <= degree; x++) //wielomian jest stopnia degree, ale jeszcze wyraz wolny
		{
			int pow;
			cin >> pow;
			in.push_back(pow);
		}

		cout << endl << "Podaj koniec i pocz�tek przedzialu calkowania: ";
		cin >> b;
		cin >> c;
		cout << endl;

		float max = getMax(in, b, c); //obliczanie maksymalnej warto�ci wielomianu w przedziale b, c
		if (max == 0)
		{
			max = 1;
		}

		getPoints(points, n, b, c, max); //losowanie punkt�w

		//sprawdzanie ile punkt�w le�y pomi�dzy wykresem, a osi� OX
		int below = 0;
		for (int i = 0; i < n; i++)
		{
			if (isBelow(in, points[i][0], points[i][1]))
			{
				below++;
			}
		}

		float calka = (((float)c - (float)b) * (float)fabs(max) * (float)below) / (float)n; //obliczanie warto�ci ca�ki
		cout << "Wartosc calki: "<< calka << endl;

	}
	else {
		cout << "Blad danych!" << endl;
	}

	delete[] points;

	cin.get();
	cin.get();
}