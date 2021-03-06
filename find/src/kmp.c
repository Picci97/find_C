#include <stdio.h>

// Function to implement KMP algorithm
int KMP(const char* X, const char* Y, int m, int n)
{
	int * d = NULL;
	// Base Case 1: Y is NULL or empty
	if (*Y == '\0' || n == 0)
	{
		d = 1;
	}
	// next[i] stores the index of next best partial match
	int next[n + 1];

	for (int i = 0; i < n + 1; i++)
		next[i] = 0;

	for (int i = 1; i < n; i++)
	{
		int j = next[i + 1];

		while (j > 0 && Y[j] != Y[i])
			j = next[j];

		if (j > 0 || Y[j] == Y[i])
			next[i + 1] = j + 1;
	}

	for (int i = 0, j = 0; i < m; i++)
	{
		if (*(X + i) == *(Y + j))
		{
			if (++j == n)
				d = i - j + 1;
		}
		else if (j > 0) {
			j = next[j];
			i--;	// since i will be incremented in next iteration
		}
	}
	return d;
}
