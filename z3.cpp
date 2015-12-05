#include "stdafx.h"
#include "iostream"

#include <omp.h>
#include <ctime>
#include <algorithm>

using namespace std;

inline unsigned int d_hash(const char* s, unsigned int c)
{
	unsigned int x = 0;
	for (unsigned int i = 0; s[i] != 0; ++i) {
		x <<= 3;
		x ^= s[i];
	}

	return (c / x) % 41;
}

inline bool wasValueFound(unsigned int i, char** toHash)
{
	unsigned int j, k, l;
	unsigned int hashed[31];

	for (j = 0; j < 31; j++)
	{
		k = d_hash(toHash[j], i);

		for (l = 0; l < j; l++)
		{
			if(hashed[l] == k)
				return false;
		}

		hashed[l] = k;	
	}

	return true;
}

int main()
{
	char* words[31] = { "and", "as", "assert", "break", "class", "continue",
	"def", "del", "elif", "else", "except", "exec", "finally",
	"for", "from", "global", "if", "import", "in", "is",
	"lambda", "not", "or", "pass", "print", "raise", "return",
	"try", "while", "with", "yield" };
	int i = 0, threadsNum = 4;
	omp_set_num_threads(threadsNum);
	clock_t start, end;

	//d_hash test
	/*
	cout << d_hash(words[0], 0) << endl;
	*/
	//valueFoundTest
	/*
	cout << valueFound(1900000000, words) << endl;
	*/
	
	start = clock();
	
	#pragma omp parallel shared(words) private (i)
	{
		#pragma omp for
		for (i = 1900000000; i < LONG_MAX; i++)
		{
			if (wasValueFound(i, words))
			{
				end = clock();
				cout << "Value found: " << i << ", after " << end-start << " ms for " << threadsNum << " thread(s)."<< endl;
			}
		}
	}
	
	system("PAUSE");

	return EXIT_SUCCESS;
}