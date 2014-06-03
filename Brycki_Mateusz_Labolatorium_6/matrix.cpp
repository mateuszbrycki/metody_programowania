#include <iostream>

using namespace std;

#include "matrix.h"

/*konstruktor 
@param n rozmiar macierzy - ilosc wierzcholkow w grafie
@param addressed informacja o tym czy graf jest skierowany
@param weighted informacja o tym czy krawedzie posiadaja wagi
*/
matrix::matrix(int *n, bool addressed, bool weighted)
{
	//ustawienie zmiennych prywatnych klasy
	this->n = *n;
	this->addressed = addressed;
	this->weighted = weighted;

	//towrzenie tablicy bedacej reprezentacja macierzy
	table = reinterpret_cast<int**>(new int[this->n]); //tablica dynamiczna na reprezentacje macierzy

	for (int z = 0; z < this->n; z++)
	{
		table[z] = reinterpret_cast<int*>(new int[this->n]);
	}

	setEmptyMatrix(); //wypelnienie macierzy zerami

}

void matrix::setEmptyMatrix()
{
	for (int x = 0; x < n; x++)
		for (int z = 0; z < n; z++)
			table[x][z] = 0;
}

/*funkcja odpowiedzialna za wype³nienie macierzy
@param e reprezentacja tablicowa listy krawedzi
@param number ilosc krawedzi w grafie
*/
void matrix::setMatrix(int ** e, int *number)
{
	for (int x = 0; x < *number; x++)
	{
		if (weighted) //jezeli graf jest wazony wstawiamy wagi w miejscu "przeciecia wierzcholkow"
		{
			table[e[x][0] - 1][e[x][1] - 1] = e[x][2]; //ustawiamy wage wedlug krawedzi z tablicy e

		}
		else { //graf nie jest wazony
			table[e[x][0] - 1][e[x][1] - 1] = 1; //ustawiamy 1 wedlug krawedzi z tablicy 
		}
		
		if (!addressed) //jezeli graf nie jest skierowany to wpisujemy krawedzie w druga strone
		{
			if (weighted) //jak wyzej - graf z wagami
			{
				table[e[x][1] - 1][e[x][0] - 1] = e[x][2];
			}
			else {
				table[e[x][1] - 1][e[x][0] - 1] = 1;
			}
		}
	}
}

//funkcja odpowiedzialna za wypisanie tablicy macierzy
void matrix::getMatrix()
{
	for (int x = 0; x < n; x++)
	{
		for (int z = 0; z < n; z++)
			cout << table[x][z] << "\t";

		cout << endl;
	}	
}

//destruktor
matrix::~matrix()
{
	for (int x = 0; x < n; x++)
		delete[] table[x];

	delete[] table;
}