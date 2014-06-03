/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i

Program wyznacza maksymalny zysk problemu plecakowego 1-0. 
G��wna funkcja wykorzystuje binarne drzewo poszukiwa� (BST).

Dane wczytywane s� w funkcji main z pliku dane.txt.
Format danych
pierwsza linia: n W
kolejne n linii: pi wi (pi/wi)
gdzie n - ilo�� przedmiot�w, W - rozmiar plecaka, pi - cena przedmiotu, wi - waga przedmiotu
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

//struktura b�d�ce reprezentacj� wierzcho�ka w drzewie
struct Node
{
	int level;
	int profit;
	int weight;
	float bound;
};

//prze�adowanie operatora << tak aby drukowa� wymagane informacje o wierzcho�ku u
ostream & operator<< (ostream & stream, Node u)
{
	stream << "Jestesmy na poziomie " << u.level << ", obecnie rozwazany wierzcholek ma wartosci: \n"
		<< "waga: " << u.weight << "\tprofit: " << u.profit << "\tgranica: " << u.bound << endl;

	return stream;
}

/*funkcja obliczaj�ca g�rn� granic� zysku dla zabranych przedmiot�w
@param u wierzcho�ek, kt�rego granic� obliczamy
@param itemTab tablica przechowywuj�ca warto�ci oraz wagi przedmiot�w
@param W pojemno�� plecaka
@param n ilo�� przedmiot�w do zabrania
*/
float bound(Node u, int ** itemTab, int & W, int & n)
{
	int j; //zmienna pomocnicza
	int totweight; //waga ca�kowita
	float result; //wynik dzia�ania funkcji

	if (u.weight >= W) //je�eli waga przedmiotu przekracza pojemno�� plecaka to zwracamy 0
	{
		return 0;
	}
	else {
		result = u.profit; 
		j = u.level + 1; //zwi�kszamy poziom, przesuwamy si� w d� tabeli itemTab -> kolejne elementy
		totweight = u.weight; 
		
		while ((j <= n) && (totweight + itemTab[j][1] <= W)) //je�eli jeste�my na poziomie wy�szym ni� maksymalny (n) oraz nowy przedmiot zmie�i si� jeszcze do plecaka
		{
			totweight += itemTab[j][1]; //do wagi ca�kowitej dodajemy wag� zabranego przedmiotu
			result += itemTab[j][0]; //do warto�ci rzeczy w plecaku dodajemy warto�� zabranego przedmiotu
			j++;
		}

		if (j <= n) //je�eli jeste�my na "dozwolonym poziomie" <= n
		{
			result += (W - totweight) * itemTab[j][2];  //obliczamy g�rn� granic� zysku, kt�ry mo�emy uzyska� przez rozwini�cie w�z�a 
		}

		return result; //zwracamy g�rn� granic� zysku dla w�z�a u
	}
}

/*funkcja sprawdzaj�ca czy wierzcho�ek jest obiecuj�cy
@param u wierzcho�ek, kt�ry b�dziemy sprawdza�
@param maxprofit najwi�kszy zysk uzyskany do tej pory
@param W pojemno�� plecaka
*/
bool isPromising(Node u, int & maxprofit, int & W)
{	//je�eli waga przedmiot�w jest wi�ksza ni� pojemno�� plecaka
	//lub
	//g�rna granica zysku po zabraniu tego przedmiotu jest mniejsza ni� najwi�kszy zysk uzyskany do tej pory => mamy lepsze rozwi�zanie
	if (u.weight >= W || u.bound <= maxprofit)
	{
		return false; //wierzcho�ek nie jest obiecuj�cy
	}
	else {
		return true;
	}
}

