/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i

Program generuj¹cy kod Huffmana dla ka¿dego z podanych znaków

Dane wczytywane s¹ w funkcji main z podanego pliku.
Format danych
pierwsza linia: n
kolejne n linii: chracter number
gdzie n - iloœæ linii, character - listera, number - numer 
*/

#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include "tree.h"

using namespace std;

int main()
{
	deque<Node *> nodes; //dane pobrane z pliku zapakowane w listê
	fstream file;
	string filename;
	int n; //iloœæ liter w tabeli	

	cout << "Podaj nazwe pliku z danymi: ";
	cin >> filename;

	file.open(filename); //otwarcie pliku

	if (file.is_open()) //je¿eli otwarcie powiod³o sie
	{
		file >> n; //pobranie iloœci liter w tabeli

		for (int x = 0; x < n; x++) //pobieranie kolejnych wartoœci
		{
			string character;
			double number;
			
			file >> character;
			file >> number;

			nodes.push_back(new(nothrow) Node(number, character)); //dodanie nowego wierzcho³ka na koniec listy
		}

		Tree * huffmanTree = new Tree(nodes, n); //utworzenie nowego drzewa na podstawie posortowanej listy wierzcho³ków
		huffmanTree->getHuffmanTree(); //wypisanie wygenerowanego drzewa

	}
	else {
		cout << "Problem z otworzeniem pliku.";
	}
	
	cin.get();
	cin.get();
}