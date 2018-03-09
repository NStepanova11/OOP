#include "stdafx.h"
#include <iostream>

using namespace std;
void CalculateFibbonaci(unsigned int firstNum, unsigned int secondNum, unsigned long limitFibbonaci, int numbersInLine);

int main(int argc, char *argv[])
{
	if (argc != 2)
		cout << "Not enough arguments. Enter in command line: project03.exe <limit value>" << endl;
	else
	{
		long long limitFibbonaci = atoll(argv[1]);
		cout << limitFibbonaci << endl;

		if (limitFibbonaci > 0 && limitFibbonaci <= ULONG_MAX)
		{
			unsigned long firstNum = 0, secondNum = 1, newElement = 0;
			int numbersInLine = 0;
			cout << firstNum << ", " << secondNum << ", ";
			numbersInLine = 2;
			CalculateFibbonaci(firstNum, secondNum, limitFibbonaci, numbersInLine);
		}
		else
		{
			cout << "Incorrect limit value: " << argv[1] << endl;
			cout << "Enter a value in the range from 1 to " << ULONG_MAX << endl;
		}
	}
	cout << endl;
	system("pause");
    return 0;
}

void CalculateFibbonaci(unsigned int firstNum, unsigned int secondNum, unsigned long limitFibbonaci, int numbersInLine)
{
    long long newElement = firstNum + secondNum;

	if (newElement <= limitFibbonaci)
	{
		numbersInLine++;
		cout << (newElement);
		
		if (newElement + secondNum < limitFibbonaci)
		{
			cout << ", ";
			if (numbersInLine == 5)
			{
				cout << endl;
				numbersInLine = 0;
			}
			CalculateFibbonaci(secondNum, newElement, limitFibbonaci, numbersInLine);
		}
	}
}
