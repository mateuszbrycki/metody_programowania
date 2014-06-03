/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i
Program generuje permutacjie ci¹gu liczb w porz¹dku antyleksykograficznym.
*/
#include <iostream>
#include <fstream>

using namespace std;

int p[5], n = 5; //tablica przechowywuj¹ca permutacjê, iloœæ permutacji
fstream plik; //plik do którego zostan¹ zapisane wyniki dzia³ania programu

//funkcja odpowiedzialna za odwrócenie tablicy
//@param m iloœæ odwracanych elementów
void odwroc(int m)
{
	int i = 1, j = m;

	while (i < j)
	{
		swap(p[i], p[j]); //funkcja zamieniaj¹ca p[i] z p[j]

		i++; 
		j--;
	}
}

//funkcja wypisuj¹ca zawartoœæ tablicy p do pliku
void wypisz()
{
	for (int x = 1; x <= n; x++)
	{
		plik << p[x];
	}
	plik << endl;
}

//funkcja odpowiedzialna za generowanie permutacji
//@param m iloœæ elementów, z których nale¿y stworzyæ permutacjê
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
	plik.open("out_2.txt", ios_base::out); //otworzenie pliku do zapisy wyniku dzia³ania programu

	for (int x = 1; x <= n; x++) //pêtla wype³niaj¹ca tablicê p
	{
		p[x] = x;
	}

	antylex(n); //wywo³anie funkcji antylex

	plik.close(); //zamkniêcie pliku

	cin.get();
	cin.get();
}