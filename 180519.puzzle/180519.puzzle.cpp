#include <iostream>
#include <memory>
#include <time.h>

unsigned char orgmap[4096][4096];
unsigned char newmap[4096][4096];
unsigned char overlabX[4096][4096];
unsigned char overlabY[4096][4096];
unsigned char dummy1[4096];
unsigned char dummy2[256][256];
//unsigned char org[4096][4096];
//unsigned char org[4096][4096];
//unsigned char org[4096][4096];

void test(unsigned char newmap[4096][4096]);

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

int ismatch()
{
	if (memcmp(orgmap, newmap, 4096 * 4096) == 0)
		return 1;
	else
		return 0;
}
int check_line(int x1, int x2, int y1, int y2)
{
	if (memcmp(dummy1, overlabX[y1], 4096) != 0)
		return 0;
	else if (memcmp(dummy1, overlabX[y2], 4096) != 0)
		return 0;
	else if (memcmp(dummy1, overlabY[x1], 4096) != 0)
		return 0;
	else if (memcmp(dummy1, overlabY[x2], 4096) != 0)
		return 0;

	return 1;
}
void build_map()
{
	int x1, y1, x2, y2;
	for (int no = 0; no < 128; no++)
	{
		while (1)
		{
			x1 = rand() % 4064 + 16;
			x2 = rand() % 4064 + 16;
			y1 = rand() % 4064 + 16;
			y2 = rand() % 4064 + 16;
			if (x2 < x1) swap(x1, x2);
			if (y2 < y1) swap(y1, y2);

			if (check_line(x1, x2, y1, y2) == 1)
				break;
		}

		memset(&overlabX[y1][x1], 1, x2 - x1 + 1);
		memset(&overlabX[y2][x1], 1, x2 - x1 + 1);
		memset(&overlabY[x1][y1], 1, y2 - y1 + 1);
		memset(&overlabY[x2][y1], 1, y2 - y1 + 1);

		unsigned char val = rand() % 254 + 1;
		memset(&orgmap[y1][x1], val, x2 - x1 + 1);
		memset(&orgmap[y2][x1], val, x2 - x1 + 1);
		for (int i = y1; i <= y2; i++)
		{
			orgmap[i][x1] = val;
			orgmap[i][x2] = val;
		}
	}
}

void puzzle_map()
{
	for (int i = 0; i < 256; i++)
	{
		int y1 = rand() % 16;
		int x1 = rand() % 16;
		int y2 = rand() % 16;
		int x2 = rand() % 16;
		for (int j = 0; j < 256; j++)
		{
			memcpy(&dummy2, &newmap[y1 * 256 + j][x1], 256);
			memcpy(&newmap[y1 * 256 + j][x1], &newmap[y2 * 256 + j][x2], 256);
			memcpy(&newmap[y2 * 256 + j][x2], &dummy2, 256);
		}
	}
}

int main()
{
	memset(dummy1, 0, 4096);
	for (int i = 0; i < 10; i++)
	{
		memset(orgmap, 0, 4096 * 4096);
		build_map();
		memcpy(newmap, orgmap, 4096 * 4096);
		//puzzle_map();

		test(newmap);
	}
	return 0;
}