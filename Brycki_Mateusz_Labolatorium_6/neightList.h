#ifndef NEIGHTLIST_H
#define NEIGHTLIST_H
#include <iostream>
using namespace std;

#include "vertex.h"
#include "lista.h"

//klasa bedaca reprezentacja listy sasiedztwa
class neightList
{

public:
	vertex *vertices; //glowna tablica z wierzcholkami grafu
	int n; //ilosc wierzcholkow w grafie

	neightList(int *max, bool addressed, bool weighted); //kreowanie listy
	void addNeight(int ** e, int *n); //dodanie sasiadow do listy sasiedztwa
	void getNeight(); //wypisanie listy sasiedztwa
	~neightList();

private:
	bool addressed; //graf skierowany (T) lub nie (F)
	bool weighted; //graf wa¿ony (T) lub nie (F)
};

#endif

