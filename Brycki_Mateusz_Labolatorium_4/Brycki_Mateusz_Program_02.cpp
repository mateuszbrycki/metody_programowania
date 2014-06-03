/*
Autor: Mateusz Brycki, informatyka, 1 rok, WIEiK, 11i

Algorytm sortowania quicksort oparty na technice "dziel i zwyci�aj".
*/
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

fstream plik_in, plik_out;  //uchwyty do plik�w z danymi oraz na wyniki


//funkcja odpowiedzialna za przestawianie element�w tablicy w miejscu
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
//@param A - tablica, kt�ra ma zosta� posortowana
//@param p - pocz�tek sortowanej cz�ci tablicy
//@param r - koniec sortowanej cz�ci tablicy
void quicksort(long int *A, int p, int r)
{
	if (p < r)
	{
		int q = partition(A, p, r);

		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);
	}
}

//funkcja wypisuj�ca tablic� do pliku
//@param set - adres pierwszego elementu zapisywanej tablicy
//@param n - ilo�� element�w tablicy
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
	int z, n; //z - ilo�� zestaw�w
			  //n - ilo�� liczb w zestawie

	string nazwa;
	cout << "Podaj nazwe pliku z danymi (.txt): ";
	cin >> nazwa;

	plik_in.open(nazwa); //otworzenie pliku z danymi
	plik_out.open("out.txt", ios_base::out); //otworzenie lub utworzenie pliku na wyniki

	plik_in >> z; //pobranie ilo�ci zestaw�w

	//p�tla wczytuj�ca kolejne dane z pliku
	do
	{
		
		plik_in >> n; //pobranie rozmiaru zestawu

		if ((n < 1) || (n > 500000))
		{
			plik_out << "B��dne dane!";
			return 0;
		}

		long int * set = new long int[n]; //dynamiczna tablica na elementy zestawu o rozmiarze n

		//p�tla wczytuj�ca n kolejnych liczb tworz�cych zestaw
		for (int x = 0; x < n; x++)
		{
			plik_in >> set[x];
		}


		quicksort(set, 0, n - 1); //funkcja sortuj�ca tablic� o liczbie element�w n

		wypisz(set, &n); //funkcja odpowiedzialna za wypisanie do pliku posortowanej tablicy

		z--;

		delete [] set; //zwolnienie pami�ci po wypisaniu posortowanej tablicy do pliku
	} while (z > 0);

	 //zamkni�cie uchwyt�w plik�w
	plik_in.close();
	plik_out.close();

	cin.get();
	cin.get();

}

/*
Algorytm Quicksort zosta� przetestowany dla danych z pliku testowe_in.txt. Wyniki dzia�ania programu zosta�y zapisane w pliku testowe_out.txt.

Pierwszy zestaw to 5500 liczb z przedzia�u 0 - 1000 zapisane losowo.
Drugi to 1500 liczb z przedzia�u 0-1000 posortowane rosn�co.
Trzeci to 1500 liczb z przedzia�u 0-1000 posortowane malej�co.
Czwarty to 1500 liczb z przedzai�u 0-1500, taki �e pierwsze 1350 liczb jest posortowane rosn�co, a ostatnie 150 to liczby ustawione losowo.

Wszystkie 4 zestawy zosta�y utworzone za pomoc� funkcji generuj() znajduj�cej si� w pliku nag��wkowym generate.h.
Dodatkowo:
- drugi zestaw zosta� posortowany za pomoc� quicksort
- trzeci r�wnie�, ale zapis odby� sie w odwrotnej kolejno�ci tj. od ko�ca tablicy
- czwarty zosta� posortowany za pomoc� quicksort od elementu 0 do 1349, dalsza cz�� tablicy pozosta�a bez zmian.

Czas sortowania tablic by� mierzony w nast�puj�cy spos�b:

	int time_start = clock();
	quicksort(set, 0, n - 1); //funkcja sortuj�ca tablic� o liczbie element�w n
	int time_end = clock();

Wyniki testu mo�na zobaczy� w pliku out_testowe.txt.

Czasy sortowania kolejnych tablic:
Czas posortowania tablicy 1: 0.003 s
Czas posortowania tablicy 2: 0.136 s
Czas posortowania tablicy 3: 0.047 s
Czas posortowania tablicy 4: 0.002 s

Z otrzymanych wynik�w mo�na wywnioskowa�, �e algorytm jest najskuteczniejszy, dla zestaw�w liczb nieposortowanych lub cz�ciowo posortowanych.

*/