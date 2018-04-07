#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const size_t REQUIRED_ARGC = 3;
const size_t ELEMENT_MAX_AMOUNT = 3;
const size_t DECIMAL_PART_SIZE = 3;
const size_t ELEMENT_WIDTH = 15;
const int NORMAL_END = 0;
const double MAX_ELEMENT_MEAN = 5000000000.0;
const double MIN_ELEMENT_MEAN = -5000000000.0;

enum errCode { argcError, fileOpenError, emptyError, limitError, numFormatError, rowCountError, colCountError };

struct MyMatrix
{
	double matrix1[ELEMENT_MAX_AMOUNT][ELEMENT_MAX_AMOUNT] = { 0 };
	double matrix2[ELEMENT_MAX_AMOUNT][ELEMENT_MAX_AMOUNT] = { 0 };
};

int CheckTheParameters(const size_t &argc);
int CheckTheFiles(ifstream &firstFile, ifstream &secondFile, string  matrixFileName1, string matrixFileName2);
int ReadTheMatrixes(ifstream &firstFile, ifstream &secondFile, string  matrixFileName1, string matrixFileName2, MyMatrix &mult);
int ReadLineFromFile(const string &fileName, ifstream &matrixFile, const size_t &matrixNumber, MyMatrix &mult);
int ConvertStringToArrayElements(string *fileLine, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult);
int ParseLine(char &digitSymbol, string line, string &numberSymbols);
int GetMatrixElement(double &arrayElement, string numberSymbols, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult);
void CreateMatrix(double arrayElement, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult);
void MultiplyTheMatrixes(MyMatrix &mult, double multMatrix[3][3]);
int ErrorMessage(int errCode, string errorSource);
void PrintMultiplyMatrix(double multMatrix[3][3]);


int main(size_t argc, char * argv[])
{
	int code = 0;
	//проверка количества параметров
	code = CheckTheParameters(argc);

	if (code == NORMAL_END)
	{
		setlocale(LC_ALL, "RUS");
		string matrixFileName1, matrixFileName2;

		matrixFileName1 = argv[1];
		matrixFileName2 = argv[2];

		int maxElementWidth = 0;
		ifstream firstFile(matrixFileName1), secondFile(matrixFileName2);
		code = CheckTheFiles(firstFile, secondFile, matrixFileName1, matrixFileName2);

		if (code == NORMAL_END)
		{
			MyMatrix mult;
			code = ReadTheMatrixes(firstFile, secondFile, matrixFileName1, matrixFileName2, mult);
			if (code == NORMAL_END)
			{
				double multMatrix[ELEMENT_MAX_AMOUNT][ELEMENT_MAX_AMOUNT] = { 0 };
				MultiplyTheMatrixes(mult, multMatrix);
				PrintMultiplyMatrix(multMatrix);
			}
		}
	}
	return code;
}

//проверка кол-ва входных параметров
int CheckTheParameters(const size_t &argc)
{
	int errCode = 0;
	if (argc < REQUIRED_ARGC)
	{
		errCode = ErrorMessage(argcError, "");
	}

	return errCode;
}

//проверка существования файлов ввода
int CheckTheFiles(ifstream &firstFile, ifstream &secondFile, string  matrixFileName1, string matrixFileName2)
{
	int errCode = 0;

	if (!firstFile.is_open())
		errCode = ErrorMessage(fileOpenError, matrixFileName1);
	else if (!secondFile.is_open())
		errCode = ErrorMessage(fileOpenError, matrixFileName2);

	return errCode;
}

int ReadTheMatrixes(ifstream &firstFile, ifstream &secondFile, string  matrixFileName1, string matrixFileName2, MyMatrix &mult)
{
	int errCode = 0;
	//если файлы существуют
	for (size_t matrixNumber = 1; matrixNumber <= 2; matrixNumber++)
	{
		if (matrixNumber == 1)
			errCode = ReadLineFromFile(matrixFileName1, firstFile, matrixNumber, mult);
		else
			errCode = ReadLineFromFile(matrixFileName2, secondFile, matrixNumber, mult);
		if (errCode != NORMAL_END)
			break;
	}
	return errCode;
}

//чтение строк из входящих файлов
int ReadLineFromFile(const string &fileName, ifstream &matrixFile, const size_t &matrixNumber, MyMatrix &mult)
{
	int errCode = 0;
	string fileLine;
	size_t row = 0, col;
	bool lineInFile = false;
	int linesCount = 0;

	while (getline(matrixFile, fileLine))
	{
		col = 0;
		lineInFile = true;
		//преобразование строки в элементы строки матрицы
		errCode = ConvertStringToArrayElements(&fileLine, matrixNumber, row, col, mult);
		if (errCode == NORMAL_END)
		{
			if (col < ELEMENT_MAX_AMOUNT)
			{
				errCode = ErrorMessage(colCountError, fileName);
				break;
			}
			else
				row++;
		}
		else
			break;
	}
	if (errCode == NORMAL_END)
	{
		if (lineInFile == false)
			errCode = ErrorMessage(emptyError, fileName);
		else if (row < ELEMENT_MAX_AMOUNT)
			errCode = ErrorMessage(rowCountError, fileName);
	}
	return errCode;
}

