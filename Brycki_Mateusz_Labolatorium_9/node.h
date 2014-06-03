#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

//klasa b�d�ca reprezentacj� wierzcho�ka zawieraj�cego: numer, liter�, kod Huffmana, adresy do rodzica, lewego potomka i prawego
class Node
{
public:
	double number; //waga, prawdopodobie�stwo
	string character; //litera jak� przechowuje wierzcho�ek
	string code; //kod Huffmana dla wierzcho�ka 

	Node * parent; //adres wierzcho�ka rodzinca
	Node * left; //adres lewego potomka
	Node * right; //adres prawego potomka

	Node(double number, string character); //konstruktor u�ywany do tworzenia nowego wierzcho�ka przy wczytywaniu z pliku
	Node(double number); //konstruktor u�ywant do tworzenia wierzcho�ka, kt�ry powsta� w wyniku ��czenia
};

#endif