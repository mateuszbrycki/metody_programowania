#include "tree.h"
#include <iostream>

/*funkcja realizuj¹ca generowanie drzewa Huffmana

*/
void Tree::setHuffmanTree()
{
	while (treeNodes.size() != 1) //do czasu gdy 
	{
		this->sortListOfNodes(); //najpierw sortujemy listê
		this->addNode();		//a nastêpnie dodajemy nowy wierzcho³ek => ³¹czymy dwa z najmniejszymi wagami
	}
}

/*funkcja dodaj¹ca nowy wierzcho³ek, który jest po³¹czeniem dwóch z najmniejszymi wagami

*/
void Tree::addNode()
{
	Node * newNode = new(nothrow) Node((treeNodes[0]->number + treeNodes[1]->number)); //tworzenie nowego wierzcho³ka

	if (newNode)
	{
		//ustawienie wierzcho³ków potomnych
		newNode->left = this->treeNodes[0];
		newNode->right = this->treeNodes[1];

		//ustawienie wierzcho³ka nadrzêdnego w wierzcho³kach potomnych
		this->treeNodes[0]->parent = newNode;
		this->treeNodes[1]->parent = newNode;

		this->treeNodes.erase(treeNodes.cbegin(), treeNodes.cbegin() + 2); //usuniêcie dwóch pierwszych wierzcho³ków z listy

		this->treeNodes.push_back(newNode); //dodanie nowego wierzcho³ka do kolejki
	}	
}

/* funkcja sortuj¹ca listê wierzcho³ków

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

/*funkcja uruchamiaj¹ca generowanie drzewa oraz wypisanie kodów dla poszczególnych liœci

*/
void Tree::getHuffmanTree()
{
	this->setHuffmanTree(); //generacja drzewa
	this->getHuffmansCode(); //wygenerowanie i wypisanie kodów Huffmana dla ka¿dego liœcia
}

/*funkcja wyznaczaj¹ca kod Huffmana dla ka¿dego liœcia z listy treeLeafs

*/
void Tree::getHuffmansCode()
{	
	Node * currentNode; //pomocnicze zmienne dziêki którym wyznaczamy kod Huffmana dla kazdego liœcia
	Node * root;
	Node * tmp;

	while (this->treeLeafs.size() != 0) //wyznaczamy kody, a¿ lista liœci do odwiedzenia nie bêdzie pusta
	{
		currentNode = this->treeLeafs.front(); //obecny wierzcho³ek ustawiamy na pierwszy z listy
		root = currentNode->parent; //root na rodzica w/w wierzcho³ka
		tmp = currentNode;

		while (root != NULL) //do czasu, a¿ rodzic wierzcho³ka nie bêdzie NULL => wierzcho³ek jest korzeniem drzewa => jesteœmy na samej górze
		{
			//w zale¿noœci od tego, w któr¹ stronê jest poprowadzony nasz wierzcho³ek uzupe³niamy jego kod
			if (root->left == tmp)
			{
				currentNode->code += "0";
			}

			if (root->right == tmp)
			{
				currentNode->code += "1";
			}

			//przesuwamy siê o jeden poziom wy¿ej w drzewie
			tmp = root;
			root = root->parent;
		}

		this->treeLeafs.pop_front(); //usuniêcie odwiedzonego wierzcho³ka z listy

		cout << currentNode->character<<" : "<<currentNode->code<<endl; //wypisujemy znak oraz wygenerowany kod
	}
}
