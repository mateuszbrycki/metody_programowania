#include "neightList.h"
#include <iostream>

using namespace std;

/*kostruktor klasy neightList
@param max ilosc wierzcholkow w grafie
@param addressed true jezeli graf jest skierowany
@param weighted informacja o tym czy graf jest wazony
*/
neightList::neightList(int *max, bool addressed, bool weighted)
{
	//ustawienie zmiennych prywatnych
	this->n = *max;
	this->addressed = addressed;
	this->weighted = weighted;

	vertices = new vertex[n]; //tablica na obiekty vertex - wierzcho³ki

	//generowanie kolejnych obiektów w kolejnych elementach tablicy
	for (int x = 0; x < n; x++)
	{
		vertices[x] = vertex(x + 1);
	}
}

/*dodanie sasiadow wierzcholka na podstawie listy krawedzi
@param e lista krawedi [poczatek][koniec]
@param n ilosc krawedzi w grafie
*/
void neightList::addNeight(int ** e, int *n)
{
	for (int x = 0; x < *n; x++)
	{	
		if (weighted) //jezeli graf jest wazony to przy dodawaniu wierzcholkow bierzemy pod uwage wagi
		{
			vertices[e[x][0] - 1].neight.add(e[x][1], e[x][2]); //dodanie do listy wierzcholka sasiadujacego
			//vertices[e[x][0] - 1] - rozpatrywany wierzcholek
			//neight.add(e[x][1]) - obiekt wierzcholka, neight lista sasiadow (skladowa klasy Vertex), add dodanie sasiada do listy
		}
		else {
			vertices[e[x][0] - 1].neight.add(e[x][1]);
		}

		if (!addressed) //graf nie jest skierowany wiec dodajemy odwrotnie
		{
			if (weighted)
			{
				vertices[e[x][1] - 1].neight.add(e[x][0], e[x][2]);
			}
			else {
				vertices[e[x][1] - 1].neight.add(e[x][0]);
			}
		}
	}
}

//wypisanie listy sasiedztwa 
void neightList::getNeight()
{
	for (int x = 0; x < n; x++)
	{
		cout << x + 1 << ". ";
		vertices[x].getNeight(weighted);
	}
}

//destruktor
neightList::~neightList()
{
	delete[] vertices;
}