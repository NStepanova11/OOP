#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int REQUIRED_ARGC = 2;
const int MAX_NUMBER_SIZE = 32;
const unsigned long MAX_NUMBER_VALUE = pow(2, 32) - 1;
const int NORMAL_END = 0;

enum errorCode { argcError, limitError, numFormatError };

int ErrorMessage(int errorCode);
int ParametersVerification(int paramQuantity);
int NumberSizeVerification(int binNumberSize);
int StringToIntConverting(int binNumberSize, string binNumberString, vector <int> &binNumber);
unsigned long CalculateDecNumber(vector <int> binNumber);

int main(int argc, char * argv[])
{
	int code = 0;
	//проверка количества параметров
	code = ParametersVerification(argc);

	if (code == NORMAL_END)
	{
		string binNumberString = argv[1];

		int binNumberSize = binNumberString.size();
		//проверка на допустимую длину числа
		code = NumberSizeVerification(binNumberSize);

		if (code == NORMAL_END)
		{
			vector <int> binNumber;
			//преобразование символов строки в int и проверка на 0 и 1
			code = StringToIntConverting(binNumberSize, binNumberString, binNumber);

			if (code == NORMAL_END)
			{
				unsigned long decNumber = 0;
				//перевод числа из двоичного вида в десятичный
				decNumber = CalculateDecNumber(binNumber);
				cout << decNumber << endl;
			}
		}
	}
	system("pause");
	return code;
}

//проверка количества параметров
int ParametersVerification(int paramQuantity)
{
	int errorCode = 0;
	if (paramQuantity != REQUIRED_ARGC)
	{
		errorCode = ErrorMessage(argcError);
	}
	return errorCode;
}

//проверка на допустимую длину числа
int NumberSizeVerification(int binNumberSize)
{
	int errorCode = 0;
	if (binNumberSize > MAX_NUMBER_SIZE)
	{
		errorCode = ErrorMessage(limitError);
	}
	return errorCode;
}

//преобразование символов строки в int и проверка на 0 и 1
int StringToIntConverting(int binNumberSize, string binNumberString, vector <int> &binNumber)
{
	int errorCode = 0;
	string binDigit;

	for (int i = 0; i < binNumberSize; i++)
	{
		binDigit = binNumberString[i];
		if ((binDigit == "1") || (binDigit == "0"))
		{
			binNumber.push_back(stoi(binDigit));
		}
		else
		{
			errorCode = ErrorMessage(numFormatError);
			break;
		}
	}
	return errorCode;
}

//перевод числа из двоичного вида в десятичный
unsigned long CalculateDecNumber(vector <int> binNumber)
{
	unsigned long decNum = 0;
	int exponent = binNumber.size() - 1;

	for (int i = 0; i < binNumber.size(); i++)
	{
		decNum += binNumber[i] * pow(2, exponent);
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
			cout << "The entered value is greater than " << MAX_NUMBER_VALUE << endl;
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