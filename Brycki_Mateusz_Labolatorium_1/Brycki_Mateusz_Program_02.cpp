#include <iostream>

using namespace std;

//funkcja zwracaj�ca true, dla takiego zestawu liczb, z kt�rego conajmniej jedna liczba jest dzielnikiem liczby N
bool sprawdz_podzielnosc(int & N, int m[])
{
	int * x = &m[0]; //wskaznik ustawiony na pierwszy element tablicy
	bool wynik = false; //wynik dzia�ania funkcji, domy�lnie ustawiony na false

	while (*x)
	{
		if ((N % *x) == 0) //sprawdzenie podzielno�ci liczby
		{
			wynik = true; //zwr�cenie true - "N dzieli si� bez reszty przez jak�kolwiek liczb� z zestawu"
			break; //przerwanie dzia�ania p�tli - znale�li�my dzielnik
		}

		x++; //przesuniecie wskaznika na kolejny element
		
	}

	return wynik;
}

int main()
{
	int N, //dzielna
		M; //ilo�� dzielnik�w

	//pobranie dzielnej, ktora musi sie znajdowac w przedziale od 1 do 1000000
	do {
		cin >> N;
	} while ((N < 1) || (N > 1000000));

	//pobranie liczby dzielnik�w, ktora musi sie znajdowac w przedziale od 1 do 1000000
	do {
		cin >> M;
	} while ((M < 1) || (M > 1000000));


	//dynamiczna tablica na podane liczby
	int *m_tab = new int[M];

	//wype�nienie tablicy dzielnikami
	for (int x = 0; x < M; x++)
	{
		do {
			cin >> m_tab[x];
		} while ((m_tab[x] < 1) || (m_tab[x] > 1000000));
	}

	//sprawdzenie podzielno�ci liczb i wydrukowanie odpowiedzi
	cout << (sprawdz_podzielnosc(N, m_tab) ? "TAK" : "NIE") << endl;

	cin.get();
	cin.get();
}