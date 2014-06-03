/*
Autor: Mateusz Brycki, informatyka I rok, II semestr, grupa 11i, 12:45

Program rozwi¹zuje problem plecakowy dyskretny. 

Dane pobiera z pliku, w którym w pierwszym wierszu wejœcia mamy iloœæ przedmiotów, rozmiar plecaka
w kolejnych n przedmiotów w postaci nazwa cena waga.

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/*funkcja wype³niaj¹ca tablicê zerami
@param table tablica, któr¹ bêdziemy "zerowaæ"
@param height iloœæ wierszy tabeli
@param width iloœæ kolumn tabeli
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

/*funkcja wypisuj¹ca tablicê
@param table tablica, któr¹ bêdziemy wypisywaæ
@param height iloœæ wierszy tabeli
@param width iloœæ kolumn tabeli
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
	struct item //struktura bêd¹ca reprezentacj¹ jednego przedmiotu
	{
		string name; //nazwa
		int weight; //waga
		int price; //cena/wartoœæ
	};

	int capacity, n; //pojemnoœæ plecaka, iloœæ przedmiotów
	fstream file; //strumieñ otwartego plik
	string name; //nazwa pliku, z danymi

	cin >> name;
	file.open(name); //otwarcie pliku o nazwie name

	file >> n; //pobranie iloœci przedmiotów
	file >> capacity; //pobranie pojemnoœci plecaka

	item ** itemTab = reinterpret_cast<item **>(new item[n]); //dynamiczna tablica na wskaŸniki do kolejnych przedmiotów

	for (int x = 0; x < n; x++)
	{
		itemTab[x] = reinterpret_cast<item *>(new item); //utowrzenie w tablicy nowej struktury item

		//w nowej strukturze ustawiamy kolejno nazwê, cenê oraz wagê
		file >> itemTab[x]->name; 
		file >> itemTab[x]->price;
		file >> itemTab[x]->weight;
	}

	//utworzenie tablic Q oraz P, obie s¹ identyczne
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

	for (int y = 1; y <= n; y++) //najpierw przelatujemy po iloœci wierszy/przedmitów
	{
		for (int x = 1; x <= capacity; x++) //nastêpnie po kolumnach/wagach
		{
			//je¿eli dla bierz¹cej wagi x waga bierz¹cego przedmiotu y jest mniejsza => mo¿emy w³o¿yc do plecaka
			//i
			//je¿eli dla przedmiotu z poprzedniego wiersza z kolumny (bierz¹ca waga x - waga przedmiotu y) + waga przedmiotu y
			//jest wiêksza ni¿ waga przedmiotu w poprzednim wierszu dla wagi x
			//np. bierz¹cy przedmiot ma wagê 9, a bierz¹ca waga to 10 => mo¿emy w³o¿yæ do plecaka ten przedmiot i inny o wadze 1
			if ((x >= itemTab[y-1]->weight) && (P[y-1][x - itemTab[y-1]->weight] + itemTab[y-1]->price > P[y-1][x]))
			{
				//do plecaka mo¿emy w³o¿yæ ten przedmiot + przedmiot z kolumny (bierz¹ca waga x - waga przedmiotu y)
				//³¹czna wartoœæ zabranych przedmiotów to wartoœæ w/w przedmitów
				P[y][x] = P[y - 1][x - itemTab[y-1]->weight] + itemTab[y-1]->price;

				//dla wiersza y, oraz kolumny x zapisujemy numer przedmiotu, który zosta³ ostatnio wsadzony
				Q[y][x] = y;
			}
			else {
				//je¿eli suma tych przedmiotów nie jest wiêksza to przepisujemy z poprzedniego wiersza
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

	//wypisanie listy zabranych przedmiotów
	int temp = capacity; //pomocnicza zmienna
	while (Q[n][temp] != 0)
	{
		//Q[n][temp] w tym miejscu jest jest zapisany numer ostatnio w³o¿onego przedmiotu

		//wypisujemy nazwê tego przedmiotu oraz wartoœæ
		cout << itemTab[Q[n][temp]-1]->name << " o wartosci " << itemTab[Q[n][temp]-1]->price << endl;


		//pomocnicz¹ zmienn¹ przestawiamy na element, który zosta³ w³o¿ony jeszcze wczeœniej, numerem kolumny to (temp - waga w/w przedmiotu)
		temp -= itemTab[Q[n][temp]-1]->weight;
	}


	//zamkniêcie pliku
	file.close();

	//usuniêcie tablic dynamicznych
	delete[] P;
	delete[] Q;

	cin.get();
	cin.get();
}