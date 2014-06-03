#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

//klasa bêd¹ca reprezentacj¹ wierzcho³ka zawieraj¹cego: numer, literê, kod Huffmana, adresy do rodzica, lewego potomka i prawego
class Node
{
public:
	double number; //waga, prawdopodobieñstwo
	string character; //litera jak¹ przechowuje wierzcho³ek
	string code; //kod Huffmana dla wierzcho³ka 

	Node * parent; //adres wierzcho³ka rodzinca
	Node * left; //adres lewego potomka
	Node * right; //adres prawego potomka

	Node(double number, string character); //konstruktor u¿ywany do tworzenia nowego wierzcho³ka przy wczytywaniu z pliku
	Node(double number); //konstruktor u¿ywant do tworzenia wierzcho³ka, który powsta³ w wyniku ³¹czenia
};

#endif