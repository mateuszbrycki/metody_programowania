/*
Autor: Mateusz Brycki, informatyka, I rok, grupa 11i

Program umo�liwia losowanie liczb za pomoc� generator�w LCG, MLCG, Fibonacciego ALFG z doborem parametr�w takich jak seed, warto�� max 
losowanych liczb oraz ilo�� losowanych liczb.
*/

#include <iostream>
#include <set>
#include <vector>
#include <fstream>
using namespace std;


//funkcja wypisuj�ca dany kontener
template <typename T>
void printRandomed(const T element)
{
	for (auto iElement = element.cbegin(); iElement != element.cend(); ++iElement)
	{
		cout << *iElement << " ";
	}
	cout << endl;
}

void menu();
void endOfFunction(const vector<int>* randomed);
int NWD(int a, int b);
set<int> getFactors(const int& a);
int getC(int m);
int getA(int const &m);
void saveToFile(const vector<int> * randomed);

/*funkcja realizuj�ca losowanie LCG lub MLCG 
@param method numer wybranego losowania LCG(1), MLCG(2)
*/
vector<int> lcg_mlcg(const int& method)
{
	int x_0, n, x_max;
	vector<int> randomed; //zbi�r wylosowanych liczb

	cout << "Podaj seed: ";
	cin >> x_0;

	cout << "Podaj ilosc generowanych liczb: ";
	cin >> n;

	cout << "Podaj wartosc maksymalna: ";
	cin >> x_max;

	int m = x_max + 1; //wyznaczamy m
	cout << "Obliczony wspolczynnik m: " << m << endl;
	if (x_0 < m && x_0 >= 0) //sprawdzamy czy podany seed jest odpowiedni
	{
		int c = 0;

		int a = getA(m); //wyznaczamy a w zale�no�ci od m
		cout << "Obliczony wspolczynnik a: " << a << endl;

		if (method == 1)
		{
			c = getC(m); //wyznaczamy c w zale�no�ci od m

			cout << "Obliczony wspolczynnik c: " << c << endl << endl;
		}

		int last = 1; //x0 = 1
		int current;

		for (int x = 1; x <= n; x++) //generujemy kolejne warto�ci
		{
			if (method == 1)
			{
				current = (a * last + c) % m; //losujemy kolejn� liczb�
			}
			else
			{
				current = (a * last) % m;
			}

			randomed.push_back(current); //dodajemy j� do listy wylosowanych
			last = current; //ustawiamy ostatnio wylosowany element
		}
	}
	else {
		cout << "Bledne dane! (seed)" << endl;
	}
	
	return randomed;
}

/*funkcja generuj�ca ci�g na podstawie ci�gu Fibonacciego*/
vector<int> fibanacci()
{
	int m;

	cout << "Podaj m: ";
	cin >> m;

	vector<int> randomed = lcg_mlcg(1); //losujemy liczby
	cout << "Wylosowano liczby: ";
	printRandomed(randomed); //wypisujemy wylosowany zbi�r

	int r = 10,
		s = 7;

	if ((r > 1) && (s > 1) && (r > s))
	{
		int i = 0;
		for (int y = 0; y < r; y++) //wykonujemy dla ka�dego wylosowanego elementu
		{
			auto iRandomed = randomed.begin();
			randomed[i] = (randomed[(r + i - s) % r] + randomed[i]) % m;
			int result = randomed[i];
			i = (i + 1) % r;

			//przesuni�cie iteratora do wskazaanego miejsca
			for (int x = 0; x < i; x++)
			{
				iRandomed++;
			}
		}
	}

	return randomed;
}

int main()
{	
	menu(); //wypisanie menu
}

/*funkcja obliczaj�ca NWD liczb a i b
@param a liczba a
@param b liczba b
*/
int NWD(int a, int b)
{
	int c;                    // Tworzymy zmienn� c o typie int
	while (b != 0)             // Tworzymy p�tl� dzia�aj�c� gdy b ? 0
	{
		c = a % b;              // Zmienna c przyjmuje warto�� a modulo b
		a = b;                // Przypisujemy b do a
		b = c;                // Przypisujemy c do b
	}

	return a;                 // Zwracamy a, czyli ��dane NWD(a,b)
}

