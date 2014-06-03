/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i

Program obliczaj¹cy ca³kê oznaczon¹ z funkcji wielomianowej jednej zmiennej w zadanym przedziale.
*/

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

/* funkcja losuj¹ca n punktów (x, y) z przedzia³u <b, c> o wartoœciach z przedzia³u <0, max>
@param points tablica, w której punkty zostan¹ zapisane
@param n iloœæ losowanych punktów
@param b pocz¹tek przedzia³u argumentów (x)
@param c koniec przedzia³u argumentów (x)
@param max koniec przedzia³u wartoœci (y)
*/
void getPoints(float ** points, const int& n, const int& b, const int& c, const float& max)
{
	srand(time(NULL)); //ziarno

	for (int x = 0; x < n; x++)
	{
		points[x][0] = (float)b + (float)(rand() / (float)(RAND_MAX))*(float)(c-b); //losujemy x z przedzia³u <b, c>
		points[x][1] = (float)(rand() / (float)(RAND_MAX))*max; //losujemy y z przedzia³u <0, max>
	}
}

/* funkcja zwracaj¹ca wartoœæ wielomianu w punkcie x
@param x argument, dla którego bêdzie obliczana wartoœæ wielomianu
@param coff lista wspó³czynników wielomianu
*/
float polynomialValue(const float& x, const vector<int>& coff)
{
	int n = coff.size()-1; //wielomian jest stopnia n, ale w coff jest wyraz wolny
	float value = 0;

	//obliczanie wartoœci przy kolejnych wspó³czynnikach wielomianu
	for (float z = 0; z < n; ++z)
	{
		value += coff[z] * (float)(pow(x, n - z));
	}
	
	value += (float)(coff[n]); //wartoœæ wyrazu wolnego

	return value;
}

/* funkcja zwracaj¹ca krok obliczania wartoœci wielomianu
@param start pocz¹tek przedzia³u
@param end koniec przedzia³u
*/
double getStep(const double& start, const double& end)
{
	return fabs((end - start) / 10000);
}

/* funkcja zwracaj¹ca maksymaln¹ wartoœæ wielomianu w przedziale b, c
@param coff lista wspó³czynników wielomianu
@param b pocz¹tek rozpatrywanego przedzia³u
@param c koniec rozpatrywanego przedzia³u
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
/* spradzanie czy podany punkt znajduje siê pomiêdzy osi¹ OX a "wielomianem"
@param coff lista wspó³czynników wielomianu
@param x argument wielomianu - wartoœæ wylosowanego punktu
@param y wartoœæ wylosowanego punktu w x
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
		n = 0; //iloœæ losowanych elementów

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

		cout << endl << "Podaj koniec i pocz¹tek przedzialu calkowania: ";
		cin >> b;
		cin >> c;
		cout << endl;

		float max = getMax(in, b, c); //obliczanie maksymalnej wartoœci wielomianu w przedziale b, c
		if (max == 0)
		{
			max = 1;
		}

		getPoints(points, n, b, c, max); //losowanie punktów

		//sprawdzanie ile punktów le¿y pomiêdzy wykresem, a osi¹ OX
		int below = 0;
		for (int i = 0; i < n; i++)
		{
			if (isBelow(in, points[i][0], points[i][1]))
			{
				below++;
			}
		}

		float calka = (((float)c - (float)b) * (float)fabs(max) * (float)below) / (float)n; //obliczanie wartoœci ca³ki
		cout << "Wartosc calki: "<< calka << endl;

	}
	else {
		cout << "Blad danych!" << endl;
	}

	delete[] points;

	cin.get();
	cin.get();
}