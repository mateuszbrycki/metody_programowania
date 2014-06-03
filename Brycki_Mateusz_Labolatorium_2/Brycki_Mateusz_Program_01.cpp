/*Zadanie 1 labolatoria 2
w kolejnych wierszach pliku wej�ciowego znajduj� si�:
	m
	m liczb oddzielonych spacj� (set_i)
	n
	n liczb oddzielonych spacj� (set_ii)

Program zwraca ilo�� powt�rzonych w obu zestawach liczb (set_i, set_ii) oraz wypisuje je do pliku w kolejnosci wyst�pienia 
w zestawie 1 (set_i).
W przypadku gdy liczba powtarza sie wi�cej ni� raz, kolejne powt�rzenia nie s� bran� pod uwag�.

IN:
5
1 3 2 1 2
7
2 4 3 3 2 1 1

OUT:
3
1
3
2
*/

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/**
funkcja sprawdzaj�ca czy dany element jest ju� w tablicy, je�eli jest zwraca true

@param tab tablica z powt�rzonymi liczbami
@param n liczba, kt�rej obecno�� b�dziemy sprawdza�
@param size rozmiar tablicy tab
*/
bool check_repeats(unsigned long int tab[], unsigned long int *n, int &size) 
{
	unsigned long int *x = &tab[0]; //wska�nik do pierwszego elementu przes�anej tablicy
	bool result = false; //zmienna przechowywuj�ca wynik dzia�ania funkcji

	for (int z = 0; z < size; z++) //p�tla przeskakuj�ca po ca�ej tablicy
	{
		if (*x == *n) //sprawdzenie czy element na kt�ry pokazuje wska�nik jest taki sam jak ten, kt�ry chcemy sprawdzi�
		{
			result = true; //je�eli element jest w tablicy zwracamy true
			break; //zako�czenie p�tli, jest przynajmniej jeden taki element
		}
		x++; //przesuwamy wskaznik na nast�pny element tablicy
	}

	return result;
}

/**
g��wa funkcja sprawdzaj�ca powt�rzenia w set_i, set_ii

@param set_i tablica z pierwszym zestawem
@param m liczba element�w w set_i
@param set_ii tablica z drugim zestawem
@param n liczba element�w w set_ii
@param repeats_number ilo�� powt�rzonych liczb
@param repeats tablica przechowywuj�ca powt�rzone liczby
*/
void get_repeats(unsigned long int set_i[], int &m, unsigned long int set_ii[], int &n, int &repeats_number, unsigned long int repeats[])
{
	for (int x = 0; x < m; x++) //p�tla przeskakuj�ca po elementach set_i
	{
		for (int y = 0; y < n; y++) //p�tla przeskakuj�ca po elementach set_ii
		{
			if ((set_i[x] == set_ii[y]) && !check_repeats(repeats, &set_i[x], repeats_number)) //elementy tablicy s� takie same i nie wyst�puj� ju� w tablicy powt�rzonych
			{
					repeats[repeats_number] = set_i[x]; //je�eli nie, to dodajemy j� do tablicy
					repeats_number++; //zwi�kszamy ilo�� powt�rze�
			}
		}
	}
}

int main()
{
	fstream file, out; //uchwyt pliku
	string name; //nazwa pliku, ktory chcemy otworzyc
	int m, n, repeats_number = 0; //zmienne do ilosci liczb w zestawach

	//pobranie od u�ytkownika nazwy pliku
	cout << "Podaj nazwe pliku (.txt) : ";
	cin >> name;

	file.open(name); //otworzenie pliku z danymi
	out.open("out.txt", ios_base::out); //plik na wyniki zostanie otworzony lub utworzony

	//sprawdzenie czy plik z danymi zosta� otworzony, je�eli nie to do pliku z wynikami zostaje zapisana wiadomo�� o b��dzie
	if (!file.is_open())
	{
		out << "Nie znalaz�em " << name << "\n";
	}

	//pobranie ilosci liczb pierwszego zestawu
	file>> m;
	if ((m < 1) || (m> 140000))
		return 0;
	
	unsigned long int *set_i = new unsigned long int[m]; //dynamiczna tablica dla pierwszego zestawu

	//pobranie kolejnych m liczb z pierwszego zestawu do tablicy
	for (int z = 0; z < m; z++)
	{
		file >> set_i[z];
		if ((set_i[z] < 1) || (set_i[z] >3000000000))
			return 0;
	}

	//pobranie ilosci liczb drugiego zestawu
	file >> n;
	if ((n < 1) || (n> 140000))
		return 0;

	unsigned long int *set_ii = new unsigned long int[n]; //dynamiczna tablica dla drugiego zestawu

	//pobranie kolejnych n liczb z drugiego zestawu do tablicy
	for (int z = 0; z < n; z++)
	{
		file >> set_ii[z];
		if ((set_ii[z] < 1) || (set_ii[z] >3000000000))
			return 0;
	}

	unsigned long int *repeats = new unsigned long int[(m < n) ? m : n]; //dynamiczna tablica na powtarzajace si� elementy, 
											 //mo�e ich by� maksymalnie tyle, co liczb w najmniejszym zestawie

	//funkcja szukaj�ca powt�rze� w zestawach
	get_repeats(set_i, m, set_ii, n, repeats_number, repeats);

	//zapisanie odpowiedzi do pliku out.txt
	if (repeats_number != 0)
	{
		//zapisanie do pliku ilo�ci powt�rzonych liczb
		out << repeats_number << endl;

		//wypisanie powt�rzonych liczb
		for (int x = 0; x < repeats_number; x++)
			out << repeats[x]<<endl;
	}
	else {
		//zapisanie ilo�ci powt�rze�
		out << "0";
	}
	
	delete[] set_i, set_ii; //zwolnienie pami�ci jak� zajmowa�y tablice zestaw_i zestaw_ii
	
	//zamkni�cie plik�w
	file.close();
	out.close();

	return 0;
}