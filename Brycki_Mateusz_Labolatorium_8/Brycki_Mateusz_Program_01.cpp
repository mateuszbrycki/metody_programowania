/*
Autor: Mateusz Brycki, informatyka, 1 rok, grupa 11i

Program wyznacza maksymalny zysk problemu plecakowego 1-0. 
G³ówna funkcja wykorzystuje binarne drzewo poszukiwañ (BST).

Dane wczytywane s¹ w funkcji main z pliku dane.txt.
Format danych
pierwsza linia: n W
kolejne n linii: pi wi (pi/wi)
gdzie n - iloœæ przedmiotów, W - rozmiar plecaka, pi - cena przedmiotu, wi - waga przedmiotu
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

//struktura bêd¹ce reprezentacj¹ wierzcho³ka w drzewie
struct Node
{
	int level;
	int profit;
	int weight;
	float bound;
};

//prze³adowanie operatora << tak aby drukowa³ wymagane informacje o wierzcho³ku u
ostream & operator<< (ostream & stream, Node u)
{
	stream << "Jestesmy na poziomie " << u.level << ", obecnie rozwazany wierzcholek ma wartosci: \n"
		<< "waga: " << u.weight << "\tprofit: " << u.profit << "\tgranica: " << u.bound << endl;

	return stream;
}

/*funkcja obliczaj¹ca górn¹ granicê zysku dla zabranych przedmiotów
@param u wierzcho³ek, którego granicê obliczamy
@param itemTab tablica przechowywuj¹ca wartoœci oraz wagi przedmiotów
@param W pojemnoœæ plecaka
@param n iloœæ przedmiotów do zabrania
*/
float bound(Node u, int ** itemTab, int & W, int & n)
{
	int j; //zmienna pomocnicza
	int totweight; //waga ca³kowita
	float result; //wynik dzia³ania funkcji

	if (u.weight >= W) //je¿eli waga przedmiotu przekracza pojemnoœæ plecaka to zwracamy 0
	{
		return 0;
	}
	else {
		result = u.profit; 
		j = u.level + 1; //zwiêkszamy poziom, przesuwamy siê w dó³ tabeli itemTab -> kolejne elementy
		totweight = u.weight; 
		
		while ((j <= n) && (totweight + itemTab[j][1] <= W)) //je¿eli jesteœmy na poziomie wy¿szym ni¿ maksymalny (n) oraz nowy przedmiot zmieœi siê jeszcze do plecaka
		{
			totweight += itemTab[j][1]; //do wagi ca³kowitej dodajemy wagê zabranego przedmiotu
			result += itemTab[j][0]; //do wartoœci rzeczy w plecaku dodajemy wartoœæ zabranego przedmiotu
			j++;
		}

		if (j <= n) //je¿eli jesteœmy na "dozwolonym poziomie" <= n
		{
			result += (W - totweight) * itemTab[j][2];  //obliczamy górn¹ granicê zysku, który mo¿emy uzyskaæ przez rozwiniêcie wêz³a 
		}

		return result; //zwracamy górn¹ granicê zysku dla wêz³a u
	}
}

/*funkcja sprawdzaj¹ca czy wierzcho³ek jest obiecuj¹cy
@param u wierzcho³ek, który bêdziemy sprawdzaæ
@param maxprofit najwiêkszy zysk uzyskany do tej pory
@param W pojemnoœæ plecaka
*/
bool isPromising(Node u, int & maxprofit, int & W)
{	//je¿eli waga przedmiotów jest wiêksza ni¿ pojemnoœæ plecaka
	//lub
	//górna granica zysku po zabraniu tego przedmiotu jest mniejsza ni¿ najwiêkszy zysk uzyskany do tej pory => mamy lepsze rozwi¹zanie
	if (u.weight >= W || u.bound <= maxprofit)
	{
		return false; //wierzcho³ek nie jest obiecuj¹cy
	}
	else {
		return true;
	}
}