/*funkcja generuj�ca czynniki pierwsze
@param a liczba, kt�r� b�dziemy rozk�ada� na czynniki pierwsze
*/
set<int> getFactors(const int& a)
{
	set<int> factors; //lista czynnik�w
	int dzielnik = 1;

	while (a >= dzielnik) //wykonujemy do momentu, a� dzielnik b�dzie wi�kszy od a
	{
		if ((a % dzielnik) == 0) //sprawdzamy czy dzielnik dzieli liczb� bez reszty
		{
			factors.insert((dzielnik)); //dodajemy dzielnik
		}

		dzielnik++; //zwi�kszamy dzielnik
	}

	return factors; //zwracamy list� dzielnik�w
}

/*funkcja generuj�ca element c - przyrost
@param m zmienna na podstawie kt�rej b�dziemy dobiera� przyrost c
*/
int getC(int m)
{
	int c = 2; //rozpocz�cie od dw�jki zagwarantuje nam, �e zwr�cona liczba nie b�dzie jedynk�

	while (NWD(c, m) != 1) //szukamy takiego c aby by� wzgl�dnie pierwszy z m
	{
		c++;
	}

	if (c >= m)
	{
		c = m - 6; //ustawiamy losowe c je�eli wcze�niej nie znaleziono takiego, kt�re spe�nia warunki zadania
	}

	return c;
}

/*funkcja odpowiedzialna za wyznaczenie elementu a
@param m czynnik na podstawie, kt�rego dopierany jest mno�nik a
*/
int getA(int const &m)
{
	set<int> factors = getFactors(m);

	int a = 2;
	auto iElement = factors.cbegin();

	while (iElement != factors.cend()) //do momentu, a� nie dojdziemy do ko�ca listy
	{
		if ((a - 1) % (2 * (*iElement)) == 0) //sprawdzamy czy a-1 jest podzielne przez wielokrotno�� czynnika
		{
			iElement++; //przesuwamy iterator na kolejny element
		}
		else {
			if (a < m) //je�eli a spe�nia warunek
			{
				a++; //zwi�kszamy a
			}
			else {
				break; //je�eli nie to ko�czymy p�tl�
			}

			iElement = factors.cbegin(); //a iterator ustawiamy na pierwszym elemencie kisty
		}
	}

	if (m / 4 != (a - 1) / 4 || a >= m) //za�o�enie twierdzenia nie jest spe�nione
	{
		a = m - 5; //ustawiamy losowe a
	}

	return a; //zwracamy obliczone a
}

void menu()
{
	cout << "Wybierz interesujacy Cie generator liczb:" << endl
		<< "1. LCG" << endl
		<< "2. MLCG " << endl
		<< "3. Generator Fibonacciego" << endl
		<< "0. Wyjscie" << endl;

	int choosen;
	cin >> choosen;
	system("CLS");

	switch (choosen)
	{
	case 1:
	{
			  vector<int> randomed = lcg_mlcg(1);
			  cout << "Wylosowano liczby: ";
			  printRandomed(randomed); //wypisujemy wylosowany zbi�r

			  endOfFunction(&randomed);
			  break;
	}
	case 2:
	{
			  vector<int> randomed = lcg_mlcg(2);
			  cout << "Wylosowano liczby: ";
			  printRandomed(randomed); //wypisujemy wylosowany zbi�r

			  endOfFunction(&randomed);
			  break;
	}
	case 3:
	{
			  vector<int> randomed = fibanacci();
			  cout << "Wylosowano liczby: ";
			  printRandomed(randomed); //wypisujemy wylosowany zbi�r

			  endOfFunction(&randomed);
			  break;
	}
	case 0:
		system("exit");
	default:
		system("exit");
	}
}

//funkcja wypisuj�ca informacje, o ko�cu dzia�ania wybranej funkcji
void endOfFunction(const vector<int>* randomed)
{
	cout << "Wcisnij 1 aby zapisac wylosowane liczby do pliku."<< endl
		<<"Wcisnij 0 aby powrocic do menu!" << endl;
	int choosen;
	cin >> choosen;
	switch (choosen)
	{
	case 0:
		system("CLS");
		menu();

	case 1:
		saveToFile(randomed);
		system("CLS");
		menu();
	}
}

void saveToFile(const vector<int> * randomed)
{
	fstream file;
	file.open("randomedNumbers_out.txt", fstream::out );

	for (auto iRandomed = randomed->cbegin(); iRandomed != randomed->cend(); ++iRandomed)
	{
		file << *iRandomed << " ";
	}

	file.close();

}