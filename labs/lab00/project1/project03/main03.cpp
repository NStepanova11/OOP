#include "stdafx.h"
#include <iostream>

using namespace std;
void CalculateFibbonaci(int a, int b, long n, int count);


int main(int argc, char *argv[])
{
	if (argc < 2)
		cout << "Not enough arguments" << endl;
	else
	{
		long n = atoi(argv[1]);
		if (n > 0)
		{
			int a = 0, b = 1, c = 0, count = 0;
			cout << a << ", " << b << ", ";
			count = 2;
			CalculateFibbonaci(a, b, n, count);
		}
		else
			cout << "Incorrect N" << endl;
	}
	system("pause");
    return 0;
}

void CalculateFibbonaci(int a, int b, long n, int count)
{
	long c = a + b;

	if (c <= n)
	{
		count++;
		cout << (c) << ", ";
		if (count == 5)
		{
			cout << endl;
			count = 0;
		}
		CalculateFibbonaci(b, c, n, count);
	}
}
