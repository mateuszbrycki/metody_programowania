#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include "lista.h"

using namespace std;

//klasa reprezentujaca konkretny wierzcholek
class vertex
{
public:
	int number;
	lista neight; //lista reprezentujaca sasiadow

	vertex();
	vertex(int number);
	void getNeight(bool &weighted);
};

#endif