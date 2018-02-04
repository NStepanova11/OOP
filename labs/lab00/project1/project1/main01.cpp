#include "stdafx.h"

const int I_MIN = 2, I_MAX = 100, STEP = 2;

int main(int argc, char* argv[])
{
	int i;
	for (i = I_MAX; i >= I_MIN; i-=STEP)
	{
		printf("%d", i);
		if (i != 2)
		{
			printf(", ");
		}
	}
	printf("\n");
	return 0;
}

