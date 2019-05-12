

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <time.h> 
//2048 64 
using namespace std;
const int BLOCK = 32;
const int X = 2048/2;
const int Y = 2048/2;
const int N = 1000;

extern void test(char bitmap[][X]);
static char bitmap[Y][X];
static char bitmap_Org[Y][X];

static void swap(int sx, int sy, int dx, int dy)
{
	for (int y = 0; y < BLOCK; y++) {
		for (int x = 0; x < BLOCK; x++) {
			int t = bitmap[sy + y][sx + x];
			bitmap[sy + y][sx + x] = bitmap[dy + y][dx + x];
			bitmap[dy + y][dx + x] = t;
		}
	}
}

static void rect(int sx, int sy, int ex, int ey)
{
	memset(&bitmap[sy][sx], 1, 1 + ex - sx);
	memset(&bitmap[ey][sx], 1, 1 + ex - sx);
	for (int y = sy + 1; y <= ey - 1; y++) {
		bitmap[y][sx] = 1;
		bitmap[y][ex] = 1;
	}
}

static void build(void)
{
	memset(bitmap, 0, sizeof(bitmap));
	for (int c = 0; c < N; c++) {
		int sx, sy, ex, ey;
		do { sx = rand() % (X - BLOCK); } while (sx % BLOCK == 0 || sx % BLOCK == BLOCK - 1);
		do { sy = rand() % (Y - BLOCK); } while (sy % BLOCK == 0 || sy % BLOCK == BLOCK - 1);
		do { ex = rand() % (X - (sx + BLOCK)) + (sx + BLOCK); } while (ex % BLOCK == 0 || ex % BLOCK == BLOCK - 1);
		do { ey = rand() % (Y - (sy + BLOCK)) + (sy + BLOCK); } while (ey % BLOCK == 0 || ey % BLOCK == BLOCK - 1);
		rect(sx, sy, ex, ey);
	}

	for (int y = 0; y < Y; y++)
		memcpy(bitmap_Org[y], bitmap[y], X);

	for (int c = 0; c < N; c++) {
	//	for (int c = 0; c < 20; c++) {
			int sx = (rand() % (X / BLOCK)) * BLOCK;
		int sy = (rand() % (Y / BLOCK)) * BLOCK;
		int dx = (rand() % (X / BLOCK)) * BLOCK;
		int dy = (rand() % (Y / BLOCK)) * BLOCK;

		if ((sx == dx) && (sy == dy)) {
			c--;
			continue;
		}
		
		swap(sx, sy, dx, dy);
	}
}

static bool isEqual()
{
	for (int y = 0; y < Y; y++) {
		if (memcmp(bitmap_Org[y], bitmap[y], X) != 0)
			return false;
	}
	return true;
}

int main(void)
{
	int tc = 1, start = clock();
	int SCORE = 0;
	srand(10);  //The seed will be changed. 

	while (clock() - start < 5000) {
		build();
		test(bitmap);
		if (isEqual()) SCORE++;

		printf("#%d %d\n", tc++, SCORE);
	}

	return 0;
}