#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

const size_t REQUIRED_ARGC = 3;

enum errorCode { argcError, fileOpenError };

using namespace std;

void ErrorMessage(int errorCode, string fileName);
int CopyLines(string inputFileName, string outputFileName);

int main(int argc, char *argv[])
{
	if (argc != REQUIRED_ARGC)
	{
		ErrorMessage(argcError, "");
	}
	else
	{
		string inputFileName = argv[1], outputFileName = argv[2];
		CopyLines(inputFileName, outputFileName);
	}
	return 0;
}

int CopyLines(string inputFileName, string outputFileName)
{
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName, ios::out);
	
	string fileLine = "";
	if (inputFile.is_open() && outputFile.is_open())
	{
		while (getline(inputFile, fileLine))
		{
			outputFile << fileLine << endl;
		}
		inputFile.close();
		outputFile.close();
	}
	else
	{
		ErrorMessage(fileOpenError, outputFileName);
	}

	return 0;
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
			cout << "File "<<fileName<<" can not be open." << endl;
			break;
		}
	}
}