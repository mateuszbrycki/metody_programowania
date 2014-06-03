#include "vertex.h"

vertex::vertex(){}

vertex::vertex(int number) {
	this->number = number;
}

//funkcja zwracajaca liste sasiedztwa
//@param weighted graf z wagami lub nie
void vertex::getNeight(bool &weighted)
{
	neight.getAll(&weighted);
}