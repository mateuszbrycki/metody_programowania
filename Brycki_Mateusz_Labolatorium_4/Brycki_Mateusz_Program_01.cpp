/*
Autor: Mateusz Brycki, informatyka, 1 rok, WIEiK, 11i

Algorytm przedstawiaj¹cy zasadê dzia³ania wie¿y Hanoi.
*/

#include <iostream>

using namespace std;

void hanoi(char A, char B, char C, int n)
{
	if (n == 1)
	{
		cout << A << " do " << C<<endl;
	}
	else {
		hanoi(A, C, B, n - 1);
		cout << A << " do " << C<<endl;
		hanoi(B, A, C, n - 1);
	}
}


int main()
{

	hanoi('A', 'B', 'C', 3);
	
	cin.get();
	cin.get();
}