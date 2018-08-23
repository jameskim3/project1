#include <iostream>

const int mat[] = { 16, 32, 64, 128, 256, };
char origin_map[256][256];
char devide_map[128][128];
int N;

extern void send_map(int n, char img[128][128]);

void make_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			origin_map[i][j] = rand() % 2;
		}
	}

	int chk = 0; 
	int offsetX, offsetY;
	while (chk != 31)
	{
		int t = rand() % 5;
		if (chk & (0x01 << t) > 0)continue;
		chk+= 0x01<<t;
		if (t < 4)
		{
			offsetY = (t / 2)*(N/2);
			offsetX = (t % 2)*(N/2);
		}
		else
		{
			offsetY = rand() % ((N / 2) - 4) + 2; 
			offsetX = rand() % ((N / 2) - 4) + 2;
		}

		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				devide_map[i][j] = origin_map[i + offsetY][j + offsetX];
			}
		}
		send_map(N / 2, devide_map);
	}


}

int main()
{
	for (int tc = 0; tc < 10; tc++)
	{
		N = mat[rand() % 5];
		make_map();
	}
	return 0;
}