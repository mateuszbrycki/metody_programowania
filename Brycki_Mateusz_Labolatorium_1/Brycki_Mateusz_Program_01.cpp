#include <iostream>

using namespace std;

//funkcja zwracaj¹ca wartosci max z podanej tablicy
int fmax(int tab[], int& n)
{
	int *max_wsk = &tab[0];

	for (int x = 1; x < n; x++)
	{
		if (tab[x] > *max_wsk)
		{
			max_wsk = &tab[x];
		}
	}

	return *max_wsk;
}

//funkcja zwracaj¹ca wartosci minimum z podanej tablicy
int fmin(int tab[], int & n)
{
	int *min_wsk = &tab[0];

	for (int x = 1; x < n; x++)
	{
		if (tab[x] < *min_wsk)
		{
			min_wsk = &tab[x];
		}
	}

	return *min_wsk;
}

int main()
{
	int n, //ilosc zestawow
		M, //ilosc liczb w zestawie
		x = 0;

	//pobranie liczby zestawów
	do {
		cin >> n;
	} while ((n < 1) || (n > 1000));

	//tworzenie dynamicznej dwuwymiarowej tablicy, w której bêd¹ znajdowaæ siê wyniki
	int **wyniki = reinterpret_cast<int**>(new int[n]);

	for (int z = 0; z < n; z++)
	{
		wyniki[z] = reinterpret_cast<int*>(new int[2]);
	}
	  

	while (x != n)
	{
		//pobranie ilosci liczb tworzacych zestaw
		do {
			cin >> M;
		} while ((M < 1) || (M > 1000));

		int *tab = new int[M]; //utworzenie tablicy dynamicznej dla wpisywanych zestawow

		//pobieranie liczb tworzacych zestaw
		for (int n = 0; n < M; n++)
		{
			//wpisana zmienna musi byc z przedzialu od 0 do 1 000 000
			do {
				cin >> tab[n];
			} while ((tab[n] < 0) || (tab[n] > 1000000)); 
		}

		wyniki[x][0] = fmin(tab, M); //minimalna wartosc zestawu
		wyniki[x][1] = fmax(tab, M); //maksymalna wartosc zestawu

		x++;

		delete[] tab; //zwolnienie pamiêci, ktora zajmowala tablica z zestawem, usuniecie tab
	}

	//wypisanie wyników min, max z tablicy wyników
	for (int z = 0; z < n; z++)
	{
		cout << wyniki[z][0] << " " << wyniki[z][1] << endl;
	}

	cin.get();
	cin.get();
}