/*funkcja realizuj�ca obliczanie maksymalnego zysku przy mo�liwych do zabrania przedmiotach
@param n ilo�� przedmiot�w
@param itemTab tablica przechowywuj�ca warto�ci oraz wagi przedmiot�w
@param W pojemno�� plecaka
@param maxprofit najwi�kszy mo�liwy zysk
*/
void knapsack(int &n, int ** itemTab, int & W, int & maxprofit)
{
	queue <Node> treeNodes; //kolejka, kt�ra b�dzie przechowywa�a wierzcho�ki do odwiedzenia
	Node u, v; //wierzcho�ek - dziecko, wierzcho�ek-rodzic

	v.level = v.profit = v.weight = 0; //pocz�tkowe warto�ci dla drzewa - korze�
	maxprofit = 0;
	v.bound = bound(v, itemTab, W, n); //obliczamy granic� dla korzenia

	treeNodes.push(v); //dodajemy korze� do koleki

	while (!treeNodes.empty()) //wykonujemy przeszukiwanie wszerz do momentu a� kolejka nie b�dzie pusta
	{	
		treeNodes.pop(); //wyci�gni�cie z kolejki elementu z najlepszym rozwi�zaniem (wierzcho�ek nadrz�dny)

		//ustawiamy potomka na poziomie + 1, oraz jego pozosta�e warto�ci wg. tabeli
		//w drzewie oznacza�oby to p�j�cie w lewo - 1
		u.level = v.level + 1; 
		u.weight = v.weight + itemTab[u.level][1];
		u.profit = v.profit + itemTab[u.level][0];
		u.bound = bound(u, itemTab, W, n); //obliczamy granic�
	
		cout << u; //wypisujemy informacje o wierzcho�ku u

		if (isPromising(u, maxprofit, W)) //sprawdzamy czy potomek wierzcho�ka v (u) jest obiecuj�cy
		{
			if (u.profit > maxprofit && u.weight <= W) //sprawdzamy czy warto�� wierzcho�ka potomnego jest wi�ksza ni� dotychczas najwi�ksza warto��
			{
				maxprofit = u.profit; //ustawiamy now� warto�� maxprofit
			}
			if (u.bound > maxprofit) //je�eli wierzcho�ek potomny jest obiecuj�cy to dodajemy go do kolejki przeszukiwania
			{
				treeNodes.push(u); //dodajemy potomka do listy przeszukiwania
			}
			
			cout << "Potomek wierzcholka jest obiecujacy wiec bierzemy przedmiot nr " << u.level << endl << endl;
			
		}
		else {
			cout << "Wierzcholek nie jest obiecujacy." << endl << endl;
		}
		

		//ustawiamy potomka na poziomie level + 1 dla wierzcho�ka v, zak�adaj�c, �e nie wzi�li�my na poziomie level przedmiotu v
		//nie zwi�kszamy warto�ci wierzcho�ka, w drzewie oznacza�oby to p�j�cie w prawo - 0
		u.level = v.level + 1; //zwi�kszamy poziom, na kt�rym znajduje si� wierzcho�ek potomny
		u.weight = v.weight;
		u.profit = v.profit;
		u.bound = bound(u, itemTab, W, n);

		cout << u; //wypisujemy informacje o wierzcho�ku u

		//je�eli wierzcho�ek pochodny u jest obiecuj�cy to dodajemy go na koniec kolejki
		if(isPromising(u, maxprofit, W))
		{
			treeNodes.push(u); //dodajemy potomka do listy przeszukiwania

			cout << "Potomek wierzcholka jest obiecujacy, ale nie bierzemy przedmiotu nr " << u.level << endl<<endl;
			
		}
		else {
			cout << "Wierzcholek nie jest obiecujacy." << endl << endl;
		}

		if (treeNodes.size() != 0) //je�eli lista nie jest pusta to pobieramy wierzcho�ek o najwi�kszej warto�ci
		{
			v = treeNodes.front(); //i ustawiamy jako rodzica
		}
	}
}

/*funkcja sortuj�ca malej�co tablic� wed�ug kolumny PW
@param itemTab tablica, kt�r� b�dziemy sortowa�
@param n ilo�� element�w w tablicy
*/
void sortByPW(int ** itemTab, int & n)
{
	int x = 1; //zaczynamy sortowa� od pierwszego wiersza

	while (x != n)
	{
		if (itemTab[x][2] < itemTab[x + 1][2])
		{

			swap(itemTab[x], itemTab[x + 1]); //zamieniamy wiersze miejscami
			x = 1; //zaczynamy sprawdza� tablic� od pocz�tku - pierwszego wiersza
		}
		else {
			x++;
		}
	}
}

int main()
{
	fstream file;
	int n, //ilo�� przedmiot�w
		W; //pojemno�� plecaka
	int maxprofit; //maksymalny zysk
	string name; //nazwa pliku z danymi

	cout << "Podaj nazwe pliku z danymi: ";
	cin >> name;
	cout << endl << endl;

	file.open(name); //otwieramy plik o podanej nazwie

	if (!file.is_open()) //je�eli otwarcie pliku nie powiod�o si� to ko�czymy prac� programu
	{
		return 0;
	}
	
	file >> n; //pobranie z pliku ilo�ci przedmiot�w
	file >> W; //pobranie z pliku pojemno�ci plecaka

	int ** itemTab = reinterpret_cast<int **>(new(nothrow) int[n+1]); //dynamiczna tablica na przedmioty

	if (itemTab) //sprawdzamy czy tablica zosta�a poprawnie utworzona
	{
		for (int x = 0; x < n + 1; x++)
		{
			itemTab[x] = reinterpret_cast<int *>(new(nothrow) int);
		}

		itemTab[0][0] = itemTab[0][1] = itemTab[0][2] = 0; //pierwszy wiersza tabeli itemTab

		for (int x = 1; x <= n; x++)
		{
			//ustawiamy kolejno cen�, wag� oraz stosunek ceny do wagi
			file >> itemTab[x][0]; //cena
			file >> itemTab[x][1]; //waga
			file >> itemTab[x][2]; // (cena/waga)
		}

		sortByPW(itemTab, n); //sortujemy malej�co itemTab wed�ug kolumny pw => itemTab[2]

		knapsack(n, itemTab, W, maxprofit); //wywo�anie g��wnej funkcji

		delete [] itemTab; //usuni�cie tablicy
	}

	cout <<"\n\nNajwiekszy zysk: "<< maxprofit;

	cin.get();
	cin.get();
}