/**
Autor: Mateusz Brycki, Informatyka I rok, 11i

Program generuje 7 losowych permutacji zbioru liczb {1,2,3,4,5,6,7,8,9} poprzez zamianê miejscami elementów tablicy.
Zamieniany elementy od koñca tablicy z elementem o numerze l (l - liczba losowana za pomoc¹ funkcji rand() ze zbioru od 0 do 8.
*/

#include <iostream>
#include <time.h> 
#include <fstream>

using namespace std;

//zmienne globalne
//tablica p, n - liczba elementów tablicy p
int p[] = {1,2,3,4,5,6,7,8,9}, n = 9;
fstream plik;

//funkcja wypisuj¹ca zawartoœæ tablicy p
void wypisz()
{
	for (int x = 0; x < n; x++)
	{
		plik << p[x];
	}
}

//g³ówna funkcja zamieniaj¹ca elementy zestawu
void randomize()
{
	//pêtla wykonuj¹ca n-2 przejœæ
	for (int x = n-1; x > 1; x--)
	{
		int l = rand() % (x+1); //rand()%(x+1) => rand()%(n-1+1) => rand()%n => losowanie od 0 do n-1, 
								//liczba ta bêdzie wskazywaæ element do zamiany

		swap(p[l], p[x]); //zamiana elementów tablicy miejscami
	
	}

	wypisz(); //po zamianie elementów na miejscach l i x wypisujemy zestaw
}

int main()
{
	
	plik.open("out_1.txt", ios_base::out); //otworzenie pliku na wyniki

	srand(time(NULL)); //gwarancja losowania ró¿nych sekwencji licz

	randomize(); //wywo³anie funkcji generuj¹cej zamiany

	plik.close(); //zamkniêcie pliku

	cin.get();
	cin.get();
}