#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <deque>

using namespace std;

//klasa b�d�ca reprezentacj� drzewa
class Tree
{
public:
	deque<Node *> treeNodes; //lista z "korzeniami"
	deque<Node *> treeLeafs; //lista li�ci drzewa
	int n; //poczatkowa ilosc wierzcholkow

	Tree(deque<Node *> list, int n) : treeNodes(list), treeLeafs(list), n(n) {} //konstruktor, na pocz�tku lista przekazana do konstruktora jest list� li�ci drzewa
	void getHuffmanTree(); //uruchamia funkcje niezb�dne do wygenerowania ci�g�w bitowych dla poszczeg�lnych element�w
	
private:
	void sortListOfNodes(); //sortowanie listy wierzcho�k�w
	void getHuffmansCode(); //wypisuje kody poszczeg�lnych element�w drzewa
	void addNode(); //dodanie wierzcho�ka do drzewa
	void setHuffmanTree(); //generuje drzewo do kodowania Huffmana
};

#endif

