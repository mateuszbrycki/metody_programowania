#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

//klasa reprezentujaca macierz sasiedztwa
class matrix {

public:
	int ** table; //tablica dwuwymiarowa reprezentujaca macierz

	matrix(int *n, bool addressed, bool weighted); //konstruktor
	void setMatrix(int ** e, int *number); //funkcja generujaca macierz sasiedztwa
	void getMatrix(); //funkcja wypisujaca macierz sasiedzstwa na ekran
	~matrix(); //destruktor

private:
	int n; //zmienna przechowywujaca rozmiar macierzy 
	bool addressed; //graf skierowany (T) lub nie (F)
	bool weighted; //graf wa¿ony (T) lub nie (F)
	void setEmptyMatrix(); //funkcja odpowiedzialna za wypelnienie macierzy 0

};

#endif