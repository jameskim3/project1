#include <iostream>
#include <time.h>

const int MAX_ID = 10000;
const int MIN_ID = 9000;
const int MAX_DATA = 256;
const int MIN_DATA = 192;

int origin[MAX_ID][256];
int y_cnt[MAX_ID];

extern void init(int a[][256], int y);
extern int matching(int arr[8]);

void build_data(int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < 256; j++)
			origin[i][j] = RAND_MAX;
		y_cnt[i] = 0;
	}
	for (int i = 0; i < y; i++)
	{
		int col = MIN_DATA + rand() % (MAX_DATA - MIN_DATA);
		y_cnt[i] = col;
		for (int j = 0; j < col; j++)
			origin[i][j] = rand() - RAND_MAX / 2;
	}
}

int main()
{
	int TC = 100;
	time_t start = clock();
	for (int tc = 0; tc < TC; ++tc)
	{
		int y = MIN_ID + rand() % (MAX_ID - MIN_ID);
		build_data(y);
		init(origin, y);

		int match = 100;
		int row, col, arr[8];
		int SCORE = 100;
		while (match--)
		{
			row = rand() % y;
			col = rand() % (y_cnt[row] - 7);
			for (int i = 0; i < 8; i++)
			{
				arr[i] = origin[row][col + i];
				arr[i] += rand() % 256 - 128;
			}
			if (matching(arr) != row)
				SCORE--;
			else
				int a = 123;
		}
		printf("#%d %d\n", tc + 1, SCORE);
	}
	int performance = (clock() - start) / (CLOCKS_PER_SEC / 1000);
	printf("Performance:%d", performance);
}

