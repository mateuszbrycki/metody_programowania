#ifndef LISTA_H
#define LISTA_H
#include <iostream>

using namespace std;

//klasa reprezentujaca liste jednokierunkowa
class lista
{
public: 
	struct element {
		int vertex; //wierzcholek
		int weight; //waga
		element *next; //nastepny element listy
	};

	lista(); //konstruktor domyslny
	lista(int m); //konstruktor
	void add(int m); //dodanie elementu do listy
	void add(int m, int w); //dodanie elementu do listy
	void getAll(bool * weighted); //wypisanie listy
	int getNumberOfElements(); //wypisanie ilosci elementow listy

private:
	element *tail = NULL; //koniec listy
	element *head = NULL; //poczatek listy
	element *new_element = NULL; //dodawany element
};

#endif