#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <string.h>

const int LM = 3;
const int TC = 20;
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
void rotate(int cube[6][3][3], int face, int cw)
{
	int local[6][LM][LM];
	copy_cube(cube, local);
	if (cw == 0)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cube[face][i][j] = local[face][j][LM - 1 - i];
	}
	else
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cube[face][i][j] = local[face][LM - 1 - j][i];
	}

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[2][2][i] = local[4][3 - 1 - i][2];
				cube[4][i][2] = local[3][0][i];
				cube[3][0][i] = local[5][3 - 1 - i][0];
				cube[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[4][3 - 1 - i][2] = local[2][2][i];
				cube[3][0][i] = local[4][i][2];
				cube[5][3 - 1 - i][0] = local[3][0][i];
				cube[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[5][i][2] = local[3][2][3 - 1 - i];
				cube[3][2][i] = local[4][i][0];
				cube[4][i][0] = local[2][0][3 - 1 - i];
				cube[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[3][2][3 - 1 - i] = local[5][i][2];
				cube[4][i][0] = local[3][2][i];
				cube[2][0][3 - 1 - i] = local[4][i][0];
				cube[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][0][i] = local[5][0][i];
				cube[5][0][i] = local[1][0][i];
				cube[1][0][i] = local[4][0][i];
				cube[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[5][0][i] = local[0][0][i];
				cube[1][0][i] = local[5][0][i];
				cube[4][0][i] = local[1][0][i];
				cube[0][0][i] = local[4][0][i];
			}
		}
		break;
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][2][i] = local[4][2][i];
				cube[4][2][i] = local[1][2][i];
				cube[1][2][i] = local[5][2][i];
				cube[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[4][2][i] = local[0][2][i];
				cube[1][2][i] = local[4][2][i];
				cube[5][2][i] = local[1][2][i];
				cube[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][i][0] = local[2][i][0];
				cube[2][i][0] = local[1][3 - 1 - i][2];
				cube[1][i][2] = local[3][3 - 1 - i][0];
				cube[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[2][i][0] = local[0][i][0];
				cube[1][3 - 1 - i][2] = local[2][i][0];
				cube[3][3 - 1 - i][0] = local[1][i][2];
				cube[0][i][0] = local[3][i][0];
			}
		}
		break;
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][i][2] = local[3][i][2];
				cube[3][i][2] = local[1][3 - 1 - i][0];
				cube[1][i][0] = local[2][3 - 1 - i][2];
				cube[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[3][i][2] = local[0][i][2];
				cube[1][3 - 1 - i][0] = local[3][i][2];
				cube[2][3 - 1 - i][2] = local[1][i][0];
				cube[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}

struct st{
	int face, cw;
};
st history[MAX_ROTATE];

int main()
{
	int total_score = 0;
	int performance = 0;
	for (int tc = 0; tc < TC; tc++)
	{
		initial_cute(Cube);
		int local[6][LM][LM];
		copy_cube(Cube, local);

		memset(history, 0, sizeof(history));
		for (int i = 0; i < MAX_ROTATE; i++)
		{
			int face = rand() % 6;
			int cw = rand() % 2;
			history[i].face = face;
			history[i].cw = cw;
			rotate(Cube, face, cw);
		}

		time_t start = clock();
		runTest(Cube);
		time_t end = clock();
		performance += end - start;

		int score = 0;
		for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
		for (int j = 0; j < LM; j++)
		{
			if (local[face][i][j] != face)
			{
				score += 1000;
			}
		}

		total_score += score;
	}

	printf("%d %.6f", total_score, double(performance) / 10000.0);

}


