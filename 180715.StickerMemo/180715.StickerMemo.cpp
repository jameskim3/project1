#include<iostream>

extern void init(int sizeY, int sizeX);
extern void makeMemo(int id, int y, int x, int height, int width, const char* data);
extern void chooseMemo(int id);
extern void moveMemo(int id, int y, int x);
extern void getContext(int y, int x, char* retString);

int SIZE_X, SIZE_Y;
void getMakeInfo(int *y, int *x, int *height,int *width,char *data)
{
	while (1)
	{
		*y = rand() % SIZE_Y;
		*x = rand() % SIZE_X;
		*height = rand() % SIZE_Y +1;
		*width = rand() % SIZE_X +1;
		if (*height + *y > SIZE_X || *width + *x > SIZE_X) continue;
		int j = 0;
		while (j < *height * *width) data[j++] = rand() % 26 + 'A';
		data[j] = '\0';
		break;
	}
}

int main()
{
	int i, j, k;
	int y, x, width, height;
	char data[2510];

	for (int tc = 0; tc < 10; tc++)
	{
		int idx = 0;
		SIZE_X = rand() % 40 + 11;
		SIZE_Y = rand() % 40 + 11;

		init(SIZE_Y, SIZE_X);

		int max_make = 10000 + rand() % 40000;
		while (idx < max_make)
		{
			getMakeInfo(&y, &x, &height, &width, data);
			makeMemo(idx++, y, x, height, width, data);
		}

		int ret = 0;
		char retString[25];
		for (i = 0; i < 100; i++)
		{
			int opt = rand() % 4;
			switch (opt)
			{
			case 0://select
				break;
				j = rand() % idx;
				chooseMemo(j);
				break;
			case 1://move
				break;
				j = rand() % idx;
				y = rand() % SIZE_Y;
				x = rand() % SIZE_X;
				moveMemo(j, y, x);
				break;
			case 2://make
				if (idx >= 50000)break;
				getMakeInfo(&y, &x, &height, &width, data);
				makeMemo(idx++, y, x, height, width, data);
				break;
			case 3://getContext
				y = rand() % (SIZE_Y-4);
				x = rand() % (SIZE_X-4);
				getContext(y, x, retString);
				for (j = 0; j < 25; j++) ret += retString[j];
				ret %= 100000;
			}
		}
		printf("#%d: %d\n", tc, ret);
	}
	return 0;
}