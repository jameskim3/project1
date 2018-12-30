#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <algorithm> 

const int FLOOR = 10000;


extern void assign(int house[FLOOR][10000]);


int main(void)
{
	static int house[FLOOR][10000];
	static int org[FLOOR][10000];
	static int shelter[FLOOR][3];

	srand(3); // The seed will be changed. 

	for (register int f = 0; f < FLOOR; f++)
	{
		for (register int c = 0; c < 10000; c++)
			org[f][c] = house[f][c] = 1 + (rand() % 9);

		for (register int c = 0; c < 3;)
		{
			int r = rand() % 10000;
			if (house[f][r] == 0) continue;

			org[f][r] = house[f][r] = 0;
			shelter[f][c++] = r;
		}
	}

	int PERFORMANCE = 100000;
	double TOTAL = 0.0;

	time_t start = clock();
	assign(house);
	PERFORMANCE -= (clock() - start) / (CLOCKS_PER_SEC / 1000);

	for (register int f = 0; f < FLOOR; f++)
	{
		int sum[3] = { 0, 0, 0 };

		for (register int i, c = 0; c < 10000; c++)
		{
			if (org[f][c] == 0) continue;

			for (i = 0; i < 3; i++)
				if (house[f][c] == shelter[f][i])
				{
					sum[i] += org[f][c];

					if (sum[i] <= 20000) TOTAL += abs(shelter[f][i] - c);
					else TOTAL += 10000;

					break;
				}

			if (i == 3) TOTAL += 10000;
		}
	}
	printf("TOTAL = %.10lf , PERFORMANCE = %d\n", TOTAL / 10000 / FLOOR, PERFORMANCE);

	return 0;
}