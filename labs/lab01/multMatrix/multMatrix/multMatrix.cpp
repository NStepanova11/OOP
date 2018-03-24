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

int ParametersVerification(const size_t &argc);
int CheckingFiles(const string &matrixFileName1, const string &matrixFileName2, MyMatrix &mult);
int ReadLineFromFile(const string &fileName, ifstream &matrixFile, const size_t &matrixNumber, MyMatrix &mult);
int ConvertStringToArrayElements(string *fileLine, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult);
void CreateMatrix(double arrayElement, const int &matrixNumber, size_t &row, size_t &col, MyMatrix &mult);
void MultMatrix(MyMatrix &mult);
int ErrorMessage(int errCode, string errorSource);

int main(size_t argc, char * argv[])
{
	int code = 0;
	//проверка количества параметров
	code = ParametersVerification(argc);

	if (code == NORMAL_END)
	{
		setlocale(LC_ALL, "RUS");
		string matrixFileName1, matrixFileName2;

		matrixFileName1 = argv[1];
		matrixFileName2 = argv[2];

		int maxElementWidth = 0;
		MyMatrix mult;
		code = CheckingFiles(matrixFileName1, matrixFileName2, mult);

		if (code == NORMAL_END)
			MultMatrix(mult);
	}
	return code;
}

//проверка кол-ва входных параметров
int ParametersVerification(const size_t &argc)
{
	int errCode = 0;
	if (argc < REQUIRED_ARGC)
	{
		errCode = ErrorMessage(argcError, "");
	}

	return errCode;
}

//проверка существования файлов ввода
int CheckingFiles(const string &matrixFileName1, const string &matrixFileName2, MyMatrix &mult)
{
	int errCode = 0;
	ifstream firstFile(matrixFileName1), secondFile(matrixFileName2);

	if (!firstFile.is_open())
		errCode = ErrorMessage(fileOpenError, matrixFileName1);
	else if (!secondFile.is_open())
		errCode = ErrorMessage(fileOpenError, matrixFileName2);

	if (errCode == NORMAL_END)
	{
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

	while (k < stringLength)
	{
		while ((line[k] != ' ') && (k<stringLength))
		{
			if ((!isdigit((unsigned char)line[k])) && (line[k] != '-') && (line[k] != ',') && (line[k] != '.'))
			{
				errCode = ErrorMessage(numFormatError, line);
				break;
			}
			else
			{
				if (line[k] == ',')
					line[k] = '.';
				numberSymbols += line[k];
			}
			k++;
		}

		if (errCode == NORMAL_END)
		{
			if ((line[k] == ' ') || (k == stringLength))
			{
				k++;
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
					break;
				}
				numberSymbols.clear();
			}
		}
		else break;
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

void MultMatrix(MyMatrix &mult)
{
	double multMatrix[ELEMENT_MAX_AMOUNT][ELEMENT_MAX_AMOUNT] = { 0 };
	cout << "Multmatrix:" << endl;

	for (size_t row = 0; row < ELEMENT_MAX_AMOUNT; row++)
	{
		for (size_t col = 0; col < ELEMENT_MAX_AMOUNT; col++)
		{
			for (size_t k = 0; k < ELEMENT_MAX_AMOUNT; k++)
			{
				multMatrix[row][col] += mult.matrix1[row][k] * mult.matrix2[k][col];
			}
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