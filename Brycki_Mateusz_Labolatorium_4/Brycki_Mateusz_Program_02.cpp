/*
Autor: Mateusz Brycki, informatyka, 1 rok, WIEiK, 11i

Algorytm sortowania quicksort oparty na technice "dziel i zwyciê¿aj".
*/
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

fstream plik_in, plik_out;  //uchwyty do plików z danymi oraz na wyniki


//funkcja odpowiedzialna za przestawianie elementów tablicy w miejscu
int partition(long int *A, int p, int r)
{
	int x = A[r];
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}

	swap(A[i + 1], A[r]);

	return i + 1;
}

//funkcja odpowiedzialna za sortowanie
//@param A - tablica, która ma zostaæ posortowana
//@param p - pocz¹tek sortowanej czêœci tablicy
//@param r - koniec sortowanej czêœci tablicy
void quicksort(long int *A, int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);

		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

//funkcja wypisuj¹ca tablicê do pliku
//@param set - adres pierwszego elementu zapisywanej tablicy
//@param n - iloœæ elementów tablicy
void wypisz(long int *set, int *n)
{
	for (int x = 0; x < *n; x++)
	{
		plik_out << set[x]<<" ";
	}

	plik_out << endl;
}

int main()
{
	int z, n; //z - iloœæ zestawów
			  //n - iloœæ liczb w zestawie

	string nazwa;
	cout << "Podaj nazwe pliku z danymi (.txt): ";
	cin >> nazwa;

	plik_in.open(nazwa); //otworzenie pliku z danymi
	plik_out.open("out.txt", ios_base::out); //otworzenie lub utworzenie pliku na wyniki

	plik_in >> z; //pobranie iloœci zestawów

	//pêtla wczytuj¹ca kolejne dane z pliku
	do
	{
		
		plik_in >> n; //pobranie rozmiaru zestawu

		if ((n < 1) || (n > 500000))
		{
			plik_out << "B³êdne dane!";
			return 0;
		}

		long int * set = new long int[n]; //dynamiczna tablica na elementy zestawu o rozmiarze n

		//pêtla wczytuj¹ca n kolejnych liczb tworz¹cych zestaw
		for (int x = 0; x < n; x++)
		{
			plik_in >> set[x];
		}


		quicksort(set, 0, n - 1); //funkcja sortuj¹ca tablicê o liczbie elementów n

		wypisz(set, &n); //funkcja odpowiedzialna za wypisanie do pliku posortowanej tablicy

		z--;

		delete [] set; //zwolnienie pamiêci po wypisaniu posortowanej tablicy do pliku
	} while (z > 0);

	 //zamkniêcie uchwytów plików
	plik_in.close();
	plik_out.close();

	cin.get();
	cin.get();

}

/*
Algorytm Quicksort zosta³ przetestowany dla danych z pliku testowe_in.txt. Wyniki dzia³ania programu zosta³y zapisane w pliku testowe_out.txt.

Pierwszy zestaw to 5500 liczb z przedzia³u 0 - 1000 zapisane losowo.
Drugi to 1500 liczb z przedzia³u 0-1000 posortowane rosn¹co.
Trzeci to 1500 liczb z przedzia³u 0-1000 posortowane malej¹co.
Czwarty to 1500 liczb z przedzai³u 0-1500, taki ¿e pierwsze 1350 liczb jest posortowane rosn¹co, a ostatnie 150 to liczby ustawione losowo.

Wszystkie 4 zestawy zosta³y utworzone za pomoc¹ funkcji generuj() znajduj¹cej siê w pliku nag³ówkowym generate.h.
Dodatkowo:
- drugi zestaw zosta³ posortowany za pomoc¹ quicksort
- trzeci równie¿, ale zapis odby³ sie w odwrotnej kolejnoœci tj. od koñca tablicy
- czwarty zosta³ posortowany za pomoc¹ quicksort od elementu 0 do 1349, dalsza czêœæ tablicy pozosta³a bez zmian.

Czas sortowania tablic by³ mierzony w nastêpuj¹cy sposób:

	int time_start = clock();
	quicksort(set, 0, n - 1); //funkcja sortuj¹ca tablicê o liczbie elementów n
	int time_end = clock();

Wyniki testu mo¿na zobaczyæ w pliku out_testowe.txt.

Czasy sortowania kolejnych tablic:
Czas posortowania tablicy 1: 0.003 s
Czas posortowania tablicy 2: 0.136 s
Czas posortowania tablicy 3: 0.047 s
Czas posortowania tablicy 4: 0.002 s

Z otrzymanych wyników mo¿na wywnioskowaæ, ¿e algorytm jest najskuteczniejszy, dla zestawów liczb nieposortowanych lub czêœciowo posortowanych.

*/