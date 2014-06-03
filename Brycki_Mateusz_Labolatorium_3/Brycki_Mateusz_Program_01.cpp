/**
Autor: Mateusz Brycki, Informatyka I rok, 11i

Program generuje 7 losowych permutacji zbioru liczb {1,2,3,4,5,6,7,8,9} poprzez zamian� miejscami element�w tablicy.
Zamieniany elementy od ko�ca tablicy z elementem o numerze l (l - liczba losowana za pomoc� funkcji rand() ze zbioru od 0 do 8.
*/

#include <iostream>
#include <time.h> 
#include <fstream>

using namespace std;

//zmienne globalne
//tablica p, n - liczba element�w tablicy p
int p[] = {1,2,3,4,5,6,7,8,9}, n = 9;
fstream plik;

//funkcja wypisuj�ca zawarto�� tablicy p
void wypisz()
{
	for (int x = 0; x < n; x++)
	{
		plik << p[x];
	}
}

//g��wna funkcja zamieniaj�ca elementy zestawu
void randomize()
{
	//p�tla wykonuj�ca n-2 przej��
	for (int x = n-1; x > 1; x--)
	{
		int l = rand() % (x+1); //rand()%(x+1) => rand()%(n-1+1) => rand()%n => losowanie od 0 do n-1, 
								//liczba ta b�dzie wskazywa� element do zamiany

		swap(p[l], p[x]); //zamiana element�w tablicy miejscami
	
	}

	wypisz(); //po zamianie element�w na miejscach l i x wypisujemy zestaw
}

int main()
{
	
	plik.open("out_1.txt", ios_base::out); //otworzenie pliku na wyniki

	srand(time(NULL)); //gwarancja losowania r�nych sekwencji licz

	randomize(); //wywo�anie funkcji generuj�cej zamiany

	plik.close(); //zamkni�cie pliku

	cin.get();
	cin.get();
}