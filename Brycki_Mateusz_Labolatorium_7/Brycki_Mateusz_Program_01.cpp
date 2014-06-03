/*
Autor: Mateusz Brycki, informatyka I rok, II semestr, grupa 11i, 12:45

Program rozwi�zuje problem plecakowy dyskretny. 

Dane pobiera z pliku, w kt�rym w pierwszym wierszu wej�cia mamy ilo�� przedmiot�w, rozmiar plecaka
w kolejnych n przedmiot�w w postaci nazwa cena waga.

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/*funkcja wype�niaj�ca tablic� zerami
@param table tablica, kt�r� b�dziemy "zerowa�"
@param height ilo�� wierszy tabeli
@param width ilo�� kolumn tabeli
*/
void setZero(int ** table, const int * height, const int * width)
{
	for (int y = 0; y < *height + 1; y++)
	{
		for (int x = 0; x < *width + 1; x++)
		{
			table[y][x] = 0;
		}
	}
}

/*funkcja wypisuj�ca tablic�
@param table tablica, kt�r� b�dziemy wypisywa�
@param height ilo�� wierszy tabeli
@param width ilo�� kolumn tabeli
*/
void getTable(int ** table, const int * height, const int * width)
{
	for (int y = 1; y < *height + 1; y++)
	{
		for (int x = 1; x < *width + 1; x++)
		{
			cout << table[y][x] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	struct item //struktura b�d�ca reprezentacj� jednego przedmiotu
	{
		string name; //nazwa
		int weight; //waga
		int price; //cena/warto��
	};

	int capacity, n; //pojemno�� plecaka, ilo�� przedmiot�w
	fstream file; //strumie� otwartego plik
	string name; //nazwa pliku, z danymi

	cin >> name;
	file.open(name); //otwarcie pliku o nazwie name

	file >> n; //pobranie ilo�ci przedmiot�w
	file >> capacity; //pobranie pojemno�ci plecaka

	item ** itemTab = reinterpret_cast<item **>(new item[n]); //dynamiczna tablica na wska�niki do kolejnych przedmiot�w

	for (int x = 0; x < n; x++)
	{
		itemTab[x] = reinterpret_cast<item *>(new item); //utowrzenie w tablicy nowej struktury item

		//w nowej strukturze ustawiamy kolejno nazw�, cen� oraz wag�
		file >> itemTab[x]->name; 
		file >> itemTab[x]->price;
		file >> itemTab[x]->weight;
	}

	//utworzenie tablic Q oraz P, obie s� identyczne
	int ** Q = reinterpret_cast<int **>(new int[n+1]);
	int ** P = reinterpret_cast<int **>(new int[n+1]);

	for (int x = 0; x < n+1; x++)
	{
		Q[x] = reinterpret_cast<int *>(new int[capacity+1]);
		P[x] = reinterpret_cast<int *>(new int[capacity+1]);
	}

	//wyzerowanie tablic P oraz Q
	setZero(P, &n, &capacity);
	setZero(Q, &n, &capacity);

	for (int y = 1; y <= n; y++) //najpierw przelatujemy po ilo�ci wierszy/przedmit�w
	{
		for (int x = 1; x <= capacity; x++) //nast�pnie po kolumnach/wagach
		{
			//je�eli dla bierz�cej wagi x waga bierz�cego przedmiotu y jest mniejsza => mo�emy w�o�yc do plecaka
			//i
			//je�eli dla przedmiotu z poprzedniego wiersza z kolumny (bierz�ca waga x - waga przedmiotu y) + waga przedmiotu y
			//jest wi�ksza ni� waga przedmiotu w poprzednim wierszu dla wagi x
			//np. bierz�cy przedmiot ma wag� 9, a bierz�ca waga to 10 => mo�emy w�o�y� do plecaka ten przedmiot i inny o wadze 1
			if ((x >= itemTab[y-1]->weight) && (P[y-1][x - itemTab[y-1]->weight] + itemTab[y-1]->price > P[y-1][x]))
			{
				//do plecaka mo�emy w�o�y� ten przedmiot + przedmiot z kolumny (bierz�ca waga x - waga przedmiotu y)
				//��czna warto�� zabranych przedmiot�w to warto�� w/w przedmit�w
				P[y][x] = P[y - 1][x - itemTab[y-1]->weight] + itemTab[y-1]->price;

				//dla wiersza y, oraz kolumny x zapisujemy numer przedmiotu, kt�ry zosta� ostatnio wsadzony
				Q[y][x] = y;
			}
			else {
				//je�eli suma tych przedmiot�w nie jest wi�ksza to przepisujemy z poprzedniego wiersza
				P[y][x] = P[y - 1][x];
				Q[y][x] = Q[y - 1][x];
			}
		}
	}

	//wypisanie tablic P oraz Q
	cout << "Tablica rzeczy zabranych do plecaka: " << endl;
	getTable(P, &n, &capacity);
	cout << "Tablica skojarzona z P: " << endl;
	getTable(Q, &n, &capacity);

	cout << "Laczna wartosc zabranych przedmiotow: " << P[n][capacity]<<endl;
	cout << "Zabrano: "<<endl;

	//wypisanie listy zabranych przedmiot�w
	int temp = capacity; //pomocnicza zmienna
	while (Q[n][temp] != 0)
	{
		//Q[n][temp] w tym miejscu jest jest zapisany numer ostatnio w�o�onego przedmiotu

		//wypisujemy nazw� tego przedmiotu oraz warto��
		cout << itemTab[Q[n][temp]-1]->name << " o wartosci " << itemTab[Q[n][temp]-1]->price << endl;


		//pomocnicz� zmienn� przestawiamy na element, kt�ry zosta� w�o�ony jeszcze wcze�niej, numerem kolumny to (temp - waga w/w przedmiotu)
		temp -= itemTab[Q[n][temp]-1]->weight;
	}


	//zamkni�cie pliku
	file.close();

	//usuni�cie tablic dynamicznych
	delete[] P;
	delete[] Q;

	cin.get();
	cin.get();
}