/*funkcja realizuj¹ca obliczanie maksymalnego zysku przy mo¿liwych do zabrania przedmiotach
@param n iloœæ przedmiotów
@param itemTab tablica przechowywuj¹ca wartoœci oraz wagi przedmiotów
@param W pojemnoœæ plecaka
@param maxprofit najwiêkszy mo¿liwy zysk
*/
void knapsack(int &n, int ** itemTab, int & W, int & maxprofit)
{
	queue <Node> treeNodes; //kolejka, która bêdzie przechowywa³a wierzcho³ki do odwiedzenia
	Node u, v; //wierzcho³ek - dziecko, wierzcho³ek-rodzic

	v.level = v.profit = v.weight = 0; //pocz¹tkowe wartoœci dla drzewa - korzeñ
	maxprofit = 0;
	v.bound = bound(v, itemTab, W, n); //obliczamy granicê dla korzenia

	treeNodes.push(v); //dodajemy korzeñ do koleki

	while (!treeNodes.empty()) //wykonujemy przeszukiwanie wszerz do momentu a¿ kolejka nie bêdzie pusta
	{	
		treeNodes.pop(); //wyci¹gniêcie z kolejki elementu z najlepszym rozwi¹zaniem (wierzcho³ek nadrzêdny)

		//ustawiamy potomka na poziomie + 1, oraz jego pozosta³e wartoœci wg. tabeli
		//w drzewie oznacza³oby to pójœcie w lewo - 1
		u.level = v.level + 1; 
		u.weight = v.weight + itemTab[u.level][1];
		u.profit = v.profit + itemTab[u.level][0];
		u.bound = bound(u, itemTab, W, n); //obliczamy granicê
	
		cout << u; //wypisujemy informacje o wierzcho³ku u

		if (isPromising(u, maxprofit, W)) //sprawdzamy czy potomek wierzcho³ka v (u) jest obiecuj¹cy
		{
			if (u.profit > maxprofit && u.weight <= W) //sprawdzamy czy wartoœæ wierzcho³ka potomnego jest wiêksza ni¿ dotychczas najwiêksza wartoœæ
			{
				maxprofit = u.profit; //ustawiamy now¹ wartoœæ maxprofit
			}
			if (u.bound > maxprofit) //je¿eli wierzcho³ek potomny jest obiecuj¹cy to dodajemy go do kolejki przeszukiwania
			{
				treeNodes.push(u); //dodajemy potomka do listy przeszukiwania
			}
			
			cout << "Potomek wierzcholka jest obiecujacy wiec bierzemy przedmiot nr " << u.level << endl << endl;
			
		}
		else {
			cout << "Wierzcholek nie jest obiecujacy." << endl << endl;
		}
		

		//ustawiamy potomka na poziomie level + 1 dla wierzcho³ka v, zak³adaj¹c, ¿e nie wziêliœmy na poziomie level przedmiotu v
		//nie zwiêkszamy wartoœci wierzcho³ka, w drzewie oznacza³oby to pójœcie w prawo - 0
		u.level = v.level + 1; //zwiêkszamy poziom, na którym znajduje siê wierzcho³ek potomny
		u.weight = v.weight;
		u.profit = v.profit;
		u.bound = bound(u, itemTab, W, n);

		cout << u; //wypisujemy informacje o wierzcho³ku u

		//je¿eli wierzcho³ek pochodny u jest obiecuj¹cy to dodajemy go na koniec kolejki
		if(isPromising(u, maxprofit, W))
		{
			treeNodes.push(u); //dodajemy potomka do listy przeszukiwania

			cout << "Potomek wierzcholka jest obiecujacy, ale nie bierzemy przedmiotu nr " << u.level << endl<<endl;
			
		}
		else {
			cout << "Wierzcholek nie jest obiecujacy." << endl << endl;
		}

		if (treeNodes.size() != 0) //je¿eli lista nie jest pusta to pobieramy wierzcho³ek o najwiêkszej wartoœci
		{
			v = treeNodes.front(); //i ustawiamy jako rodzica
		}
	}
}

/*funkcja sortuj¹ca malej¹co tablicê wed³ug kolumny PW
@param itemTab tablica, któr¹ bêdziemy sortowaæ
@param n iloœæ elementów w tablicy
*/
void sortByPW(int ** itemTab, int & n)
{
	int x = 1; //zaczynamy sortowaæ od pierwszego wiersza

	while (x != n)
	{
		if (itemTab[x][2] < itemTab[x + 1][2])
		{

			swap(itemTab[x], itemTab[x + 1]); //zamieniamy wiersze miejscami
			x = 1; //zaczynamy sprawdzaæ tablicê od pocz¹tku - pierwszego wiersza
		}
		else {
			x++;
		}
	}
}

int main()
{
	fstream file;
	int n, //iloœæ przedmiotów
		W; //pojemnoœæ plecaka
	int maxprofit; //maksymalny zysk
	string name; //nazwa pliku z danymi

	cout << "Podaj nazwe pliku z danymi: ";
	cin >> name;
	cout << endl << endl;

	file.open(name); //otwieramy plik o podanej nazwie

	if (!file.is_open()) //je¿eli otwarcie pliku nie powiod³o siê to koñczymy pracê programu
	{
		return 0;
	}
	
	file >> n; //pobranie z pliku iloœci przedmiotów
	file >> W; //pobranie z pliku pojemnoœci plecaka

	int ** itemTab = reinterpret_cast<int **>(new(nothrow) int[n+1]); //dynamiczna tablica na przedmioty

	if (itemTab) //sprawdzamy czy tablica zosta³a poprawnie utworzona
	{
		for (int x = 0; x < n + 1; x++)
		{
			itemTab[x] = reinterpret_cast<int *>(new(nothrow) int);
		}

		itemTab[0][0] = itemTab[0][1] = itemTab[0][2] = 0; //pierwszy wiersza tabeli itemTab

		for (int x = 1; x <= n; x++)
		{
			//ustawiamy kolejno cenê, wagê oraz stosunek ceny do wagi
			file >> itemTab[x][0]; //cena
			file >> itemTab[x][1]; //waga
			file >> itemTab[x][2]; // (cena/waga)
		}

		sortByPW(itemTab, n); //sortujemy malej¹co itemTab wed³ug kolumny pw => itemTab[2]

		knapsack(n, itemTab, W, maxprofit); //wywo³anie g³ównej funkcji

		delete [] itemTab; //usuniêcie tablicy
	}

	cout <<"\n\nNajwiekszy zysk: "<< maxprofit;

	cin.get();
	cin.get();
}