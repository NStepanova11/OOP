#include "stdafx.h"
#include <iterator>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void ReadVector(vector <double> &vectorOfNumbers);
void PrintVector(vector <double> vectorOfNumbers);
void ProcessVector(vector <double> &vectorOfNumbers);

int main()
{
	vector <double>vectorOfNumbers;
	ReadVector(vectorOfNumbers);
	if (!vectorOfNumbers.empty())
	{
		ProcessVector(vectorOfNumbers);
		sort(vectorOfNumbers.begin(), vectorOfNumbers.end());
		PrintVector(vectorOfNumbers);
	}
    return 0;
}

void ReadVector(vector <double> &vectorOfNumbers)
{
	string lineOfDouble;
	getline(cin, lineOfDouble);
	istringstream iss(lineOfDouble);
	copy(istream_iterator<double>(iss), istream_iterator<double>(), back_inserter(vectorOfNumbers));
}

void PrintVector(vector <double> vectorOfNumbers)
{
	copy(vectorOfNumbers.begin(), vectorOfNumbers.end(), ostream_iterator<double>(cout, " "));
}

void ProcessVector(vector <double> &vectorOfNumbers)
{
	const double MIN_NUMBER = *min_element(vectorOfNumbers.begin(), vectorOfNumbers.end());
	cout << "minimal: " << MIN_NUMBER << endl;
	for (auto &element : vectorOfNumbers)
	{
		element *= MIN_NUMBER;
	}
}