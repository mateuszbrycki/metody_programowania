/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i
Program generuje permutacjie ci�gu liczb w porz�dku antyleksykograficznym.
*/
#include <iostream>
#include <fstream>

using namespace std;

int p[5], n = 5; //tablica przechowywuj�ca permutacj�, ilo�� permutacji
fstream plik; //plik do kt�rego zostan� zapisane wyniki dzia�ania programu

//funkcja odpowiedzialna za odwr�cenie tablicy
//@param m ilo�� odwracanych element�w
void odwroc(int m)
{
	int i = 1, j = m;

	while (i < j)
	{
		swap(p[i], p[j]); //funkcja zamieniaj�ca p[i] z p[j]

		i++; 
		j--;
	}
}

//funkcja wypisuj�ca zawarto�� tablicy p do pliku
void wypisz()
{
	for (int x = 1; x <= n; x++)
	{
		plik << p[x];
	}
	plik << endl;
}

//funkcja odpowiedzialna za generowanie permutacji
//@param m ilo�� element�w, z kt�rych nale�y stworzy� permutacj�
void antylex(int m)
{
	
	if (m == 1)
	{
		wypisz();
	}
	else {
		for (int i = 1; i <= m; i++)
		{
			antylex(m - 1);

			if (i < m)
			{
				swap(p[i], p[m]); //zamiana miejscami p[i] i p[m]
				odwroc(m - 1);
			}
		}
	}
}

int main()
{
	plik.open("out_2.txt", ios_base::out); //otworzenie pliku do zapisy wyniku dzia�ania programu

	for (int x = 1; x <= n; x++) //p�tla wype�niaj�ca tablic� p
	{
		p[x] = x;
	}

	antylex(n); //wywo�anie funkcji antylex

	plik.close(); //zamkni�cie pliku

	cin.get();
	cin.get();
}