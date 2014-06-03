/**
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i
Program generuje wariacje z powt�rzeniami zbioru liczb {1,2,3,4,5}.
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;
/*n - ilo�� element�w pierwotnego ci�gu, k - ilo�� element�w wariacji, 
w[] - tablica na kolejne 3-elementowe wariacje, skok[] tablica odpowiedzialna za przechowywanie warto�ci skoku
plik - uchwyt do pliku na odpowiedzi
*/
int n = 5, k = 3, w[3] = { 1, 1, 1 }, skok[3] = { 1, 1, 1 };
fstream plik;

//funkcja odpowiedzialna za wypisanie tablicy w do pliku
void wypisz()
{
	for (int x = 1; x <= k; x++)
	{
		plik << w[x];
	}

	plik << endl;
}

//funkcja zwracaj�ca miejsce liczby 
//@param m liczba, kt�rej miejsce b�dziemy zwraca�
int f_index(int m)
{
	int i = 0 ;

	while (m % n == 0)
	{
		i++;

		div_t divresult;
		divresult = div(m,n);

		m = divresult.quot;

	}
	return i;
}

//funkcja odpowiedzialna za generowanie wariacji
void wariacja()
{
	for (int z = 1; z <= k; z++)
		skok[z] = 1;

	int m = 0, i = 0;

	do{
		m++;
		
		wypisz();
			
		i = f_index(m) + 1;

		if (i <= k)
		{
			w[i] = w[i] + skok[i];

			if (w[i] == 1) 
				skok[i] = 1;

			if (w[i] == n) 
				skok[i] = -1;
		}
	} while (i <= k);
	
}



int main()
{
	plik.open("out_3.txt", ios_base::out); //otworzenie pliku na wyniki dzia�ania programu

	wariacja(); //wywo�anie funkcji generuj�cej wariacje ci�gu

	plik.close(); //zamkni�cie pliku

	cin.get();
	cin.get();
}