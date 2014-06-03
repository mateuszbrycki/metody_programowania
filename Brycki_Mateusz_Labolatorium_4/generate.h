int *generuj(int n, int a)
{
	

	int *A = new int[n];
	int r = 0;
	for (int x = 0; x < n; x++)
	{
		r= rand() % (a+1);

		A[x] = r;
	}

	return A;
}