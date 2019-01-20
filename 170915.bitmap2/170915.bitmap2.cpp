#include <iostream>
#include <time.h> 

using namespace std;
static char SRC[1000][100];
static char QRC[1000][100][100];
static char IMG[1000][200][200];
static char GRA[1000][100][100];
static char TAR[1000][100];
int TC = 1000;

extern  void encode(char TMP[100], char QRC[][100]);
extern  void decode(char TMP[][100], char TAR[100]);

int seed = 3;
static int pseudo_rand()
{
	seed = (214013 * seed + 2531011);
	return (seed >> 16) & 32767;
}

int main()
{
	for (int t = 0; t < TC; t++)
	{
		for (int i = 0; i < 100; i++)
		{
			SRC[t][i] = pseudo_rand() % 26 + 'A';
		}
	}
	for (int t = 0; t < TC; t++)
	{
		char TMP[100];
		memcpy(TMP, SRC[t], 100);
		encode(TMP, QRC[t]);
	}

	for (int t = 0; t < TC; t++)
	{
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				IMG[t][i][j] = pseudo_rand() % 2;
			}
		}
	}

	for (int t = 0; t < TC; t++)
	{
		int off_x, off_y;
		off_x = pseudo_rand() % 101;
		off_y = pseudo_rand() % 101;

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				IMG[t][i + off_y][j + off_x] = QRC[t][i][j] == 0 ? 0 : 1;
			}
		}
	}

	for (int t = 0; t < TC; t++)
	{
		for (int i = 0; i < 13000; i++)
		{
			int pos_x, pos_y;
			pos_x = pseudo_rand() % 200;
			pos_y = pseudo_rand() % 200;
			IMG[t][pos_x][pos_y] = 1;
		}
	}

	for (int t = 0; t < TC; t++)
	{
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				GRA[t][i / 2][j / 2] += IMG[t][i][j];
			}
		}
	}

	time_t start = clock();
	int FAIL = 0;
	for (int t = 0; t < TC; t++)
	{
		decode(GRA[t], TAR[t]);
	}

	for (int t = 0; t < TC; t++)
	{
		char TMP[100];
		memcpy(TMP, SRC[t], 100);
		int cal = memcmp(TMP, TAR[t], 100) != 0 ? 1 : 0;
		FAIL += cal;
	}

	printf("Performance : %d\n", FAIL * 10000 + clock() - start);
}
