#include "stdafx.h"
#include <iostream>

using namespace std;

const int REQUIRED_ARGC = 2;
const int MAX_NUMBER_SIZE = 32;
const unsigned long MAX_NUMBER_VALUE = pow(2, 32) - 1;
const int NORMAL_END = 0;

enum errorCode { argcError, limitError, numFormatError };

int ErrorMessage(int errorCode);
int CheckTheParameters(int paramQuantity);
int CheckTheNumberSize(int binNumberSize);
int CheckToBinary(char *binNumberLine, int binNumberSize);
unsigned long CalculateDecNumber(char *binNumberLine, int binNumberSize);

int main(int argc, char * argv[])
{
	int code = 0;
	//проверка количества параметров
	code = CheckTheParameters(argc);

	if (code == NORMAL_END)
	{
		int binNumberSize = strlen(argv[1]);
		//проверка на максимальное значение
		code = CheckTheNumberSize(binNumberSize);
		if (code == NORMAL_END)
		{
			char * binNumberLine = new char[binNumberSize];
			binNumberLine = argv[1];
			//проверка на 0 и 1
			code = CheckToBinary(binNumberLine, binNumberSize);

			if (code == NORMAL_END)
			{
				unsigned long decNumber = 0;
				decNumber = CalculateDecNumber(binNumberLine, binNumberSize);
				cout << decNumber << endl;
			}
		}
	}
	return code;
}

//проверка количества параметров
int CheckTheParameters(int paramQuantity)
{
	int errorCode = 0;
	if (paramQuantity != REQUIRED_ARGC)
	{
		errorCode = ErrorMessage(argcError);
	}
	return errorCode;
}

//проверка на допустимую длину числа
int CheckTheNumberSize(int binNumberSize)
{
	int errorCode = 0;
	if (binNumberSize > MAX_NUMBER_SIZE)
	{
		errorCode = ErrorMessage(limitError);
	}
	return errorCode;
}

int CheckToBinary(char *binNumberLine, int binNumberSize)
{
	int errCode = 0;
	for (int i = 0; i < binNumberSize; i++)
	{
		if ((binNumberLine[i] != '0') && (binNumberLine[i] != '1'))
		{
			errCode = ErrorMessage(numFormatError);
			break;
		}
	}
	return errCode;
}

//перевод числа из двоичного вида в десятичный
unsigned long CalculateDecNumber(char *binNumberLine, int binNumberSize)
{
	unsigned long decNum = 0;
	int exponent = binNumberSize - 1;
	int number = 0;

	for (int i = 0; i < binNumberSize; i++)
	{
		number = binNumberLine[i] - '0';
		decNum += number*pow(2, exponent);
		exponent--;
	}
	return decNum;
}

int ErrorMessage(int errorCode)
{
	switch (errorCode)
	{
		case argcError:
		{
			cout << "Not enough arguments. Usage: bin2dec.exe <binary number>." << endl;
			break;
		}
		case limitError:
		{
			cout << "The entered number length is exeeds "<< MAX_NUMBER_SIZE<<" symbols and value is greater than " << MAX_NUMBER_VALUE << endl;
			break;
		}
		case numFormatError:
		{
			cout << "Error number, the binary number consists of 0 and 1" << endl;
			break;
		}
	}
	return 1;
}