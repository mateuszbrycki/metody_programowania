#include "node.h"
#include <iostream>

/*konstruktor, ustawiaj¹cy numer oraz znak

*/
Node::Node(double number, string character) : number(number), character(character)
{
	//ustawienie wskaŸników na NULL ju¿ na pocz¹tku, domyœlnie ka¿dy wierzcho³ek jest korzeniem
	code = ""; //ustawienie kodu 
	parent = NULL;
	left = NULL;
	right = NULL;
}

/* konstruktor ustawiajacy w nowym obiekcie numer oraz pusty znak*/
Node::Node(double number) : number(number), character("")
{
	//to samo co wczeœniej tylko, ¿e literê ustawiamy na znak pusty
	code = "";
	parent = NULL;
	left = NULL;
	right = NULL;
}



