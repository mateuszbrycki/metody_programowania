#include <iostream>

using namespace std;

//funkcja zwracaj¹ca true, dla takiego zestawu liczb, z którego conajmniej jedna liczba jest dzielnikiem liczby N
bool sprawdz_podzielnosc(int & N, int m[])
{
	int * x = &m[0]; //wskaznik ustawiony na pierwszy element tablicy
	bool wynik = false; //wynik dzia³ania funkcji, domyœlnie ustawiony na false

	while (*x)
	{
		if ((N % *x) == 0) //sprawdzenie podzielnoœci liczby
		{
			wynik = true; //zwrócenie true - "N dzieli siê bez reszty przez jak¹kolwiek liczbê z zestawu"
			break; //przerwanie dzia³ania pêtli - znaleŸliœmy dzielnik
		}

		x++; //przesuniecie wskaznika na kolejny element
		
	}

	return wynik;
}

int main()
{
	int N, //dzielna
		M; //iloœæ dzielników

	//pobranie dzielnej, ktora musi sie znajdowac w przedziale od 1 do 1000000
	do {
		cin >> N;
	} while ((N < 1) || (N > 1000000));

	//pobranie liczby dzielników, ktora musi sie znajdowac w przedziale od 1 do 1000000
	do {
		cin >> M;
	} while ((M < 1) || (M > 1000000));


	//dynamiczna tablica na podane liczby
	int *m_tab = new int[M];

	//wype³nienie tablicy dzielnikami
	for (int x = 0; x < M; x++)
	{
		do {
			cin >> m_tab[x];
		} while ((m_tab[x] < 1) || (m_tab[x] > 1000000));
	}

	//sprawdzenie podzielnoœci liczb i wydrukowanie odpowiedzi
	cout << (sprawdz_podzielnosc(N, m_tab) ? "TAK" : "NIE") << endl;

	cin.get();
	cin.get();
}