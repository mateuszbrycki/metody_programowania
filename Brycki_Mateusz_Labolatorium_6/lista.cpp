#include "lista.h"

//domyœlny konstruktor
lista::lista() {}

//konstruktor dodaj¹cy pierwszy element listy
lista::lista(int m)
{
	add(m);
}

//funkcja odpowiedzialna za dodanie elementu na koniec listy
//@param m element dodawany do listy
void lista::add(int m)
{
	new_element = new element; //alokacja pamieci dla nowego elementu

	new_element->vertex = m; //ustawienie zmiennej liczbowej na zmienna przeslana w argumencie funkcji
	new_element->next = NULL; //ustawienie adresu nastepnego wskaznika na NULL - ten jest ostatni

	if (head == NULL) //sprawdzamy czy jest to pierwszy element listy
	{
		head = new_element; //ustawiamy wskaznik head na ten element
		tail = head; //to samo z ogonem
	}
	else { //juz istnieje jakis element w tej liscie
		tail->next = new_element; //adres ogonu ustawiamy na nowy
		tail = new_element; //ogon przesuwamy na nowy element
	}
}

//prze³adowana funkcja dodania elementu do koñca listy, wersja z dodaniem wagi
//@param m element dodawany do listy
//@param w waga elementu m
void lista::add(int m, int w)
{
	new_element = new element; //alokacja pamieci dla nowego elementu

	new_element->vertex = m; //ustawienie zmiennej liczbowej na zmienna przeslana w argumencie funkcji
	new_element->next = NULL; //ustawienie adresu nastepnego wskaznika na NULL - ten jest ostatni
	new_element->weight = w; //ustawienie wagi

	if (head == NULL) //sprawdzamy czy jest to pierwszy element listy
	{
		head = new_element; //ustawiamy wskaznik head na ten element
		tail = head; //to samo z ogonem
	}
	else { //juz istnieje jakis element w tej liscie
		tail->next = new_element; //adres ogonu ustawiamy na nowy
		tail = new_element; //ogon przesuwamy na nowy element
	}
}

//funkcja wypisuj¹ca wszystkie elementy listy
//@param weighted graf z wagami lub nie
void lista::getAll(bool *weighted)
{
	element * cursor = head; //pomocniczy wskaznik, ktory bedziemy przesuwac po elementach listy
	
	if (cursor) //wypisujemy tylko wtedy gdy istnieja wierzcholki sasiednie => head != NULL
	{
		for (int x = 0; x <= getNumberOfElements(); x++) //petla odpowiedzialna za wypiasanie wartosci liczb z kolejnych elementow
		{
			if (cursor->weight != NULL)
			{
				//wypisanie listy w odpowiednim formacie
				if (*weighted)
				{
					cout << "(" << cursor->vertex << ", " << cursor->weight << ")\t";
				}
				else {
					cout << cursor->vertex << "\t";
				}
		
			}
			else {
				cout << cursor->vertex << "\t"; //wypisanie tej wrtosci
			}
			
			cursor = cursor->next; //ustawienie pomocniczego kursora na nastepny element

		}
		cout << endl;
	}
}

//funkcja zwracaj¹ca iloœæ elementów listy
int lista::getNumberOfElements()
{
	element * cursor = head; //pomocniczy wektor poruszaj¹cy siê po tablicy

	if (cursor) //wypisujemy tylko wtedy gdy istnieja wierzcholki sasiednie => head != NULL
	{
		int x = 0;

		while (cursor->next)
		{
			x++; //zwiekszenie licznika ilosci elementow
			cursor = cursor->next; //przesuniecie wektora na nastepny element listy
		}
		return x;
	}	
}