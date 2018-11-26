#include <iostream>

const int W = 64;
unsigned char image[W][W];
int COUNT;
extern int recog(unsigned char image[W][W]);

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
void build()
{
	int sx, sy, ex, ey;
	while (1)
	{
		sx = rand() % W;
		ex = rand() % W;
		sy = rand() % W;
		ey = rand() % W;
		if (sx > ex) swap(&sx, &ex);
		if (sy > ey) swap(&sy, &ey);
		if (ex - sx < 9)continue;
		if (ey - sy < 9)continue;

		break;
	}
	if (ey - sy == ex - sx) COUNT++;
	for (int y = sy; y <= ey; y++)
		for (int x = sx; x <= ex; x++)
			image[y][x]++;
}

int main()
{
	int TC = 10000;
	int score = 0;
	for (int tc = 0; tc < TC; tc++)
	{
		COUNT = 0;
		for (int i = 0; i < 50;i++)
			build();

		int ret = recog(image);
		if (ret == COUNT) score++;
	}
	printf("SCORE: %d", score);
}