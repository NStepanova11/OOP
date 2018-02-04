#include "stdafx.h"
#include <string>
const int I_MIN = 1, I_MAX = 1000;

using namespace std;

int SumDigits(int i);

int main(int argc, char *argv[])
{
	if (argc < 2)
		printf("Not enough arguments");
	else
	{
		char *max = argv[1];
		int maxLimit = atoi(max);

		if (maxLimit > 0)
		{
			for (int i = I_MIN; i <= maxLimit; i++)
			{
				int sum = SumDigits(i);
				if (i%sum == 0)
				{
					printf("%d", i);
					if (i != maxLimit)
						printf(",");
				}
			}
		}
	}
    return 0;
}

int SumDigits(int i)
{
	int sum = 0;

	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}
