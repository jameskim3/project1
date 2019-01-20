#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <string.h>

const int LM = 3;
const int TC = 100;
const int MAX_ROTATE = 8;
int Cube[6][LM][LM];

extern void runTest(int local[6][LM][LM]);

enum PLANE
{
	F, B, U, D, L, R,
};

void initial_cute(int cube[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				cube[face][i][j] = face;
}
void copy_cube(int src[6][LM][LM], int tar[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				tar[face][i][j] = src[face][i][j];
}
int check_cube(int src[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				if (src[face][i][j] != face)
					return 0;

	return 1;
}
double rotScore;
void rotate(int face, int cw)
{
	int local[6][LM][LM];
	copy_cube(Cube, local);
	rotScore += 1.;

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[2][2][i] = local[4][3 - 1 - i][2];
				Cube[4][i][2] = local[3][0][i];
				Cube[3][0][i] = local[5][3 - 1 - i][0];
				Cube[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[4][3 - 1 - i][2] = local[2][2][i];
				Cube[3][0][i] = local[4][i][2];
				Cube[5][3 - 1 - i][0] = local[3][0][i];
				Cube[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[5][i][2] = local[3][2][3 - 1 - i];
				Cube[3][2][i] = local[4][i][0];
				Cube[4][i][0] = local[2][0][3 - 1 - i];
				Cube[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[3][2][3 - 1 - i] = local[5][i][2];
				Cube[4][i][0] = local[3][2][i];
				Cube[2][0][3 - 1 - i] = local[4][i][0];
				Cube[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][0][i] = local[5][0][i];
				Cube[5][0][i] = local[1][0][i];
				Cube[1][0][i] = local[4][0][i];
				Cube[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[5][0][i] = local[0][0][i];
				Cube[1][0][i] = local[5][0][i];
				Cube[4][0][i] = local[1][0][i];
				Cube[0][0][i] = local[4][0][i];
			}
		}
		break;
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][2][i] = local[4][2][i];
				Cube[4][2][i] = local[1][2][i];
				Cube[1][2][i] = local[5][2][i];
				Cube[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[4][2][i] = local[0][2][i];
				Cube[1][2][i] = local[4][2][i];
				Cube[5][2][i] = local[1][2][i];
				Cube[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][i][0] = local[2][i][0];
				Cube[2][i][0] = local[1][3 - 1 - i][2];
				Cube[1][i][2] = local[3][3 - 1 - i][0];
				Cube[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[2][i][0] = local[0][i][0];
				Cube[1][3 - 1 - i][2] = local[2][i][0];
				Cube[3][3 - 1 - i][0] = local[1][i][2];
				Cube[0][i][0] = local[3][i][0];
			}
		}
		break;
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				Cube[0][i][2] = local[3][i][2];
				Cube[3][i][2] = local[1][3 - 1 - i][0];
				Cube[1][i][0] = local[2][3 - 1 - i][2];
				Cube[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				Cube[3][i][2] = local[0][i][2];
				Cube[1][3 - 1 - i][0] = local[3][i][2];
				Cube[2][3 - 1 - i][2] = local[1][i][0];
				Cube[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}

int main()
{
	int total_score = 0;
	int performance = 0;
	srand(3);
	for (int tc = 0; tc < TC; tc++)
	{
		initial_cute(Cube);

		for (int i = 0; i < MAX_ROTATE; i++)
		{
			int face = rand() % 6;
			int cw = rand() % 2;
			rotate(face, cw);
		}

		rotScore = 0;
		time_t start = clock();
		runTest(Cube);
		time_t end = clock();
		performance += end - start;

		for (int face = 0; face < 6; face++)
			for (int i = 0; i < LM; i++)
				for (int j = 0; j < LM; j++)
				{
					if (Cube[face][i][j] != face)
					{
						rotScore += 1000.;
					}
				}

		total_score += rotScore;
		printf("#%d : %.3f\n", tc, rotScore);
	}

	printf("Performance = %d, Final=%d\n", performance, total_score);
//	printf("total: %d %.6f", total_score, double(performance) / 10000.0);

}


