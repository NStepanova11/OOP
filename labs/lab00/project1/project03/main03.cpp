#include "stdafx.h"
#include <iostream>
#include <climits>

const unsigned int secondMax = UINT_MAX;
using namespace std;
void CalculateFibbonaci(unsigned int firstNum, unsigned int secondNum, unsigned long limitFibbonaci, int numbersInLine);

int main(int argc, char *argv[])
{
	if (argc < 2)
		cout << "Not enough arguments" << endl;
	else
	{
		unsigned long long limitFibbonaci = atoll(argv[1]);

		if (limitFibbonaci > 0 && limitFibbonaci <= UINT_MAX)
		{
			unsigned int firstNum = 0, secondNum = 1, c = 0, numbersInLine = 0;
			cout << firstNum << ", " << secondNum << ", ";
			numbersInLine = 2;
			CalculateFibbonaci(firstNum, secondNum, limitFibbonaci, numbersInLine);
		}
		else
			cout << "Incorrect N" << endl;
	}
	cout << endl;
	system("pause");
    return 0;
}

void CalculateFibbonaci(unsigned int firstNum, unsigned int secondNum, unsigned long limitFibbonaci, int numbersInLine)
{
	unsigned long long c = firstNum + secondNum;

	if (c <= limitFibbonaci)
	{
		numbersInLine++;
		cout << (c)<< ", ";
		if (numbersInLine == 5)
		{
			cout << endl;
			numbersInLine = 0;
		}
		if (c + secondNum < secondMax)
			CalculateFibbonaci(secondNum, c, limitFibbonaci, numbersInLine);
	}
}