int ConvertStringToArrayElements(string *fileLine, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult)
{
	int errCode = 0;
	string line = *fileLine;
	size_t stringLength = line.size();
	string numberSymbols;
	double arrayElement = 0.0;
	size_t k = 0;

	while ((k < stringLength) && (errCode==NORMAL_END))
	{
		while ((line[k] != ' ') && (k<stringLength))
		{
			errCode = ParseLine(line[k], line, numberSymbols);
			if (errCode==NORMAL_END)
				k++;
			else 
				break;
		}

		if (errCode == NORMAL_END)
		{
			if ((line[k] == ' ') || (k == stringLength))
			{
				k++;
				errCode = GetMatrixElement(arrayElement, numberSymbols, matrixNumber, row, col, mult);
				numberSymbols.clear();
			}
		}
		else break;
	}
	return errCode;
}


int ParseLine(char &digitSymbol, string line, string &numberSymbols)
{
	int errCode = 0;

	if ((!isdigit((unsigned char) digitSymbol)) && (digitSymbol != '-') && (digitSymbol != ',') && (digitSymbol != '.'))
	{
		errCode = ErrorMessage(numFormatError, line);
	}
	else
	{
		if (digitSymbol == ',')
			digitSymbol = '.';
		numberSymbols += digitSymbol;
	}

	return errCode;
}

int GetMatrixElement(double &arrayElement, string numberSymbols, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult)
{
	int errCode = 0;
	stringstream numbersStream(numberSymbols);
	numbersStream >> arrayElement;
	if ((arrayElement <= MAX_ELEMENT_MEAN) && (arrayElement > MIN_ELEMENT_MEAN))
	{
		//добавление преобразованного элемента в матрицу
		CreateMatrix(arrayElement, matrixNumber, row, col, mult);
	}
	else
	{
		errCode = ErrorMessage(limitError, numberSymbols);
	}
	return errCode;
}

//добавление преобразованного элемента в матрицу
void CreateMatrix(double arrayElement, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult)
{
	if (matrixNumber == 1)
	{
		mult.matrix1[row][col] = arrayElement;
	}
	else if (matrixNumber == 2)
	{
		mult.matrix2[row][col] = arrayElement;
	}
	if (col < ELEMENT_MAX_AMOUNT)
		col++;
}

void MultiplyTheMatrixes(MyMatrix &mult, double multMatrix[3][3])
{
	for (size_t row = 0; row < ELEMENT_MAX_AMOUNT; row++)
	{
		for (size_t col = 0; col < ELEMENT_MAX_AMOUNT; col++)
		{
			for (size_t k = 0; k < ELEMENT_MAX_AMOUNT; k++)
			{
				multMatrix[row][col] += mult.matrix1[row][k] * mult.matrix2[k][col];
			}
		}
	}
}

void PrintMultiplyMatrix(double multMatrix[3][3])
{
	cout << "Multmatrix:" << endl;
	for (int row = 0; row < ELEMENT_MAX_AMOUNT; row++)
	{
		for (int col = 0; col < ELEMENT_MAX_AMOUNT; col++)
		{
			cout.setf(ios::fixed);
			cout.width(ELEMENT_WIDTH);
			cout.precision(DECIMAL_PART_SIZE);
			cout << left << multMatrix[row][col];
		}
		cout << endl;
	}
}

int ErrorMessage(int errCode, string errorSource)
{
	switch (errCode)
	{
	case argcError:
	{
		cout << "Enter the command line: multmatrix.exe <matrixfile1> <matrixfile2>" << endl;
		break;
	}
	case fileOpenError:
	{
		cout << "File \"" << errorSource << "\" can not be open." << endl;
		break;
	}
	case emptyError:
	{
		cout << "File \"" << errorSource << "\" is empty." << endl;
		break;
	}
	case limitError:
	{
		cout << "Uncorrect matrix element: \"" << errorSource << "\", numbers must be in the range from " << MIN_ELEMENT_MEAN << " to " << MAX_ELEMENT_MEAN << endl;
		break;
	}
	case numFormatError:
	{
		cout << "Invalid matrix element in line \": " << errorSource <<"\""<< endl;
		break;
	}
	case rowCountError:
	{
		cout << "Uncorrect matrix in \"" << errorSource << "\", the number of rows of the matrix must be 3" << endl;
		break;
	}
	case colCountError:
	{
		cout << "Uncorrect matrix in \"" << errorSource << ",\" the number of columns of the matrix must be 3" << endl;
		break;
	}
	}
	return 1;
}