#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

const size_t REQUIRED_ARGC = 3;

enum errorCode { argcError, fileOpenError, emptyError };

using namespace std;

void ErrorMessage(int errorCode, string fileName);
void CopyLines(string inputFileName, string outputFileName, int &code);

int main(int argc, char *argv[])
{
	int code = 0;
	if (argc != REQUIRED_ARGC)
	{
		ErrorMessage(argcError, "");
		code = 1;
	}
	else
	{
		string inputFileName =argv[1], outputFileName = argv[2];
		CopyLines(inputFileName, outputFileName, code);
	}
	//system("pause");
	return code;
}

void CopyLines(string inputFileName, string outputFileName, int &code)
{
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName);
	bool inputFileOpened = true, outputFileOpened = true, fileHaveLines = true;

	string fileLine = "";
		
	if (!inputFile.is_open())
	{
		inputFileOpened = false;
		ErrorMessage(fileOpenError, inputFileName);
		code = 1;
	}

	if (!outputFile.is_open())
	{
		outputFileOpened = false;
		ErrorMessage(fileOpenError, outputFileName);
		code = 1;
	}

	if (inputFileOpened && outputFileOpened)
	{
		int linesCount = 0;
		while (fileHaveLines)
		{
			if (getline(inputFile, fileLine))
			{
				outputFile << fileLine << endl;
				linesCount++;
			}
			else
			{
				fileHaveLines = false;
			}
		}
		if (linesCount == 0)
		{
			ErrorMessage(emptyError, inputFileName);
			code = 1;
		}
		inputFile.close();
		outputFile.close();
	}
}

void ErrorMessage(int errorCode, string fileName)
{
	switch (errorCode)
	{
		case argcError:
		{
			cout << "Not enough arguments. Usage: copyfile.exe <file1.txt> <file2.txt>." << endl;
			break;
		}
		case fileOpenError:
		{
			cout << "File \""<< fileName <<"\" can not be open." << endl;
			break;
		}
		case emptyError:
		{
			cout << "File \"" << fileName << "\" is empty." << endl;
			break;
		}
	}
}