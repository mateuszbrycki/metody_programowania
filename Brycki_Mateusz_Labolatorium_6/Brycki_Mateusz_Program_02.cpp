/*
Autor: Mateusz Brycki, informatyka, 1 rok, 11i

Program wykorzystujacy klasy matrix oraz neightList zwraca macierz oraz liste sasiedztwa dla grafu skierowanego z wagami.
Liste krawedzi nalezy podac w pliku tekstowym.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "matrix.h" //plik naglowkowy z klasa matrix
#include "neightList.h" //plik naglowkowy z klasa neightList

using namespace std;

/*funkcja zwracajaca ilosc wierzcholkow w zadanym grafie
@param tablica dwuwymiarowa z krawedziami
@param n ilosc wierszy w tej tablicy
*/
int getMax(int **e, int * n)
{
	int max = e[0][0];

	for (int x = 0; x < *n; x++)
	{
		//sprawdzamy kolejne elementy z n-tego wiersza tablicy
		if (e[x][0] > max)
			max = e[x][0];

		if (e[x][1] > max)
			max = e[x][1];
	}

	return max;
}

int main()
{
	fstream file; //uchwyt do pliku
	string name; //nazwa pliku z danymi

	cin >> name; //pobranie nazwy pliku

	file.open(name); //otworzenie pliku

	int n; //ilosc krawedzi w grafie

	file >> n; //pobranie ilosci krawedzi w grafie

	int **e = reinterpret_cast<int**>(new int[n]); //tablica dynamiczna na krawedzie o n wierszach i 2 kolumnach
	for (int z = 0; z < n; z++)
	{
		e[z] = reinterpret_cast<int*>(new int[3]);
	}

	//pobranie kolejnych krawedzi i zapisanie do tablicy
	for (int x = 0; x < n; x++)
	{
		file >> e[x][0]; //poczatek krawedzi
		file >> e[x][1]; //koniec krawedzi
		file >> e[x][2]; //waga
	}

	int max = getMax(e, &n); //ilosc wierzcholkow w grafie

	matrix matrix(&max, true, true); //utworzenie obiektu macierzy o wymiarach max x max, graf skierowany wazony
	matrix.setMatrix(e, &n); //wygenerowanie macierzy wg. tablicy krawedzi e, o n wierszach
	matrix.getMatrix(); //wypisanie macierzy na ekran

	cout << endl << endl;

	neightList vertices(&max, true, true); //graf skierowany wazony
	vertices.addNeight(e, &n); //dodawanie sasiadow na podstawie tablicy krawedzi
	vertices.getNeight(); //wypisanie listy sasiedztwa w grafie


	//zamkniecie pliku i usuniecie tablic dynamicznych
	file.close();

	for (int x = 0; x < n; x++)
	{
		delete e[x];
	}

	delete[] e;

	cin.get();
	cin.get();
}