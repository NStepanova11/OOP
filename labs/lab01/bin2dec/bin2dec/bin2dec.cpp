#include "stdafx.h"
#include <iostream>
#include <string>
#include <climits>
#include <vector>

using namespace std;

const size_t REQUIRED_ARGC = 2;
const size_t MAX_NUMBER = pow(2, 32) - 1;
const size_t MAX_NUMBER_SIZE = 32;

enum errorCode { argcError, limitError, numFormatError};

int ErrorMessage(int errorCode);

int main(int argc, char * argv[])
{
	int code = 0;
	vector <int> binNumber;
	
	if (argc != REQUIRED_ARGC)
	{
		code = ErrorMessage(argcError);
	}
	else
	{
		string line = argv[1];
		if (line.size() > MAX_NUMBER_SIZE)
		{
			code = ErrorMessage(limitError);
		}
		else
		{
			string num;
			cout << line << endl;
			for (int i = 0; i < line.size(); i++)
			{
				num = line[i];
				if ((num == "1") || (num == "0"))
				{
					binNumber.push_back(atoi(num.c_str()));
				}
				else
				{
					code = ErrorMessage(numFormatError);
					break;
				}
			}

			int exponent = binNumber.size() - 1;
			int decNumber = 0;

			for (int i = 0; i < binNumber.size(); i++)
			{
				decNumber += binNumber[i] * pow(2, exponent);
				exponent--;
			}
			cout << decNumber << endl;
		}
	}
	system("pause");
	return code;
}

int ErrorMessage(int errorCode)
{
	switch (errorCode)
	{
		case argcError:
		{
			cout << "Not enough arguments. Usage: bin2dec.exe <dec number>." << endl;
			break;
		}
		case limitError:
		{
			cout << "The value is greater than "<< MAX_NUMBER_SIZE<< " or less than 0." << endl;
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