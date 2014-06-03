#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <deque>

using namespace std;

//klasa bêd¹ca reprezentacj¹ drzewa
class Tree
{
public:
	deque<Node *> treeNodes; //lista z "korzeniami"
	deque<Node *> treeLeafs; //lista liœci drzewa
	int n; //poczatkowa ilosc wierzcholkow

	Tree(deque<Node *> list, int n) : treeNodes(list), treeLeafs(list), n(n) {} //konstruktor, na pocz¹tku lista przekazana do konstruktora jest list¹ liœci drzewa
	void getHuffmanTree(); //uruchamia funkcje niezbêdne do wygenerowania ci¹gów bitowych dla poszczególnych elementów
	
private:
	void sortListOfNodes(); //sortowanie listy wierzcho³ków
	void getHuffmansCode(); //wypisuje kody poszczególnych elementów drzewa
	void addNode(); //dodanie wierzcho³ka do drzewa
	void setHuffmanTree(); //generuje drzewo do kodowania Huffmana
};

#endif

