/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i

Program wyznacza licz� PI metod� Monte Carlo.
*/

#include <iostream>
#include <ctime>

using namespace std;

/* funkcja generuj�ca tablic� losowych punkt�w 
@param points tablica na wygenerowane punkty
@param n ilo�� generowanych punkt�w
*/
void getPoints(float ** points, const int& n)
{
	srand(time(NULL)); //ziarno

	for (int x = 0; x < n; x++)
	{
		points[x][0] =  (float)(rand() / (float)(RAND_MAX)); //losujemy x 
		points[x][1] = (float)(rand() / (float)(RAND_MAX)); //losujemy y
	}
}

/* funkcja sprawdzaj�ca czy podany punkt znajduje si� w kole o promieniu r
@param x warto�� x punktu
@param y warto�� y punktu
*/
bool isIn(const float& x, const float& y)
{
	int r = 1;

	if (x*x + y*y <= r*r)
	{
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	int n = 0; //ilo�� losowanych punkt�w
		
	cout << "Podaj dokladnosc metod (0 - inf), im wiecej tym lepiej: ";
	cin >> n;

	float **points = reinterpret_cast<float**>(new(nothrow) float[n]);

	if (points)
	{
		for (int z = 0; z < n; z++)
		{
			points[z] = reinterpret_cast<float*>(new float[2]);
		}

		int in = 0;
		float PI = 0;

		getPoints(points, n); //losowanie punkt�w do tablicy points

		//zliczanie punkt�w znajduj�cych si� w okr�gu
		for (int x = 0; x < n; x++)
		{
			if (isIn(points[x][0], points[x][1]))
			{
				in++;
			}
		}

		PI = 4 * ((float)in / (float)n); //obliczanie liczby PI
		cout << PI << endl;
	}
	else {
		cout << "Blad danych!" << endl;
	}

	delete[] points;

	cin.get();
	cin.get();
}