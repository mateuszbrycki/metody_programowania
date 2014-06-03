#include "node.h"
#include <iostream>

/*konstruktor, ustawiaj�cy numer oraz znak

*/
Node::Node(double number, string character) : number(number), character(character)
{
	//ustawienie wska�nik�w na NULL ju� na pocz�tku, domy�lnie ka�dy wierzcho�ek jest korzeniem
	code = ""; //ustawienie kodu 
	parent = NULL;
	left = NULL;
	right = NULL;
}

/* konstruktor ustawiajacy w nowym obiekcie numer oraz pusty znak*/
Node::Node(double number) : number(number), character("")
{
	//to samo co wcze�niej tylko, �e liter� ustawiamy na znak pusty
	code = "";
	parent = NULL;
	left = NULL;
	right = NULL;
}



