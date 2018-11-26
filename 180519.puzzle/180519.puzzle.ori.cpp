#include <iostream>
#include <string>
#include <time.h>
void test(unsigned char newmap[4096][4096]);
static int seed = 3;
static unsigned char dummy1[256];
static unsigned char orgmap[4096][4096];
static unsigned char dummy2[256];
static unsigned char newmap[4096][4096];
static unsigned char dummy3[256];
static unsigned char xoverlab[4096][4096];
static unsigned char yoverlab[4096][4096];

bool check_map(unsigned char map[4096][4096])
{
	if (memcmp(orgmap, map, 4096 * 4096) == 0)
		return true;
	return false;
}
static bool line_check(int x1, int y1, int x2, int y2)
{
	if (x2 - x1<16)return false;
	if (y2 - y1<16)return false;
	if (memcmp(&xoverlab[y1][x1], dummy3, x2 - x1 + 1) != 0)return false;
	if (memcmp(&xoverlab[y2][x1], dummy3, x2 - x1 + 1) != 0)return false;
	if (memcmp(&yoverlab[x1][y1], dummy3, y2 - y1 + 1) != 0)return false;
	if (memcmp(&yoverlab[x2][y1], dummy3, y2 - y1 + 1) != 0)return false;
	return true;
}
static void draw_line(int x1, int y1, int x2, int y2)
{
	memset(&xoverlab[y1][x1], 1, x2 - x1 + 1);
	memset(&xoverlab[y2][x1], 1, x2 - x1 + 1);
	memset(&yoverlab[x1][y1], 1, y2 - y1 + 1);
	memset(&yoverlab[x2][y1], 1, y2 - y1 + 1);
}
static int pseudo_rand()
{
	seed = (214013 * seed + 2531011);
	return (seed >> 16) & 32767;
}
static void draw_rect()
{
	int x1, y1, x2, y2, t;
	while (true)
	{
		x1 = 16 + (pseudo_rand() % 4064);
		y1 = 16 + (pseudo_rand() % 4064);
		x2 = 16 + (pseudo_rand() % 4064);
		y2 = 16 + (pseudo_rand() % 4064);
		if (x1>x2)
		{
			t = x1; x1 = x2; x2 = t;
		}
		if (y1>y2)
		{
			t = y1; y1 = y2; y2 = t;
		}
		if (line_check(x1, y1, x2, y2))
		{
			draw_line(x1, y1, x2, y2);
			break;
		}
	}
	int c = 1 + pseudo_rand() % 255;
	for (int x = x1; x <= x2; x++)
		orgmap[y1][x] = c;
	for (int x = x1; x<x2; x++)
		orgmap[y2][x] = c;
	for (int y = y1; y <= y2; y++)
		orgmap[y][x1] = c;
	for (int y = y1; y <= y2; y++)
		orgmap[y][x2] = c;
}

static void build_map(void)
{
	memset(orgmap, 0, 4096 * 4096);
	memset(xoverlab, 0, 4096 * 4096);
	memset(yoverlab, 0, 4096 * 4096);

	for (int c = 0; c<1024; c++) draw_rect();

	memcpy(newmap, orgmap, 4096 * 4096);

	for (int c = 0; c<256; c++)
	{
		int x1 = pseudo_rand() % 16;
		int y1 = pseudo_rand() % 16;
		int x2 = pseudo_rand() % 16;
		int y2 = pseudo_rand() % 16;
		for (int cy = 0; cy<256; cy++)
		{
			memcpy(dummy1, &newmap[y1 * 256 + cy][x1 * 256], 256);
			memcpy(&newmap[y1 * 256 + cy][x1 * 256], &newmap[y2 * 256 + cy][x2 * 256], 256);
			memcpy(&newmap[y2 * 256 + cy][x2 * 256], dummy1, 256);
		}
	}
}
int main()
{
	setbuf(stdout, NULL);
	int result = 1000000;
	memset(dummy3, 0,4096);
	for (register int T = 0; T<10; T++)
	{
		build_map();
		time_t start = clock();
		test(newmap);
		result += (int)((clock() - start) / (CLOCKS_PER_SEC / 1000));
		if (check_map(newmap))result -= 100000;
		printf("%2d:%6d", T + 1, result);
	}
	return 0;
}