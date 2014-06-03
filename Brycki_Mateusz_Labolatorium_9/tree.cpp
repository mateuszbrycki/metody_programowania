#include "tree.h"
#include <iostream>

/*funkcja realizuj�ca generowanie drzewa Huffmana

*/
void Tree::setHuffmanTree()
{
	while (treeNodes.size() != 1) //do czasu gdy 
	{
		this->sortListOfNodes(); //najpierw sortujemy list�
		this->addNode();		//a nast�pnie dodajemy nowy wierzcho�ek => ��czymy dwa z najmniejszymi wagami
	}
}

/*funkcja dodaj�ca nowy wierzcho�ek, kt�ry jest po��czeniem dw�ch z najmniejszymi wagami

*/
void Tree::addNode()
{
	Node * newNode = new(nothrow) Node((treeNodes[0]->number + treeNodes[1]->number)); //tworzenie nowego wierzcho�ka

	if (newNode)
	{
		//ustawienie wierzcho�k�w potomnych
		newNode->left = this->treeNodes[0];
		newNode->right = this->treeNodes[1];

		//ustawienie wierzcho�ka nadrz�dnego w wierzcho�kach potomnych
		this->treeNodes[0]->parent = newNode;
		this->treeNodes[1]->parent = newNode;

		this->treeNodes.erase(treeNodes.cbegin(), treeNodes.cbegin() + 2); //usuni�cie dw�ch pierwszych wierzcho�k�w z listy

		this->treeNodes.push_back(newNode); //dodanie nowego wierzcho�ka do kolejki
	}	
}

/* funkcja sortuj�ca list� wierzcho�k�w

*/
void Tree::sortListOfNodes()
{
	int x = 0;

	while (x != this->treeNodes.size() - 1 && this->treeNodes.size() > 1)
	{
		if (this->treeNodes[x]->number > this->treeNodes[x + 1]->number)
		{
			//zamieniamy elementy 		
			swap(this->treeNodes[x], this->treeNodes[x + 1]);
			x = 0;
		}
		else { 
			x++; 
		}
	}
}

/*funkcja uruchamiaj�ca generowanie drzewa oraz wypisanie kod�w dla poszczeg�lnych li�ci

*/
void Tree::getHuffmanTree()
{
	this->setHuffmanTree(); //generacja drzewa
	this->getHuffmansCode(); //wygenerowanie i wypisanie kod�w Huffmana dla ka�dego li�cia
}

/*funkcja wyznaczaj�ca kod Huffmana dla ka�dego li�cia z listy treeLeafs

*/
void Tree::getHuffmansCode()
{	
	Node * currentNode; //pomocnicze zmienne dzi�ki kt�rym wyznaczamy kod Huffmana dla kazdego li�cia
	Node * root;
	Node * tmp;

	while (this->treeLeafs.size() != 0) //wyznaczamy kody, a� lista li�ci do odwiedzenia nie b�dzie pusta
	{
		currentNode = this->treeLeafs.front(); //obecny wierzcho�ek ustawiamy na pierwszy z listy
		root = currentNode->parent; //root na rodzica w/w wierzcho�ka
		tmp = currentNode;

		while (root != NULL) //do czasu, a� rodzic wierzcho�ka nie b�dzie NULL => wierzcho�ek jest korzeniem drzewa => jeste�my na samej g�rze
		{
			//w zale�no�ci od tego, w kt�r� stron� jest poprowadzony nasz wierzcho�ek uzupe�niamy jego kod
			if (root->left == tmp)
			{
				currentNode->code += "0";
			}

			if (root->right == tmp)
			{
				currentNode->code += "1";
			}

			//przesuwamy si� o jeden poziom wy�ej w drzewie
			tmp = root;
			root = root->parent;
		}

		this->treeLeafs.pop_front(); //usuni�cie odwiedzonego wierzcho�ka z listy

		cout << currentNode->character<<" : "<<currentNode->code<<endl; //wypisujemy znak oraz wygenerowany kod
	}
}
