#include "stdafx.h"
#include <iostream>
const int I_MIN = 2, I_MAX = 100, STEP = 2;

using namespace std;

int main(int argc, char* argv[])
{
	int i;
	for (i = I_MAX; i >= I_MIN; i-=STEP)
	{
		//printf("%d", i);
		cout << i;
		if (i != 2)
		{
			//printf(", ");
			cout << ", ";
		}
	}
	//printf("\n");
	cout << endl;
	return 0;
}

